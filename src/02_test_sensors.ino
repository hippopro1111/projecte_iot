#define PIN_LIGHT   34
#define PIN_TEMP    36
#define PIN_PIR     27
#define PIN_BUTTON  12

void setup() {
  Serial.begin(115200);
  pinMode(PIN_PIR, INPUT);
  pinMode(PIN_BUTTON, INPUT);
}

void loop() {
  int lightValue  = analogRead(PIN_LIGHT);
  int tempValue   = analogRead(PIN_TEMP);
  int pirValue    = digitalRead(PIN_PIR);
  int buttonValue = digitalRead(PIN_BUTTON);

  Serial.print("LIGHT=");   Serial.print(lightValue);
  Serial.print(" | TEMP=");  Serial.print(tempValue);
  Serial.print(" | PIR=");   Serial.print(pirValue);
  Serial.print(" | BUTTON="); Serial.println(buttonValue);

  delay(1000);
}
