
#include <LiquidCrystal.h>// include the library code
#include <Servo.h>

// Servo init
Servo servoLeft, servoRight;
//const int SW_pin = 2; //DIGITAL pin connected to switch output.
//const int X_pin = 0; //ANALOG pin connected to X output.
//const int Y_pin = 1; //ANALOG pin connected to Y output.
int servoPinLeft = 5, servoPinRight = 4;
int speed = 100;


int buttonPaddleLeft = 6;
int buttonPaddleRight = 7;
int buttonLoseLife = 3;

int numberOfCharacters = 21;
int score = 0;
int lives = 3;

// LCD init
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);
char array1[] =  "Score           ";
char array2[] =  "Lives           ";
char welcome[] = "Welcome pinball ";
char over[] =    "Game Over       ";
int delTime = 50;

int state = 0;

//Acc. init. ADXL 345
#include <Wire.h>  //Call the I2C library built in Arduino
//Set the address of the register
#define Register_ID 0
#define Register_2D 0x2D
#define Register_X0 0x32
#define Register_X1 0x33
#define Register_Y0 0x34
#define Register_Y1 0x35
#define Register_Z0 0x36
#define Register_Z1 0x37

int ADXAddress = 0x53;  //I2C address
int reading = 0;
int val = 0;
int X0, X1, X_out;
int Y0, Y1, Y_out;
int Z1, Z0, Z_out;
double Xg, Yg, Zg;


void setup() {
  pinMode(buttonPaddleLeft, INPUT);
  pinMode(buttonPaddleRight, INPUT);
  pinMode(buttonLoseLife, INPUT);
  digitalWrite(buttonPaddleLeft, HIGH);
  digitalWrite(buttonPaddleRight, HIGH);
  digitalWrite(buttonLoseLife, HIGH);
  Serial.begin(9600);
  servoLeft.attach(servoPinLeft);
  pinMode(servoLeft.attach(servoPinLeft), OUTPUT);
  servoRight.attach(servoPinRight);
  pinMode(servoRight.attach(servoPinRight), OUTPUT);
  
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  for (int pos = 0; pos<numberOfCharacters; pos++) {
    lcd.print(welcome[pos]);
  }

  //ACC ADXL 345 setup, analog 4,5 used.
  Wire.begin();  //Initialize I2C
  delay(100);
  Wire.beginTransmission(ADXAddress);
  Wire.write(Register_2D);
  Wire.write(8);
  Wire.endTransmission();
}

void loop() {
  // Left button
  if(digitalRead(buttonPaddleLeft) == LOW) {
    //Serial.println("Laft paddle pressed");
    servoLeft.write(90);
    if(state == 0) state++;
  }
  else {
    servoLeft.write(0);
  }
  
  // Right button
  if(digitalRead(buttonPaddleRight) == LOW) {
    //Serial.println("Right paddle pressed");
    servoRight.write(90);
    if(state == 0) state++;
  }
  else {
    servoRight.write(0);
  }



  // Print score and lives
  if(state != 0) {
      printScoreLives();
  }
  if (lives == 0) {
    printGameOver();
    delay(delTime);
    return;
  }


  //Lose life
  if(digitalRead(buttonLoseLife) == LOW) {
    if(state == 0) {
      state++;
    }
    else lives--;
    delay(400);
  }


  
  // Accelerometer 
  Wire.beginTransmission(ADXAddress);
  Wire.write(Register_X0);
  Wire.write(Register_X1);
  Wire.endTransmission();
  Wire.requestFrom(ADXAddress, 2);
  if (Wire.available() <= 2);
  {
    X0 = Wire.read();
    X1 = Wire.read();
    X1 = X1 << 8;
    X_out = X0 + X1;
  }

  Wire.beginTransmission(ADXAddress);
  Wire.write(Register_Y0);
  Wire.write(Register_Y1);
  Wire.endTransmission();
  Wire.requestFrom(ADXAddress, 2);
  if (Wire.available() <= 2);
  {
    Y0 = Wire.read();
    Y1 = Wire.read();
    Y1 = Y1 << 8;
    Y_out = Y0 + Y1;
  }

  Wire.beginTransmission(ADXAddress);
  Wire.write(Register_Z0);
  Wire.write(Register_Z1);
  Wire.endTransmission();
  Wire.requestFrom(ADXAddress, 2);
  if (Wire.available() <= 2);
  {
    Z0 = Wire.read();
    Z1 = Wire.read();
    Z1 = Z1 << 8;
    Z_out = Z0 + Z1;
  }
  Xg = X_out / 256.00; //Convert the output result into the acceleration g, accurate to 2 decimal points.
  Yg = Y_out / 256.00;
  Zg = Z_out / 256.00;
  Serial.print("X=");
  Serial.print(Xg);
  Serial.print("\tY=");
  Serial.print(Yg);
  Serial.print("\tZ=");
  Serial.println(Zg);

  float xyTolerance = 0.2;
  if( Zg < 0.8 || Zg > 1.1) {    
      score++;
      delay(400);
  }
  if(abs(Xg) > xyTolerance) {
      score++;
      delay(400);
  }
  if(abs(Yg) > xyTolerance) {    
      score++;
      delay(400);
  }



  
  
  delay(delTime);
}

void printScoreLives() {
  lcd.setCursor(0,0);
  for (int pos = 0; pos<numberOfCharacters; pos++) {
    lcd.print(array1[pos]);
  }
  lcd.setCursor(7,0);
  lcd.print(score);
  
  lcd.setCursor(0,1);
  for (int pos = 0; pos<numberOfCharacters; pos++) {
    lcd.print(array2[pos]);
  }
  lcd.setCursor(7,1);
  lcd.print(lives);
  
}

void printGameOver() {
  lcd.setCursor(0,1);
  for (int pos = 0; pos<numberOfCharacters; pos++) {
    lcd.print(over[pos]);
  }
}

