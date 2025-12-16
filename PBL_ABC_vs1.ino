/*
 *
 * =========================================================
 *  MAPA DE PINOS – ESP32 (DevKit)
 * =========================================================
 *
 *  ALIMENTAÇÃO
 *
 *    3V3  -> VCC sensores/atuadores (DHT11, PIR, RFID, OLED, etc.)
 *    GND  -> GND comum de todos os módulos
 *
 *  I2C  (OLED 128x64)
 *
 *    GPIO 21 -> SDA_PIN  -> Linha de dados I2C (OLED)
 *    GPIO 22 -> SCL_PIN  -> Linha de clock I2C (OLED)
 *
 *  SENSOR DE MOVIMENTO PIR
 *
 *    GPIO 27 -> PIR_PIN  -> Saída digital do sensor PIR
 *
 *  BUZZER
 *
 *    GPIO 26 -> BUZZER_PIN -> Buzzer ativo (alarme / erro)
 *
 *  SENSOR DHT11 (Temperatura / Humidade)
 *
 *    GPIO 4 -> DHTPIN -> Pino de dados do DHT11
 *
 *  LED RGB (comum ligado ao GND)
 *
 *    GPIO 13 -> LED_R -> Canal Vermelho
 *    GPIO 12 -> LED_G -> Canal Verde
 *    GPIO 14 -> LED_B -> Canal Azul
 *
 *  MÓDULO RFID-RC522 (SPI)
 *
 *    GPIO 18 -> RFID_SCK  -> SCK
 *    GPIO 19 -> RFID_MISO -> MISO 
 *    GPIO 23 -> RFID_MOSI -> MOSI 
 *    GPIO 5  -> RFID_SS   -> SDA/SS 
 *    GPIO 2  -> RFID_RST  -> RST 
 *
 */

#include <WiFi.h>
#include <HTTPClient.h>

#include <MFRC522.h>
#include <SPI.h>

#include <DHT.h>
#include <DHT_U.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ===============================
//  CONFIG Wi-Fi / SERVIDOR
// ===============================
const char* WIFI_SSID = "Vodafone-85383B";
const char* WIFI_PASS = "hWR7XWtXMJ";

const char* SERVER_HOST = "192.168.1.201";

String URL_SENSORES = String("http://") + SERVER_HOST + "/sensores.php";
String URL_ACESSOS  = String("http://") + SERVER_HOST + "/acessos.php";

// --- OLED ---
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// --- Pinos ---
#define SDA_PIN     21
#define SCL_PIN     22
#define PIR_PIN     27
#define BUZZER_PIN  26
#define DHTPIN       4
#define DHTTYPE   DHT11

// --- LED RGB ---
#define LED_R 13
#define LED_G 12
#define LED_B 14
const bool COMMON_CATHODE = true;

// --- RC522 (SPI) ---
#define RFID_SCK   18
#define RFID_MISO  19
#define RFID_MOSI  23
#define RFID_SS     5
#define RFID_RST    2
MFRC522 rfid(RFID_SS, RFID_RST);

// --- Cartão autorizado do RFID ---
byte AUT1[] = { 0x9B, 0x1E, 0xF6, 0x04 };

// --- Estado / temporizações ---
DHT dht(DHTPIN, DHTTYPE);
const bool BUZZER_ATIVO = true;
const unsigned long DURACAO_TOQUE_MS = 1000;
const unsigned long INTERVALO_MIN_MS  = 2000;
unsigned long ultimoDisparo = 0;

float tempC = NAN, hum = NAN;
unsigned long lastDhtMs = 0;
const unsigned long DHT_INTERVAL = 10000;

bool armado = true;
unsigned long unlockSince = 0;
const unsigned long UNLOCK_DURATION_MS = 30000;

// --- RGB ---
inline void setRGB(bool r, bool g, bool b) {
  if (COMMON_CATHODE) {
    digitalWrite(LED_R, r ? HIGH : LOW);
    digitalWrite(LED_G, g ? HIGH : LOW);
    digitalWrite(LED_B, b ? HIGH : LOW);
  } else {
    digitalWrite(LED_R, r ? LOW : HIGH);
    digitalWrite(LED_G, g ? LOW : HIGH);
    digitalWrite(LED_B, b ? LOW : HIGH);
  }
}
inline void ledGreen() { setRGB(false, true, false); }
inline void ledRed()   { setRGB(true, false, false); }

void tocarBuzzer() {
  if (BUZZER_ATIVO) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(DURACAO_TOQUE_MS);
    digitalWrite(BUZZER_PIN, LOW);
  }
}

void desenhaEcran(const char* status, int tempoRestante = -1) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  // Linha 1: Temp/Hum
  display.setCursor(0, 0);
  if (isnan(tempC) || isnan(hum)) display.print("T: --.-C  H: --%");
  else {
    display.print("T: "); display.print(tempC, 1); display.print("C  ");
    display.print("H: "); display.print((int)hum); display.print("%");
  }

  // Linha 2-3: texto grande
  display.setCursor(0, 16);
  display.setTextSize(2);
  display.println(status);

  // Linha 4: Estado Bloq/Desblq
  display.setTextSize(1);
  display.setCursor(0, 48);
  display.print("Estado: ");
  display.println(armado ? "Bloq" : "Desblq");

  // Linha 5: Tempo
  if (!armado && tempoRestante >= 0) {
    display.setCursor(0, 56);
    display.print("Tempo: ");
    display.print(tempoRestante);
    display.print("s");
  }

  display.display();
}

bool uidEquals(byte *a, byte *b, byte size) {
  for (byte i = 0; i < size; i++)
    if (a[i] != b[i]) return false;
  return true;
}

