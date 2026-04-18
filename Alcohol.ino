#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize LCD (0x27 is common address)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pin definitions
int sensorPin = A0;
int relayPin = 7;
int buzzerPin = 8;

// Threshold value (adjust based on testing)
int threshold = 400;

void setup() {
  pinMode(relayPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  digitalWrite(relayPin, HIGH); // Motor ON initially
  digitalWrite(buzzerPin, LOW);

  Serial.begin(9600);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("BreatheLock");
  delay(2000);
  lcd.clear();
}

void loop() {
  int sensorValue = analogRead(sensorPin);

  Serial.print("Alcohol Value: ");
  Serial.println(sensorValue);

  lcd.setCursor(0, 0);
  lcd.print("Value: ");
  lcd.print(sensorValue);

  if (sensorValue > threshold) {
    // Alcohol detected
    digitalWrite(relayPin, LOW);   // Motor OFF
    digitalWrite(buzzerPin, HIGH); // Alarm ON

    lcd.setCursor(0, 1);
    lcd.print("ALCOHOL DETECT!");
  } 
  else {
    // Safe condition
    digitalWrite(relayPin, HIGH);  // Motor ON
    digitalWrite(buzzerPin, LOW);  // Alarm OFF

    lcd.setCursor(0, 1);
    lcd.print("SAFE TO DRIVE  ");
  }

  delay(1000);
}
