#include <SeeedOLED.h>
#include <Wire.h>
#include <EEPROM.h>


/*
Timer F-stop pour tirage photo
*/


#define Safelightrelay 11
#define Enlargerrelay 12
#define Buzzer 10
#define StartExposure 9
#define ExpUp 8
#define ExpDn 7
#define StepChange 6
#define FocusSwitch 5


int BaseExposure = 100;
int NextCountDwn = 3000;
int Step = 1 / 3;
int ms;
unsigned long startcountdwn;

int hunstopstoms(int hundst) {  //Fonction qui convertit les centièmes de stops en millisecondes
  int result;
  result = 2 + 10 * hundst;
  return result;
}

void setup() {
  pinMode (Safelightrelay, OUTPUT);
  pinMode (Enlargerrelay, OUTPUT);
  pinMode (Buzzer, OUTPUT);
  pinMode (StartExposure, INPUT);
  pinMode (ExpUp, INPUT);
  pinMode (ExpDn, INPUT);
  pinMode (StepChange, INPUT);
  pinMode (FocusSwitch, INPUT);



  ms = hunstopstoms(100);

  Wire.begin();
  SeeedOled.init();  //initialze SEEED OLED display
  SeeedOled.clearDisplay();          //clear the screen and set start position to top left corner
  SeeedOled.setNormalDisplay();       //Set display to Normal mode
  SeeedOled.setPageMode();            //Set addressing mode to Page Mode
  SeeedOled.putString("Temps restant");
  SeeedOled.setTextXY(1,0);
  SeeedOled.putNumber(ms);
  Serial.begin(9600);
  digitalWrite(Safelightrelay, HIGH);


  
  Serial.print(ms);
}



void loop() {


  if (digitalRead(StartExposure) == HIGH) {
    int StartTime = millis();
    while (millis() < (millis() + 5000)) {
      Serial.print(ms);
      delay(1000);
    }
  }

  if (digitalRead(StepChange) == HIGH) {
    Step = Step / 2;
    if (Step == 1 / 24) {  //voir si on peut mettre un else ici
      Step = 1;
    }
  }

}


