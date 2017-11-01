#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
int i = 0;
int ledVert = 0 ;
int ledRouge = 1 ;
int cptFinCourseEst = 8 ;
int cptFinCourseWest = 9 ;

int positionActuel = 0 ;
char prenom[10] = "YOUSSEF";
char message[16] ="";

void setup() {
  pinMode(ledVert , OUTPUT);
  pinMode(ledRouge , OUTPUT);
  pinMode(cptFinCourseEst , INPUT);
  pinMode(cptFinCourseWest , INPUT);
  lcd.begin(16, 2);
  lcd.print("Test LCD 16X2");
  lcd.setCursor(0, 1);
  lcd.print("Youssef");
  initMotor();
}

void initMotor(){
  positionActuel = 0 ;
  while( digitalRead(cptFinCourseWest) == LOW){
    digitalWrite(ledVert , HIGH);
    delay(100);
    digitalWrite(ledVert , LOW);
    delay(50);
  }
  
  afficherMessageLcd("Position " , "Est 0°");  
}

void tounrnerLeMoteur(int versLaPositionEnDegre){
  int v = positionActuel - versLaPositionEnDegre ;
  
  if(versLaPositionEnDegre == positionActuel){
    
  }else if(positionActuel < versLaPositionEnDegre &&  digitalRead(cptFinCourseWest) == LOW){
    afficherMessageLcd("vers West -->","");
    while(v !=0 && digitalRead(cptFinCourseWest) == LOW){                // fin de cource    position <0     resultat
      v = v + 1 ;                                                        //         0        0               0
      digitalWrite(ledVert , HIGH);                                      //         0        1               1
      delay(500);                                                        //         1        0               0
      digitalWrite(ledVert , LOW);                                       //         1        1               0 
      delay(100);
    }
    positionActuel= versLaPositionEnDegre  ;
    afficherMessageLcd("Position","----");
  }else if(positionActuel > versLaPositionEnDegre){
    afficherMessageLcd("vers Est -->","");
    while(v !=0 && digitalRead(cptFinCourseEst) == LOW){                // fin de cource    position <0     resultat
      v = v - 1 ;                                                        //         0        0               0
      digitalWrite(ledRouge , HIGH);                                     //         0        1               1
      delay(500);                                                        //         1        0               0
      digitalWrite(ledRouge , LOW);                                      //         1        1               0 
      delay(100);
    }
    positionActuel= versLaPositionEnDegre  ;
    afficherMessageLcd("Position","++++");
  }
}

void afficherMessageLcd(char messageLigne1[16] , char messageLigne2[16] ){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(messageLigne1);
  lcd.setCursor(0, 1);
  lcd.print(messageLigne2);
}
void loop() {
   //lcd.setCursor(col, row) 
//  lcd.setCursor(0, 0);
//  lcd.print("LDR Value =");
//  
//  lcd.setCursor(0, 1);
 //  for (int i = 0 ; i <= 20 ; i++) {
//    sprintf(message,"%2d -> %s",i,prenom);
//    delay(500);
//  }

  int ldr = analogRead(A0);
  int cptValue = map(ldr , 0 , 1023 , 0 , 180 );   // mapper la conversion pour une rotation de 0 à 180 
   //lcd.setCursor(col, row) 
  //lcd.setCursor(0, 0);
  //lcd.print("LDR Value =");
  //lcd.setCursor(0, 1);
  //lcd.print(tmp);
  ///delay(500);
  //lcd.clear();

//  if(tmp == 0 ){
//    digitalWrite(ledRouge , LOW);
//      digitalWrite(ledVert , LOW);
//  }
//  if(tmp > 0 && tmp <= 32){
//    digitalWrite(ledRouge , LOW);
//    digitalWrite(ledVert , HIGH);    
//  }
//  if(tmp > 32 && tmp <= 64){
//    digitalWrite(ledRouge , HIGH);
//    digitalWrite(ledVert , LOW);    
//  }

  tounrnerLeMoteur(cptValue);

}
