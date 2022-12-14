
#include <Arduino.h>
#include <LiquidCrystal_74HC595.h>
#include <DHT.h>

/// LCD
#define SHIFT_DS 13    // Shift Reg Data (input)
#define SHIFT_SH_CP 12 // Shift Reg Clock
#define SHIFT_ST_CP 11 // Shift Reg Latch

//    LCD SIDE <> Shift Reg Side (starting from 0 (i.e. if RS is connected to 2, subtract 1))
#define LCD_RS 1 // NOT Arduino pin
#define LCD_E 3  // NOT Arduino pin
#define LCD_D4 4 // NOT Arduino pin
#define LCD_D5 5 // NOT Arduino pin
#define LCD_D6 6 // NOT Arduino pin
#define LCD_D7 7 // NOT Arduino pin

/// H-Bridge
#define HB_ENABLE 3 // Enable HBridge, also speed (*PWM*)
#define HB_1 2      // HBridge forward
#define HB_2 4      // HBridge reverse

#define LED_R 10
#define LED_G 9
#define LED_B 6

#define BUZZER 7

#define IR_IN 8
#define DHT_TMP_IN 5
#define THERMISTOR_IN A0
#define POT_IN A1

#define THERMISTORNOMINAL 10000 // resistance at 25 degrees C
#define TEMPERATURENOMINAL 25   // temp. for nominal resistance (almost always 25 C)
#define NUMSAMPLES 5            // how many samples to take and average, more takes longer but is more 'smooth'
#define BCOEFFICIENT 3950       // The beta coefficient of the thermistor (usually 3000-4000)
#define SERIESRESISTOR 10000    // the value of the 'other' resistor

//// Tweakable ////

#define LOW_THRESHOLD 350
#define HIGH_THRESHOLD 800

DHT dht = DHT(DHT_TMP_IN, DHT11);

LiquidCrystal_74HC595 lcd(SHIFT_DS, SHIFT_SH_CP, SHIFT_ST_CP, LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

float getThemistorTempF()
{
  static int thermistorSamples[NUMSAMPLES];
  uint8_t i;
  float average;

  // take N samples in a row, with a slight delay
  for (i = 0; i < NUMSAMPLES; i++)
  {
    thermistorSamples[i] = analogRead(THERMISTOR_IN);
    delay(10);
  }

  // average all the samples out
  average = 0;
  for (i = 0; i < NUMSAMPLES; i++)
  {
    average += thermistorSamples[i];
  }
  average /= NUMSAMPLES;

  // Serial.print("Average analog reading ");
  // Serial.println(average);

  // convert the value to resistance
  average = 1023 / average - 1;
  average = SERIESRESISTOR / average;
  // Serial.print("Thermistor resistance ");
  // Serial.println(average);

  float steinhart;
  steinhart = average / THERMISTORNOMINAL;          // (R/Ro)
  steinhart = log(steinhart);                       // ln(R/Ro)
  steinhart /= BCOEFFICIENT;                        // 1/B * ln(R/Ro)
  steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15); // + (1/To)
  steinhart = 1.0 / steinhart;                      // Invert
  steinhart -= 273.15;                              // convert absolute temp to C

  float f = (steinhart * 1.8) + 32;

  return f;
}

float getDHTTempF()
{
  float f = (dht.readTemperature() * 1.8) + 32;
  return f;
}

float getTempF()
{
  return (getThemistorTempF() + getDHTTempF()) / 2;
}

float getPot()
{
  return analogRead(POT_IN);
}

// speed between 0 and 255
void setMotor(int speed, boolean reverse)
{
  analogWrite(HB_ENABLE, HIGH);
  digitalWrite(HB_1, HIGH);
  digitalWrite(HB_2, LOW);
}

void setMotorOff() {
  analogWrite(HB_ENABLE, LOW);
  digitalWrite(HB_1, HIGH);
  digitalWrite(HB_2, LOW);
}

// Freq in hz
void buzzerOn(int freq)
{
  tone(BUZZER, freq);
}

void buzzerOff()
{
  noTone(BUZZER);
}

void setup()
{
  lcd.begin(20, 4);

  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);

  pinMode(HB_1, OUTPUT);
  pinMode(HB_2, OUTPUT);
  pinMode(HB_ENABLE, OUTPUT);
}

void loop()
{
  lcd.setCursor(0, 0);
  lcd.print("Temp:");
  lcd.print(getTempF());
  lcd.print("*f ");
  lcd.print(getDHTTempF());

  lcd.setCursor(0, 1);
  lcd.print("Pot: ");
  lcd.print(getPot());
  lcd.print("     ");

  digitalWrite(LED_R, LOW);
  digitalWrite(LED_G, LOW);
  digitalWrite(LED_B, LOW);

  if (getPot() > HIGH_THRESHOLD)
  {
    digitalWrite(LED_R, HIGH);
    setMotor(250, false);
    buzzerOn(262);
  }
  else if (getPot() > LOW_THRESHOLD)
  {
    buzzerOff();
    digitalWrite(LED_B, HIGH);
    setMotorOff();
  }
  else
  {
    buzzerOff();
    digitalWrite(LED_G, HIGH);
    setMotorOff();
  }

  delay(1000);
}
