/*
  Buzzer
  Plays a buzzer using DIGITAL pin 13
  Buzzer play turning on for a brief moment and then turning off (like the blink tutorial),repeatedly.
  The delay between ON and OFF will change the tone you play with the buzzer.
  CONNECTIONS:
  There are two buzzers in class:
  Active Buzzers (no sticker!): S = Digital signal (pin 13), Middle= 5Volts, "-"= GND through 220-Ohm resistor
  Non-active Buzzers (with a sticker): S = Digital signal (pin 13), Middle= GND through 220-Ohm resistor, "-"= 5Volts 
*/
int buzzer=3;
unsigned char i,j; // this is for the "for-loops".

void setup() {
  pinMode(buzzer, OUTPUT); // initialize pin 13 as buzzer = output.
}

// the loop function runs over and over again forever
void loop() {
  for(i=0;i<80;i++)//output sound of one frequency
  {
    digitalWrite(buzzer, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1);              // wait for a milisecond
    digitalWrite(buzzer, LOW);    // turn the LED off by making the voltage LOW
    delay(1);              // wait for a second
  }
  
}
