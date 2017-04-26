int buttonIn = 6;
int ledOut = 7;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledOut, OUTPUT);
  pinMode(buttonIn, INPUT);
  digitalWrite(buttonIn, HIGH);
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  int val = digitalRead(buttonIn);
  if (val == LOW) {
    digitalWrite(ledOut, HIGH);
    Serial.println("Pressed");
  }
  else
    digitalWrite(ledOut, LOW);
  //delay(1000);
}
