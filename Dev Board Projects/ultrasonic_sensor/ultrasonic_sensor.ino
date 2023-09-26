#include <LiquidCrystal_I2C.h>

/*
  read distance from ultrasonic sensor
*/
LiquidCrystal_I2C lcd(0x27, 16, 2);


#define trigPin  8
#define  echoPin  7
long duration;
int distance;
#define Water_pump 6
#define red_led 5
#define green_led 4
#define yellow_led 3
#define buzzer_indicator3 13
#define buzzer_indicator2 12
#define buzzer_indicator1 11

void setup() {
  //initializes 
  Serial.begin(115200);
  
  lcd.begin();
  lcd.backlight();
  lcd.cursor();
  lcd.clear();
 
  pinMode(trigPin, OUTPUT); //trig emits sound waves
  pinMode(echoPin, INPUT);  //echo receives sound waves
 
}

void loop() {
  
  digitalWrite(trigPin, LOW);   //set trig pin low to produce no waves
  delayMicroseconds(2);         //let low persist 2 microseconds
  digitalWrite(trigPin, HIGH);  //set trig pin high to produce waves
  delayMicroseconds(10);        //let high persist 10 microseconds
  digitalWrite(trigPin, LOW);   //set trig pin low to produce no waves

  duration = pulseIn(echoPin, HIGH);  //determine how time for sound waves to return
  distance = (duration / 2) * 0.0344; //calculate distance based on time and speed of sound
  Serial.print(" | ");
  Serial.print(duration);
  Serial.print(" | ");
  Serial.print(distance); //print out distance
  Serial.println(" cm");

  delay(100);
  //water level insufficient
  if (distance >= 130) {
    Serial.print("water-level = low");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("water-level ");
    lcd.setCursor(0,1);
    lcd.print("= low");
    lcd.setCursor(6,1);
    lcd.print("dis=");
    lcd.print(distance);
    lcd.print("cm");
    digitalWrite(Water_pump,HIGH );
    digitalWrite(red_led, HIGH);
    digitalWrite(buzzer_indicator3, HIGH);
   
  }

  //water is mid-level 
  if(distance <=95 && distance >=52 ) {
    Serial.print("water-level = mid ");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("water-level ");
    lcd.setCursor(0,1);
    lcd.print("= middle");
    lcd.setCursor(6,1);
    lcd.print("dis=");
    lcd.print(distance);
    lcd.print("cm");
    digitalWrite(Water_pump,LOW );
    digitalWrite(yellow_led, LOW);
    digitalWrite(buzzer_indicator2, HIGH);
  }

  //water is full
 if(distance >=5 && distance <=50 ) {
    Serial.print("water-level = full");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("water-level ");
    lcd.setCursor(0,1);
    lcd.print("= full");
    lcd.setCursor(6,1);
    lcd.print("dis=");
    lcd.print(distance);
    lcd.print("cm");
    digitalWrite(Water_pump, LOW );
    digitalWrite(green_led, LOW);
    digitalWrite(buzzer_indicator1, HIGH);
  }
  /* //water is going down 
  if(distance <=--44 && distance >=30 ) {
    Serial.print("water level = ");
    //lcd.print("water level = ");
    //digitalWrite(Water_pump,LOW );
    //digitalWrite(green_led, LOW);
    //digitalWrite(buzzer_indicator1, HIGH);
    }*/
}





