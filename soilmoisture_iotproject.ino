#define BLYNK_TEMPLATE_ID "TMPL38ZufXQuy"
#define BLYNK_TEMPLATE_NAME "Soil Monitoring for Smart Irrigation"
#define BLYNK_AUTH_TOKEN "s5kzqcNz78y7w5JlhKWMk0-waHH1xSEE"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// --- Pin Definitions ---
#define SOIL_MOISTURE_PIN 34   // Analog pin for soil moisture sensor
#define PUMP_PIN 25            // Digital pin for IN1 of 2-channel relay (controls pump) - Changed from 2 to 25

// --- Relay Configuration ---
#define RELAY_ON LOW           // Inverted: LOW turns relay ON
#define RELAY_OFF HIGH         // Inverted: HIGH turns relay OFF

// --- Virtual Pins ---
#define V_MOISTURE V5          // Virtual pin for soil moisture percentage
#define V_PUMP_SWITCH V6       // Virtual pin for manual pump control
#define V_MODE_SWITCH V4       // Virtual pin for Auto/Manual mode

// --- WiFi Credentials ---
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Redmi";
char pass[] = "poojasn123";

BlynkTimer timer;

// --- Variables ---
bool isPumpOn = false;         // Track pump status
bool isAutoMode = true;        // Default mode = Auto
int THRESHOLD_MOISTURE = 40;   // Moisture % threshold for auto mode

// --- Calibration Values (Adjust based on your sensor) ---
const int DRY_VALUE = 4095;    // Sensor value in dry air
const int WET_VALUE = 1500;    // Sensor value in water

// --- Function to Read and Send Sensor Data ---
void sendSensorData()
{
  int rawValue = analogRead(SOIL_MOISTURE_PIN);
  int moisturePercent = map(rawValue, DRY_VALUE, WET_VALUE, 0, 100);
  moisturePercent = constrain(moisturePercent, 0, 100);

  Serial.print("Soil Moisture: ");
  Serial.print(rawValue);
  Serial.print(" => ");
  Serial.print(moisturePercent);
  Serial.println("%");

  Blynk.virtualWrite(V_MOISTURE, moisturePercent); // Send data to Blynk

  // --- Auto Mode Operation ---
  if (isAutoMode)
  {
    if (moisturePercent < THRESHOLD_MOISTURE)
    {
      digitalWrite(PUMP_PIN, RELAY_ON); // Turn pump ON
      isPumpOn = true;
      Blynk.virtualWrite(V_PUMP_SWITCH, 1); // Update Blynk switch
      Serial.println("Auto Mode: Soil is dry. Pump ON.");
      Blynk.logEvent("moisture_alert", "Soil moisture low! Pump turned ON automatically.");
    }
    else
    {
      digitalWrite(PUMP_PIN, RELAY_OFF); // Turn pump OFF
      isPumpOn = false;
      Blynk.virtualWrite(V_PUMP_SWITCH, 0); // Update Blynk switch
      Serial.println("Auto Mode: Soil is wet. Pump OFF.");
    }
  }
  else
  {
    // Manual mode - pump state is controlled from Blynk switch
    digitalWrite(PUMP_PIN, isPumpOn ? RELAY_ON : RELAY_OFF);
  }
}

// --- Handle Manual Pump Switch (V6) ---
BLYNK_WRITE(V_PUMP_SWITCH)
{
  if (!isAutoMode)  // Only works in manual mode
  {
    isPumpOn = param.asInt();
    digitalWrite(PUMP_PIN, isPumpOn ? RELAY_ON : RELAY_OFF);
    Serial.println(isPumpOn ? "Manual Mode: Pump ON" : "Manual Mode: Pump OFF");
  }
  else
  {
    // If user tries to toggle pump in auto mode, ignore it
    Blynk.virtualWrite(V_PUMP_SWITCH, isPumpOn);
    Serial.println("Ignored manual control - system in Auto Mode");
  }
}

// --- Handle Mode Switch (V4) ---
BLYNK_WRITE(V_MODE_SWITCH)
{
  isAutoMode = param.asInt();
  if (isAutoMode)
  {
    Serial.println("Switched to AUTO Mode");
    Blynk.virtualWrite(V_PUMP_SWITCH, 0); // Reset manual control
    isPumpOn = false;
    digitalWrite(PUMP_PIN, RELAY_OFF); // Ensure pump is OFF when switching to auto
  }
  else
  {
    Serial.println("Switched to MANUAL Mode");
  }
}

// --- Setup ---
void setup()
{
  Serial.begin(115200); // Changed from 9600 to 115200
  pinMode(PUMP_PIN, OUTPUT);
  digitalWrite(PUMP_PIN, RELAY_OFF); // Ensure pump is OFF initially

  Serial.println("Starting Smart Irrigation System...");
  Serial.println("Connecting to WiFi and Blynk...");

  Blynk.begin(auth, ssid, pass);
  
  // Wait for connection
  int attempts = 0;
  while (Blynk.connect() == false && attempts < 20) {
    Serial.print(".");
    delay(500);
    attempts++;
  }
  
  if (Blynk.connected()) {
    Serial.println("\nConnected to Blynk!");
  } else {
    Serial.println("\nFailed to connect to Blynk. Check credentials.");
  }

  timer.setInterval(3000L, sendSensorData); // Every 3 seconds

  // Initialize dashboard
  Blynk.virtualWrite(V_MODE_SWITCH, 1); // Start in Auto mode
  Blynk.virtualWrite(V_PUMP_SWITCH, 0);
  
  Serial.println("System Ready!");
  Serial.println("--------------------------------");
  
  // Test relay for 5 seconds
  Serial.println("Testing relay...");
  digitalWrite(PUMP_PIN, RELAY_ON);
  Serial.println("Relay should be ON now");
  delay(5000);
  digitalWrite(PUMP_PIN, RELAY_OFF);
  Serial.println("Relay should be OFF now");
  delay(2000);
}

// --- Main Loop ---
void loop()
{
  if (Blynk.connected()) {
    Blynk.run();
  } else {
    Serial.println("Blynk disconnected. Reconnecting...");
    Blynk.connect();
  }
  timer.run();
}