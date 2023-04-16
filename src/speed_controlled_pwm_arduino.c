/*
 * C code for knob-controlled ...
 * PWM to drive on Arduino UNO board.
 * 
 * Created: 14.04.2022 20:12:11
 * Author : @volkbay
 */ 
 
int motorPin = 0;
int analogPin = A3;
int value;
int currentVal = 0;
int currentCnt = 0;

void setup() {
  pinMode(motorPin, OUTPUT);
  pinMode(analogPin, INPUT);
  analogWrite(motorPin, 0);
}

void loop() {
  value = analogRead(analogPin)/4;
  if (currentCnt == 10){
    currentCnt = 0;
    analogWrite(motorPin, currentVal);
    currentVal = 0;    
  }
  else{
    currentCnt++;
    if (currentVal < value) currentVal = value;
  }
}