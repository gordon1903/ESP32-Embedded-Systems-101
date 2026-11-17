// USING SWITCH-CASE TO CONTROL LED'S OPERATING STATES: OFF, ON, BLINK.
// TWO SWITCH-CASE USED
// FIRST: ADVANCING THE CURRENTMODE TO THE NEXT MODE WHEN THE BUTTON IS PRESSED
// SECOND: DECIDE THE OPERATE STATE OF LED BASED ON CURRENTMODE 


const int LED_PIN = 23;
const int BUTTON_PIN = 18;

// Define operating states
// enum CREATE A TYPE LedMode, and giving interger 0, 1, and 2 a special easy-to-understand name subsequancely, MODE_OFF, MODE_ON, AND MODE_BLINK 
enum LedMode {
  MODE_OFF,
  MODE_ON,
  MODE_BLINK
};

// DEFINE A VARIABLE OF THE TYPE LedMode, AND SET THE ORIGIN STATE AS MODE_OFF
LedMode currentMode = MODE_OFF;

// Button debouncing variables
bool lastReading = HIGH;
bool stableButtonState = HIGH;

unsigned long lastPressed = 0;
const unsigned long debounceDelay = 50;

// LED blinking variables
bool blinkState = LOW;
unsigned long previousBlinkTime = 0;
const unsigned long blinkInterval = 50;

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  digitalWrite(LED_PIN, LOW);
}

void loop() {

  // TASK 1: Read and debounce the button
  // Debounce error avoiding part
  bool reading = digitalRead(BUTTON_PIN);

  if (reading != lastReading) {
    lastPressed = millis();
  }

  if (millis() - lastPressed >= debounceDelay) {

    if (reading != stableButtonState) {
      stableButtonState = reading;

      // actual input confirmed, only pressing down will be effective
      if (stableButtonState == LOW) {

        // Advance to the next operating mode
        // USING enum allow us to understand the relationship between the intergers and the cases, 
        // Ex. using MODE_OFF is easy to know that in this case, the program will be in LED off state, instead of just using case 0, which we can't directly understand what program function is 0 link with 
        switch (currentMode) {

          case MODE_OFF:
            currentMode = MODE_ON;
            break;

          case MODE_ON:
            currentMode = MODE_BLINK;
            blinkState = LOW;
            previousBlinkTime = millis();
            break;

          case MODE_BLINK:
            currentMode = MODE_OFF;
            break;
        }

        Serial.print("Current mode: ");
        Serial.println((int)currentMode);
      }
    }
  }

  lastReading = reading;

  // TASK 2: Control the LED
  switch (currentMode) {

    case MODE_OFF:
      digitalWrite(LED_PIN, LOW);
      break;

    case MODE_ON:
      digitalWrite(LED_PIN, HIGH);
      break;

    case MODE_BLINK:

      // USING MILLIS TO REALISE THE BLINKING INTERVAL WITHOUT STOPPING THE WHOLE PROGRAM
      if (millis() - previousBlinkTime >= blinkInterval) {
        previousBlinkTime = millis();

        blinkState = !blinkState;
        digitalWrite(LED_PIN, blinkState);
      }

      break;
  }
}
