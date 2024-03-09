#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int buzzerPin = 11; 
int pinLedVermelho = 13;
int pinLedVerde = 12;
int pinTrigger = 10;
int pinEcho = 9;
float pulse;
float dist_cm;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();
  lcd.backlight();
  
  pinMode(pinLedVermelho, OUTPUT);
  pinMode(pinLedVerde, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(pinTrigger, OUTPUT);
  pinMode(pinEcho, INPUT);
  digitalWrite(pinTrigger, LOW);
  Serial.begin(9600);
  
}

void loop() {
  digitalWrite(pinTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrigger, LOW);
  pulse = pulseIn(pinEcho, HIGH);
  dist_cm = pulse / 57;

  if (dist_cm < 30.00 and dist_cm > 10.01) {
  digitalWrite(pinLedVermelho, HIGH);
  digitalWrite(pinLedVerde, LOW);
  delay(800);
  tone (buzzerPin,1000,500);
  lcd.setCursor(0, 0);
  lcd.print("Distancia:");
  lcd.setCursor(10, 0);
  lcd.print(dist_cm);
  lcd.setCursor(14, 0);
  lcd.print("cm");
 
  } 
  else if (dist_cm >= 30.00) {
    digitalWrite(pinLedVerde, HIGH);
    digitalWrite(pinLedVermelho, LOW);
    delay(800);
    lcd.setCursor(0, 0);
  	lcd.print("Distancia:");
  	lcd.setCursor(10, 0);
  	lcd.print(dist_cm);
  	lcd.setCursor(14, 0);
  	lcd.print("cm");
    
  }
  else if (dist_cm < 10.00) {    
    digitalWrite(pinLedVermelho, HIGH);
    digitalWrite(pinLedVerde, LOW);
    delay(800);
    tone (buzzerPin,1000,500);
    lcd.setCursor(0, 0);
    lcd.print("PERIGO !!!");
    lcd.setCursor(10, 0);
    lcd.print(dist_cm);
    lcd.setCursor(14, 0);
    lcd.print("cm");
    
  }

  Serial.print("Valor do sensor de distância: ");
  Serial.println(dist_cm);
}
