#include <WiFi.h>

#define WIFI_SSID     "Iphone de Arturo"
#define WIFI_PASSWORD "arturo12"
#define AULA_ID       "A01"

#define PIN_LIGHT  34
#define PIN_TEMP   36
#define PIN_PIR    27
#define PIN_RGBLED 25
#define PIN_BUTTON 12

unsigned long lastRead = 0;
const unsigned long intervalMs = 1000;

void connectWiFi() {
  Serial.print("Connectant a WiFi");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(". ");
  }

  Serial.println();
  Serial.println("WiFi connectat");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);
  pinMode(PIN_PIR, INPUT);
  pinMode(PIN_BUTTON, INPUT);
  pinMode(PIN_RGBLED, OUTPUT);
  connectWiFi();
}

void loop() {
  unsigned long now = millis();

  if (now - lastRead >= intervalMs) {
    lastRead = now;

    int lightValue  = analogRead(PIN_LIGHT);
    int tempValue   = analogRead(PIN_TEMP);
    int pirValue    = digitalRead(PIN_PIR);
    int buttonValue = digitalRead(PIN_BUTTON);

    digitalWrite(PIN_RGBLED, pirValue ? HIGH : LOW);

    Serial.print("AULA=");    Serial.print(AULA_ID);
    Serial.print(" | LIGHT="); Serial.print(lightValue);
    Serial.print(" | TEMP=");  Serial.print(tempValue);
    Serial.print(" | PIR=");   Serial.print(pirValue);
    Serial.print(" | BUTTON="); Serial.println(buttonValue);
  }
}
