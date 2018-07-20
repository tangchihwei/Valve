
int ain1 = 7;
int ain2 = 5;
int stby = 6;
int pwm = 4;
int trigPin = 9;
int echoPin = 10;
int threshold = 90;
bool valveState;

void turnOff() {
  digitalWrite(pwm, LOW);
  digitalWrite(ain1, LOW);
  digitalWrite(ain2, HIGH); //CCW
  digitalWrite(pwm, HIGH);
  delay(30);
  digitalWrite(pwm, LOW);
  valveState = false; //off
}

void turnOn () {
  digitalWrite(pwm, LOW);
  digitalWrite(ain2, LOW);
  digitalWrite(ain1, HIGH); //CW
  digitalWrite(pwm, HIGH);
  delay(30);
  digitalWrite(pwm, LOW);
  valveState = true; //on
  
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

  turnOff();

}

int getDist(){
  int dist, duration = 0;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  dist = duration * 0.034/2;
  return dist;
}

void loop() {
//  if (Serial.available()){
//    if (Serial.read() == '1'){
//      turnOn();
//      Serial.println("On");
//    }
//    else{
//      turnOff();
//      Serial.println("Off");
//    }
//  }
  int i = 0;
  int dist = 0;
  for (i = 0; i < 10; i ++){
    dist = getDist() + dist;
  }
  dist = dist/10;
  
  if (dist >= threshold && valveState == true){
    turnOff();
  }
  else if (dist <threshold && valveState == false){
    turnOn();
  }
  Serial.print("Dist: ");
  Serial.print(dist);
  Serial.print("  Valve is");
  Serial.println(valveState);
  delay(100);

}
