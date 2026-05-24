/*
  -------------------------------------------------------
  IOT Based Smart Air Quality Management System
  -------------------------------------------------------
  Developed By : Pranjal Jawalkar
  Platform     : ESP32 + Blynk IoT

  Features:
  - AQI Monitoring
  - Gas Detection
  - Temperature & Humidity Monitoring
  - LCD Display
  - Automatic Fan Control
  - LED Status Indicators
  - Real-Time IoT Dashboard
  -------------------------------------------------------
*/

#define BLYNK_TEMPLATE_ID "TMPL3uJhSpM_D"
#define BLYNK_TEMPLATE_NAME "Air monitoring system"
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// =====================================================
// BLYNK CONFIGURATION
// =====================================================
char auth[] = "YOUR_BLYNK_AUTH_TOKEN";
char ssid[] = "YOUR_WIFI_NAME";
char pass[] = "YOUR_WIFI_PASSWORD";

// =====================================================
// LCD CONFIGURATION
// =====================================================
LiquidCrystal_I2C lcd(0x27, 16, 2);

// =====================================================
// SENSOR PINS
// =====================================================
const int dustPin = 34;
const int dustLEDPin = 5;
const int mqPin = 35;

// =====================================================
// LED STATUS PINS
// =====================================================
const int greenLED = 25;
const int yellowLED = 26;
const int redLED = 27;

// =====================================================
// RELAY PIN
// =====================================================
const int relayPin = 33;

// =====================================================
// DHT SENSOR CONFIGURATION
// =====================================================
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// =====================================================
// FUNCTION DECLARATIONS
// =====================================================
int calculateAQI(int sensorValue);
void updateLEDsAndFan(int aqi);
void displayData(int aqi, float humidity, float temperature, String status);
String getAirQualityStatus(int aqi);

// =====================================================
// SETUP FUNCTION
// =====================================================
void setup()
{
    Serial.begin(115200);

    // Pin Configuration
    pinMode(dustLEDPin, OUTPUT);

    pinMode(greenLED, OUTPUT);
    pinMode(yellowLED, OUTPUT);
    pinMode(redLED, OUTPUT);

    pinMode(relayPin, OUTPUT);

    // Fan OFF initially
    digitalWrite(relayPin, HIGH);

    // LCD Initialization
    lcd.init();
    lcd.backlight();

    // DHT Initialization
    dht.begin();

    // Blynk Connection
    Blynk.begin(auth, ssid, pass);

    lcd.setCursor(0, 0);
    lcd.print("System Starting");

    delay(2000);
    lcd.clear();
}

// =====================================================
// MAIN LOOP
// =====================================================
void loop()
{
    Blynk.run();

    // Dust Sensor Reading
    digitalWrite(dustLEDPin, LOW);
    delayMicroseconds(280);

    int dustValue = analogRead(dustPin);

    delayMicroseconds(40);
    digitalWrite(dustLEDPin, HIGH);
    delayMicroseconds(9680);

    // Gas Sensor Reading
    int gasValue = analogRead(mqPin);

    // DHT Sensor Reading
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();

    // Error Handling
    if (isnan(humidity) || isnan(temperature))
    {
        Serial.println("DHT Sensor Error!");
        return;
    }

    // AQI Calculation
    int dustAQI = calculateAQI(dustValue);
    int gasAQI = calculateAQI(gasValue);

    int finalAQI = max(dustAQI, gasAQI);

    // Air Quality Status
    String status = getAirQualityStatus(finalAQI);

    // Update Outputs
    updateLEDsAndFan(finalAQI);

    // LCD Display
    displayData(finalAQI, humidity, temperature, status);

    // Serial Monitor
    Serial.println("============================");
    Serial.print("Dust Value : ");
    Serial.println(dustValue);

    Serial.print("Gas Value  : ");
    Serial.println(gasValue);

    Serial.print("AQI        : ");
    Serial.println(finalAQI);

    Serial.print("Humidity   : ");
    Serial.println(humidity);

    Serial.print("Temperature: ");
    Serial.println(temperature);

    Serial.print("Status     : ");
    Serial.println(status);

    // Blynk Upload
    Blynk.virtualWrite(V0, finalAQI);
    Blynk.virtualWrite(V1, temperature);
    Blynk.virtualWrite(V2, humidity);

    delay(2000);
}

// =====================================================
// AQI CALCULATION FUNCTION
// =====================================================
int calculateAQI(int sensorValue)
{
    return map(sensorValue, 0, 4095, 0, 500);
}

// =====================================================
// AIR QUALITY STATUS FUNCTION
// =====================================================
String getAirQualityStatus(int aqi)
{
    if (aqi < 100)
    {
        return "Air is Good";
    }
    else if (aqi < 200)
    {
        return "Moderate Air";
    }
    else
    {
        return "Poor Air";
    }
}

// =====================================================
// LED + FAN CONTROL FUNCTION
// =====================================================
void updateLEDsAndFan(int aqi)
{
    if (aqi < 100)
    {
        digitalWrite(greenLED, HIGH);
        digitalWrite(yellowLED, LOW);
        digitalWrite(redLED, LOW);

        digitalWrite(relayPin, HIGH); // Fan OFF
    }
    else if (aqi < 200)
    {
        digitalWrite(greenLED, LOW);
        digitalWrite(yellowLED, HIGH);
        digitalWrite(redLED, LOW);

        digitalWrite(relayPin, LOW); // Fan ON
    }
    else
    {
        digitalWrite(greenLED, LOW);
        digitalWrite(yellowLED, LOW);
        digitalWrite(redLED, HIGH);

        digitalWrite(relayPin, LOW); // Fan ON
    }
}

// =====================================================
// LCD DISPLAY FUNCTION
// =====================================================
void displayData(int aqi, float humidity, float temperature, String status)
{
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("AQI:");
    lcd.print(aqi);

    lcd.print(" H:");
    lcd.print((int)humidity);

    lcd.setCursor(0, 1);
    lcd.print("T:");
    lcd.print((int)temperature);

    lcd.print(" ");
    lcd.print(status);
}