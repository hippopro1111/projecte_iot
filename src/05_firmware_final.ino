#include <WiFi.h>
#include <WebServer.h>

#define WIFI_SSID "Iphone de Arturo"
#define WIFI_PASSWORD "arturo12"
#define AULA_ID "A01"

#define PIN_LIGHT 35
#define PIN_TEMP 34
#define PIN_PIR 14
#define PIN_RGBLED 25
#define PIN_BUTTON 16

WebServer server(80);

unsigned long lastRead = 0;
const unsigned long intervalMs = 1000;

int lightValue = 0;
int tempValue = 0;
int pirValue = 0;
int buttonValue = 0;

const char էջ_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>ESP32 Aula</title>
  <style>
    body { font-family: Arial; background:#111; color:#eee; text-align:center; }
    .box { background:#222; margin:20px auto; padding:20px; border-radius:12px; max-width:360px; }
    .v { font-size: 2rem; color:#00d1ff; }
  </style>
</head>
<body>
  <h1>ESP32 Aula A01</h1>
  <div class="box">
    <p>Luz: <span class="v" id="light">--</span></p>
    <p>Temp: <span class="v" id="temp">--</span></p>
    <p>PIR: <span class="v" id="pir">--</span></p>
    <p>Boton: <span class="v" id="button">--</span></p>
    <p>LED: <span class="v" id="led">--</span></p>
  </div>

  <script>
    async function updateData() {
      const r = await fetch('/data');
      const d = await r.json();
      document.getElementById('light').textContent = d.light;
      document.getElementById('temp').textContent = d.temp;
      document.getElementById('pir').textContent = d.pir;
      document.getElementById('button').textContent = d.button;
      document.getElementById('led').textContent = d.led;
    }
    setInterval(updateData, 1000);
    updateData();
  </script>
</body>
</html>
)rawliteral";

void connectWiFi() {
  Serial.print("Conectando a WiFi");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi conectado");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void readSensors() {
  lightValue = analogRead(PIN_LIGHT);
  tempValue = analogRead(PIN_TEMP);
  pirValue = digitalRead(PIN_PIR);
  buttonValue = digitalRead(PIN_BUTTON);
  digitalWrite(PIN_RGBLED, pirValue ? HIGH : LOW);
}

void handleRoot() {
  server.send(200, "text/html", index_html);
}

void handleData() {
  String json = "{";
  json += "\"light\":" + String(lightValue) + ",";
  json += "\"temp\":" + String(tempValue) + ",";
  json += "\"pir\":" + String(pirValue) + ",";
  json += "\"button\":" + String(buttonValue) + ",";
  json += "\"led\":" + String(digitalRead(PIN_RGBLED));
  json += "}";
  server.send(200, "application/json", json);
}

void setup() {
  Serial.begin(115200);
  pinMode(PIN_PIR, INPUT);
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  pinMode(PIN_RGBLED, OUTPUT);

  connectWiFi();

  server.on("/", handleRoot);
  server.on("/data", handleData);
  server.begin();
  Serial.println("Servidor web iniciado");
}

void loop() {
  server.handleClient();

  unsigned long now = millis();
  if (now - lastRead >= intervalMs) {
    lastRead = now;
    readSensors();
  }
}
