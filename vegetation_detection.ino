
// include the library code:
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
SoftwareSerial GSM(0,1);
const int Switch=8;
const int Sensor=9;
int Buzzer=13;
unsigned long lastScroll =0;
int scrollCount=0;

void setup() {
  pinMode(Sensor,INPUT);
  pinMode(Buzzer,OUTPUT);
  Serial.begin(9600);
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("SYSTEM");
  lcd.setCursor(0, 1);
  lcd.print("STARTING...");
  delay(100);
  lcd.clear();
}
void loop() {
  // Print a message to the LCD.  
  if(digitalRead(Switch)==HIGH) {     
    lcd.setCursor(0, 0);
    lcd.print("Detection System ");
    lcd.setCursor(0, 1);
    lcd.print("    ACTIVATED    ");

    if(digitalRead(Sensor)==HIGH) {
      // Print a message to the LCD.
      lcd.setCursor(0, 0);
      lcd.print("VegetationError!");
      lcd.setCursor(0, 1);
      lcd.print("Sending SMS.....");
      //Turn on Alarm here
      digitalWrite(13,HIGH);  //Turn on Alarm connect buzzer to this pin through transistor
      sendSMS();
      delay(100);
    }
    else {
      digitalWrite(13,LOW);    //Turn off alarm
    }
  }
  else {
    lcd.setCursor(0, 0);
    lcd.print("Detection System ");
    lcd.setCursor(0, 1);
    lcd.print("   DEACTIVATED     ");
  }
}
void sendSMS() {
  Serial.println("AT+CMGD=1");    //Delete previous sent SMS
  delay(100);
  Serial.println("AT+CMGF=1");   //Set SMS configuration
  delay(100);
  Serial.print("AT+CMGW=");          //Write New SMS
  Serial.write(34);                  //Double quotes ASCII Code
  Serial.print("+233*********");         //Enter Your Mobile number
  Serial.write(34);
  Serial.println();                  //Send return
  delay(400);
  Serial.println("Alert : VEGETATION DETECTED!!!");
  delay(100);
  Serial.write(26); //Cntrl+Z to send SMS
  delay(1000);
  Serial.println("AT+CMSS=1");      //Send SMS from memory location 1
  delay(100);
}
