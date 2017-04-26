int rPin = 3;
int gPin = 5;
int bPin = 6;

void setup() {
  pinMode(rPin, OUTPUT);
  pinMode(bPin, OUTPUT);
  pinMode(gPin, OUTPUT);

}

void loop() {
  // Red
  analogWrite(rPin,255);
  analogWrite(bPin,0);
  analogWrite(gPin,0);
  delay(300);

  // Green
  analogWrite(rPin,0);
  analogWrite(bPin,0);
  analogWrite(gPin,255);

  delay(300);

  // Blue
  analogWrite(rPin,0);
  analogWrite(bPin,255);
  analogWrite(gPin,0);

  delay(300);
  // Red
  analogWrite(rPin,255);
  analogWrite(bPin,0);
  analogWrite(gPin,0);

  delay(300);
  // Orange
  analogWrite(rPin,255);
  analogWrite(bPin,0);
  analogWrite(gPin,165);

  delay(300);
  // Yellow
  analogWrite(rPin,255);
  analogWrite(bPin,0);
  analogWrite(gPin,255);

  delay(300);
  // Green
  analogWrite(rPin,0);
  analogWrite(bPin,0);
  analogWrite(gPin,255);

  delay(300);
  // Blue
  analogWrite(rPin,0);
  analogWrite(bPin,255);
  analogWrite(gPin,0);

  delay(300);
  // Indigo
  analogWrite(rPin,75);
  analogWrite(bPin,130);
  analogWrite(gPin,0);

  delay(300);
  // Purple
  analogWrite(rPin,255);
  analogWrite(bPin,255);
  analogWrite(gPin,0);
  delay(300);


  delay(1000);
}
