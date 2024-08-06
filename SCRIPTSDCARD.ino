#include <WiFi.h>
#include <DHT.h>
#include "time.h"
#include <ESP_Google_Sheet_Client.h>
#include <GS_SDHelper.h>
#include "HX710B.h"
#include <WiFiClientSecure.h>
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include "Base64.h"
#include "FS.h"
#include "SD_MMC.h"
#include "esp_camera.h"
String ssid = "";
String password = "";
int delayValue = 0;
const int gpioPin = 14;
const char* myDomain = "script.google.com";
#define PROJECT_ID "test-environmentdatacapturing"
#define CLIENT_EMAIL "test-environmentdatacapturing@test-environmentdatacapturing.iam.gserviceaccount.com"
const char PRIVATE_KEY[] PROGMEM = "-----BEGIN PRIVATE KEY-----\nMIIEvgIBADANBgkqhkiG9w0BAQEFAASCBKgwggSkAgEAAoIBAQClgdyAYI13DC4B\nq1l/sVFuNHy+2ii4I4Yrr+4dswGBBiT8gMLGeYHfr5ZuNhtoQjfl5cbsSCCf9zOm\n2BAgAlOywT8pEYrkilloSgo15J/+jqKe837E8glwiBLrlb2cukWgbnsImLUC/Jn6\nsbDrIBRJq9LlLOC8MD4s8SXKSwUiPjn3QXjU7ugLjyZ7O2fPIf2EAFA2u1y0zpt6\nQwlB0aXJrt8KCcVifAcFrgRF/qn5laoylM60rteefdgqJsiTaYKuP9w41mQD65Es\nvnqMB96khtq6aNfXU2hur8g4GXj3tx9rSF/dXn1z3eYbBW0wUUQHS21BkKus5YwC\nDap+Sw3DAgMBAAECggEAE20CFgP/Jq1vIEgIhFnUyR7E/jD58t73NQfRvCT8tLRQ\nFrOq6NkYeso6WauPx6AaEn7ykbIc44RZc32hquLLCHdGdAoN537WOUzov47wOSnB\nrEQVKYWPwRMKRszNCWkS7154TLfWax197zRNo9NLPk26E6cS+6jylfDPSDFKTsyW\n39NSTgEO3IykI99vUYhep4iH6amxvc48F13GUSUkK757xXBQz+VwyTPCZJrWs6s3\nmwZBJrRirGpQIugVrpYAPOMK85vPWUDdaaamkcGMpPM4NkO9evr0AfXjwbkWRvjS\nRytJyZZseAsmD8dXM8vUavsmZE7L9+CoFgd5rjJd2QKBgQDay563d11UbPJAmxO2\ngKCG7J0R2N6sJHnoF9ibxauQRX803w+Xfgur0jZoba9zcyObgd8FQiOEXrECOAdM\nGRQbJGgELvjSNApPGzEbFEW1+MF1si2PTX5Dt44izOblb68siwFEXwM3usy4QXZC\nVvRHra/xXka+HDl3wDeQd8SoqQKBgQDBpo6FnbA12nqj7fsLvJjlzT8E/AN1kYCE\noJriOZPtYj2JY5nwpiJ9ffEyQXI94UP1zKdhs7kcvgGW3b4LEB41eLSTzulKlA0I\nf4U2Ow5iyNRe/2+dUDy2jF6IBzjmTFx2SloZ2a6+aRyw0SdSSDQG3hFGF1VYW1dl\n2A1HjDHqiwKBgQDMmZ7pR+jxuxNq0NnFT1FN+tQCzX+lEFMjc7EuMdH2jtaetXza\nGJeHbINOckugtWn10KOiQi/+Z6I1Rfmk8sq3evr99oLd5qZBRVdNUE7EFUOr8Rvj\npv7NCkgTSPMeWKtCBxb/Pa4/niI0p5qT/MZghQ5DsvqKatBeqFQNd8JiSQKBgG+7\nHt5fJk1cOoidBc02yu1EaAkDMyfBhOqBE/xVBlHf7et4aVidMqc/ZEv/0N99Os32\nf9jybmr0Aky+sikF6rglZeMmbhpWo9J0aTLqDhnXEBmjvg2BPxaAlQZdTGosQukJ\na0UhAR7h3Oj0NIDYIhSYSlUrn1V0lk+vwbG3ZRGTAoGBAMYghS0uajE1r+xV8LoC\nvVqTWQ2oaw/+BrdFdVoJjBn4w1NgF+f2ixQfwjGxhEk0dpf8e/dKz3AIfVWumnEn\nVyRGTP/QmLO+wsTVuTWDh7Yrfq+HhlhXN6jZC4cNUfVdUV2ANovxqKGcOBYO0oEM\nBs5XJD7QSb67tBqljQ/dL8as\n-----END PRIVATE KEY-----\n";
String myFilename = "filename=Test-EnvironmentalDataCapturing-Images.jpg";
String mimeType = "&mimetype=image/jpeg";
String myImage = "&data=";
int waitingTime = 10000;
String spreadsheetUrl = "";
String spreadsheetId;
String ScriptDriveUrl = "";
String myScript;
void readFile(fs::FS &fs, const char * path){
  Serial.printf("Reading file: %s\n", path);

  File file = fs.open(path);
  if(!file || file.isDirectory()){
    Serial.println("Failed to open file for reading");
    return;
  }

  Serial.println("ssid:");
  ssid = ""; // Clear the variable before reading new content
  while(file.available()){
    ssid += (char)file.read();
  }
  file.close();

  // Print the content stored in the variable
  Serial.println(ssid);
}
void readFile1(fs::FS &fs, const char * path){
  Serial.printf("Reading file: %s\n", path);

  File file = fs.open(path);
  if(!file || file.isDirectory()){
    Serial.println("Failed to open file for reading");
    return;
  }

  Serial.println("password:");
  password = ""; // Clear the variable before reading new content
  while(file.available()){
    password += (char)file.read();
  }
  file.close();

  // Print the content stored in the variable
  Serial.println(password);
}
void readDelayFromFile(fs::FS &fs, const char * path) {
  Serial.printf("Reading file: %s\n", path);

  File file = fs.open(path);
  if(!file || file.isDirectory()){
    Serial.println("Failed to open file for reading");
    return;
  }

  Serial.println("Reading delay value from file:");
  String delayString = ""; // Clear the variable before reading new content
  while(file.available()){
    delayString += (char)file.read();
  }
  file.close();

  // Convert the string to an integer
  delayValue = delayString.toInt();

  // Print the delay value
  Serial.print("Delay value: ");
  Serial.println(delayValue);
}
void readFile2(fs::FS &fs, const char * path){
  Serial.printf("Reading file: %s\n", path);

  File file = fs.open(path);
  if(!file || file.isDirectory()){
    Serial.println("Failed to open file for reading");
    return;
  }

  Serial.println("ScriptDriveUrl:");
  ScriptDriveUrl = ""; // Clear the variable before reading new content
  while(file.available()){
    ScriptDriveUrl += (char)file.read();
  }
  file.close();

  // Print the content stored in the variable
  Serial.println(ScriptDriveUrl);
}
void readFile3(fs::FS &fs, const char * path){
  Serial.printf("Reading file: %s\n", path);

  File file = fs.open(path);
  if(!file || file.isDirectory()){
    Serial.println("Failed to open file for reading");
    return;
  }

  Serial.println("spreadsheetUrl:");
  spreadsheetUrl = ""; // Clear the variable before reading new content
  while(file.available()){
    spreadsheetUrl += (char)file.read();
  }
  file.close();

  // Print the content stored in the variable
  Serial.println(spreadsheetUrl);
}
String extractMyScriptFromUrl(String url) {
  int startIndex = url.indexOf("/macros/");
  if (startIndex == -1) {
    Serial.println("Error: Invalid DriveUrl format.");
    return "";
  }
  return url.substring(startIndex);
}
String extractSpreadsheetId(String url)
{
  int idStart = url.indexOf("/d/") + 3;
  int idEnd = url.indexOf("/edit");
  return url.substring(idStart, idEnd);
}
#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27
#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

