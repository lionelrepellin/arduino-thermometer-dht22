#include "DHT.h"
#define DHTPIN 8 // pin where the sensor is connected to

#define DHTTYPE DHT22 // DHT 22 (AM2302)

DHT dht(DHTPIN, DHTTYPE); // declare the sensor

// the led with the corresponding pin numbler
int blue = 10;
int green = 11;
int yellow = 12;
int red = 13;

void setup()
{
  // initialize monitor
  Serial.begin(9600);
  Serial.println("Start!");
  dht.begin();

  SetPinOutPut();
  SetPinStatus();
}

// set pin mode to output for all the leds
void SetPinOutPut()
{
  pinMode(blue, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(red, OUTPUT);
}

// set voltage status for all the leds
void SetPinStatus() 
{
  digitalWrite(blue, LOW);
  digitalWrite(green, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(red, LOW);
}

void loop()
{
  delay(2000);
 
  // the read of the sensor takes about 250ms
  // the read values can be up to 2 seconds old (the sensor is slow)
  float h = dht.readHumidity();//on lit l'hygrometrie

  // read the temperature (default is Celsius)
  float t = dht.readTemperature();
  
  // if the read failed, exit the loop
  if (isnan(h) || isnan(t))
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
 
  // calculation of the temperature index in Celsius (isFahreheit = false)
  // (the measure of temperature felt by the human skin)
  float hic = dht.computeHeatIndex(t, h, false);
    
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
 
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" °C\t");
  
  Serial.print("Temperature index: ");
  Serial.print(hic);
  Serial.println(" °C "); 

  // can replace t by hic
  SwitchLed(blue, t, 0, 20.0);
  SwitchLed(green, t, 20.0, 23.0);
  SwitchLed(yellow, t, 23.0, 26.0);
  SwitchLed(red, t, 26.0, 35.0);
}

// switch the led on/off
void SwitchLed(int led, float temp, float minTemp, float maxTemp) 
{
  if((temp >= minTemp && temp < maxTemp)  || temp >= maxTemp)
  {
    digitalWrite(led, HIGH);
  }
  else 
  {
    if(temp < minTemp)
    {
      digitalWrite(led, LOW);
    }  
  }
}

