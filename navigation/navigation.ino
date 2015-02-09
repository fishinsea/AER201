int leftSensor = A5;
int rightSensor = A4;

int leftLED = 10;
int rightLED = 11; 

int leftControl1 = 12;
int leftControl2 = 8;
int leftEnable = 3;

int rightControl1 = 13;
int rightControl2 = 7;
int rightEnable = 5;

int whiteLeft = 0; 
int whiteRight = 0;
int leftSensorValue = 0;
int rightSensorValue = 0;

int time;
int tolerance = 50;
int motorSpeed = 80;
int turnDuration = 500;

void setup() {
  Serial.begin(9600);
  pinMode(leftSensor, INPUT);
  pinMode(rightSensor, INPUT);

  pinMode(leftControl1, OUTPUT);
  pinMode(leftControl2, OUTPUT);
  pinMode(leftEnable, OUTPUT);

  pinMode(rightControl1, OUTPUT);
  pinMode(rightControl2, OUTPUT);
  pinMode(rightEnable, OUTPUT);

//
//  digitalWrite(leftEnable, HIGH);
  digitalWrite(leftControl1, HIGH);
  digitalWrite(leftControl2, LOW);
//
//  digitalWrite(rightEnable, HIGH);
  digitalWrite(rightControl1, LOW);
  digitalWrite(rightControl2, HIGH);

  calibrate();
}

void loop(){
  leftSensorValue = analogRead(leftSensor);
  rightSensorValue = analogRead(rightSensor);

  Serial.print(leftSensorValue);
  Serial.print(", ");
  Serial.println(rightSensorValue);
  delay(50);

//  if (leftSensorValue > whiteLeft + tolerance & rightSensorValue > whiteRight + tolerance){
//    //intersectionCount ++;
//    analogWrite(rightEnable, motorSpeed);
//    analogWrite(leftEnable, 0);
//    delay(turnDuration);
//  }

  if (leftSensorValue > whiteLeft + tolerance){
    analogWrite(leftEnable, 0);
    digitalWrite(leftLED, HIGH);
  }
  else{
    analogWrite(leftEnable, motorSpeed);
    digitalWrite(leftLED, LOW);
  }

  if (rightSensorValue > whiteRight + tolerance){
    analogWrite(rightEnable, 0);
    digitalWrite(rightLED, HIGH);
  }
  else{
    analogWrite(rightEnable, motorSpeed);
    digitalWrite(rightLED, LOW);
  }
}

void calibrate(){
  int count = 0;
  int leftSum = 0;
  int rightSum = 0;

  while (count < 50) {
    count ++;
    leftSensorValue = analogRead(leftSensor);
    rightSensorValue = analogRead(rightSensor);

    whiteLeft = max(whiteLeft, leftSensorValue);
    whiteRight = max(whiteRight, rightSensorValue);
    

    Serial.print("Calibrating: ");
    Serial.print(leftSensorValue);
    Serial.print(", ");
    Serial.print(rightSensorValue);
    Serial.print("\n");
    delay(100);
  }

  Serial.print("whiteleft");
  Serial.print(whiteLeft);
  Serial.print("\t whiteright");
  Serial.print(whiteRight);
  Serial.print("\n");
}




