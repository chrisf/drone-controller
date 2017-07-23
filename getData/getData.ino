#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_FXOS8700.h>
#include <Adafruit_FXAS21002C.h>

//Assign I2C Ports
Adafruit_FXAS21002C gyro = Adafruit_FXAS21002C(0x0021002C);
Adafruit_FXOS8700 accelmag = Adafruit_FXOS8700(0x8700A, 0x8700B);

void setup() {

  //Initialize serial connection and wait for monitor
  Serial.begin(9600);
  while(!Serial){};
  
  //Initialize sensors
  gyro.begin();
  accelmag.begin(ACCEL_RANGE_4G); //Limit range to 4G ~ 40 M/S^2

  sensor_t gyroscope, accel, mag;

  //Get Sensor settings
  accelmag.getSensor(&accel,&mag);
  gyro.getSensor(&gyroscope);
}

void loop() {  
  //Declare a new sensor event
  sensors_event_t aevent, mevent, gevent;

  //Refresh event data from sensors
  accelmag.getEvent(&aevent, &mevent);
  gyro.getEvent(&gevent);

  
  //Access and print sensor data
  Serial.print("AX: " + String(aevent.acceleration.x));
  Serial.print("  AY: " + String(aevent.acceleration.y));
  Serial.print("  AZ: " + String(aevent.acceleration.z));
  
  Serial.print("  GX: " + String(gevent.gyro.x));
  Serial.print("  GY: " + String(gevent.gyro.y));
  Serial.println("  GZ: " + String(gevent.gyro.z));
  
  Serial.print("  MX: " + String(mevent.magnetic.x));
  Serial.print("  MY: " + String(mevent.magnetic.y));
  Serial.println("  MZ: " + String(mevent.magnetic.z));
  
  Serial.println();
  
  delay(5000);

}
