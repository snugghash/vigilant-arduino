int button = 7;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(button,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int t = digitalRead(button);
  if(t==1)
    Serial.println("Button is on");
  else
    Serial.println("Button is off");
}
