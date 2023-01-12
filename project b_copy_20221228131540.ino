#include <LiquidCrystal_I2C.h>
#include <Wire.h>

const int trigPin = 4;
const int echoPin = 3;
const int servoPin = 9;

int dnky;
float angle = 0;
float changeValue = 1;
float decValue = -changeValue;
float incValue = changeValue;

LiquidCrystal_I2C lcd(0x27, 16, 2) ;
long calculate_distance() {

  long sure, uzaklik;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  sure = pulseIn(echoPin, HIGH);
  uzaklik = sure / 58.2;
  delay(50);
  return uzaklik;
}

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(servoPin, OUTPUT);
  lcd.begin();
}

void loop() {
  long distance = calculate_distance();
  if (angle == 180) {

    changeValue = decValue;  
  }
  else if (angle == 0) {

    changeValue = incValue;
  }
  angle = angle + changeValue;

  Serial.println(angle);
  Serial.println(distance);
  dnky = map(angle, 0, 180, 500, 2400);  //dnky = 2500;
  digitalWrite(9, HIGH);
  delayMicroseconds(dnky);

  digitalWrite(9, LOW);

  delayMicroseconds(2400 - dnky);

  delayMicroseconds(800);
  delay(17);

  while (distance < 15) {
    distance = calculate_distance();
    Serial.print(angle);
    lcd.setCursor(0, 0);
    lcd.print("Angle: " + String(angle) + " deg");
    lcd.setCursor(0, 1);
    lcd.print("Dist: " + String(distance) + " cm");
    delay(150);
    
  }
  
  lcd.setCursor(0, 0);
  lcd.print("Angle: " + String(angle) + " deg");
  lcd.setCursor(0, 1);
  lcd.print("Dist: " + String(distance) + " cm");
  delay(150);
}
