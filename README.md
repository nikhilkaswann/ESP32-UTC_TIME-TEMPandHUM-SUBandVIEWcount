# ESP32-UTC_TIME-TEMPandHUM-SUBandVIEWcount

This project uses an ESP32 microcontroller to create a simple dashboard that displays time, temperature/humidity, and YouTube channel statistics. The dashboard includes a menu system with navigation buttons.

## Requirements

- **Arduino IDE:** Make sure you have the Arduino IDE installed on your computer.
- **ESP32 board support:** Install the ESP32 board support in the Arduino IDE.
- **LiquidCrystal_I2C library:** Library for driving I2C LCD displays.
- **DHTesp library:** Library for DHT22 temperature and humidity sensor.
- **ArduinoJson library:** Library for parsing JSON data.
- **HTTPClient library:** Library for making HTTP requests.

## Setup

1. Clone or download the repository.
2. Open the Arduino IDE.
3. Install the required libraries via the Arduino Library Manager.
4. Connect your ESP32 board to your computer.
5. Select the correct board and port in the Arduino IDE.
6. Upload the code to your ESP32.

## Configuration

Replace `"YOUR_YOUTUBE_API_KEY"` and `"YOUR_YOUTUBE_CHANNEL_ID"` in the code with your actual YouTube API key and channel ID.

```cpp
const char* apiKey = "YOUR_YOUTUBE_API_KEY";
const char* channelId = "YOUR_YOUTUBE_CHANNEL_ID";
```
In this part of the code, you need to replace "YOUR_YOUTUBE_API_KEY" with your actual YouTube API key, and "YOUR_YOUTUBE_CHANNEL_ID" with your YouTube channel's ID.

YouTube API Key:

Obtain your YouTube API key from the Google Developers Console.
Create a project, enable the YouTube Data API v3, and generate an API key.
Replace "YOUR_YOUTUBE_API_KEY" with the generated API key.
YouTube Channel ID:

You can find your YouTube channel ID in the URL of your channel.
It usually looks like "UCxxxxxxxxxxxxxxxxxxxx" where "x" is a combination of letters and numbers.
Replace "YOUR_YOUTUBE_CHANNEL_ID" with your actual YouTube channel ID.
After making these changes, your code will be configured to fetch data from the specified YouTube channel.

## Usage

1. Power up your ESP32.
2. Use the up and down buttons to navigate through the menu.
3. Press the select button to execute the selected action.

## Menu Options

- **Time:** Displays the current time.
- **Humidity & Temperature:** Displays the current temperature and humidity.
- **Subscribers & Views:** Fetches and displays your YouTube channel's subscriber and view count.
- **Timer:** Placeholder option for future features.

## Contributors

- NIKHIL KASWAN

Feel free to contribute to this project by adding new features or improving existing ones!
