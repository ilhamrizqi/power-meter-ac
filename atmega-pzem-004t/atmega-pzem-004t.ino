#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <PZEM004Tv30.h>

// declare global variables
LiquidCrystal_I2C lcd(0x27,20,4);
PZEM004Tv30 pzem(11, 12);
float voltage, current, power, energy, frequency, pf = 0; 

void setup()
{
  Serial.begin(9600);  
  lcd.init();  
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(F("IRS Power Meter"));
  lcd.setCursor(0,1);
  lcd.print(F("Version 1.0"));
  delay(1000);
  lcd.clear();  
}

void loop()
{
  // put your main code here, to run repeatedly:  
  readSensor();
  displaySensorValue();
  delay(1000);
}

void readSensor()
{
  voltage = pzem.voltage();
  if( !isnan(voltage) )
  {       
    Serial.print("Voltage: "); Serial.print(voltage); Serial.println("V");
  } else {
    voltage = 0;
    Serial.println("Error reading voltage");
  }

  current = pzem.current();
  if( !isnan(current) ){
    Serial.print("Current: "); Serial.print(current); Serial.println("A");
  } else {
    current = 0;
    Serial.println("Error reading current");
  }

  power = pzem.power();
  if( !isnan(power) ){
    Serial.print("Power: "); Serial.print(power); Serial.println("W");
  } else {
    power = 0;
    Serial.println("Error reading power");
  }

  energy = pzem.energy();
  if( !isnan(energy) ){
      Serial.print("Energy: "); Serial.print(energy,3); Serial.println("kWh");
  } else {
    energy = 0;
    Serial.println("Error reading energy");
  }

  frequency = pzem.frequency();
  if( !isnan(frequency) ){
    Serial.print("Frequency: "); Serial.print(frequency, 1); Serial.println("Hz");
  } else {
    frequency = 0;
    Serial.println("Error reading frequency");
  }

  pf = pzem.pf();
  if( !isnan(pf) ){    
    Serial.print("PF: "); Serial.println(pf);
  } else {
    pf = 0;
    Serial.println("Error reading power factor");
  }    
}

void displaySensorValue()
{
  static char str[6];
  dtostrf(voltage, 6, 2, str);
  lcd.setCursor(0,0);
  lcd.print(F("V:"));
  lcd.setCursor(3,0);
  lcd.print(str);

  dtostrf(current, 6, 2, str);
  lcd.setCursor(0,1);  
  lcd.print(F("I:"));
  lcd.setCursor(3,1);
  lcd.print(str);

  dtostrf(power, 6, 2, str);
  lcd.setCursor(0,2);
  lcd.print(F("P:"));
  lcd.setCursor(3,2);
  lcd.print(str);

  dtostrf(energy, 6, 2, str);
  lcd.setCursor(0,3);
  lcd.print(F("E:"));
  lcd.setCursor(3,3);
  lcd.print(str);

  dtostrf(frequency, 6, 0, str);
  lcd.setCursor(11,0);
  lcd.print(F("F :"));
  lcd.setCursor(14,0);
  lcd.print(str);

  dtostrf(pf, 6, 2, str);
  lcd.setCursor(11,1);
  lcd.print(F("PF:"));
  lcd.setCursor(14,1);
  lcd.print(str);  
}