// ===============================
//  FUNÇÕES DE REDE / HTTP
// ===============================

void conectarWiFi() {
  Serial.print("A ligar ao Wi-Fi: ");
  Serial.println(WIFI_SSID);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  int tentativas = 0;
  while (WiFi.status() != WL_CONNECTED && tentativas < 30) {
    delay(500);
    Serial.print(".");
    tentativas++;
  }

  Serial.println();

  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("Wi-Fi ligado! IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("Falha ao ligar ao Wi-Fi.");
  }
}

// Enviar leitura de sensor (temperatura ou humidade)
void enviarSensorParaServidor(const char* tipo, float valor) {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Wi-Fi desligado, tentando reconectar...");
    conectarWiFi();
  }

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(URL_SENSORES);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    String body = "tipo=";
    body += tipo;
    body += "&valor=";
    body += String(valor, 1);

    Serial.print("POST sensores -> ");
    Serial.println(body);

    int httpCode = http.POST(body);
    if (httpCode > 0) {
      String payload = http.getString();
      Serial.print("Resposta sensores (");
      Serial.print(httpCode);
      Serial.print("): ");
      Serial.println(payload);
    } else {
      Serial.print("Erro POST sensores: ");
      Serial.println(httpCode);
    }

    http.end();
  }
}

// Enviar acesso RFID
void enviarAcessoParaServidor(const char* id_usuario, const char* acao) {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Wi-Fi desligado, tentando reconectar...");
    conectarWiFi();
  }

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(URL_ACESSOS);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    String body = "id_usuario=";
    body += id_usuario;
    body += "&acao=";
    body += acao;

    Serial.print("POST acessos -> ");
    Serial.println(body);

    int httpCode = http.POST(body);
    if (httpCode > 0) {
      String payload = http.getString();
      Serial.print("Resposta acessos (");
      Serial.print(httpCode);
      Serial.print("): ");
      Serial.println(payload);
    } else {
      Serial.print("Erro POST acessos: ");
      Serial.println(httpCode);
    }

    http.end();
  }
}

// ===============================
//  SETUP
// ===============================

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("Inicializar sistema...");

  pinMode(PIR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);

  ledGreen();

  Wire.begin(SDA_PIN, SCL_PIN);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Erro ao iniciar OLED!");
  }
  display.clearDisplay();
  display.display();

  dht.begin();
  tempC = dht.readTemperature();
  hum = dht.readHumidity();
  lastDhtMs = millis();

  SPI.begin(RFID_SCK, RFID_MISO, RFID_MOSI, RFID_SS);
  rfid.PCD_Init();

  desenhaEcran("Pronto");

  conectarWiFi();
}

// ===============================
//  LOOP PRINCIPAL
// ===============================

void loop() {
  unsigned long now = millis();

  int tempoRestante = -1;
  if (!armado) {
    long restante = UNLOCK_DURATION_MS - (now - unlockSince);
    if (restante < 0) restante = 0;
    tempoRestante = restante / 1000;
  }

  if (!armado && (now - unlockSince >= UNLOCK_DURATION_MS)) {
    armado = true;
    desenhaEcran("Bloq", -1);
    Serial.println("Tempo expirado -> Sistema BLOQUEADO");
  }

  // Atualizar DHT
  if (now - lastDhtMs >= DHT_INTERVAL) {
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    if (!isnan(h) && !isnan(t)) {
      hum = h;
      tempC = t;
      Serial.print("DHT -> T: ");
      Serial.print(tempC);
      Serial.print(" C  H: ");
      Serial.print(hum);
      Serial.println(" %");

      // Enviar para o servidor (2 registos: temp + hum)
      enviarSensorParaServidor("temperatura", tempC);
      enviarSensorParaServidor("humidade", hum);
    } else {
      Serial.println("Falha na leitura do DHT");
    }
    lastDhtMs = now;
  }

  // RFID leitura do Cartão
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {

    Serial.print("UID lido: ");
    for (byte i = 0; i < rfid.uid.size; i++) {
      Serial.print(rfid.uid.uidByte[i], HEX);
      Serial.print(" ");
    }
    Serial.println();

    if (rfid.uid.size == 4 && uidEquals(rfid.uid.uidByte, AUT1, 4)) {
      if (armado) {
        armado = false;
        unlockSince = now;
        ledGreen();
        desenhaEcran("Desblq", tempoRestante);
        Serial.println("RFID OK -> DESBLOQUEADO");

        // Regista "entrada"
        enviarAcessoParaServidor("RFID001", "entrada");

      } else {
        armado = true;
        ledRed();
        desenhaEcran("Bloq", -1);
        Serial.println("RFID OK -> BLOQUEADO");

        // Regista "saida"
        enviarAcessoParaServidor("RFID001", "saida");
      }

    } else {
      // Cartão não autorizado
      armado = true;
      ledRed();
      tocarBuzzer();
      desenhaEcran("RFID ERR", -1);
      Serial.println("RFID NAO AUTORIZADO!");
      delay(2000);
    }

    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
  }

  // PIR
  int movimento = digitalRead(PIR_PIN);

  if (movimento == HIGH) {
    if (armado) {
      ledRed();
      desenhaEcran("ALERTA!", tempoRestante);
      tocarBuzzer();
      Serial.println("Movimento DETECTADO com sistema ARMADO");
    } else {
      ledGreen();
      desenhaEcran("Movimento", tempoRestante);
      Serial.println("Movimento detectado (sistema desarmado)");
    }
  } else {
    ledGreen();
    desenhaEcran(armado ? "Sem Mov" : "Clear", tempoRestante);
  }

  delay(60);
}