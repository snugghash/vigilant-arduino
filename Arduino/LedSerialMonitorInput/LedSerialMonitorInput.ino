
int pinRed = 7;
int pinYellow = 8;
int pinGreen = 9;
void setup() {
  pinMode(pinRed, OUTPUT);
  pinMode(pinGreen, OUTPUT);
  pinMode(pinYellow, OUTPUT);
  
  Serial.begin(9600);  
  digitalWrite(pinRed, LOW);
  digitalWrite(pinYellow, LOW);
  digitalWrite(pinGreen, LOW);
}

void loop() {
  //Check if some input is stored in buffer
  if(Serial.available()) {
    char input = Serial.read();
    if (input == 'R') {
      //Serial.println(digitalRead(pinRed));
      if (digitalRead(pinRed) == HIGH)
        digitalWrite(pinRed,LOW);
      else
        digitalWrite(pinRed, HIGH);
      //Serial.println(digitalRead(pinRed));

    }
    else if (input == 'Y') {
      if (digitalRead(pinYellow) == HIGH)
        digitalWrite(pinYellow,LOW);
      else
        digitalWrite(pinYellow, HIGH);
    }
    else if (input == 'G') {
      if (digitalRead(pinGreen) == HIGH)
        digitalWrite(pinGreen,LOW);
      else
        digitalWrite(pinGreen, HIGH);
    }
    else if(input == 'O') {
      digitalWrite(pinRed, LOW);
      digitalWrite(pinGreen,LOW);
      digitalWrite(pinYellow,LOW);
    }
    else 
      digitalWrite(pinRed, LOW);
  }
  //delay(1000);
}
