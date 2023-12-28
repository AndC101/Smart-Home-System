/*
 * Author: Andrew Chen and Ethan Lin
 * Date: December 12th 2023
 * Description: Takes the voice command inputted from python and controls the LED or the fan. Displays to the LCD screen
 */


//include libraries and declare variables
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
String str;  
int redPin= 3;
int greenPin = 5;
int bluePin = 6;
int fanPin = 9;
String ledState = "off"; 
String fanState = "off";

//setup the LCD screen
const int rs = 13, en = 10, d4 = 11, d5 = 12, d6 = 4, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
        //start the serial and the outputs
        Serial.begin(115200);      
        
        //outputs calibration method to the lcd
        lcd.begin(16, 2);
        lcd.setCursor(0, 0);
        lcd.print("Silence please.");
        lcd.setCursor(0,1);
        lcd.print("Calibrating: ");

        //outputs a timed calibration message to the lcd
        //e.g. "Calibrating: 1"
        for(int i = 5; i >= 0; i--) {
          lcd.setCursor(13, 1);
          lcd.print(i);
          lcd.print(" ");
          delay(1000);
        }

        //clears the screen and tells user it is safe to speak now
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Calibrated!");
        lcd.setCursor(0,1);
        lcd.print("Speak now!");
        
        //set the pins to output
        pinMode(redPin, OUTPUT);
        pinMode(greenPin, OUTPUT);
        pinMode(bluePin, OUTPUT);
        pinMode(fanPin, OUTPUT);

        //set the LED pins as high
        digitalWrite(greenPin, HIGH);
        digitalWrite(redPin, HIGH);
        digitalWrite(bluePin, HIGH);
       
}

void loop() {

        //Checks if the serial is avaliable (from python)
        if (Serial.available() > 0) {
                str = Serial.readStringUntil('\n'); // read the inputted string

                //if condition for all the various voice commands

                //random color
                if(str == "random"){
                  printState("random", fanState); //printState updates the LCD display to the correct information 
                  setColor(random(0,255),random(0,255),random(0,255)); //sets colour to random RGB values
                }

                //white color
                else if (str == "turn on lamp" || str == "white"){
                  printState("white", fanState);

                  setColor(255, 255, 255);
                }

                //lamp off
                else if (str == "turn off lamp"){
                  printState("off", fanState);

                  setColor(0, 0, 0);
                } 

                //various different colors
                else if(str == "red") {
                  printState("red", fanState);
                  setColor(255, 0, 0);
                }

                else if(str == "blue") {
                  printState("blue", fanState);
                  setColor(0, 0, 255);
                }
              
                else if(str == "green"){
                  printState("green", fanState);
                  setColor(0, 255, 0);
                }

                else if(str =="purple") {
                  printState("purple", fanState);
                  setColor(128, 0, 128);
                }
                
                else if(str == "pink") {
                  printState("pink", fanState);
                  setColor(231, 84, 128);
                }

                else if(str =="light blue") {
                  printState("l-blue", fanState);
                  setColor(0, 255, 255);
                }

                else if(str =="yellow") {
                  printState("yellow", fanState);
                  setColor(204, 102,0); 
                }

                else if(str == "orange") {
                  printState("orange", fanState);
                  setColor(255, 50, 0);
                }

                //set the fan on and off
                else if(str == "fan on"){
                  printState(ledState, "on");
                  digitalWrite(fanPin, HIGH);

                }

                else if(str == "fan off") {
                  printState(ledState, "off");
                  digitalWrite(fanPin, LOW);
                }

                //turns led and fan off. Displays goodbye message
                else if(str == "goodbye"){
                  printState(ledState, "off");
                  digitalWrite(fanPin, LOW);
                  setColor(0, 0, 0);
                  lcd.clear();
                  lcd.setCursor(0, 0);
                  lcd.print("Goodbye!");
                  delay(3000);
                  lcd.clear();
                }

        }


}

//easier method to set the mode for the color of the lamp, given RGB values
void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(redPin, 255 - redValue);
  analogWrite(greenPin, 255 - greenValue);
  analogWrite(bluePin, 255 - blueValue);
}

//easier method for printing the state of the fan and LED to the screen for user friendliness
void printState(String led, String fan){
  //updates the state for fan and LED
  ledState = led;
  fanState = fan;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("LED: ");
  lcd.print(ledState);
  lcd.setCursor(0, 1);
  lcd.print("FAN: ");
  lcd.print(fanState);

} 