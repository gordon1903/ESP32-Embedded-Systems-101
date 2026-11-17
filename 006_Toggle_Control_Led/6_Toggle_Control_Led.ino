//LED TOGGLE CONTROL, PRESS AND RELEASE THE BUTTON TO CHANGE THE STATUS OF THE LED.
const int LED_PIN = 23;
const int BUTTON_PIN = 18;

bool ledState = false;
bool lastButtonState = HIGH;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  digitalWrite(LED_PIN, LOW);
  Serial.begin(115200);
}

void loop() {
  bool buttonState = digitalRead(BUTTON_PIN);

  // Detect when button changes from released to pressed
  if (lastButtonState == HIGH && buttonState == LOW) {

    // Toggle LED state
    ledState = !ledState;

    digitalWrite(LED_PIN, ledState);

    Serial.println(ledState ? "LED ON" : "LED OFF");

    delay(50);  // Simple debounce delay
  }

  // Remember button state for next iteration
  lastButtonState = buttonState;
}

//THE BUTTON IS PULL-UP SO RELEASE == HIGH, PRESSED == LOW
//SYSTEM COMPARE THE BUTTON STATE WITH ITS PREVIOUS STATE,
//PRESSED MEANS THE IF CONDITION FULFILL SO PROCEED WITH TOGGLE CONTROL
//DELAY TO DENIAL DOUBLE INPUT OR DEBOUNCE ERROR
//IDLE: LAST = HIGH; CURRENT = HIGH
//PRESSED: LAST = HIGH; CURRENT = LOW
//DEBOUCING OR HOLDING: LAST = LOW; CURRENT = LOW,
//RELEASED: LAST = LOW; CURRENT = HIGH
//GO BACK TO IDLE