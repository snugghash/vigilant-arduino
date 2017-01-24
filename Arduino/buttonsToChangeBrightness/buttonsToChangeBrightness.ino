int buttonUp = 7;
int buttonDown = 9;
int led = 5;

int brightness = 125;
int stepB = 32;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(buttonUp,INPUT);
  pinMode(buttonDown,INPUT);
  pinMode(led,OUTPUT);
  analogWrite(led,brightness);
}

void loop() {
  // put your main code here, to run repeatedly:
  int up = digitalRead(buttonUp);
  int down = digitalRead(buttonDown);
  if(up == 1) {
    brightness = brightness + stepB;
    
    //Make invalid brightness to closest valid
    if(brightness >= 255)
      brightness = 255;
    else if(brightness <= 0)
      brightness = 1;

    Serial.println(brightness);
    analogWrite(led,brightness);
    delay(400);
  }
  if(down == 1) {
    brightness = brightness - stepB;

    //Make invalid brightness to closest valid
    if(brightness >= 255)
      brightness = 255;
    else if(brightness <= 0)
      brightness = 1;

    Serial.println(brightness);
    analogWrite(led,brightness);
    delay(400);
  }
  down = 0;
  up = 0;
}
