/*
 * MIT License - Copyright (c) 2020 Giuseppe Caliendo
 * arduino-quiz 
 */
#include <LiquidCrystal.h>

const unsigned int RS = 12;
const unsigned int EN = 11;
const unsigned int D4 = 5;
const unsigned int D5 = 4;
const unsigned int D6 = 3;
const unsigned int D7 = 2;

const unsigned int YES_BUTTON_PIN = 10;

LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  Serial.begin(9600);

  pinMode(YES_BUTTON_PIN, INPUT);
}

void loop() {
  
  if (Serial.available()) {
    delay(100);
    lcd.clear();

    // leggo tutti i caratteri dalla seriale
    while (Serial.available() > 0) {
      String correct_answer = Serial.readString();
      Serial.println(correct_answer);
      
      String msg = Serial.readString();
      unsigned int msgLength = msg.length();
      Serial.println(msg);
      unsigned int pos = 0; 
      
      // scorro carattere per carattere il messaggio
      for (int thisChar = 0; thisChar < msgLength; thisChar++) {
        lcd.print(msg.charAt(thisChar));
        delay(300);
        if(pos > 16){
          lcd.scrollDisplayLeft();  
        } else {
          pos++;
        }
      }

      lcd.clear();
      lcd.setCursor(0,1);
      lcd.print("YES=red/NO=yellow");

     while(digitalRead(YES_BUTTON_PIN) == LOW){
     }
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("YESSSA!");
      
    }// fine while 
      
  }// fine attesa della porta seriale
}
