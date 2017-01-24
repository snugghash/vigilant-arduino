
int buttonIn = 5;
int ledOut = 7;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledOut, OUTPUT);
  pinMode(buttonIn, INPUT);
  digitalWrite(ledOut,LOW);

  
}

void loop() {
  // put your main code here, to run repeatedly:
  int val = digitalRead(buttonIn);
  
  digitalWrite(ledOut, val);

  delay(1000);
}
