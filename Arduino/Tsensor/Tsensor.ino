#include <math.h>

//Remember to connect pin "S" to an analog pin (A5 in this example)
//Now connect the GROUND through a 220-Ohm resistor to the MIDDLE pin of the thermometer.
//Connect the +5V of the Arduino board to the pin labeled as "-" in the thermometer.
//Finally, double check that you got the connections right!!.

int sensorPin = A5; // input pin for the thermometer

double Thermistor(int RawADC)
{
  double tempC; //Temperature in Celsius
  tempC = log(10000.0 * ((1024.0 / RawADC - 1)));
  tempC = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * tempC * tempC )) * tempC );
  tempC = tempC - 273.15;            // Convert Kelvin to Celcius
  //Temp = (Temp * 9.0)/ 5.0 + 32.0; // Convert Celcius to Fahrenheit
  return tempC;
}

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  int readVal = analogRead(sensorPin); //Gets the readout from the Temp sensor.
  double temp =  Thermistor(readVal); //Sends the readout to the function that calculate the real Temp in Celsius
 
  Serial.print("Temperature (Celsius) = ");
  Serial.println(temp);  // display tempature
  double tempF = (temp * 9.0)/ 5.0 + 32.0; // Convert Celcius to Fahrenheit
  Serial.print("Temperature (Fahrenheit) = ");
  Serial.println(tempF);  // display tempature

  delay(500);
}

