#include <DHT.h>                      //library for the DHT11 sensor
#include <LiquidCrystal_I2C.h>        //library for the LCD screen


#define DHTPIN 2                      // Pin 2 is the designated pin for the DHT11    
#define DHTTYPE DHT11                 // Specifies that we are using the DHT11 sensor      

DHT dht(DHTPIN, DHTTYPE);             // Initializes an object named 'dht', with parameters DHTPIN and DHTTYPE
const int potPin = A0;                // Connect the potentionmeter to this pin. This pin is used to read 				      // analog voltage values (0V-5V) using the ADC built into the 					      // arduino
const int fanPin1 = 3;                // Connect fan1 to this pin
const int fanPin2 = 4;                // Connect fan2 to this pin

LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD address and dimensions (I2C address, # of collumns, # of rows)

void setup() {
  dht.begin();                     // Initialize the DHT11 sensor
  pinMode(fanPin1, OUTPUT);        // Sets the fanPin1 to an output pin 
  pinMode(fanPin2, OUTPUT);        // Sets the fanPin2 to an output pin
  lcd.init();                      // Initialize the LCD
  lcd.backlight();                 // Turn on the backlight
  lcd.setCursor(0, 0);             // Setting the location for the print that comes after
  lcd.print("Vent Booster");     
  lcd.setCursor(0, 1);             // Setting the location for the prin that comes after 
  lcd.print("by Group 1");
  delay(2000);
  lcd.clear();
}

void loop() {
  int threshold = map(analogRead(potPin), 0, 1023, 60, 80); // Map potentiometer value to temperature range

  float temperature = (dht.readTemperature() * 1.8) + 32;   // Channge the measurement from Celsius to Farenheit
  float fan_speed = temperature - threshold;                // Variable to base the fan speed off of
  
  if (isnan(temperature)) {
    lcd.clear();                                            // Clears the screen
    lcd.setCursor(0, 0);
    lcd.print("Failed to read");
    lcd.setCursor(0, 1);
    lcd.print("temperature!");
    delay(2000);
    return;
  }

  // Fan speed control based on temperature. Prints the fan speed at the bottom
  if (temperature < threshold) {                // Fan should be off if the room is colder than the threshold
    analogWrite(fanPin1, 0);                    // Sets the PWM (Pulse Width Modulation) for fanPin1
    analogWrite(fanPin2, 0);                    // Sets the PWM (Pulse Width Modulation) for fanPin2
    lcd.setCursor(0, 1);  
    lcd.print("Fan OFF            ");
  } else if (fan_speed <= 2) {                  // Fan should be at 20% speed 
    analogWrite(fanPin1, 51);
    analogWrite(fanPin2, 51);
    lcd.setCursor(0, 1);
    lcd.print("Fan Speed: 20%   ");
  } else if (fan_speed <= 4 && fan_speed > 2) { // Fan should be at 40% speed
    analogWrite(fanPin1, 102);
    analogWrite(fanPin2, 102);
    lcd.setCursor(0, 1);
    lcd.print("Fan Speed: 40%   ");
  } else if (fan_speed <= 6 && fan_speed > 4) { // Fan should be at 60% speed
    analogWrite(fanPin1, 153);
    analogWrite(fanPin2, 153);
    lcd.setCursor(0, 1);
    lcd.print("Fan Speed: 60%   ");
  } else if (fan_speed <= 8 && fan_speed > 6) { // Fan should be at 80% speed
    analogWrite(fanPin1, 204);
    analogWrite(fanPin2, 204);
    lcd.setCursor(0, 1);
    lcd.print("Fan Speed: 80%   ");
  } else if (fan_speed > 10) {                  // Fan should be at full power
    analogWrite(fanPin1, 255);
    analogWrite(fanPin2, 255);
    lcd.setCursor(0, 1);
    lcd.print("Fan Speed: 100%   ");
  }
  
  // Prints the temperature measurement and the threshold measurement
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temperature);
  lcd.print("F  ");
  lcd.print("TH:");
  lcd.print(threshold);
  lcd.print("F");

  delay(3000);
}