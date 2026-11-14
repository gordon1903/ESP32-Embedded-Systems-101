// Using a 10K OHM Potentiometer to provide analog input
// Potentiometer got 3 Pins, which to be connected to 3.3V, GPIO, GND
// The 10K ohm Resistance between 3.3V and GND splits at GPIO pin, R1+R2=Rtotal=10K
// V_GPIO34=3.3*{R2/{R1+R2}}

const int POT_PIN = 34;
// on esp32, PIN 34 is one of the pin supports ADC

void setup() {
  Serial.begin(115200);

  // Configure ADC resolution
  analogReadResolution(12);
  // For 12 bits Resolution, Analog voltage input could assign into 2^12= 4096 intergers, which is 0 to 4095 ADC input code
  // Higher resolution could achieve finer quantize input control
}

void loop() {

  // Read the potentiometer
  // Using analogRead for analog input
  int adcValue = analogRead(POT_PIN);

  // Approximate voltage (idealized)
  // float allows decimal values
  float voltage = adcValue * (3.3 / 4095.0);

  // Display results
  Serial.print("ADC Value: ");
  Serial.print(adcValue);

  Serial.print(" | Approx. Voltage: ");
  Serial.print(voltage, 2);

  Serial.println(" V");

  delay(200);
}
