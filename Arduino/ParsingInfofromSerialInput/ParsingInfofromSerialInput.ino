//1
int inChar = 0; //incoming characters from the Serial.Read
String inString = ""; //on this string we store the incoming characters


  void setup() {
Serial.begin(9600);
}

void loop() {

        if (Serial.available()) {
          int inChar = Serial.read();
            if (isDigit(inChar)) {
              // convert the incoming byte to a char
              // and add it to the string:
              inString += (char)inChar;
            }
            // if you get a newline, print the string,
            // then the string's value:
            if (inChar == '\n' && inString.toInt()<100) {
              Serial.print("The password so far is: ");
              Serial.println(inString.toInt());
            }
              
            if(inChar == '\n' && inString.toInt() > 100 && inString.toInt()<400) {
               Serial.print("The final password is: ");
               Serial.println(inString);
               char c1 = inString[0]; //Extracting the first character out of the in String
               char c2 = inString[1]; //Extracting the second character out of the in String 
               char c3 = inString[2]; //Extracting the third character out of the in String
               
               String s1 = "";
               s1.concat(c1); //Converting the character to String
               int p1 = s1.toInt(); //Converting the character to Integer
               
               String s2 = "";
               s2.concat(c2); //Converting the character to String
               int p2 = s2.toInt(); //Converting the character to Integer
               
               String s3 = "";
               s3.concat(c3); //Converting the character to String
               int p3 = s3.toInt(); //Converting the character to Integer
               
               Serial.println("You can close the Serial Monitor,"); 
               Serial.println("the password has been successfully updated");
            }

            if(inChar == '\n' && inString.toInt()>400) {
               Serial.println("The final password is: ");
               inString.remove(3,25); // Remove 25 characters starting at index=3
               Serial.println(inString);
               Serial.println("Please close the Serial Monitor,"); 
               Serial.println("the password has been successfully updated");
            }
            
        }  //end of the if Serial Available

}

