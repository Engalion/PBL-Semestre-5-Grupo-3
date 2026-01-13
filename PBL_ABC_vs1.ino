/*
 * =========================================================
 *  MAPA DE PINOS – ESP32 (DevKit)
 * =========================================================
 *
 *  3V3  -> VCC sensores
 *  GND  -> GND comum
 *
 *  OLED (I2C)
 *    GPIO 21 -> SDA
 *    GPIO 22 -> SCL
 *
 *  PIR
 *    GPIO 27 -> PIR
 *
 *  BUZZER
 *    GPIO 26 -> BUZZER
 *
 *  DHT11
 *    GPIO 4  -> DATA
 *
 *  LED RGB (catodo comum)
 *    GPIO 13 -> R
 *    GPIO 12 -> G
 *    GPIO 14 -> B
 *
 *  RFID RC522 (SPI)
 *    GPIO 18 -> SCK
 *    GPIO 19 -> MISO
 *    GPIO 23 -> MOSI
 *    GPIO 5  -> SS
 *    GPIO 2  -> RST
 *
 */

#include <WiFi.h>
#include <HTTPClient.h>

#include <MFRC522.h>
#include <SPI.h>

#include <DHT.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ===============================
//  WIFI / SERVIDOR
// ===============================
const char* WIFI_SSID = "Vodafone-85383B";
const char* WIFI_PASS = "hWR7XWtXMJ";

const char* SERVER_HOST = "192.168.1.201";
String URL_SENSORES = String("http://") + SERVER_HOST + "/sensores.php";
String URL_ACESSOS  = String("http://") + SERVER_HOST + "/acessos.php";

// ===============================
//  OLED
// ===============================
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// ===============================
//  PINOS
// ===============================
#define SDA_PIN     21
#define SCL_PIN     22
#define PIR_PIN     27
#define BUZZER_PIN  26
#define DHTPIN       4
#define DHTTYPE   DHT11

// LED RGB
#define LED_R 13
#define LED_G 12
#define LED_B 14
const bool COMMON_CATHODE = true;

// RFID
#define RFID_SCK   18
#define RFID_MISO  19
#define RFID_MOSI  23
#define RFID_SS     5
#define RFID_RST    2
MFRC522 rfid(RFID_SS, RFID_RST);

// UID autorizado (o teu cartão)
byte AUT1[] = { 0x9B, 0x1E, 0xF6, 0x04 };

// ===============================
//  ESTADO
// ===============================
DHT dht(DHTPIN, DHTTYPE);

bool armado = true; // true=bloqueado, false=desbloqueado
unsigned long unlockSince = 0;
const unsigned long UNLOCK_DURATION_MS = 30000;  // 30s desbloqueado

float tempC = NAN, hum = NAN;
unsigned long lastDhtMs = 0;
const unsigned long DHT_INTERVAL = 10000; // envia temp/hum a cada 10s

unsigned long lastMovSendMs = 0;
const unsigned long MOV_SEND_COOLDOWN_MS = 5000; // envia "movimento" no max 1x/5s

// Tocar o buzzer só 1x por evento (LOW->HIGH)
int pirAnterior = LOW;

// ===============================
//  RGB
// ===============================
inline void setRGB(bool r, bool g, bool b) {
  if (COMMON_CATHODE) {
    digitalWrite(LED_R, r);
    digitalWrite(LED_G, g);
    digitalWrite(LED_B, b);
  } else {
    digitalWrite(LED_R, !r);
    digitalWrite(LED_G, !g);
    digitalWrite(LED_B, !b);
  }
}
inline void ledGreen() { setRGB(false, true,  false); } // Bloq sem mov
inline void ledRed()   { setRGB(true,  false, false); } // Alerta/Erro
inline void ledBlue()  { setRGB(false, false, true);  } // Desbloq

void atualizarLED(int movimento) {
  if (!armado) ledBlue();
  else {
    if (movimento == HIGH) ledRed();
    else ledGreen();
  }
}

// ===============================
//  BUZZER
// ===============================
void tocarBuzzer(unsigned long durMs = 1000) {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(durMs);
  digitalWrite(BUZZER_PIN, LOW);
}

// ===============================
//  OLED
// ===============================
void desenhaEcran(const char* status, int tempo = -1) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  if (isnan(tempC) || isnan(hum)) {
    display.print("T: --.-C  H: --%");
  } else {
    display.print("T: "); display.print(tempC, 1);
    display.print("C  H: "); display.print((int)hum); display.print("%");
  }

  display.setTextSize(2);
  display.setCursor(0, 16);
  display.println(status);

  display.setTextSize(1);
  display.setCursor(0, 48);
  display.print("Estado: ");
  display.println(armado ? "Bloq" : "Desblq");

  if (!armado && tempo >= 0) {
    display.setCursor(0, 56);
    display.print("Tempo: ");
    display.print(tempo);
    display.print("s");
  }

  display.display();
}

// UID -> String para guardar na Base de Dados
String uidToString(const MFRC522::Uid &uid) {
  String s = "";
  for (byte i = 0; i < uid.size; i++) {
    if (uid.uidByte[i] < 0x10) s += "0";
    s += String(uid.uidByte[i], HEX);
  }
  s.toUpperCase();
  return s;
}

