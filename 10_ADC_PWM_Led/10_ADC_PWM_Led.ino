/*
Using Potentiometer analog input control PWM module to adjust LED Brightness
*/

const int POT_PIN = 34;
const int LED_PIN = 23;

// PWM configuration
const int PWM_FREQ = 5000;        // 5 kHz
const int PWM_RESOLUTION = 8;     // 8-bit: 0-255

/*
Using ledcAttach to setup PWM Output, the frequency and the resolution could be decided by the user within the given range
Frequency 1-40MHz
Resolution 1-16 bits
*/

void setup() {
  Serial.begin(115200);

  // Configure ADC resolution
  analogReadResolution(12);
  // ADC resolution didn't have to be the same as PWM resolution

  // Configure hardware PWM
  // A function could be called and execute within an if condition
  // If PWM Setup unsuccessfull,  while loop keeps delay for 1000 ms and stop the program by infinite loop
  if (!ledcAttach(LED_PIN, PWM_FREQ, PWM_RESOLUTION)) {
    Serial.println("PWM setup failed!");
    while (true) {
      delay(1000);
    }
  }
}

void loop() {

  // STEP 1: Read potentiometer (0-4095)
  int adcValue = analogRead(POT_PIN);

  // STEP 2: Convert ADC value to PWM duty (0-255)
  // map() apply the ratio value of adcvalue/4095 on the PWM resolution, 
  // mathematical process --> (adcValue/4095) * 255
  // Despite mathematical result would be a float value, but map() only keep interger part, decimal part would be ignore 
  int dutyValue = map(adcValue, 0, 4095, 0, 255);

  // STEP 3: Update LED brightness
  // ledcWrite apply PWM output with variable dutycycle based on the ratio of dutyValue and Max PWM Resolution, 
  // in this case is dutyValue/255, 
  // For instance, to output 50% dutycycle, dutyValue should 50% of 255 which is 127
  ledcWrite(LED_PIN, dutyValue);

  // STEP 4: Display values
  Serial.print("ADC: ");
  Serial.print(adcValue);

  Serial.print(" | PWM Duty: ");
  Serial.print(dutyValue);

  Serial.print(" | Duty Cycle: ");
  Serial.print(dutyValue * 100.0 / 255.0, 1);
  Serial.println("%");

  delay(100);
}
