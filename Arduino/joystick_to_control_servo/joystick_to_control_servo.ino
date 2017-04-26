// HOW TO ADD A JOYSTICK TO CONTROL YOUR ROBOTIC SYSTEMS:
// Joysticks can move to left(0) to right(1023) (ANALOG pin will control position in X).
// They can also move from down (1023) to up (0) (another ANALOG pin will control position in Y).
// Finally, Joysticks can be pressed, acting as if they were a button or a switch (making a DIGITAL pin will 0 or 1)

// HOW TO CONNECT THE JOYSTICK:
// GND pin to Arduino GND.
// 5V pin to Arduino 5V.
// VRx pin to Arduino ANALOG A0 (controls position in X).
// VRy pin to Arduino ANALOG A1 (controls position in Y).
// SW pin (which stands for "switch") to Arduino DIGITAL 9 (to know if the button is pressed or not).

// Constants:

#include <Servo.h>

Servo servoX, servoY;
const int SW_pin = 2; //DIGITAL pin connected to switch output.
const int X_pin = 0; //ANALOG pin connected to X output.
const int Y_pin = 1; //ANALOG pin connected to Y output.
int servoPin = 7, servoPinY = 8;
int X_val, Y_val;

void setup() {
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  Serial.begin(115200);
  servoX.attach(servoPin);
  servoY.attach(servoPinY);
}

void loop() {
  Serial.print("Switch: ");
  Serial.print(!digitalRead(SW_pin));
  Serial.print("\n"); //To leave one line empty ("print to new line" order).
  Serial.print("X-axis: ");
  X_val = analogRead(X_pin);
  Serial.print(X_val);
  X_val = map(X_val, 0, 1023, 0, 180);
  servoX.write(X_val);
  Serial.print("\n"); //To leave one line empty ("print to new line" order).
  Serial.print("Y-axis: ");
  Y_val = analogRead(Y_pin);
  Serial.print(Y_val);
  Y_val = map(Y_val, 0, 1023, 0, 180);
  servoY.write(Y_val);
  Serial.print("\n\n"); //To leave one line empty ("print to new line" order).
  delay(50);
}
