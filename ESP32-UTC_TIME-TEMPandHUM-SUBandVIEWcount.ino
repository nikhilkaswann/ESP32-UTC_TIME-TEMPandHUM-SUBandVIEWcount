#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <YoutubeApi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h> 
#include <DHTesp.h>
#include <HTTPClient.h>

const char* apiKey = "YOUR_YOUTUBE_API_KEY"; // Obtain from Google Developers Console
const char* channelId = "YOUR_YOUTUBE_CHANNEL_ID";

// Replace these placeholders with your actual WiFi credentials
const char* ssid = "YourWiFiSSID";
const char* password = "YourWiFiPassword";

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int DHT_PIN = 15;
DHTesp dhtSensor;

int upButton = 5;
int downButton = 18;
int selectButton = 19;
int menu = 1;
int Timer = 0;
int Timer_1 = 0;
int Timer2 = 0;
int Timer3 = 0;
 
#define NTP_SERVER     "pool.ntp.org"
#define UTC_OFFSET     0
#define UTC_OFFSET_DST 0


unsigned long api_mtbs = 1000; 
unsigned long api_lasttime;
long subs = 0;
String subs_count;
String view_count;

void spinner() {
  static int8_t counter = 0;
  const char* glyphs = "\xa1\xa5\xdb";
  lcd.setCursor(15, 1);
  lcd.print(glyphs[counter++]);
  if (counter == strlen(glyphs)) {
    counter = 0;
  }
}

void printLocalTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    lcd.setCursor(0, 1);
    lcd.println("Connection Err");
    return;
  }
  lcd.setCursor(0, 0);
  lcd.println("TIME:   ");
  lcd.setCursor(8, 0);
  lcd.println(&timeinfo, "%H:%M:%S");
  

  lcd.setCursor(0, 1);
  lcd.println(&timeinfo, "%d/%m/%Y   %a");
}

void subcount() {
  // Make an HTTP request to the YouTube Data API
  HTTPClient http;
  String url = "https://www.googleapis.com/youtube/v3/channels?part=statistics&id=" + String(channelId) + "&key=" + String(apiKey);
  http.begin(url);
  int httpCode = http.GET();

  if (httpCode > 0) {
    if (httpCode == HTTP_CODE_OK) {
      // Parse JSON response
      DynamicJsonDocument doc(1024);
      DeserializationError error = deserializeJson(doc, http.getString());

      if (!error) {
        long subscriberCount = doc["items"][0]["statistics"]["subscriberCount"].as<long>();
        Serial.println("Subscriber Count: " + String(subscriberCount));
        long viewCount = doc["items"][0]["statistics"]["viewCount"].as<long>();
        Serial.println("View Count: " + String(viewCount));
        lcd.setCursor(0, 0);
        lcd.print("sub: " );
        lcd.print(subscriberCount );
        lcd.setCursor(0, 1);
        lcd.print("view: ");
        lcd.print(viewCount );
      } else {
        Serial.println("Failed to parse JSON");
      }
    } else {
      Serial.println("HTTP request failed");
    }
  } else {
    Serial.println("HTTP request failed");
  }

  http.end();

   // Wait for 1 minute before making the next request
}
void setup(){
  Serial.begin(115200);
  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  lcd.begin();
  lcd.backlight();
  lcd.print("Connecting to ");
  lcd.setCursor(0, 1);
  lcd.print("WiFi ");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    spinner();
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  IPAddress ip = WiFi.localIP();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.println("Online");
  lcd.setCursor(0, 1);
  lcd.println("Updating time...");

  configTime(UTC_OFFSET, UTC_OFFSET_DST, NTP_SERVER);


  pinMode(upButton, INPUT_PULLUP);
  pinMode(downButton, INPUT_PULLUP);
  pinMode(selectButton, INPUT_PULLUP);
  updateMenu();


}
void updateMenu() {
  switch (menu) {
    case 0:
      menu ++;
      break;
    case 1:
      lcd.clear();
      lcd.print(">TIME");
      lcd.setCursor(0, 1);
      lcd.print(" HUM & TEMP");
      break;
    case 2:
      lcd.clear();
      lcd.print(" TIME");
      lcd.setCursor(0, 1);
      lcd.print(">HUM & TEMP");
      break;
    case 3:
      lcd.clear();
      lcd.print(">SUB & VIEW");
      lcd.setCursor(0, 1);
      lcd.print(" TIMER");
      break;
    case 4:
      lcd.clear();
      lcd.print(" SUB & VIEW");
      lcd.setCursor(0, 1);
      lcd.print(">TIMER");
      break;
    case 5:
      menu = 4;
      break;
  }
}

void loop() {
  if (!digitalRead(downButton)){
    menu++;
    updateMenu();
    delay(100);
    while (!digitalRead(downButton));
  }
  if (!digitalRead(upButton)){
    menu--;
    updateMenu();
    delay(100);
    while(!digitalRead(upButton));
  }
  if (!digitalRead(selectButton)){
    executeAction();
    updateMenu();
    delay(100);
    while (!digitalRead(selectButton));
  }
}

void executeAction() {
  switch (menu) {
    case 1:
    delay(1000);
      action1();
      break;
    case 2:
    delay(1000);
      action2();
      break;
    case 3:
    delay(1000);
      action3();
      break;
    case 4:
    delay(1000);
      action4();
      break;
  }
}

void temphum(){
  TempAndHumidity  data = dhtSensor.getTempAndHumidity();
  //Serial.println("Temp: " + String(data.temperature, 2) + "°C");
  //Serial.println("Humidity: " + String(data.humidity, 1) + "%");
  lcd.setCursor(0, 0);
  lcd.println("Temp: " + String(data.temperature, 2) + " C   ");
  lcd.setCursor(0, 1);
  lcd.println("Humidity: " + String(data.humidity, 1) + "% ");
}


void action1() {
  lcd.clear();
     while (digitalRead(selectButton)==HIGH) {
        printLocalTime();
        }
      while (!digitalRead(selectButton));
}
void action2() {
  lcd.clear();
   while (digitalRead(selectButton)==HIGH) {
      temphum();
        }
      while (!digitalRead(selectButton));
}
void action3() {
  lcd.clear();
     while (digitalRead(selectButton)==HIGH) {
        subcount();
        }
      while (!digitalRead(selectButton));
}
void action4() {
  lcd.clear();
     while (digitalRead(selectButton)==HIGH) {
        lcd.setCursor(0, 0);
        lcd.println("Nothing here");
        }
      while (!digitalRead(selectButton));
      delay(2000);
} 
