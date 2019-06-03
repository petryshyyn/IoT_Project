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

const int buttonUp = 8;
const int buttonDown = 13;
int buttonValue;
int temperature = 23;
int button_old = 1;
int transistor = 3;

void setup()
{
  //TCCR1A = TCCR1A & 0xe0 | 1;
  //TCCR1B = TCCR1B & 0xe0 | 0x09;
  lcd.init();
  lcd.backlight();
  lcd.createChar(1, degree);
  Serial.begin(9600);
  dht.begin();

  pinMode(buttonUp, INPUT_PULLUP);
  pinMode(buttonDown, INPUT_PULLUP);
  pinMode(transistor, OUTPUT);
}

void result()
{
  int t = dht.readTemperature();
  lcd.setCursor(0, 0); 
  lcd.print("Temperature "); 
  lcd.setCursor(12, 0);
  lcd.print(t);
  lcd.setCursor(0, 1); 
  lcd.print(" Should be: ");
  lcd.setCursor(12, 1); 
  lcd.print(temperature);
  if ((digitalRead(buttonUp)==LOW)&&(button_old==1))
  {
    temperature = temperature + 1;
    buttonValue == buttonUp;
  }
     
  if ((digitalRead(buttonDown)==LOW)&&(button_old==1))
  {
    temperature = temperature - 1;
    buttonValue == buttonDown;
  }
    
  if ((temperature - t) >= 5)
  {
    analogWrite(transistor, 255);//255 204 153 102 51
  }
  else if (((temperature - t) == 4))
  {
     analogWrite(transistor, 204);
  }
    else if ((temperature - t) == 3)
    {
       analogWrite(transistor, 153);
    }
    else if ((temperature - t) == 2)
    {
       analogWrite(transistor, 102);
    }
    else if ((temperature - t) == 1)
    {
       analogWrite(transistor, 51);
    }else
    {
      analogWrite(transistor, 0);
    }
  }

void loop() 
{
  result();
  delay(90);
}
