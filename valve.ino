
int ain1 = 7;
int ain2 = 5;
int stby = 6;
int pwm = 4;
int trigPin = 9;
int echoPin = 10;

void turnOff() {
  digitalWrite(pwm, LOW);
  digitalWrite(ain1, LOW);
  digitalWrite(ain2, HIGH); //CCW
  digitalWrite(pwm, HIGH);
  delay(30);
  digitalWrite(pwm, LOW);
}

void turnOn () {
  digitalWrite(pwm, LOW);
  digitalWrite(ain2, LOW);
  digitalWrite(ain1, HIGH); //CW
  digitalWrite(pwm, HIGH);
  delay(30);
  digitalWrite(pwm, LOW);
  
}

void setup() {
  // put your setup code here, to run once:
  pinMode(ain1, OUTPUT);
  pinMode(ain2, OUTPUT);
  pinMode(stby, OUTPUT);
  pinMode(pwm, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  digitalWrite(ain1, LOW);
  digitalWrite(ain2, LOW);
  digitalWrite(stby, HIGH);
  digitalWrite(pwm, LOW);

  digitalWrite(trigPin, LOW);
  Serial.begin(9600);

}

void loop() {
  if (Serial.available()){
    if (Serial.read() == '1'){
      turnOn();
      Serial.println("On");
    }
    else{
      turnOff();
      Serial.println("Off");
    }
  }
  delay(1000);

}