// ===============================
//  WIFI / HTTP
// ===============================
void conectarWiFi() {
  Serial.print("A ligar WiFi");
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  int tries = 0;
  while (WiFi.status() != WL_CONNECTED && tries < 30) {
    delay(500);
    Serial.print(".");
    tries++;
  }
  Serial.println();

  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("WiFi OK IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("WiFi FAIL");
  }
}

void enviarSensor(const char* tipo, float valor) {
  if (WiFi.status() != WL_CONNECTED) conectarWiFi();
  if (WiFi.status() != WL_CONNECTED) return;

  HTTPClient http;
  http.begin(URL_SENSORES);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  String body = "tipo=" + String(tipo) + "&valor=" + String(valor, 1);

  Serial.print("POST sensores -> ");
  Serial.println(body);

  int httpCode = http.POST(body);
  String payload = http.getString();
  Serial.print("Resposta sensores ("); Serial.print(httpCode); Serial.print("): ");
  Serial.println(payload);

  http.end();
}

// Envia "estado=" para o acessos.php para depois comunicar com a base de dados
void enviarAcesso(const String& id_usuario, const char* estado) {
  if (WiFi.status() != WL_CONNECTED) conectarWiFi();
  if (WiFi.status() != WL_CONNECTED) return;

  HTTPClient http;
  http.begin(URL_ACESSOS);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  String body = "id_usuario=" + id_usuario + "&estado=" + String(estado);

  Serial.print("POST acessos -> ");
  Serial.println(body);

  int httpCode = http.POST(body);
  String payload = http.getString();
  Serial.print("Resposta acessos ("); Serial.print(httpCode); Serial.print("): ");
  Serial.println(payload);

  http.end();
}

// ===============================
//  SETUP
// ===============================
void setup() {
  Serial.begin(115200);

  pinMode(PIR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);

  Wire.begin(SDA_PIN, SCL_PIN);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();

  dht.begin();

  SPI.begin(RFID_SCK, RFID_MISO, RFID_MOSI, RFID_SS);
  rfid.PCD_Init();

  conectarWiFi();

  pirAnterior = digitalRead(PIR_PIN);

  atualizarLED(digitalRead(PIR_PIN));
  desenhaEcran("Pronto");
}

// ===============================
//  LOOP
// ===============================
void loop() {
  unsigned long now = millis();

  // tempo restante (quando desbloqueado)
  int tempoRestante = -1;
  if (!armado) {
    long r = (long)UNLOCK_DURATION_MS - (long)(now - unlockSince);
    if (r < 0) r = 0;
    tempoRestante = (int)(r / 1000);
  }

  // auto-bloqueio
  if (!armado && (now - unlockSince >= UNLOCK_DURATION_MS)) {
    armado = true;
    atualizarLED(digitalRead(PIR_PIN));
  }

  // DHT -> BD
  if (now - lastDhtMs >= DHT_INTERVAL) {
    float t = dht.readTemperature();
    float h = dht.readHumidity();
    if (!isnan(t) && !isnan(h)) {
      tempC = t;
      hum = h;
      enviarSensor("temperatura", tempC);
      enviarSensor("humidade", hum);
    }
    lastDhtMs = now;
  }

  // RFID
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    String uidStr = uidToString(rfid.uid);

    bool autorizado = (rfid.uid.size == 4 && memcmp(rfid.uid.uidByte, AUT1, 4) == 0);

    if (autorizado) {
      if (armado) {
        armado = false;
        unlockSince = now;
        enviarAcesso(uidStr, "entrada");
        desenhaEcran("Desblq", tempoRestante);
      } else {
        armado = true;
        enviarAcesso(uidStr, "saida");
        desenhaEcran("Bloq", -1);
      }

      atualizarLED(digitalRead(PIR_PIN)); // garante azul/verde já

    } else {
      armado = true;
      enviarAcesso(uidStr, "nao_autorizado");

      ledRed();
      tocarBuzzer(1000);
      desenhaEcran("RFID ERR", -1);
      delay(2000);

      atualizarLED(digitalRead(PIR_PIN));
    }

    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
  }

  // ===============================
  // PIR (com buzzer 1x por evento)
  // ===============================
  int movimento = digitalRead(PIR_PIN);
  atualizarLED(movimento);

  // toca só quando o movimento começa (LOW -> HIGH) e está bloqueado
  if (armado && pirAnterior == LOW && movimento == HIGH) {
    tocarBuzzer(1000);
  }
  pirAnterior = movimento;

  // movimento -> BD
  if (movimento == HIGH && (now - lastMovSendMs >= MOV_SEND_COOLDOWN_MS)) {
    enviarSensor("movimento", 1);
    lastMovSendMs = now;
  }

  // OLED
  if (movimento == HIGH && armado) {
    desenhaEcran("ALERTA!", tempoRestante);
  } else if (movimento == HIGH) {
    desenhaEcran("Movimento", tempoRestante);
  } else {
    desenhaEcran(armado ? "Sem Mov" : "Clear", tempoRestante);
  }

  delay(60);
}