/*
 * With this code you will be able to control the direction of rotation of an servo motor using two buttons.
 * You will need two buttons, two resistors (10K Ohms, since the program assumes pull-down mode for the buttons), and one servo motor.
 * MODIFIED: buttons are pull up
 */
#include <Servo.h>

Servo myservo; //create servo object to control a servo

const int buttonPin = 12;
const int buttonPin2 = 11;

//int buttonState = 0;
//int buttonState2 = 0;
int servoPin = 7;
int speed = 100;

int pos = 0; //variable to store the servo position

void setup() 
{
  myservo.attach(servoPin); //attaches the servo on pin 9
  pinMode(myservo.attach(servoPin), OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(buttonPin2, INPUT); 
  digitalWrite(buttonPin,HIGH);
  digitalWrite(buttonPin2,HIGH);
  Serial.begin(9600);
}

void loop() 
{
  int buttonState = digitalRead(buttonPin);
  int buttonState2 = digitalRead(buttonPin2);
  
  if(buttonState == LOW)
  {
    Serial.println("1");
    for(pos = 0; pos <=180; pos +=1) //goes from 0 degrees to 180 degrees
    {
      myservo.write(pos); //tell servo to go to position in variable 'pos'
      
      delay(15);
    }
    
  }
  
  if(buttonState2 == LOW)
  {
    Serial.println("2");
    for(pos = 180; pos >= 0; pos -=1) //goes from 180 degrees to 0 degrees
    {
      myservo.write(pos); //tell servo to go to position in variable 'pos'
      
      delay(15);
    }
  }
  
}
