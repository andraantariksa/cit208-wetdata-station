#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
#include <dht.h>

String WIFI_AP = "";
String WIFI_PASS = "";
String API = "";
String HOST = "api.thingspeak.com";
String PORT = "80";

const int ESP_RX = 10;
const int ESP_TX = 11;
const int DHT_ANALOG_PIN = A0;
const int SOIL_MOISTURE_ANALOG_PIN = A1;
const int RAINDROP_ANALOG_PIN = A2;

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 5, 4, 6, 7, 3, POSITIVE);
dht DHT;
SoftwareSerial esp8266(ESP_RX,ESP_TX); 

int countTrueCommand;
int countTimeCommand; 

void lcdPrintData(int temperature, int humidity, int soil_moisture, int raindrop)
{
  lcd.print(String("T: ") + temperature + " H: " + humidity);
  lcd.setCursor(0, 1);
  lcd.print(String("SH: ") + soil_moisture + " R: " + raindrop);
}

void setup() {
  Serial.begin(9600);
  esp8266.begin(115200);
  
  lcd.begin(16, 2);
  lcd.clear();
  
  sendCommand("AT", 5, "OK");
  sendCommand("AT+CWMODE=1", 5, "OK");
  sendCommand("AT+CWJAP=\"" + WIFI_AP + "\",\""+ WIFI_PASS +"\"", 20, "OK");
}

void loop() {
  DHT.read11(DHT_ANALOG_PIN);
  int temperature = DHT.temperature;
  int humidity = DHT.humidity;
  int soil_moisture = analogRead(SOIL_MOISTURE_ANALOG_PIN);
  int raindrop = analogRead(RAINDROP_ANALOG_PIN);

  lcdPrintData(temperature, humidity, soil_moisture, raindrop);
  
  String request = "GET /update?api_key="+ API +"&field1=" + temperature + "&field2=" + humidity + "&field3=" + soil_moisture + "&field4=" + raindrop;
  
  sendCommand("AT+CIPMUX=1", 5, "OK");
  sendCommand("AT+CIPSTART=0,\"TCP\",\"" + HOST + "\"," + PORT, 15, "OK");
  sendCommand("AT+CIPSEND=0," + String(request.length() + 4), 4, ">");
  esp8266.println(request);
  delay(10000);
  countTrueCommand++;
  sendCommand("AT+CIPCLOSE=0", 5, "OK");
}

void sendCommand(String command, int maxTime, char readReplay[]) {
  boolean found = false;
  Serial.print(countTrueCommand);
  Serial.print(". at command => ");
  Serial.print(command);
  Serial.print(" ");
  while(countTimeCommand < (maxTime*1))
  {
    esp8266.println(command);
    if(esp8266.find(readReplay))
    {
      found = true;
      break;
    }
    countTimeCommand++;
  }
  
  if(found)
  {
    Serial.println("OYI");
    countTrueCommand++;
    countTimeCommand = 0;
  }
  else
  {
    Serial.println("Fail");
    countTrueCommand = 0;
    countTimeCommand = 0;
  }
}
