
#include <LiquidCrystal.h>// include the library code
#include <Servo.h>

Servo servoX, servoY;
const int SW_pin = 2; //DIGITAL pin connected to switch output.
const int X_pin = 0; //ANALOG pin connected to X output.
const int Y_pin = 1; //ANALOG pin connected to Y output.
int servoPin = 6, servoPinY = 7;
int X_val, Y_val, buttonValue;
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);
int delTime = 100;

int numberOfCharacters = 16;
char state[] = "00";

char array1[]="Option          ";  //the string to print on the LCD
char array2[]="Option 2        ";  //the string to print on the LCD
char array3[]="Option 2        ";  //the string to print on the LCD
char array4[]="Option 1.2      ";  


void setup() {
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  Serial.begin(115200);
  servoX.attach(servoPin);
  servoY.attach(servoPinY);
  lcd.begin(16, 2);
}

void loop() {
  //Serial.print("Switch: ");
  buttonValue = !digitalRead(SW_pin);
  //Serial.print(buttonValue);
  //Serial.print("\n"); //To leave one line empty ("print to new line" order).
  //Serial.print("X-axis: ");
  X_val = analogRead(X_pin);
  //Serial.print(X_val);
  X_val = map(X_val, 0, 1023, 0, 180);
  servoX.write(X_val);
  //Serial.print("\n"); //To leave one line empty ("print to new line" order).
  //Serial.print("Y-axis: ");
  Y_val = analogRead(Y_pin);
  //Serial.print(Y_val);
  Y_val = map(Y_val, 0, 1023, 0, 180);
  servoY.write(Y_val);
  //Serial.print("\n\n"); //To leave one line empty ("print to new line" order).

  lcd.setCursor(0,0);
  for (int pos = 0; pos<numberOfCharacters; pos++) {
    lcd.print(array1[pos]);
  }
  lcd.setCursor(0,8);
  Serial.print("State is:");
  Serial.println(state[0]);
  lcd.print(state[0]);
  lcd.print(state[1]);
  
  lcd.setCursor(0,1);
  for (int pos = 0; pos<numberOfCharacters; pos++) {
    lcd.print(array2[pos]);
  }
  //char tempC[3];
  //sprintf(tempC, "%g", temperature);
  //puts(temperature)
  //lcd.setCursor(8,1);
  //lcd.print(toFarenheit(temperature));

  
  if (strcmp(state,"00")) {
    strcpy(state,"10");
    Serial.println("State is:");
    Serial.print(state);
  }
  delay(delTime);
}
