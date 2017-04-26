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

int alarm;
int buzzer = 13;
int stopAlarmPin = 7;
int delayTime = 200;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);//Set the baud rate of serial monitor as 9600bps
  delay(100);
  Wire.begin();  //Initialize I2C
  delay(100);
  Wire.beginTransmission(ADXAddress);
  Wire.write(Register_2D);
  Wire.write(8);
  Wire.endTransmission();
  Serial.println("Accelerometer Test ");
  alarm = 0;
  pinMode(buzzer, OUTPUT);
  digitalWrite(stopAlarmPin, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
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
  if( Zg < 0.80 || Zg > 1.1) {    
      alarm = 1;
  }
  if(abs(Xg) > xyTolerance) {
      alarm = 1;
  }
  if(abs(Yg) > xyTolerance) {
      alarm = 1;
  }

  if(alarm == 1) {
    for(int i=0;i<80;i++)//output sound of one frequency
    {
      digitalWrite(buzzer, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(1);              // wait for a second
      digitalWrite(buzzer, LOW);    // turn the LED off by making the voltage LOW
      delay(1);              // wait for a second
    }
    Serial.println("Alarm!"); 
  }

  //Serial.println(digitalRead(stopAlarmPin));
  if(digitalRead(stopAlarmPin) == LOW) {
    alarm = 0;
    Serial.println("Stopped alarm");
  }
  

  delay(delayTime);  //Delay 0.3s. Adjust the value to change the refresh rate. 

}
