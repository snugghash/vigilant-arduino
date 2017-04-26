#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

// Servo stuff
#include <Servo.h> 
Servo doorControl;
int doorPosition = 0; 
int servoPin = 0;
 
/*
nRF Serial Chat
Desc : 
I worte this simple interactive serial chat over nRF that can be used for both sender 
and receiver as I swapped the TX & RX addr during read/write operation.

It read input from Serial Monitor and display the output to the other side
Serial Monitor or 16x2 LCD (if available)... like a simple chat program.

Max payload is 32 bytes for radio but the serialEvent will chopped the entire buffer
for next payload to be sent out sequentially.

*/

#include <LiquidCrystal.h>
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

LiquidCrystal lcd(2,3,4,5,6,7);

RF24 radio(9,10);

const uint64_t pipes[2] = { 0xf0f0f0f0e1LL, 0xf0f0f0f0c3LL };

boolean stringComplete = false;  // whether the string is complete
static int dataBufferIndex = 0;
boolean stringOverflow = false;
char charOverflow = 0;

char SendPayload[31] = "";
char RecvPayload[31] = "";
char serialBuffer[31] = "";

int forwardPin = 8; // Forward
int leftPin = 1; // Left
int rightPin = 0; // Right

void setup(void) {
  
  // Serial Monitor
  Serial.begin(57600);
  Serial.println();
  Serial.println(vigilance-string);    
  delay(500);

  // LCD
  lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(vigilance-string);
  lcd.setCursor(0,1);
  lcd.print("RACE!");


  // 
  printf_begin();
  radio.begin();
  
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MAX);
  radio.setChannel(70);
  
  radio.enableDynamicPayloads();
  radio.setRetries(15,15);
  radio.setCRCLength(RF24_CRC_16);

  radio.openWritingPipe(pipes[0]);
  radio.openReadingPipe(1,pipes[1]);  
  
  radio.startListening();
  radio.printDetails();


  
  pinMode(forwardPin, INPUT);
  pinMode(leftPin, INPUT);
  pinMode(rightPin, INPUT);
  digitalWrite(forwardPin, HIGH);
  digitalWrite(leftPin, HIGH);
  digitalWrite(rightPin, HIGH);

  // Door
  doorControl.attach(servoPin);
}

void loop(void) {
  
  //nRF_receive();
  serial_receive();
  
  
  delay(50);
  
} // end loop()

void serialEvent() {
  while (Serial.available() > 0 ) {
      char incomingByte = Serial.read();
      
      if (stringOverflow) {
         serialBuffer[dataBufferIndex++] = charOverflow;  // Place saved overflow byte into buffer
         serialBuffer[dataBufferIndex++] = incomingByte;  // saved next byte into next buffer
         stringOverflow = false;                          // turn overflow flag off
      } else if (dataBufferIndex > 31) {
         stringComplete = true;        // Send this buffer out to radio
         stringOverflow = true;        // trigger the overflow flag
         charOverflow = incomingByte;  // Saved the overflow byte for next loop
         dataBufferIndex = 0;          // reset the bufferindex
         break; 
      } 
      else if(incomingByte=='\n'){
          serialBuffer[dataBufferIndex] = 0; 
          stringComplete = true;
      } else {
          serialBuffer[dataBufferIndex++] = incomingByte;
          serialBuffer[dataBufferIndex] = 0; 
      }           
  } // end while()
} // end serialEvent()

void nRF_receive(void) {
  int len = 0;
  if ( radio.available() ) {
      bool done = false;
      while ( !done ) {
        len = radio.getDynamicPayloadSize();
        done = radio.read(&RecvPayload,len);
        delay(5);
      }
  
    RecvPayload[len] = 0; // null terminate string
    
    lcd.setCursor(0,0);
    lcd.print("R:");
    Serial.print("R:");
    lcd.setCursor(2,0);
    lcd.print(RecvPayload);
    Serial.print(RecvPayload);
    Serial.println();
    
    //Custom LED code
    
    RecvPayload[0] = 0;  // Clear the buffers    
  }  

} // end nRF_receive()

void serial_receive(void){
  
  if (stringComplete) { 
        strcat(SendPayload,serialBuffer);      
        // swap TX & Rx addr for writing
        radio.openWritingPipe(pipes[1]);
        radio.openReadingPipe(0,pipes[0]);  
        radio.stopListening();
        bool ok = radio.write(&SendPayload,strlen(SendPayload));

        //lcd.setCursor(0,1);
        //lcd.print("S:");
        Serial.print("S:");
        //lcd.setCursor(2,1);
        //lcd.print(SendPayload);
        Serial.print(SendPayload);          
        Serial.println();
        stringComplete = false;

        // restore TX & Rx addr for reading       
        radio.openWritingPipe(pipes[0]);
        radio.openReadingPipe(1,pipes[1]); 
        radio.startListening();
        SendPayload[0] = 0;
        strcpy(SendPayload,"");
        dataBufferIndex = 0;

        delay(100);
        
  } // endif

  char buttonState = '0';
  // Button communication code
  if(!digitalRead(forwardPin)) {
    Serial.print("Forward\n");
    buttonState = '1';
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("Forward");
  }
  if(!digitalRead(leftPin)) {
    Serial.print("Left\n");
    buttonState = '4';
    
      lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("Left");
  }
  if(!digitalRead(rightPin)) {
    if(buttonState == '1') {
      buttonState = '3';
      Serial.print("Forward-Right\n");
      
      lcd.clear();
      lcd.setCursor(0,1);
      lcd.print("Forward-Right");
    }
    else {
      Serial.print("Right\n");
      buttonState = '2';
      lcd.clear();
      lcd.setCursor(0,1);
      lcd.print("Right");
    }
  }
  

  if(buttonState == '0'){
    return;
  }
  else {
    SendPayload[0] = buttonState;
    stringComplete = true;
  }
  
} 
