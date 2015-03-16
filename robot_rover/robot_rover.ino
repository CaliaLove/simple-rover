#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"
#include <Servo.h> 

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *myMotor1 = AFMS.getMotor(1);
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2);
Adafruit_DCMotor *myMotor3 = AFMS.getMotor(3);
Adafruit_DCMotor *myMotor4 = AFMS.getMotor(4);
 
Servo servo1;
int servoPos = 0;    // variable to store the servo position 

const int pingPin = 7;
 
void setup() 
{
  // initialize serial communication:
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("MMMMotor party!");

  // create with the default frequency 1.6KHz
  AFMS.begin();  

  // Attach a servo to pin #10
  servo1.attach(10);
  
  // Set the speed to start, from 0 (off) to 255 (max speed)
  myMotor1->setSpeed(100);
  myMotor1->run(FORWARD);
  myMotor1->run(RELEASE);
  
  myMotor2->setSpeed(100);
  myMotor2->run(FORWARD);
  myMotor2->run(RELEASE);
  
  myMotor3->setSpeed(100);
  myMotor3->run(FORWARD);
  myMotor3->run(RELEASE);
  
  myMotor4->setSpeed(100);
  myMotor4->run(FORWARD);
  myMotor4->run(RELEASE);
}

int i;

void loop()
{
  long distanceInCentimeter;

  lookForward();
  
  distanceInCentimeter = getDistanceInCentimeter();

  if ( distanceInCentimeter > 15 )
  {
       moveForwardSlowly();
  }
  else
  {
       rotateLeft();
       rotateLeft();
   
       lookRight();
       lookLeft();
       
       lookForward();
             
       distanceInCentimeter = getDistanceInCentimeter();
       
       if ( distanceInCentimeter > 15 )
       { 
           rotateLeft();
           lookForward();
           moveForwardSlowly(); 
       }
       else
       {
           rotateLeft();
           rotateLeft();
           lookForward();
           
           distanceInCentimeter = getDistanceInCentimeter();
           
           if ( distanceInCentimeter > 15 )
           {
                rotateRight();
                rotateRight();
                lookRight();
                lookLeft();
           }
           else
           {
                moveBackwardSlowly(); 
                moveBackwardSlowly(); 
                rotateRight();
                rotateRight();
                rotateRight();
                lookForward();
                moveForwardSlowly(); 
           }
       }
  }
}
 
long getDistanceInCentimeter()
{
  // establish variables for duration of the ping, 
  // and the distance result in inches and centimeters:
  long durationInMicroseconds;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  durationInMicroseconds = pulseIn(pingPin, HIGH);
  
  long distanceInCentimeter = 0;
   
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  distanceInCentimeter =  durationInMicroseconds / 29 / 2;
  
  Serial.print(distanceInCentimeter);
  Serial.print("cm");
  Serial.println();
  
  return distanceInCentimeter;
}

void lookAround()
{
   for(servoPos = 0; servoPos < 180; servoPos += 1)  // goes from 0 degrees to 180 degrees 
   {                                  // in steps of 1 degree 
       servo1.write(servoPos);              // tell servo to go to position in variable 'pos' 
       delay(50);                       // waits 15ms for the servo to reach the position 
   } 
   
   for(servoPos = 180; servoPos>=1; servoPos-=1)     // goes from 180 degrees to 0 degrees 
   {                                
       servo1.write(servoPos);              // tell servo to go to position in variable 'pos' 
       delay(50);                       // waits 15ms for the servo to reach the position 
   } 
}

void lookForward()
{
     servo1.write(120);   
}

void lookLeft()
{
   for(servoPos = 0; servoPos < 180; servoPos += 1)  // goes from 0 degrees to 180 degrees 
   {                                  // in steps of 1 degree 
       servo1.write(servoPos);              // tell servo to go to position in variable 'pos' 
       delay(10);                       // waits 15ms for the servo to reach the position 
   } 
}

void lookRight()
{
   for(servoPos = 180; servoPos>=1; servoPos-=1)     // goes from 180 degrees to 0 degrees 
   {                                
       servo1.write(servoPos);              // tell servo to go to position in variable 'pos' 
       delay(10);                       // waits 15ms for the servo to reach the position 
   } 
}

void moveForwardSlowly()
{ 
    // * speed setting
    myMotor1->setSpeed(50);
    myMotor2->setSpeed(50);
    myMotor3->setSpeed(50);
    myMotor4->setSpeed(50);
    
    myMotor1->run(FORWARD);
    myMotor2->run(FORWARD);
    myMotor3->run(FORWARD);
    myMotor4->run(FORWARD);
  
    delay(1000);
   
    myMotor1->run(RELEASE);
    myMotor2->run(RELEASE);
    myMotor3->run(RELEASE);
    myMotor4->run(RELEASE);
  
    delay(1000);
}

void moveBackwardSlowly()
{ 
    // * speed setting
    myMotor1->setSpeed(50);
    myMotor2->setSpeed(50);
    myMotor3->setSpeed(50);
    myMotor4->setSpeed(50);
    
    myMotor1->run(BACKWARD);
    myMotor2->run(BACKWARD);
    myMotor3->run(BACKWARD);
    myMotor4->run(BACKWARD);
  
    delay(1000);
   
    myMotor1->run(RELEASE);
    myMotor2->run(RELEASE);
    myMotor3->run(RELEASE);
    myMotor4->run(RELEASE);
  
    delay(1000);
}

void rotateRight()
{ 
    // * speed setting
    myMotor1->setSpeed(150);
    myMotor2->setSpeed(150);
    myMotor3->setSpeed(150);
    myMotor4->setSpeed(150);
    
    myMotor1->run(FORWARD);
    myMotor2->run(BACKWARD);
    myMotor3->run(BACKWARD);
    myMotor4->run(FORWARD);
  
    delay(1000);
   
    myMotor1->run(RELEASE);
    myMotor2->run(RELEASE);
    myMotor3->run(RELEASE);
    myMotor4->run(RELEASE);
  
    delay(1000);
}

void rotateLeft()
{ 
    // * speed setting
    myMotor1->setSpeed(150);
    myMotor2->setSpeed(150);
    myMotor3->setSpeed(150);
    myMotor4->setSpeed(150);
    
    myMotor1->run(BACKWARD);
    myMotor2->run(FORWARD);
    myMotor3->run(FORWARD);
    myMotor4->run(BACKWARD);
  
    delay(1000);
   
    myMotor1->run(RELEASE);
    myMotor2->run(RELEASE);
    myMotor3->run(RELEASE);
    myMotor4->run(RELEASE);
  
    delay(1000);
}


void testMovement()
{
  myMotor1->run(FORWARD);
  myMotor2->run(BACKWARD);
  myMotor3->run(BACKWARD);
  myMotor4->run(FORWARD);
  
  delay(1000);
   
  myMotor1->run(RELEASE);
  myMotor2->run(RELEASE);
  myMotor3->run(RELEASE);
  myMotor4->run(RELEASE);
  
  delay(1000);
   
  myMotor1->run(BACKWARD);
  myMotor2->run(FORWARD);
  myMotor3->run(FORWARD);
  myMotor4->run(BACKWARD);
  
  delay(1000);
    
  myMotor1->run(RELEASE);
  myMotor2->run(RELEASE);
  myMotor3->run(RELEASE);
  myMotor4->run(RELEASE); 
  
  delay(1000);
}

