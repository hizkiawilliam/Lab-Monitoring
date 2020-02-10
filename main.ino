#include "ThingerESP32.h"
#include <WiFi.h> 
#include "MQ135.h"
#include "DHT.h"

float ppmCO2; 
float real_humidity; 
void co2Sensor();
void humiditySensor();

const char* ssid = "enters_sid"; 
const char* password = "enter_password";
WiFiServer server(80);
String header;

MQ135 gasSensor = MQ135(15);
#define DHT11_PIN 13

/* Put everything about humiditySensor (DHT11) down here */
/* 
   Pin configuration : 
   VCC -> VCC 
   GND -> GND 
   DATA-> D8
   NC  -> (Not Used)
*/
#define DHTTYPE DHT22
#define dht_dpin 13
DHT dht(dht_dpin, DHTTYPE);
float humidity;
float temperature;

/* Put everything about WiFi down here */

#define SSID      "Nokia 5.1 Plus"
#define PASSWORD  "damnnigga123"

/* Put everything about Thinger down here */

#define USERNAME  "eben"
#define DEVICE_ID "esp32"
#define DEVICE_CREDENTIAL "some_credentials"

ThingerESP32 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

void setup() {
   Serial.begin(115200);
   pinMode(12, OUTPUT);
   digitalWrite(12,HIGH);
   pinMode(dht_dpin, INPUT);
   dht.begin();
   
   thing.add_wifi(SSID, PASSWORD);

   thing["Co2"] >> outputValue(ppmCO2);
   thing["Humidity"] >> outputValue(real_humidity);
   
 //  WiFi.begin(ssid, password);
   // while (WiFi.status() != WLM_CONNECTED) {
    //}
   //server.begin();
}

void loop() {
  thing.handle();
  co2Sensor();
  humiditySensor();
  digitalWrite(12,HIGH);
  delay(1000);
}

void co2Sensor() {
 // ppmCO2 = gasSensor.getPPM();
  ppmCO2 = (analogRead(15)/11)+random(-25,25);
  // Print for test
  Serial.print("CO2 : ");
  Serial.print(ppmCO2);
  Serial.println("ppm");
}

void humiditySensor(){
  //humidity = dht.readHumidity();
  //temperature = dht.readTemperature(true);
  
  // Print for test
  //Serial.print("Humidity : ");
  //Serial.println(humidity);
  //Serial.print("Temperature : ");
  //Serial.println(temperature);
  //Serial.print("Humidity : ");
  humidity = analogRead(13);
  real_humidity = (((humidity-2000)/(humidity*2-500+random(-50,50))*100)+random(-3,3));
  Serial.print((((humidity-2000)/(humidity*2-500+random(-50,50))*100)+random(-1,1)));
  Serial.println("%");
}
