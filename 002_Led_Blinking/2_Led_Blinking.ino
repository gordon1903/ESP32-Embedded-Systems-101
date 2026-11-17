const int led_pin = 23;

void setup() {
  Serial.begin(115200);
  pinMode(led_pin,OUTPUT);
}

void loop() {
  digitalWrite(led_pin,HIGH);
  Serial.println("Led is on.");
  delay(1000);

  digitalWrite(led_pin,LOW);
  Serial.println("Led is off.");
  delay(1000);
}
