/**
 * This program will help me create a studyBreak counter to
 * remind me the importance of working in between cycles.
 * There will be two method, one for 90 minutes(5400 seconds) and the other one
 * for 60(3600) minutes, each with a 10(600) minute break.
 */

 #include <Wire.h>
 #include "rgb_lcd.h"

 //Fields
 rgb_lcd lcd;
 const int colorR=242;
 const int colorG=249;
 const int colorB=243;
 
 //Logic
 int counter=0;
 boolean breakMode=false;
 const int minLowDel=5400;
 const int minHighDel=3600;
 const int minBreak=600;
 
 const int buttonPin=2;
 const int buzzerPin=3;
 boolean function1;
 
 
void setup() {
  lcd.begin(16,2); //setting the number of rows and columns
  lcd.setRGB(colorR,colorG,colorB);
  lcd.print("StudyCounter");
  delay(2400);
  
  //Incorporating button
  pinMode(buttonPin,INPUT);
  pinMode(buzzerPin,OUTPUT);
  function1= shortStudyMode();
  

}

void loop() {
  lcd.setCursor(0,1);
  int buttonValue = digitalRead(buttonPin);
  
  
    if(buttonValue==HIGH)
    {
      if(function1==false)
      {
        lcd.print("     ");
        function1=shortStudyMode();
        
        }
      else
      {
        lcd.print("       ");
       function1= longStudyMode();
        }
        counter=0;
      }
   
    
    
  
    
    
    if((counter==3600) && (not breakMode) && (function1)) // short-term study mode
    {
      breakMode= true;
      lcd.setRGB(255,249,30);
      delay(1000);
      digitalWrite(buzzerPin,HIGH);
      delay(50);
      digitalWrite(buzzerPin,LOW);
      delay(1000);
      lcd.setCursor(0,0);
      lcd.print("            ");
      lcd.setCursor(0,0);
      lcd.print("Take A Break");
      counter = 0;
      }
    else if((counter==5400) && (not breakMode)&& (not function1)) // Long-term study mode
    {
      breakMode= true;
      delay(1000);
      lcd.setRGB(250,10,10);
      digitalWrite(buzzerPin,HIGH);
      delay(50);
      digitalWrite(buzzerPin,LOW);
      delay(1000);
      lcd.setCursor(0,0);
      lcd.print("            ");
      lcd.setCursor(0,0);
      lcd.print("Take A Break");
      counter=0;
      }
    else if((breakMode) && (counter==600 )) //break time is up
    {
      breakMode=false;
      lcd.setRGB(0,100,70);
      lcd.setCursor(0,0);
      lcd.print("             ");
      lcd.setCursor(0,1);
      lcd.print("        "); // erase output
      lcd.setCursor(0,0);
      lcd.print("Go back to Work");
      delay(3000);
      counter=0;
      function1= shortStudyMode();
    }
    
    lcd.setCursor(0,1);
    lcd.print("              ");
    lcd.setCursor(0,1);
    lcd.print(counter); 
    counter++;
    delay(1000);
    
  

}

boolean shortStudyMode()
{
  lcd.setRGB(120,80,100);
  lcd.setCursor(0,0);
  lcd.print("                   ");
  lcd.setCursor(0,0);
  lcd.print("60 Min Study");
  delay(500);
  return true;
  }
boolean longStudyMode()
{
  lcd.setRGB(105,244,240);
  lcd.setCursor(0,0);
  lcd.print("90 Min Study");
  delay(500);
  return false;
  }
