//LCD1602
//You should now see your LCD1602 display the flowing characters "SUNFOUNDER" and "hello, world"
//Email:support@sunfounder.com
//Website:www.sunfounder.com
//2015.5.7 
#include <LiquidCrystal.h>// include the library code
#include <OneWire.h>
#include <stdio.h>
#include<string.h>

char array1[]="Enter password  ";  //the string to print on the LCD
char array2[]="                ";  //the string to print on the LCD
int tim = 350;  //the value of delay time
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);
int numberOfCharacters = 16;


int button1 = 5;
int button2 = 6;
int button3 = 7;
int led1 = 2;
int led2 = 3;
int led3 = 4;


int v = -1;
int state = 0;
char pass[3], entered[3];

/*********************************************************/
void setup()
{
  pass[0] = '0';
  lcd.begin(16, 2);  // set up the LCD's number of columns, rows: 
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  digitalWrite(button1, HIGH);
  digitalWrite(button2, HIGH);
  digitalWrite(button3, HIGH);
  Serial.print("Enter length 3 (and base 10) password");
  
      entered[0] = '0';
      entered[1] = '0';
      entered[2] = '0';
}
/*********************************************************/
void loop() 
{
  

  if( (pass[0]== '0') && Serial.available()) {
    pass[0] = Serial.read();
    pass[1] = Serial.read();
    pass[2] = Serial.read();
    
    Serial.print(pass[0]);
    Serial.print(pass[1]);
    Serial.print(pass[2]);
    
  }
  if(pass[0] != '0') {
  //Reading pass
    v = digitalRead(button1);
    if(v == 1)
    { 
      entered[state] = '1';
      state++;
      delay(400);
    }
    v = digitalRead(button2);
    if(v == 1) {
      entered[state] = '2';
      state++; 
      delay(400);
    }
    v = digitalRead(button3);
    if(v == 1) {
      entered[state] = '3';
      state++;
      delay(400);
    }

    Serial.println(state);
    Serial.print(entered[0]);
    Serial.print(entered[1]);
    Serial.print(entered[2]);
    
    if (state == 3) {
      if(strcmp(pass,entered) == 0) 
        Serial.println("Success");
      else 
        Serial.println("Failure");
        
      state = 0;
      entered[0] = '0';
      entered[1] = '0';
      entered[2] = '0';
    }
  
  }
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

    
    /*lcd.setCursor(0,0);
    for (int pos = 0; pos<numberOfCharacters; pos++) {
      lcd.print(array1[pos]);
    }
    
    lcd.setCursor(0,1);
    for (int pos = 0; pos<numberOfCharacters; pos++) {
      lcd.print(array2[pos]);
    }*/
    //delay(tim);
}

