/*
This example shows how to take simple range measurements with the VL53L1X. The
range readings are in units of mm.
*/

#include <Wire.h>
#include <VL53L1X.h>
#include <VL53L0X.h>

VL53L1X gen2;
VL53L0X gen1;

int gen1_shdn = 4;
int gen2_shdn = 5;

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

  Serial.print("gen 2 old address: ");
  Serial.println(gen2.getAddress());
  gen2.setAddress(0x30);
  Serial.print("gen 2 new address: ");
  Serial.println(gen2.getAddress());

  gen2.startContinuous(50);
}

void gen1_setup(){
  digitalWrite(gen1_shdn, LOW);
  delay(10);
  digitalWrite(gen1_shdn, HIGH);
  
  gen1.init();
  gen1.setTimeout(500);
  Serial.println("gen1 setup complete");
  gen1.startContinuous();

}

uint16_t gen2_read(){
  static uint16_t val = 0;
//  Serial.print("Gen2:");
  val = gen2.read();
//  Serial.print(val);
  if (gen2.timeoutOccurred()) { Serial.print("Gen2 TIMEOUT"); }
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
  pinMode(gen1_shdn, OUTPUT);
  pinMode(gen2_shdn, OUTPUT);
  digitalWrite(gen1_shdn, LOW);
  digitalWrite(gen2_shdn, LOW);
  gen2_setup();
  gen1_setup();
  // Start continuous readings at a rate of one measurement every 50 ms (the
  // inter-measurement period). This period should be at least as long as the
  // timing budget.
}

void loop()
{
  
  static uint16_t gen1_val = 0;
  static uint16_t gen2_val = 0;
  gen1_val = gen1_read();
  gen2_val = gen2_read();
  Serial.print("Gen1: ");
  Serial.print(gen1_val);
  Serial.print("  Gen2: ");
  Serial.println(gen2_val);
}
