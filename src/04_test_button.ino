#define PIN_BUTTON 12

void setup() {
  Serial.begin(115200);
  pinMode(PIN_BUTTON, INPUT);
}

void loop() {
  int buttonValue = digitalRead(PIN_BUTTON);
  Serial.print("BUTTON=");
  Serial.println(buttonValue);
  delay(300);
}
