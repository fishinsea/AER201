int leftSensor = A5;
int rightSensor = A4;

int leftLED = 10;
int rightLED = 11; 

int leftControl1 = 7;
int leftControl2 = 13;
int leftEnable = 5;

//int rightControl1 = 8;
//int rightControl2 = 12;
//int rightEnable = 6;

int whiteLeft = 0; 
int whiteRight = 0;
int leftSensorValue = 0;
int rightSensorValue = 0;

int time;

void setup() {
  Serial.begin(9600);
  pinMode(leftSensor, INPUT);
  pinMode(rightSensor, INPUT);
  
  pinMode(leftControl1, OUTPUT);
  pinMode(leftControl2, OUTPUT);
  pinMode(leftEnable, OUTPUT);

//  pinMode(rightControl1, OUTPUT);
//  pinMode(rightControl2, OUTPUT);
//  pinMode(rightEnable, OUTPUT);
  
  
  digitalWrite(leftEnable, HIGH);
  digitalWrite(leftControl1, HIGH);
  digitalWrite(leftControl2, LOW);

//  analogWrite(rightEnable, 150);
//  digitalWrite(rightControl1, HIGH);
//  digitalWrite(rightControl2, LOW);

  calibrate();
}

void loop(){
  leftSensorValue = analogRead(leftSensor);
  rightSensorValue = analogRead(rightSensor);

  Serial.print(leftSensorValue);
  Serial.print(", ");
  Serial.println(rightSensorValue);
  delay(200);
  
  if (leftSensorValue > whiteLeft + 100){
    analogWrite(leftEnable, 150);
    digitalWrite(leftLED, HIGH);
  }
  else{
    digitalWrite(leftEnable, LOW);
    digitalWrite(leftLED, LOW);
  }
//  
//  if (rightSensorValue > whiteRight + 100){
//    analogWrite(rightEnable, 0);
//    digitalWrite(rightLED, HIGH);
//  }
//  else{
//    analogWrite(rightEnable, 50);
//    digitalWrite(rightLED, LOW);
//  }
}

void calibrate(){
  whiteLeft = analogRead(leftSensor);
  whiteRight = analogRead(rightSensor);
  Serial.print(whiteLeft); 
  Serial.print(", ");
  Serial.print(whiteRight);
  Serial.print("\n");

  time = millis();
  while ((millis() - time) < 3000) {
    leftSensorValue = analogRead(leftSensor);
    rightSensorValue = analogRead(rightSensor);
    whiteLeft = (whiteLeft + leftSensorValue ) / 2;
    whiteRight = (whiteRight + rightSensorValue ) / 2;
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


