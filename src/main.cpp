#include <Arduino.h>
#include <Adafruit_INA219.h>
#include <Wire.h>
#include "LiquidCrystal_I2C.h"
LiquidCrystal_I2C  lcd(PCF8574_ADDR_A21_A11_A01, 4, 5, 6, 16, 11, 12, 13, 14, POSITIVE);
Adafruit_INA219 ina;
void setup() {
  Serial.begin(9600);  
  lcd.begin();
  while (!lcd.begin())
  {
    Serial.println(F("El modulo PCF8574 no esta conectado"));
    delay(5000);   
  }
  while(!ina.begin()) 
  {
    Serial.println("No se encuentra el modulo INA219");
    delay(5000);    
  }
  ina.setCalibration_16V_400mA();
  lcd.print(F("Iniciando..."));
  delay(2000);  
  lcd.clear();
}
void loop() {
  float Voltaje = ina.getBusVoltage_V();
  float Corriente = ina.getCurrent_mA();
  float Potencia = ina.getPower_mW();
  if (Corriente < 0){Corriente = 0;}
  if (Voltaje < 0){Voltaje = 0;}
  if (Potencia < 0){Potencia = 0;}  
  
  lcd.setCursor(0,0);
  lcd.print("V=" + String(Voltaje));

  lcd.setCursor(8,0);
  lcd.print("mA=" + String(Corriente));

  lcd.setCursor(0,1);
  lcd.print("mW=" + String(Potencia));    

  delay(1000);
  lcd.clear();
}


