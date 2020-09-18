#include <Arduino.h>

#define DEBUG_MODE 0

#define LEDSTRIP_PIN 11
#define OZONATOR_PIN 12
#define FAN_PIN 10
#define SENSOR_PIN 9

#define EN_LED digitalWrite(LEDSTRIP_PIN, HIGH);
#define DISABLE_LED digitalWrite(LEDSTRIP_PIN, LOW);

#define EN_OZONATOR digitalWrite(OZONATOR_PIN, LOW);
#define DISABLE_OZONATOR digitalWrite(OZONATOR_PIN, HIGH);

#define EN_FAN digitalWrite(FAN_PIN, HIGH);
#define DISABLE_FAN digitalWrite(FAN_PIN, LOW);

uint8_t time;
bool sensorState;
bool workState = false;

void setup() 
{

  if(DEBUG_MODE)
  {
    Serial.begin(115200);
    delay(100);
    Serial.println("Debug Mode Enabled");
    Serial.println("---------------------------");
  }
  //Init pins
  if(DEBUG_MODE)
  {
    Serial.println("Start Initialize proccedure");
    Serial.println("---------------------------");
  }

  pinMode(LEDSTRIP_PIN, OUTPUT);
  pinMode(OZONATOR_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);
  pinMode(SENSOR_PIN, INPUT);
  delay(100);

  if(DEBUG_MODE)
  {
    Serial.print("Led Pin Status: ");
    Serial.println(digitalRead(LEDSTRIP_PIN));
    Serial.print("Ozonator Pin Status: ");
    Serial.println(digitalRead(OZONATOR_PIN));
    Serial.print("FAN Pin Status: " + digitalRead(FAN_PIN));
    Serial.println (digitalRead(FAN_PIN));
    Serial.print("Sensor Pin Status: ");
    Serial.println(digitalRead(SENSOR_PIN));
    Serial.println("Initializing pin done");
    Serial.println("---------------------------");
    delay(100);
  }
  //Init pin state
  DISABLE_FAN;
  DISABLE_LED;
  DISABLE_OZONATOR;

  sensorState = digitalRead(SENSOR_PIN);

  if(DEBUG_MODE)
  {
    Serial.println("Checking sensor status");
    Serial.println("---------------------------");
    if(sensorState)
    {
      Serial.println("Sensor OK, HIGH logical level");
      Serial.println("---------------------------");
      delay(100);
    }
    if(!sensorState)
    {
      Serial.println("Sensor in LOW logical level, check sensor or huamn near sensor");
      Serial.println("---------------------------");
      delay(100);
    }
    Serial.println("Setup done");
    Serial.println("Starting Loop");
    Serial.println("---------------------------");
    delay(200);
  }
}

void loop() 
{
  sensorState = digitalRead(SENSOR_PIN);
  if(!sensorState)
  {
    if(DEBUG_MODE)
    {
      Serial.println("Sensor LOW state detect");
      Serial.println("Wait 3 second");
      Serial.println("---------------------------");
    }
    delay(3000);

    if(DEBUG_MODE)
    {
      Serial.println("3 seconds gone");
      Serial.println("---------------------------");
    }
    sensorState = digitalRead(SENSOR_PIN);
    if(!sensorState)
    {
      if(DEBUG_MODE)
      {
        Serial.println("Human detected, turn ON ALL");
        Serial.println("---------------------------");
      }
      workState = true;
      if(DEBUG_MODE)
      {
        Serial.println("WorkState is True now");
        Serial.println("---------------------------");
      }
      EN_FAN;
      EN_LED;
      EN_OZONATOR;
      if(DEBUG_MODE)
      {
        Serial.print("Led Pin Status: ");
        Serial.println(digitalRead(LEDSTRIP_PIN));
        Serial.print("Ozonator Pin Status: ");
        Serial.println(digitalRead(OZONATOR_PIN));
        Serial.print("FAN Pin Status: " + digitalRead(FAN_PIN));
        Serial.println (digitalRead(FAN_PIN));
        Serial.print("Sensor Pin Status: ");
        Serial.println(digitalRead(SENSOR_PIN));
        Serial.println("---------------------------");
    delay(100);
      }
      delay(6000);
      if(DEBUG_MODE)
      {
        Serial.println("6 second gone, turning all off");
        Serial.println("---------------------------");
      }
      DISABLE_FAN;
      DISABLE_LED;
      DISABLE_OZONATOR;

      if(DEBUG_MODE)
      {
        Serial.print("Led Pin Status: ");
        Serial.println(digitalRead(LEDSTRIP_PIN));
        Serial.print("Ozonator Pin Status: ");
        Serial.println(digitalRead(OZONATOR_PIN));
        Serial.print("FAN Pin Status: " + digitalRead(FAN_PIN));
        Serial.println (digitalRead(FAN_PIN));
        Serial.print("Sensor Pin Status: ");
        Serial.println(digitalRead(SENSOR_PIN));
        Serial.println("---------------------------");
      }
      delay(200);
      if(DEBUG_MODE)
      {
        Serial.println("Main cycle done, go to huamn check");
        Serial.println("---------------------------");
      }
      while(workState)
      {
        sensorState = digitalRead(SENSOR_PIN);
        if(sensorState)
        {
          workState = false;
          if(DEBUG_MODE)
          {
            Serial.println("No human, workState is false now");
            Serial.println("---------------------------");
          }
          delay(200);
        }
        
      }
    }
  }

}