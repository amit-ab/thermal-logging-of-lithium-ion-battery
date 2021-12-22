#include <RTC.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <LiquidCrystal.h>

File myFile;
char filename[10];

static DS3231 RTC;

// voltage between thermistor and known resistor = V0//
float Vo;
//Known resistance value, R1= 100k ohm//
int Vin=1023.0;
float R1 = 10000.0;
float logR2, R2, T1, T2, T3, T4, T5, T6 ;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

LiquidCrystal lcd(2 , 3, 4, 5, 6, 7);

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
  RTC.begin();

  RTC.setHourMode(CLOCK_H24);
  RTC.setDay(28);
  RTC.setMonth(8);
  RTC.setYear(2021);

  RTC.setHours(11);
  RTC.setMinutes(45);
  RTC.setSeconds(56);

  RTC.setWeek(5);

  if (!SD.begin(53)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
  pinMode(53, OUTPUT);
}
void loop() 
  {
  int day=RTC.getDay();

  getFileName();
  Serial.println(filename);
  myFile = SD.open(filename, FILE_WRITE);
  
  //rtc code
  switch (RTC.getWeek())
  {
    case 1:
      Serial.print("SUN");
      break;
    case 2:
      Serial.print("MON");
      break;
    case 3:
      Serial.print("TUE");
      break;
    case 4:
      Serial.print("WED");
      break;
    case 5:
      Serial.print("THU");
      break;
    case 6:
      Serial.print("FRI");
      break;
    case 7:
      Serial.print("SAT");
      break;
  }
  Serial.print(" ");
  Serial.print(RTC.getDay());
  Serial.print("-");
  Serial.print(RTC.getMonth());
  Serial.print("-");
  Serial.print(RTC.getYear());

  Serial.print(" ");

  Serial.print(RTC.getHours());
  Serial.print(":");
  Serial.print(RTC.getMinutes());
  Serial.print(":");
  Serial.print(RTC.getSeconds());
  Serial.print(" ");


  //rtc code ends
  
  //thermistor and lcd code starts
  Vo = analogRead(A0);
  R2 = R1 * (Vin / Vo - 1.0);//voltage divider formula
  logR2 = log(R2);
  T1 = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));//equation to convert resistance to temperature//T1 = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  T1 = T1 - 273.15;
  
  Serial.println(" ");
  Serial.print("Temp T1=  ");
  Serial.print(T1);
  Serial.print(" C");

  //Printing temperature T2 on the serial monitor//
  Vo = analogRead(A1);
  R2 = R1 * (Vin / (float)Vo - 1.0);
  logR2 = log(R2);
  T2 = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));//T2 = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  T2 = T2 - 273.15;
  //T2 = 25;
   
 
  Serial.println(" ");
  Serial.print("Temp T2=  ");  
  Serial.print(T2);
  Serial.print(" C");

  //Printing temperature T3 on the serial monitor//
  Vo = analogRead(A2);
  R2 = R1 * (Vin / (float)Vo - 1.0);
  logR2 = log(R2);
  T3 = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));//T3 = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  T3 = T3 - 273.15;
  //T3 = 25;
 
  Serial.println(" ");
  Serial.print("Temp T3=  ");
  Serial.print(T3);
  Serial.print(" C");
  
  //Printing temperature T4 on the serial monitor//
  
  Vo = analogRead(A3);
  R2 = R1 * (Vin / (float)Vo - 1.0);
  logR2 = log(R2);
  T4 = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));//T4 = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  T4 = T4 - 273.15;
  //T4 = 25;
  Serial.println(" ");
  Serial.print("Temp T4=  ");
  Serial.print(T4);
  Serial.print(" C");
  
  //Printing temperature T5 on the serial monitor//
   
  Vo = analogRead(A4);
  R2 = R1 * (Vin / (float)Vo - 1.0);
  logR2 = log(R2);
  T5 = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));//T5 = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  T5 = T5 - 273.15;
  //T5 = 25;
  Serial.println(" ");
  Serial.print("Temp T5=  ");
  Serial.print(T5);
  Serial.print(" C");

  //Printing temperature T6 on the serial monitor//
  
  Vo = analogRead(A5);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T6 = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));//T6 = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  T6 = T6 - 273.15;
  //T6 = 25;
  
 
  Serial.println(" ");
  Serial.print("Temp T6=  ");
  Serial.print(T6);
  Serial.print(" C");
  
  //delay(1000);
  lcd.setCursor(0,0);
  lcd.print("T1:");
  lcd.print(T1,1);
  lcd.print("  ");
  lcd.print("T2:");
  lcd.println(T2,1);
  delay(750);

  lcd.setCursor(0,1);
  lcd.print("T3:");
  lcd.print(T3,1);
  lcd.print("  ");
  lcd.print("T4:");
  lcd.println(T4,1);
  delay(750);
  lcd.clear();
  
  lcd.setCursor(0,0);
  lcd.print("T5:");
  lcd.print(T5,1);
  lcd.print("  ");
  lcd.print("T6:");
  lcd.println(T6,1);
  delay(1000);
  lcd.clear();

  
  String dataString=String(String(RTC.getHours())+","+String(RTC.getMinutes())+","+String(RTC.getSeconds())+" T1="+String(T1)+" T2="+String(T2)+" T3="+String(T3)+" T4="+String(T4)+" T5="+String(T5)+" T6="+String(T6));
  myFile.println(dataString);
  myFile.close();
  delay(1000);
  
}
void getFileName(){

  sprintf(filename, "%02d-%02d.txt", RTC.getDay(),RTC.getMonth());
}
