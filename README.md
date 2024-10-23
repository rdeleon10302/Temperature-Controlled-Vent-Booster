# Temperature Controlled Vent Booster
- This Arduino project controls fan speeds based on temperature readings, allowing users to set a custom temperature threshold using a potentiometer. The system uses NPN transistors to manage fan power and displays real-time data on an LCD.

# Features
- Controls two fans via NPN transistors based on temperature
- Adjustable temperature threshold using a potentiometer
- Displays temperature and fan speed on an LCD
# Components
- Arduino Mega
- DHT11 Temperature Sensor
- Potentiometer
- 2 NPN Transistors
- 2 Fans
- LCD Display (I2C)
- 12V Battery
# Setup
- Connect the DHT11 sensor to pin 2.
- Connect the potentiometer to pin A0.
- Connect the base of each NPN transistor to pins 3 and 4 to control the fans.
- Connect the fans' power supply to the battery through the transistors.
- Connect the LCD to the I2C bus.
# Usage
- Turn the potentiometer to set a temperature threshold between 60°F-80°F.
- Fans will turn on and adjust speed automatically based on the current temperature.
- The LCD displays the current temperature, threshold, and fan speed.
# How It Works
- The potentiometer sets a user-defined temperature threshold.
- The fans are controlled via NPN transistors, adjusting speed in relation to how much hotter it gets than the set threshold.
- The LCD provides real-time updates on both temperature and fan speed, offering a clear display of system operation.

