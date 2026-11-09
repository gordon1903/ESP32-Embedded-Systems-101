//USING MILLIS() INSTEAD OF DELAY TO AVOID DEBOUNCING ERROR
//MILLIS() STARTS COUNTING FROM THE STARTUP OF THE PROGRAM BY MILLISECOND
//DELAY WOULD STOP THE PROGRAM COMPLETELY, SO SOME IMPORTANT SIGNAL INPUT MIGHT BE SKIPPED DURING THE DELAY WINDOW
//WE COULD USE MILLIS() TO CREATE TIMESTAMP AT THE MOMENT WHEN THE BUTTON IS PRESSED, AND SET AN INTERVAL WINDOW,
//BY COMPARING THE FOLLOWING TIMESTAMP, WE COULD KNOW EITHER IT IS AN ACTUAL INPUT OR JUST THE FALSE SIGNAL CAUSED BY DEBOUNCING
//WITHOUT STOPPING THE WHOLE PROGRAM 


const int LED_PIN = 23;
const int BUTTON_PIN = 18;

bool ledState = false;

// SET A BOOLEAN VARIABLE FOR LAST BUTTON READING, PRESET STATUS AS RELEASED == HIGH
bool lastReading = HIGH;

// STABLE button state, AS A PULLUP BUTTON
bool stableButtonState = HIGH;

// Timing variables
unsigned long lastPressed = 0;
const unsigned long debounceDelay = 50; //INTERVAL WINDOW, BASED ON THE AVERAGE DEBOUNCE TIME OF BUTTON AFTER BEING PRESSED BY A HUMAN, 50-100 MS

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  digitalWrite(LED_PIN, LOW);
}

void loop() {

  // Step 1: Read the button
  bool reading = digitalRead(BUTTON_PIN);

  // Step 2: Detect any change in raw input
  if (reading != lastReading) {
    lastPressed = millis(); // RECORD THE CURRENT MILLIS() AS THE TIMESTAMP OF THE LAST INPUT SIGNAL DETECTED, EITHER ACTUAL INPUT OR ERROR WOULD LEAVE A TIMESTAMP
  }

  // Step 3: Check if input is actual input
  if (millis() - lastPressed >= debounceDelay) { //COMPARE THE TIMESTAMP, ALL DEBOUNCE ERROR HAPPENS WITHIN IN INTERVAL WINDOW WOULD BE IGNORED

    // Step 4: Accept a new stable button state
    if (reading != stableButtonState) {

      stableButtonState = reading;

      // Step 5: TOGGLE
      if (stableButtonState == LOW) { //ONLY CHANGE THE LED STATE WHEN THE BUTTONSTATE IS CHANGED FROM HIGH TO LOW, 

        ledState = !ledState;
        digitalWrite(LED_PIN, ledState);

        Serial.println(ledState ? "LED ON" : "LED OFF");
      }
    }
  }

  // Step 6: Remember the latest raw reading
  lastReading = reading;
}
