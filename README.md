# ESP32-UTC_TIME-TEMPandHUM-SUBandVIEWcount
This project uses an ESP32 microcontroller to create a simple dashboard that displays time, temperature/humidity, and YouTube channel statistics. The dashboard includes a menu system with navigation buttons.

Requirements
Arduino IDE - Make sure you have the Arduino IDE installed on your computer.
ESP32 board support - Install the ESP32 board support in the Arduino IDE.
LiquidCrystal_I2C library - Library for driving I2C LCD displays.
DHTesp library - Library for DHT22 temperature and humidity sensor.
ArduinoJson library - Library for parsing JSON data.
HTTPClient library - Library for making HTTP requests.

Setup
Clone or download the repository.
Open the Arduino IDE.
Install the required libraries via the Arduino Library Manager.
Connect your ESP32 board to your computer.
Select the correct board and port in the Arduino IDE.
Upload the code to your ESP32.
Configuration
Update the following variables in the code with your specific information:

cpp
Copy code
const char* apiKey = "YOUR_YOUTUBE_API_KEY";
const char* channelId = "YOUR_YOUTUBE_CHANNEL_ID";
Replace "YOUR_YOUTUBE_API_KEY" and "YOUR_YOUTUBE_CHANNEL_ID" with your actual YouTube API key and channel ID.

Usage
Power up your ESP32.
Use the up and down buttons to navigate through the menu.
Press the select button to execute the selected action.
Menu Options
Time: Displays the current time.
Humidity & Temperature: Displays the current temperature and humidity.
Subscribers & Views: Fetches and displays your YouTube channel's subscriber and view count.
Timer: Placeholder option for future features.

Contributors

NIKHIL KASWAN

Feel free to contribute to this project by adding new features or improving existing ones!
