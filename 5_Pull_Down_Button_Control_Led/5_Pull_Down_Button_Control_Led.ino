//EXTERNAL PULL DOWN BUTTON, PRESSED = HIGH; RELEASED = LOW.
//USING PULL-DOWN BUTTON INPUT TO CONTROL A LED.
//WHEN PRESSED, LED SWITCHED ON; VICE VERSA.
const int LED_PIN = 23;
const int BUTTON_PIN = 18;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
}

void loop() {
  int buttonState = digitalRead(BUTTON_PIN);

  if (buttonState == HIGH) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }
}
