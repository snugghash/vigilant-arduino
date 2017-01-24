
int buttonIn = 5;
int ledOut = 7;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledOut, OUTPUT);
  pinMode(buttonIn, INPUT);
  digitalWrite(buttonIn, HIGH);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  int val = digitalRead(buttonIn);
  if (val == LOW)
    digitalWrite(ledOut, HIGH);
  else
    digitalWrite(ledOut, LOW);
  //delay(1000);
}
