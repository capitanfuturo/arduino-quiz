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

const unsigned int YES_BUTTON_PIN = 9;
const unsigned int NO_BUTTON_PIN = 10;

bool isTrue = false;
bool isFalse = false;

LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  lcd.blink();
  
  Serial.begin(9600);

  pinMode(YES_BUTTON_PIN, INPUT);
  pinMode(NO_BUTTON_PIN, INPUT);
}


void buttonsWait(){
  int buttonState = 0;
  while(1){
    int buttonYesState = digitalRead(YES_BUTTON_PIN);
    int buttonNoState = digitalRead(NO_BUTTON_PIN); 
    if (buttonYesState == HIGH) {
      isTrue = true;
      return;
    } else if(buttonNoState == HIGH){
      isFalse = true;
      return;
    }
  }
}

void loop() {
  
  if (Serial.available()) {
    delay(100);
    lcd.clear();
    
    while (Serial.available() > 0) {
      String correct_answer = Serial.readString();
      Serial.println(correct_answer);
      
      String msg = Serial.readString();
      unsigned int msgLength = msg.length();
      Serial.println(msg);
      unsigned int pos = 0; 
      
      lcd.setCursor(0,0);
      int currentCursor = 0;
      
      for (int thisChar = 0; thisChar < msgLength; thisChar++) {
        lcd.print(msg.charAt(thisChar));
        delay(200);
        
        if(currentCursor == 15){
          lcd.setCursor(0,1);  
        }else if(currentCursor == 31){
          delay(1000);
          lcd.clear();
          lcd.setCursor(0,0);
          currentCursor = 0;
        }
        currentCursor++;
        pos++;
      }

      delay(1000);
      lcd.setCursor(0,1);
      lcd.print("YES=yellowNO=red");
      
      while(!isTrue && !isFalse){
        buttonsWait();
      }
      lcd.clear();
      lcd.setCursor(0,0);
      if(isTrue && correct_answer.equals("TRUE")){
        lcd.print("YOU WIN!");
      }else{
        lcd.print("YOU LOOSE!");  
      }
      
    }// fine while 
      
  }// fine attesa della porta seriale
}
