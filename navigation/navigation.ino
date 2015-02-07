int leftSensor = A5;
int rightSensor = A4;

int leftLED = 10;
int rightLED = 11; 

int leftControl1 = 7;
int leftControl2 = 13;
int leftEnable = 5;

int rightControl1 = 8;
int rightControl2 = 12;
int rightEnable = 3;

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
  delay(200);

  if (leftSensorValue > whiteLeft + 100){
    analogWrite(leftEnable, 0);
    digitalWrite(leftLED, HIGH);
  }
  else{
    analogWrite(leftEnable, 150);
    digitalWrite(leftLED, LOW);
  }

  if (rightSensorValue > whiteRight + 100){
    analogWrite(rightEnable, 0);
    digitalWrite(rightLED, HIGH);
  }
  else{
    analogWrite(rightEnable, 150);
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

    leftSum += leftSensorValue;
    rightSum += rightSensorValue;

    Serial.print("Calibrating: ");
    Serial.print(leftSensorValue);
    Serial.print(", ");
    Serial.print(rightSensorValue);
    Serial.print("\n");
    delay(100);
  }

  whiteLeft = leftSum / 50;
  whiteRight = rightSum / 50; 

  Serial.print("whiteleft");
  Serial.print(whiteLeft);
  Serial.print("\t whiteright");
  Serial.print(whiteRight);
  Serial.print("\n");
}




