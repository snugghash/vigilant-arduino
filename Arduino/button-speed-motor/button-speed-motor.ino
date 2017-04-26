// Button to chage speed of motor
int inPin1 = 10;
int inPin2 = 9;
int speedPin = 2;

int state = 255;
int step = 64;
//int inPin = 10;

  
void setup() {
  // put your setup code here, to run once:
  pinMode(inPin1, OUTPUT);
  pinMode(inPin2, OUTPUT);
  pinMode(speedPin, INPUT);
  Serial.begin(9600);
  digitalWrite(speedPin, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  //analogWrite(inPin1, 255);
  //analogWrite(inPin2, 0);
  if(state > 255) {
      // Clockwise
      Serial.println(state%256);
      analogWrite(inPin1, state%256);
      analogWrite(inPin2, 0);
    }
    else {
      Serial.println(state%256);
      analogWrite(inPin1, 0);
      analogWrite(inPin2, state%256);
    }
  if(!digitalRead(speedPin)) {
    state = (state + step)%512;
    Serial.println(state); 
    delay(300);
  }
  delay(100);
}

