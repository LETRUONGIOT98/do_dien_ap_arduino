#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define LCD_ADDRESS 0x27 // Địa chỉ I2C của LCD 1602
#define LCD_COLUMNS 16
#define LCD_ROWS 2

LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);

const int analogPin = A0; // Chân analog để đọc điện áp

#define nutnhan1 2
#define nutnhan2 3
#define relay1 4
#define relay2 5
unsigned long time;
unsigned long thoigian = 10000;///Thời gian sáng đèn

void setup(void) {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Dien Ap: ");
  pinMode(nutnhan1, INPUT_PULLUP);
  pinMode(nutnhan2, INPUT_PULLUP);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
}

void loop(void) {
  if(digitalRead(nutnhan1) == 0){
    digitalWrite(relay2, LOW);
    digitalWrite(relay1, HIGH);
    time = millis();
  }
  if(digitalRead(nutnhan2) == 0){
    digitalWrite(relay1, LOW);
    digitalWrite(relay2, HIGH);
    time = millis();
  }
  if(millis() - time >= thoigian){
    digitalWrite(relay1, LOW);
    digitalWrite(relay2, LOW);
  }
  int sensorValue = analogRead(analogPin);
  float voltage = sensorValue / 1023.0; // Đọc điện áp từ phân áp
  float voltage25V = voltage * 25.0; // Tính toán điện áp gốc từ phân áp

  lcd.setCursor(0, 1);
  lcd.print(voltage25V);
  lcd.print(" V   "); // In ra giá trị điện áp

  delay(1000); // Đợi 1 giây trước khi cập nhật lại
  
}
