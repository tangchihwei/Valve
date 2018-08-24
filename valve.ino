/*
This example shows how to take simple range measurements with the VL53L1X. The
range readings are in units of mm.
*/

#include <Wire.h>
#include <VL53L1X.h>
#include <VL53L0X.h>
#include "CRC_VCNL4200.h"

VL53L1X gen2;
VL53L0X gen1;
VL53L1X gen2_2;
CRC_VCNL4200 vcnl4200;

int gen1_shdn = 4;
int gen2_shdn = 5;
int gen2_2_shdn = 4;

void vshay_setup(){
  if(vcnl4200.exists()){
    Serial.println("VCNL4200 found");
    vcnl4200.initialize();
    Serial.println("VCNL4200 initialized");
  }
}

void gen2_setup(){
 digitalWrite(gen2_shdn, LOW);
 delay(10);
 digitalWrite(gen2_shdn, HIGH);
 gen2.setTimeout(500);
  if (!gen2.init())
  {
    Serial.println("Failed to detect and initialize gen2 sensor!");
    while (1);
  }
  // Use long distance mode and allow up to 50000 us (50 ms) for a measurement.
  // You can change these settings to adjust the performance of the sensor, but
  // the minimum timing budget is 20 ms for short distance mode and 33 ms for
  // medium and long distance modes. See the VL53L1X datasheet for more
  // information on range and timing limits.
  gen2.setDistanceMode(VL53L1X::Long);
  gen2.setMeasurementTimingBudget(50000);

//  Serial.print("gen 2 old address: ");
//  Serial.println(gen2.getAddress());
  gen2.setAddress(0x30);
//  Serial.print("gen 2 new address: ");
//  Serial.println(gen2.getAddress());

  gen2.startContinuous(50);
}

void gen2_2_setup(){
 digitalWrite(gen2_2_shdn, LOW);
 delay(10);
 digitalWrite(gen2_2_shdn, HIGH);
 gen2_2.setTimeout(500);
  if (!gen2_2.init())
  {
    Serial.println("Failed to detect and initialize gen2_2 sensor!");
    while (1);
  }
  // Use long distance mode and allow up to 50000 us (50 ms) for a measurement.
  // You can change these settings to adjust the performance of the sensor, but
  // the minimum timing budget is 20 ms for short distance mode and 33 ms for
  // medium and long distance modes. See the VL53L1X datasheet for more
  // information on range and timing limits.
  gen2_2.setDistanceMode(VL53L1X::Long);
  gen2_2.setMeasurementTimingBudget(50000);

//  Serial.print("gen 2 old address: ");
//  Serial.println(gen2.getAddress());
  // gen2.setAddress(0x30);
//  Serial.print("gen 2 new address: ");
//  Serial.println(gen2.getAddress());

  gen2_2.startContinuous(50);
}

void gen1_setup(){
  digitalWrite(gen1_shdn, LOW);
  delay(10);
  digitalWrite(gen1_shdn, HIGH);
  
  gen1.init();
  gen1.setTimeout(500);
//  Serial.println("gen1 setup complete");
  gen1.startContinuous();

}

uint16_t vshay_read(){
  static uint16_t val = 0;
  val = vcnl4200.getProximity();
  return val;
}

uint16_t gen2_read(){
  static uint16_t val = 0;
//  Serial.print("Gen2:");
  val = gen2.readRangeContinuousMillimeters();
//  Serial.print(val);
  if (gen2.timeoutOccurred()) { Serial.print("Gen2 TIMEOUT"); }
//  Serial.println();
  return val;
}

uint16_t gen2_2_read(){
  static uint16_t val = 0;
//  Serial.print("Gen2:");
  val = gen2_2.readRangeContinuousMillimeters();
//  Serial.print(val);
  if (gen2_2.timeoutOccurred()) { Serial.print("Gen2_2 TIMEOUT"); }
//  Serial.println();
  return val;
}

uint16_t gen1_read(){
  static uint16_t val = 0;
//  Serial.print("Gen1:");
  val = gen1.readRangeContinuousMillimeters();
//  Serial.print(val);
  if (gen1.timeoutOccurred()) { Serial.print(" Gen 1 TIMEOUT"); }
//  Serial.println();
  return val;
}

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  Wire.setClock(400000); // use 400 kHz I2C
  pinMode(gen2_2_shdn, OUTPUT);
  pinMode(gen2_shdn, OUTPUT);
  digitalWrite(gen2_2_shdn, LOW);
  digitalWrite(gen2_shdn, LOW);
  gen2_setup();
  // gen1_setup();
  gen2_2_setup();
  // Start continuous readings at a rate of one measurement every 50 ms (the
  // inter-measurement period). This period should be at least as long as the
  // timing budget.
}

void loop()
{
  
  static double sen1_val = 0;
  static double sen2_val = 0;
  static double sen3_val = 0;
  sen1_val = gen2_2_read()/25.4;
  sen2_val = gen2_read()/25.4;
  sen3_val = vshay_read();
  Serial.print("Sen1:");
  Serial.print(sen1_val);
  Serial.print(",Sen2:");
  Serial.print(sen2_val);
  Serial.print(",Sen3:");
  Serial.println(sen3_val);
}
