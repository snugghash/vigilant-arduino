//LCD1602
//You should now see your LCD1602 display the flowing characters "SUNFOUNDER" and "hello, world"
//Email:support@sunfounder.com
//Website:www.sunfounder.com
//2015.5.7 
#include <LiquidCrystal.h>// include the library code
#include <OneWire.h>
#include <stdio.h>

char array1[]="Temp C:         ";  //the string to print on the LCD
char array2[]="Temp F:         ";  //the string to print on the LCD
int tim = 350;  //the value of delay time
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8,9, 10, 11, 12, 13);
int numberOfCharacters = 16;


int DS18S20_Pin = 2; //DS18S20 Signal pin on digital 2
//Temperature chip i/o
OneWire ds(DS18S20_Pin);  // on digital pin 2

/*********************************************************/
void setup()
{
  lcd.begin(16, 2);  // set up the LCD's number of columns, rows: 
  Serial.begin(9600);
}
/*********************************************************/
void loop() 
{
    /*for ( int positionCounter1 = 0; positionCounter1 < numberOfCharacters; positionCounter1++)
    {
      lcd.scrollDisplayLeft();  //Scrolls the contents of the display one space to the left.
      lcd.print(array1[positionCounter1]);  // Print a message to the LCD.
      delay(tim);  //wait for 250 microseconds
    }
    lcd.clear();  //Clears the LCD screen and positions the cursor in the upper-left corner.
    lcd.setCursor(15,1);  // set the cursor to column 15, line 1
    for (int positionCounter2 = 0; positionCounter2 < numberOfCharacters; positionCounter2++)
    {
      lcd.scrollDisplayLeft();  //Scrolls the contents of the display one space to the left.
      lcd.print(array2[positionCounter2]);  // Print a message to the LCD.
      delay(tim);  //wait for 250 microseconds
    }
    lcd.clear();  //Clears the LCD screen and positions the cursor in the upper-left corner.
    */

    // Get temperature
    float temperature = getTemp(); //will take about 750ms to run
    Serial.println(temperature);
    
    lcd.setCursor(0,0);
    for (int pos = 0; pos<numberOfCharacters; pos++) {
      lcd.print(array1[pos]);
    }
    //char tempC[3];
    //sprintf(tempC, "%g", temperature);
    //puts(temperature)
    lcd.setCursor(8,0);
    lcd.print(temperature);
    
    lcd.setCursor(0,1);
    for (int pos = 0; pos<numberOfCharacters; pos++) {
      lcd.print(array2[pos]);
    }
    //char tempC[3];
    //sprintf(tempC, "%g", temperature);
    //puts(temperature)
    lcd.setCursor(8,1);
    lcd.print(toFarenheit(temperature));
    delay(tim);
}
/************************************************************/
float toFarenheit(float tmp) {
  return (tmp*9/5 + 32);
}

float getTemp(){
  //returns the temperature from one DS18S20 in DEG Celsius

  byte data[12];
  byte addr[8];

  if ( !ds.search(addr)) {
      //no more sensors on chain, reset search
      ds.reset_search();
      return -1000;
  }

  if ( OneWire::crc8( addr, 7) != addr[7]) {
      Serial.println("CRC is not valid!");
      return -1000;
  }

  if ( addr[0] != 0x10 && addr[0] != 0x28) {
      Serial.print("Device is not recognized");
      return -1000;
  }

  ds.reset();
  ds.select(addr);
  ds.write(0x44,1); // start conversion, with parasite power on at the end
  
  delay(750); // Wait for temperature conversion to complete

  byte present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE); // Read Scratchpad

  
  for (int i = 0; i < 9; i++) { // we need 9 bytes
    data[i] = ds.read();
  }
  
  ds.reset_search();
  
  byte MSB = data[1];
  byte LSB = data[0];

  float tempRead = ((MSB << 8) | LSB); //using two's compliment
  float TemperatureSum = tempRead / 16;
  
  return TemperatureSum;
  
}
