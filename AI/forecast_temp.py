import sys
import json
import warnings
from datetime import timedelta, datetime

import mysql.connector
import pandas as pd
from statsmodels.tsa.arima.model import ARIMA

warnings.filterwarnings("ignore")

DB = {
    "host": "127.0.0.1",
    "user": "root",
    "password": "",
    "database": "datacenter"
}

def clamp(x, a, b):
    return max(a, min(b, x))

# args:
    #   argv[1] = minutos exemplo: 60 / 180
    #   argv[2] = historyN opcional, default 120
def main():
    minutes = 60
    history_n = 120

    if len(sys.argv) >= 2:
        try:
            minutes = int(sys.argv[1])
        except:
            minutes = 60

    if len(sys.argv) >= 3:
        try:
            history_n = int(sys.argv[2])
        except:
            history_n = 120

    minutes = clamp(minutes, 5, 24 * 60)
    history_n = clamp(history_n, 30, 400)

    # -----------------------------
    #           Ler dados
    # -----------------------------
    conn = mysql.connector.connect(**DB)
    df = pd.read_sql("""
        SELECT data_hora, valor
        FROM sensores
        WHERE tipo='temperatura'
        ORDER BY data_hora DESC
        LIMIT 150000
    """, conn)
    conn.close()

    if df.empty:
        print(json.dumps({"ok": False, "error": "sem_dados"}, ensure_ascii=False))
        return

    df["data_hora"] = pd.to_datetime(df["data_hora"], errors="coerce")
    df["valor"] = pd.to_numeric(df["valor"], errors="coerce")
    df = df.dropna(subset=["data_hora", "valor"]).copy()

    if len(df) < 30:
        print(json.dumps({"ok": False, "error": "poucos_dados"}, ensure_ascii=False))
        return

    df = df.sort_values("data_hora").reset_index(drop=True)

    last_dt = df["data_hora"].iloc[-1]

    # ------------------------------------
    #  Frequência real mediana dos deltas
    # ------------------------------------
    diffs = df["data_hora"].diff().dt.total_seconds().dropna()
    if len(diffs) == 0:
        freq_sec = 60
    else:
        freq_sec = diffs.median()
        if pd.isna(freq_sec) or freq_sec <= 0:
            freq_sec = 60
        freq_sec = int(round(freq_sec))
        freq_sec = clamp(freq_sec, 1, 600)  # 1s..10min

    # minutos -> steps
    steps = int(round((minutes * 60) / freq_sec))
    steps = clamp(steps, 5, 2000)

    # -----------------------------
    #    Histórico para desenhar
    # -----------------------------
    hist_df = df.tail(history_n)
    history_labels = [x.strftime("%Y-%m-%d %H:%M:%S") for x in hist_df["data_hora"].tolist()]
    history_data = [round(float(x), 2) for x in hist_df["valor"].tolist()]

    # -----------------------------
    #           ARIMA(2,0,2)
    # -----------------------------
    series = df["valor"].astype(float)

    model = ARIMA(series, order=(2, 0, 2))
    fit = model.fit()

    # forecast + intervalos (95%)
    pred = fit.get_forecast(steps=steps)
    mean = pred.predicted_mean

    conf = pred.conf_int(alpha=0.05)  # 95%
    lower = conf.iloc[:, 0]
    upper = conf.iloc[:, 1]

    # Base do forecast = agora (hora do servidor), não o último registo
    now_dt = datetime.now()

    future_labels = [
        (now_dt + timedelta(seconds=freq_sec * i)).strftime("%Y-%m-%d %H:%M:%S")
        for i in range(1, steps + 1)
    ]

    out = {
        "ok": True,
        "minutes": minutes,
        "freq_seconds": freq_sec,
        "steps": steps,
        "last_timestamp": last_dt.strftime("%Y-%m-%d %H:%M:%S"),
        "base_timestamp": now_dt.strftime("%Y-%m-%d %H:%M:%S"),
        "history": {
            "labels": history_labels,
            "data": history_data
        },
        "forecast": {
            "labels": future_labels,
            "mean":  [round(float(x), 2) for x in mean.tolist()],
            "lower": [round(float(x), 2) for x in lower.tolist()],
            "upper": [round(float(x), 2) for x in upper.tolist()]
        }
    }

    print(json.dumps(out, ensure_ascii=False))

if __name__ == "__main__":
    main()