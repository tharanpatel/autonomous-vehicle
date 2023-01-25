// Motor speed controller
#define motorPinA 8
#define motorPinB 7
#define speedPin A0
#define motorPinC 6
#define motorPinD 5
#define speedPin2 A1
#define BUTTON 3
#define led2 4
int reqSpeed = 0;
int reqSpeed2 = 0;
int input1;
int input2;
volatile bool buttonFlag = 0; //using volatile bool so we do not have to wait for the program to finish executing
void setup()
{
 // Open COMMS channel
 Serial.begin(9600);
 Serial.println();
 Serial.println("Starting L293D motor driver...");
 
 // Set digital pins used for motor control
 pinMode(motorPinA, OUTPUT);
 pinMode(motorPinB, OUTPUT);
 pinMode(motorPinC, OUTPUT);
 pinMode(motorPinD, OUTPUT);
 pinMode(BUTTON, INPUT);
 attachInterrupt(digitalPinToInterrupt(BUTTON), whenpressed, RISING);
 pinMode(led2, OUTPUT);
}
void loop()
{
 // Read potentiometer
 while (Serial.available() ==2)//allowing serial monitor to read first two characters
   input1=Serial.read();//reads serial input and assigns it to variable 'input1'
  input2=Serial.read();
 reqSpeed = map(input1,65,90,0,3);//converting serial input to numbers relevant to motor required RPM
 reqSpeed2 = map(input2,65,90,0,3);
 
 // Set motor 1 speed
 if(reqSpeed>0)
 {
 // Drive motor 1 clockwise
 Serial.print("Clockwise at motor 1: ");
 Serial.println(reqSpeed);
 analogWrite(motorPinA, reqSpeed);
 digitalWrite(motorPinB, LOW);
 }
 else if(reqSpeed<0)
 {
 // Drive motor 1 anticlockwise
 Serial.print("Antilockwise at motor 1: ");
 Serial.println(-reqSpeed);
 analogWrite(motorPinB, -reqSpeed);
 digitalWrite(motorPinA, LOW);
 }
 else
 {
 // If zero then brake using:
 Serial.print("Braking motor 1 for: ");
 Serial.println(reqSpeed);
 digitalWrite(motorPinA, HIGH);
 digitalWrite(motorPinB, HIGH);
 
 delay(100);
}
 if (reqSpeed2>0)
{
 Serial.print("Clockwise at motor 2: ");
 Serial.println(reqSpeed2);
 analogWrite(motorPinC, reqSpeed2);
 digitalWrite(motorPinD, LOW);
}
 else if(reqSpeed2<0)
{
 // Drive motor 1 clockwise
 Serial.print("Anticlockwise at motor 2: ");
 Serial.println(-reqSpeed);
 analogWrite(motorPinD, -reqSpeed);
 digitalWrite(motorPinC, LOW);
}
 else
{
 // If zero then brake using:
 Serial.print("Braking motor 2 for: ");
 Serial.println(reqSpeed2);
 digitalWrite(motorPinC, HIGH);
 digitalWrite(motorPinD, HIGH);
}
  delay(5000);
//bumper led 
  digitalWrite(led2,LOW);
if(buttonFlag)
{
  digitalWrite(led2,HIGH);
 Serial.print("COLLISION HAS OCCURRED, STOPPING VEHICLE!!");
 digitalWrite(motorPinA, HIGH);//immediately stops both motors
 digitalWrite(motorPinB, HIGH);
 digitalWrite(motorPinC, HIGH);
 digitalWrite(motorPinD, HIGH);
 while
   (1)//while loop means program is stopped from looping while in emergency break, to allow for manual override
 buttonFlag = 0; // Reset flag
 }
 
 // Switch back off before next loop
 digitalWrite(led2,LOW);
}
// interrupt service routine
//
void whenpressed()
{
//pin has gone high so set flag
 buttonFlag = 1;
}