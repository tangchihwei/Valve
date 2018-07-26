#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X lox = Adafruit_VL53L0X();
int ain1 = 7;
int ain2 = 5;
int stby = 6;
int pwm = 4;
bool valveState;
int threshold = 25;

void turnOff() {
  digitalWrite(pwm, LOW);
  digitalWrite(ain1, LOW);
  digitalWrite(ain2, HIGH); //CCW
  digitalWrite(pwm, HIGH);
  delay(30);
  digitalWrite(pwm, LOW);
  valveState = false; //off
  Serial.println("valve off");
}

void turnOn () {
  digitalWrite(pwm, LOW);
  digitalWrite(ain2, LOW);
  digitalWrite(ain1, HIGH); //CW
  digitalWrite(pwm, HIGH);
  delay(30);
  digitalWrite(pwm, LOW);
  valveState = true; //on
  Serial.println("valve on");
}

void setup() {
  Serial.begin(115200);

  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }

  Serial.println("Adafruit VL53L0X test");
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while (1);
  }
  // power
  Serial.println(F("VL53L0X API Simple Ranging example\n\n"));

  pinMode(ain1, OUTPUT);
  pinMode(ain2, OUTPUT);
  pinMode(stby, OUTPUT);
  pinMode(pwm, OUTPUT);
  digitalWrite(ain1, LOW);
  digitalWrite(ain2, LOW);
  digitalWrite(stby, HIGH);
  digitalWrite(pwm, LOW);

  turnOff();

}


void loop() {
  VL53L0X_RangingMeasurementData_t measure;
  int dist = 0;

//  Serial.print("Reading a measurement... ");
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    dist = (measure.RangeMilliMeter) / 10; //cm
    Serial.print("Distance (cm): "); Serial.println(dist);
  } else {
    Serial.println(" out of range ");
  }
//    Serial.print("Distance (cm): "); Serial.print(dist);
//    Serial.print(" .  valve state: "); Serial.println(valveState);
  if (dist <= 10){
    dist = threshold+15;
  }
  Serial.print("Distance (cm): "); Serial.print(dist);
  Serial.print(" .  valve state: "); Serial.println(valveState);
  if ((dist >= threshold) && valveState == true) {
    turnOff();
  }
  else if (dist < threshold && valveState == false) {
    turnOn();
  }
  delay(100);
}
