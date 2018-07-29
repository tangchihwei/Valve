/*
This example shows how to take simple range measurements with the VL53L1X. The
range readings are in units of mm.
*/

#include <Wire.h>
#include <VL53L1X.h>

VL53L1X gen2;

void gen2_setup(){
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

  Serial.print("old address: ");
  Serial.println(gen2.getAddress());
  gen2.setAddress(0x30);
  Serial.print("new address: ");
  Serial.println(gen2.getAddress());

  gen2.startContinuous(50);
}



void setup()
{
  Serial.begin(9600);
  Wire.begin();
  Wire.setClock(400000); // use 400 kHz I2C

  gen2_setup();

  // Start continuous readings at a rate of one measurement every 50 ms (the
  // inter-measurement period). This period should be at least as long as the
  // timing budget.
}

void loop()
{
  Serial.print(gen2.read());
  if (gen2.timeoutOccurred()) { Serial.print("Gen2 TIMEOUT"); }

  Serial.println();
}