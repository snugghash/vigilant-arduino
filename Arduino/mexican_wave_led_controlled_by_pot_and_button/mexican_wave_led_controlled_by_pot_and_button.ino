/*
 Fade

 This example shows how to fade an LED on pin 9
 using the analogWrite() function.

 The analogWrite() function uses PWM, so if
 you want to change the pin you're using, be
 sure to use another PWM capable pin. On most
 Arduino, the PWM pins are identified with 
 a "~" sign, like ~3, ~5, ~6, ~9, ~10 and ~11.

 */

int led1 = 3;
int led2 = 5;
int led3 = 6;
int led4 = 9;
int led5 = 10;
int led6 = 11;// the PWM pin the LED is attached to
int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by
int reversePin = 13;
int brightnessPin = 0;
bool direction = 0;
int angle = 0;
int angleStep = 10;
const int NUM_LED = 6;
int led[NUM_LED];

// the setup routine runs once when you press reset:
void setup() {
  // declare pin 9 to be an output:
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  //pinMode(brightnessPin, INPUT);
  pinMode(reversePin, INPUT);
  digitalWrite(reversePin, HIGH);
  brightness = 127;
  Serial.begin(9600);
  for(int i=0;i<NUM_LED;i++) {
    led[i] = i;
  }
}

int getGoodAngle(int angle) {
  if(angle >= 180) {
    angle = angle%180;
  }
  else if (angle <= 0) {
    angle = (angle+180)%180;
  }
  
  return angle;
}

// the loop routine runs over and over again forever:
void loop() {
  analogWrite(led1, brightness*sin((float)getGoodAngle(angle)*3.14/180));
  analogWrite(led2, brightness*sin((float)getGoodAngle(angle+angleStep)*3.14/180));
  analogWrite(led3, brightness*sin((float)getGoodAngle(angle+2*angleStep)*3.14/180));
  analogWrite(led4, brightness*sin((float)getGoodAngle(angle+3*angleStep)*3.14/180));
  analogWrite(led5, brightness*sin((float)getGoodAngle(angle+4*angleStep)*3.14/180));
  analogWrite(led6, brightness*sin((float)getGoodAngle(angle+5*angleStep)*3.14/180));

  //for(int i = 0; i<NUM_LED; i++) {
  //  analogWrite(led[i], brightness*sin((float)getGoodAngle(angle+i*angleStep)*3.14/180));
  //}
/*
  analogWrite(led1, brightness);
  analogWrite(led2, brightness);
  analogWrite(led3, brightness);
  analogWrite(led4, brightness);
  */
  // change the brightness for next time through the loop:
  brightness = map(analogRead(brightnessPin),0,1023,0,127);
  //Serial.print("brightness");
  //Serial.println(brightness);
  //Serial.println(brightness*sin(getGoodAngle(angle)));
  //Serial.println(sin(getGoodAngle(angle)));
  
  if(digitalRead(reversePin) == LOW) {
    direction = !direction;
    Serial.print("Direction");
    Serial.println(direction);
    delay(300);
  }


  //Code for the mexican wave
  
  angle += (-2 * direction * angleStep) + angleStep;
  //Serial.print("increment");
  //Serial.println((-2 * direction * angleStep) + angleStep);
  //Serial.println("Angle");
  //Serial.println(angle);
  angle = getGoodAngle(angle);
  // wait for 30 milliseconds to see the dimming effect
  delay(30);
}
