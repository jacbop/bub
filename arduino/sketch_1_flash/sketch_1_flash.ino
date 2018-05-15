// A simple flashing LED test program to make sure we
// can program the 8266 properly

void setup() {
  pinMode(2, OUTPUT);
}

void loop() {
  digitalWrite(2, !digitalRead(2));
  delay(1000);
}
