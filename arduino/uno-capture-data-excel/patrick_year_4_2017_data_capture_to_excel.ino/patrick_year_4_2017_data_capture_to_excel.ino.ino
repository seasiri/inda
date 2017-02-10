#include <Wire.h>
#include "TSL2561.h"
TSL2561 tsl(TSL2561_ADDR_FLOAT); 
#include "DHT.h"
#define DHTPIN 3     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE);
void setup(void) {
  Serial.begin(9600);
  dht.begin();
  Serial.println("id,photocell,humidity,celcius,lux,ir,spectrum");  
  // You can change the gain on the fly, to adapt to brighter/dimmer light situations
  //tsl.setGain(TSL2561_GAIN_0X);         // set no gain (for bright situtations)
  tsl.setGain(TSL2561_GAIN_16X);      // set 16x gain (for dim situations)
  // Changing the integration time gives you a longer time over which to sense light
  // longer timelines are slower, but are good in very low light situtations!
  tsl.setTiming(TSL2561_INTEGRATIONTIME_13MS);  // shortest integration time (bright light)
  //tsl.setTiming(TSL2561_INTEGRATIONTIME_101MS);  // medium integration time (medium light)
  //tsl.setTiming(TSL2561_INTEGRATIONTIME_402MS);  // longest integration time (dim light)
}
int mq7=0;
int photo=0;
int dht22=0;
int i=0;
void loop(void) {
  // This can take 13-402 milliseconds! Uncomment whichever of the following you want to read
  uint16_t x = tsl.getLuminosity(TSL2561_VISIBLE);     
  //uint16_t x = tsl.getLuminosity(TSL2561_FULLSPECTRUM);
  //uint16_t x = tsl.getLuminosity(TSL2561_INFRARED);
  
  // More advanced data read example. Read 32 bits with top 16 bits IR, bottom 16 bits full spectrum
  // That way you can do whatever math and comparisons you want!
  uint32_t lum = tsl.getFullLuminosity();
  uint16_t ir, full;
  ir = lum >> 16;
  full = lum & 0xFFFF;
  Serial.print(i);
  Serial.print(",");
  //PHOTO
  photo=analogRead(A1);
  photo = map(photo, 0, 1023, 1023, 0);
  Serial.print(photo);
  Serial.print(",");
  /*MQ7
  mq7=analogRead(A2);
  Serial.print(mq7);
  Serial.print(",");*/
  //Humid
  float h = dht.readHumidity();
  Serial.print(h);
  Serial.print(",");
  //TEMP
  float t = dht.readTemperature();
  Serial.print(t);  
  Serial.print(",");
  Serial.print(tsl.calculateLux(full, ir)); 
  Serial.print(",");
  Serial.print(ir);  
  Serial.print(",");
  Serial.println(full);   
  delay(1000); 
  i++;
}
