int led = 5;
void setup() {
  // put your setup code here, to run once:
  pinMode(led,OUTPUT);
  Serial.begin(250000);
}

void loop() {
  digitalWrite(led,HIGH);
  Serial.print("On");
  delay(500);
  // put your main code here, to run repeatedly:
  digitalWrite(led,LOW);
  Serial.println("Off");
  delay(500);
}
