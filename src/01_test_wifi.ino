#include <WiFi.h>

#define WIFI_SSID "Iphone de Arturo"
#define WIFI_PASSWORD "arturo12"

void setup() {
  Serial.begin(115200);
  Serial.print("Connectant a WiFi");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(". ");
  }

  Serial.println();
  Serial.println("WiFi OK");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {}
