import mysql.connector
import pandas as pd
import pickle

from statsmodels.tsa.arima.model import ARIMA

DB = {
    "host": "127.0.0.1",
    "user": "root",
    "password": "",
    "database": "datacenter"
}

# -----------------------------
#           Ler dados
# -----------------------------
conn = mysql.connector.connect(**DB)

df = pd.read_sql("""
    SELECT data_hora, valor
    FROM sensores
    WHERE tipo='temperatura'
    ORDER BY data_hora ASC
    LIMIT 150000
""", conn)

conn.close()

df["valor"] = pd.to_numeric(df["valor"], errors="coerce")
series = df["valor"].dropna()

# -----------------------------
#     Treinar ARIMA(p,0,q)
# -----------------------------
model = ARIMA(series, order=(2, 0, 2))
model_fit = model.fit()

print(model_fit.summary())

# -----------------------------
#        Guardar modelo
# -----------------------------
with open("model_temp_arima.pkl", "wb") as f:
    pickle.dump(model_fit, f)

print("✔ Modelo ARIMA treinado")
