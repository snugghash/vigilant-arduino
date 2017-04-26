/*
  ReadAnalogVoltage
  Reads an analog input on pin 0, converts it to voltage, and prints the result to the serial monitor.
  Graphical representation is available using serial plotter (Tools > Serial Plotter menu)
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.
*/

int buzzer = 5;
unsigned char i,j; // this is for the "for-loops".

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(buzzer,OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  float voltage = sensorValue * (5.0 / 1023.0);
  float frequency = map(sensorValue,0,1023,1,1000);
  float digital255 = map(sensorValue,0,1023,0,255);
  Serial.println(voltage);

  for(i=0;i<80;i++)//output sound of one frequency
  {
    digitalWrite(buzzer, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1/frequency);              // wait for a second
    digitalWrite(buzzer, LOW);    // turn the LED off by making the voltage LOW
    delay(1/frequency);              // wait for a second
  }
  
}
