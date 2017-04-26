
int buttonIn = 5;
int ledOut = 7;
const int debounceDelay = 50;
int lastDebounceTime = 0, lastButtonState = LOW, buttonState = HIGH;
int ledState = LOW;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledOut, OUTPUT);
  pinMode(buttonIn, INPUT);
  digitalWrite(buttonIn, HIGH);
}

void loop() {
  int reading = digitalRead(buttonIn);

  if (reading != lastButtonState) {
      lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      
    }
  }

  if (buttonState == HIGH) {
    ledState = LOW;
  }
  else {
    ledState = HIGH;
  }

  digitalWrite(ledOut, ledState);
 
  lastButtonState = reading;
}
