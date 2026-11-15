/*
 Improvisation for 10_ADC_PWM_Led
 Changing delay to millis
 Allow other program to run while processing the PWM 
*/

const int POT_PIN = 34;
const int LED_PIN = 23;

const int PWM_FREQ = 5000;
const int PWM_RESOLUTION = 8;

// ADC sampling interval
const unsigned long sampleInterval = 50;

// Stores the time of the previous ADC update
unsigned long previousSampleTime = 0;

// For Task 2: Heartbeat
const unsigned long heartbeatInterval = 100;
unsigned long previousHeartbeatTime = 0;

void setup() {
  Serial.begin(115200);

  analogReadResolution(12);

  if (!ledcAttach(LED_PIN, PWM_FREQ, PWM_RESOLUTION)) {
    Serial.println("PWM setup failed!");
    while (true) {
      delay(1000);
    }
  }
}

void loop() {

  unsigned long currentTime = millis();

  // TASK 1: Update LED brightness every 100 ms
  if (currentTime - previousSampleTime >= sampleInterval) {

    previousSampleTime = currentTime;

    int adcValue = analogRead(POT_PIN);

    int dutyValue = map(adcValue, 0, 4095, 0, 255);

    ledcWrite(LED_PIN, dutyValue);

    Serial.print("ADC: ");
    Serial.print(adcValue);

    Serial.print(" | PWM Duty: ");
    Serial.println(dutyValue);
  }

  // TASK 2: Other tasks can run here without waiting.
  if (currentTime - previousHeartbeatTime >= heartbeatInterval) {
    previousHeartbeatTime = currentTime;

    Serial.println("ESP32 is running...");
  }
}
