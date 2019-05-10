#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#define DHTPIN A0
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27,16,2);
byte degree[8] =
{
  B00111,
  B00101,
  B00111,
  B00000,
  B00000,
  B00000,
  B00000,
};

const int buttonUp = 13;
const int buttonDown = 12;
int buttonValue;
float temperature = 23.0;
int button_old = 1;

void setup()
{
  lcd.init();
  lcd.backlight();
  lcd.createChar(1, degree);
  Serial.begin(9600);
  dht.begin();

  pinMode(buttonUp, INPUT_PULLUP);
  pinMode(buttonDown, INPUT_PULLUP);
}

void result()
{
    float t = dht.readTemperature();
    //float f = dht.readTemperature(true);
    lcd.setCursor(0, 0); 
    lcd.print("Temperature "); 
    lcd.setCursor(12, 0);
    lcd.print(t);
    lcd.print("C ");
    lcd.setCursor(0, 1); 
    lcd.print(" Should be: ");
    lcd.setCursor(12, 1); 
    lcd.print(temperature);
    if ((digitalRead(buttonUp)==LOW)&&(button_old==1))
      {
        temperature = temperature + 1;
        buttonValue == buttonUp;
      }
      
    if((digitalRead(buttonDown)==LOW)&&(button_old==1))
    {
      temperature = temperature - 1;
      buttonValue == buttonDown;
    }
  } 

void loop() 
{
  result();
  delay(90);
}
 
