//ULTRASONIC SENSORS
#define trigPin1 13 //telling program which arduino pins correspond to which pins on sensor
#define echoPin1 12
#define trigPin2 11
#define echoPin2 10
#define trigPin3 9
#define echoPin3 8
//Magnetometer Pin and also defining value of PI
#define PI 3.14159
#define potPin A1
#define led1 7
// Constants for magnetometer - set as required
#define X_OFFSET 300 //correcting magnetometer as potentiometer does not have full 0-360 span
#define Y_OFFSET 200 
#define X_SENS 1000
#define Y_SENS 1000
#define NOISE 50
int usensor1 = 0; //defining ultrasonic sensors for ascii conversion, LEFT ULTRASONIC SENSOR
int usensor2 = 0; //FRONT ULTRASONIC SENSOR
int usensor3 = 0; //RIGHT ULTRASONIC SENSOR
int inputPin = A0;//LIGHT SENSOR/PHOTOTRANSISTOR
int phototransistorValue = 0;//LS/PHOTOTRANSISTOR
int led1Pin = 7;
int delayPeriod = 100; //defining value for delay period for hysteresis
int delayPeriod2 = 200;
int squirrelCount = 0;
int squirrelCount2 = 0;
int potentiometer = 0;
int heading = 0;
int headingAscii = 0;
void setup()  
{
Serial.begin (9600); //defining baud rate , speed of communication of arduino
pinMode(trigPin1, OUTPUT); //defining which pins are output and input
pinMode(echoPin1, INPUT);
pinMode(trigPin2, OUTPUT);
pinMode(echoPin2, INPUT);
pinMode(trigPin3, OUTPUT);
pinMode(echoPin3, INPUT);
pinMode(led1Pin, OUTPUT);
}
void loop() {
int duration1, duration2, duration3; //defining these variables as integers
digitalWrite(trigPin1, LOW);
delayMicroseconds(2);
digitalWrite(trigPin1, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin1, LOW);
duration1 = pulseIn(echoPin1, HIGH);
digitalWrite(trigPin2, LOW);
delayMicroseconds(2);
digitalWrite(trigPin2, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin2, LOW);
duration2 = pulseIn(echoPin2, HIGH);
digitalWrite(trigPin3, LOW);
delayMicroseconds(2);
digitalWrite(trigPin3, HIGH);
delayMicroseconds(10); 
digitalWrite(trigPin3, LOW);
duration3 = pulseIn(echoPin3, HIGH);
usensor1 = map (duration1, 0, 20000, 65, 90);//converting sensor duration times to corresponding ASCII values
usensor2 = map (duration2, 0, 20000, 65, 90);//Ultrasensor duration range is 0 to 20000, ASCII span is 65 to 90
usensor3 = map (duration3, 0, 20000, 65, 90);
Serial.println("NEW READING");
Serial.print("Ultrasonic Sensor LEFT duration : ");
Serial.println(duration1);//combination of types of serial printing to serial monitor for readable neat display
Serial.print("Ultrasonic Sensor LEFT to ASCII : ");
Serial.write(usensor1);//prints value to serial monitor as its raw ASCII value, must use write and serial.print causes problems here
Serial.println();
 delay(1000);// adding delays just to make reading serial monitor easier,unneccesary,  can remove but keeping for the sake of assessment
Serial.print("Ultrasonic sensor FRONT duration : ");
Serial.println(duration2);
Serial.print("Ultrasonic Sensor FRONT to ASCII : ");
Serial.write(usensor2);
Serial.println();
delay(1000);
Serial.print("Ultrasonic sensor RIGHT duration : ");
Serial.println(duration3);
Serial.print("Ultrasonic Sensor RIGHT to ASCII : ");
Serial.write(usensor3);
Serial.println();
delay(1000);
//phototransistor
phototransistorValue = analogRead(inputPin);
Serial.println("Phototransistor value is...");
Serial.println(phototransistorValue);
if (phototransistorValue>0)//if squirrel is present then phototransistor will output 0 as it completely blocks sensor
{
digitalWrite(led1Pin, LOW); // turn the LED on
delay(delayPeriod); // hysteresis system
Serial.println("No squirrel detected...ASCII : A");
}
else
{
digitalWrite(led1Pin, HIGH); // turn the LED off
delay(delayPeriod2); // this delay is larger to allow for an overlap for hysteresis so that squirrel even is registered numerous times
squirrelCount = ++squirrelCount;//increments of +1
Serial.println("SQUIRREL DETECTED...ASCII : B");
Serial.print("Squirrel Count = ");
Serial.println(squirrelCount);
squirrelCount2 = map (squirrelCount, 0, 25, 65, 90);
Serial.print("Squirrel Count to ASCII : ");
Serial.write(squirrelCount2);
Serial.println();
}
// To replicate the compass, take the potentiometer reading and convert to a heading
// 0 deg -> 360 deg over pot rotation
potentiometer = analogRead(A1);
 heading = potentiometer*360.0/1023.0;
//potentiometer
Serial.print("Vehicle Direction is : ");
Serial.print(heading);
Serial.println();
  headingAscii = map (heading, 0, 360, 65, 90);//converting potentiometer compass reading to range 65-90 (A-Z)
Serial.print("Heading to ASCII : ");
Serial.write(headingAscii);
Serial.println();
 //final outputs to serial monitor
Serial.print("FINAL LABVIEW ASCII CODE INPUTS : ");
Serial.write(usensor1);
Serial.write(usensor2);
Serial.write(usensor3);
Serial.write(squirrelCount2);
Serial.write(headingAscii);
Serial.println();
}
