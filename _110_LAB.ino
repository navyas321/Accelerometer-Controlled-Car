/**************************************************************************/
/*!
    @file     Adafruit_MMA8451.h
    @author   K. Townsend (Adafruit Industries)
    @license  BSD (see license.txt)

    This is an example for the Adafruit MMA8451 Accel breakout board
    ----> https://www.adafruit.com/products/2019

    Adafruit invests time and resources providing this open source code,
    please support Adafruit and open-source hardware by purchasing
    products from Adafruit!

    @section  HISTORY

    v1.0  - First release
*/
/**************************************************************************/

#include <Wire.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>

Adafruit_MMA8451 mma = Adafruit_MMA8451();

void setup(void) {
  Serial.begin(9600);
  
  Serial.println("Adafruit MMA8451 test!");
  

  if (! mma.begin()) {
    Serial.println("Couldnt start");
    while (1);
  }
  Serial.println("MMA8451 found!");
  
  mma.setRange(MMA8451_RANGE_2_G);
  
  Serial.print("Range = "); Serial.print(2 << mma.getRange());  
  Serial.println("G");
  
  pinMode(11, OUTPUT);
  pinMode(9, OUTPUT);
}

void loop() {
  // Read the 'raw' data in 14-bit counts
  mma.read();
  
  /* Get a new sensor event */ 
  sensors_event_t event; 
  mma.getEvent(&event);

  /* Display the results (acceleration is measured in m/s^2) */
  Serial.print("X: \t"); Serial.print(event.acceleration.x); Serial.print("\t");
  Serial.print("Y: \t"); Serial.print(event.acceleration.y); Serial.print("\t");
  //Serial.print("Z: \t"); Serial.print(event.acceleration.z); Serial.print("\t");
  Serial.println("m/s^2 ");

  int rightMotorVal = 120 - event.acceleration.y * 10 + event.acceleration.x * 10;
  int leftMotorVal = 120 - event.acceleration.y * 10 - event.acceleration.x * 10;

  //Serial.print("

  if(rightMotorVal > 255)
    analogWrite(11, 255);
  else if(rightMotorVal < 0)
    analogWrite(11, 0);
  else
    analogWrite(11, rightMotorVal);
    
  if(leftMotorVal > 255)
    analogWrite(9, 255);
  else if(leftMotorVal < 0)
    analogWrite(9, 0);
  else
    analogWrite(9, leftMotorVal);
  
  Serial.println();
  delay(10);
  
}
