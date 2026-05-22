#define PIN_PIR    27
#define PIN_RGBLED 25

void setup() {
  Serial.begin(115200);
  pinMode(PIN_PIR, INPUT);
  pinMode(PIN_RGBLED, OUTPUT);
}

void loop() {
  int pirValue = digitalRead(PIN_PIR);
  digitalWrite(PIN_RGBLED, pirValue ? HIGH : LOW);

  Serial.print("PIR=");
  Serial.println(pirValue);

  delay(300);
}