unsigned long lastTime = 0;
//unsigned long timerDelay = 10;
void tokenStatusCallback(TokenInfo info);
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
float temp;
float hum;
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 19800;
const int daylightOffset_sec = 0;
const int DOUT = 13;   
const int SCLK = 12;   
const int GAIN = 128;  
HX710B pressure_sensor;
float pressurePascal;
float pressureATM;
float pressuremmHg;
float pressurePSI;
String getTimestamp()
{
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo))
  {
    return "Failed to obtain time";
  }
  char timeStringBuff[50];
  strftime(timeStringBuff, sizeof(timeStringBuff), "%Y-%m-%d %H:%M:%S", &timeinfo);
  return String(timeStringBuff);
}
void setup() 
{
  pinMode(gpioPin, OUTPUT);
  //pinMode(gpioPin1, OUTPUT);
  Serial.begin(115200);
  
  if(!SD_MMC.begin()){
    Serial.println("Card Mount Failed");
    return;
  }
  
  readFile(SD_MMC, "/ssid.txt");
  readFile1(SD_MMC, "/password.txt");
  readFile2(SD_MMC, "/ScriptDriveUrl.txt");
  readFile3(SD_MMC, "/spreadsheetUrl.txt");
  readDelayFromFile(SD_MMC, "/delay.txt"); 
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
  //digitalWrite(gpioPin, LOW); (Transisitor Purpose)
  WiFi.mode(WIFI_STA);
  //WiFi.setAutoReconnect(true);
  Serial.println("");
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("STAIP address: ");
  Serial.println(WiFi.localIP()); 
  
  Serial.println("");
  
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  config.frame_size = FRAMESIZE_VGA;  // UXGA|SXGA|XGA|SVGA|VGA|CIF|QVGA|HQVGA|QQVGA
  config.jpeg_quality = 10;
  config.fb_count = 1;
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo))
  {
    Serial.println("Failed to obtain time");
        ESP.restart();
  }
  Serial.println(&timeinfo, "%Y-%m-%d %H:%M:%S");
  dht.begin();
  pressure_sensor.begin(DOUT, SCLK, GAIN);
  spreadsheetId = extractSpreadsheetId(spreadsheetUrl);
  myScript = extractMyScriptFromUrl(ScriptDriveUrl);
  GSheet.printf("ESP Google Sheet Client v%s\n\n", ESP_GOOGLE_SHEET_CLIENT_VERSION);
  GSheet.setTokenCallback(tokenStatusCallback);
  GSheet.setPrerefreshSeconds(10 * 60);
  GSheet.begin(CLIENT_EMAIL, PROJECT_ID, PRIVATE_KEY);
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) 
  {
    Serial.printf("Camera init failed with error 0x%x", err);
    delay(1000);
    ESP.restart();
  }
 digitalWrite(gpioPin, HIGH);
 Serial.println("check!!!!!!!!!!!!!!!!!!");
 delay(1000);
}
boolean enviar = true;
void loop()
{
  //digitalWrite(gpioPin1, HIGH);
  //Serial.println("check!!!!!!!!!!!!!!!!!!");
  //delay(1000);
  //if(enviar) {
  bool ready = GSheet.ready();
  if (ready && millis() - lastTime > (delayValue*1000))
  {
    lastTime = millis();
    FirebaseJson response;
    Serial.println("\nAppend spreadsheet values...");
    Serial.println("----------------------------");
    FirebaseJson valueRange;
    temp = dht.readTemperature();
    hum = dht.readHumidity();
    if (isnan(temp) || isnan(hum))
    {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }
    if (pressure_sensor.is_ready()) 
    {
      pressurePascal = pressure_sensor.pascal();
      pressureATM = pressure_sensor.atm();
      pressuremmHg = pressure_sensor.mmHg();
      pressurePSI = pressure_sensor.psi();
    } 
    else 
    {
      Serial.println("Pressure sensor not found.");
      return;
    }
    String timestamp = getTimestamp();
    Serial.print("Timestamp: ");
    Serial.println(timestamp);
    valueRange.add("majorDimension", "COLUMNS");
    valueRange.set("values/[0]/[0]", timestamp);
    valueRange.set("values/[1]/[0]", temp);
    valueRange.set("values/[2]/[0]", hum);
    valueRange.set("values/[3]/[0]", pressurePascal);
    valueRange.set("values/[4]/[0]", pressureATM);
    valueRange.set("values/[5]/[0]", pressuremmHg);
    valueRange.set("values/[6]/[0]", pressurePSI);
    bool success = GSheet.values.append(&response /* returned response */, spreadsheetId.c_str() /* spreadsheet Id to append */, "Sheet1!A1" /* range to append */, &valueRange /* data range to append */);
    if (success)
    {
      response.toString(Serial, true);
      valueRange.clear();
    }
    else
    {
      Serial.println(GSheet.errorReason());
    }
    Serial.println();
    Serial.println(ESP.getFreeHeap());
    saveCapturedImage();
    enviar = false;
    
  //}
  }
}
void tokenStatusCallback(TokenInfo info) 
{
  if (info.status == token_status_error)
  {
    GSheet.printf("Token info: type = %s, status = %s\n", GSheet.getTokenType(info).c_str(), GSheet.getTokenStatus(info).c_str());
    GSheet.printf("Token error: %s\n", GSheet.getTokenError(info).c_str());
  }
  else
  {
    GSheet.printf("Token info: type = %s, status = %s\n", GSheet.getTokenType(info).c_str(), GSheet.getTokenStatus(info).c_str());
  }
}
void saveCapturedImage() 
{
  Serial.println(myScript);
  Serial.println("Connect to " + String(myDomain));
  WiFiClientSecure client;
  client.setInsecure();
  if (client.connect(myDomain, 443)) 
  {
    Serial.println("Connection successful");
    camera_fb_t * fb = NULL;
    fb = esp_camera_fb_get();  
    if(!fb) 
    {
      Serial.println("Camera capture failed");
      delay(1000);
      ESP.restart();
      return;
    }
    char *input = (char *)fb->buf;
    char output[base64_enc_len(3)];
    String imageFile = "";
    for (int i=0;i<fb->len;i++) 
    {
      base64_encode(output, (input++), 3);
      if (i%3==0) imageFile += urlencode(String(output));
    }
    String Data = myFilename+mimeType+myImage;
    esp_camera_fb_return(fb);
    Serial.println("Send a captured image to Google Drive.");
    client.println("POST " + myScript + " HTTP/1.1");
    client.println("Host: " + String(myDomain));
    client.println("Content-Length: " + String(Data.length()+imageFile.length()));
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.println();
    client.print(Data);
    int Index;
    for (Index = 0; Index < imageFile.length(); Index = Index+1000) 
    {
      client.print(imageFile.substring(Index, Index+1000));
    }
    Serial.println("Waiting for response.");
    long int StartTime=millis();
    while (!client.available()) 
    {
      Serial.print(".");
      delay(100);
      if ((StartTime+waitingTime) < millis()) 
      {
        Serial.println();
        Serial.println("No response.");
        //If you have no response, maybe need a greater value of waitingTime
        break;
      }
    }
    Serial.println();   
    while (client.available()) 
    {
      Serial.print(char(client.read()));
    }  
  } 
  else 
  {         
    Serial.println("Connected to " + String(myDomain) + " failed.");
  }
  client.stop();
}
//https://github.com/zenmanenergy/ESP8266-Arduino-Examples/
String urlencode(String str)
{
    String encodedString="";
    char c;  
    char code0;
    char code1;
    char code2;
    for (int i =0; i < str.length(); i++)
    {
      c=str.charAt(i);
      if (c == ' ')
      {
        encodedString+= '+';
      } 
      else if (isalnum(c))
      {
        encodedString+=c;
      } 
      else
      {
        code1=(c & 0xf)+'0';
        if ((c & 0xf) >9)
        {
            code1=(c & 0xf) - 10 + 'A';
        }
        c=(c>>4)&0xf;
        code0=c+'0';
        if (c > 9)
        {
            code0=c - 10 + 'A';
        }
        code2='\0';
        encodedString+='%';
        encodedString+=code0;
        encodedString+=code1;
        //encodedString+=code2;
      }
      yield();
    }
    return encodedString;
}
