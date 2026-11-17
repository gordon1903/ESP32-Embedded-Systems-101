//PULL UP BUTTON INPUT, PRESSED = LOW; RELEASED = HIGH.
const int BUTTON_PIN = 18;

void setup() {
  Serial.begin(115200);

  pinMode(BUTTON_PIN, INPUT_PULLUP); //INPUT_PULLUP WILL ACTIVATE THE BUILT-IN PULL-UP RESISTOR IN THE BOARD.
}

void loop() {
  int buttonState = digitalRead(BUTTON_PIN);

  if (buttonState == LOW) {
    Serial.println("Button Pressed");
  } else {
    Serial.println("Button Released");
  }

  delay(200);
}
