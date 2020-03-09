#include <ThingSpeak.h>               // add thingspeak librery
#include <ESP8266WiFi.h>              // add wifi library
// DHT settings starts
#include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306.h"
#include "DHT.h"
#define DHTPIN 5     // what digital pin we're connected to
// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321 
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
DHT dht(DHTPIN, DHTTYPE);
SSD1306  display(0x3C, D3, D5);
float tValue;// 
float hValue;
WiFiClient  client;
unsigned long myChannelNumber = your_channel_id;                // Channel ID
const char * myWriteAPIKey = "your_api_key";      // Read API Key
                               

void setup()
{
  display.init();

  // display.flipScreenVertically();

  display.setContrast(255);

  printBuffer0();
  delay(3000);
  display.clear();
  printBuffer01();
  delay(3000);
  display.clear();

  
  dht.begin();
  Serial.begin(115200);
  Serial.println();

  WiFi.begin("wifi_name", "wifi_password");                 // write wifi name & password           

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
  ThingSpeak.begin(client);
}

void loop() 
{
  float c = dht.readTemperature();// Read temperature as Celsius (the default)
  float h = dht.readHumidity();// Reading humidity 
  float f = dht.readTemperature(true);// Read temperature as Fahrenheit (isFahrenheit = true)
  delay(100);
  String Hu=" %\t";
  String Tc=" *C";

  Serial.print("Humidity: "); 
  Serial.println(h+Hu);
  tValue =c;
  delay(400);
  Serial.print("Temperature: "); 
  Serial.println(c+Tc);
  hValue =h;
  delay(400);

  display.clear();
  display.setLogBuffer(2, 30);
  display.setFont(ArialMT_Plain_10);

  display.print("Temperature: "); 
  display.print(tValue);
  display.println(" *C");
  display.print("Humidity: ");
  display.print(hValue);
  display.println(" %");

    
    // Draw it to the internal screen buffer
    display.drawLogBuffer(0, 0);
    // Display it on the screen
    display.display();
    delay(4000);
     if(tValue >= 20){                                   // condition on a tempeture limit if temp is over limit we have an alert
    
    Serial.println("temperature issue");
    display.println(" temperature over limit");
   

    display.clear();
    printBuffer03();
    delay(3000);
    display.clear();

     }
  int x0 = ThingSpeak.writeField(myChannelNumber, 1, tValue, myWriteAPIKey); // sending tempeture values to the first channel


  if(x0 == 200){
    Serial.println("Channel-1 update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x0));
  }
  
  int x1 = ThingSpeak.writeField(myChannelNumber, 2, hValue, myWriteAPIKey); // sending humidity values to the second channel

   if(x1 == 200){
    Serial.println("Channel-2 update successful.");                                     // this is for know if our data is up to the thingspeak or not u can find more details in the library file
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x1));
  }


}