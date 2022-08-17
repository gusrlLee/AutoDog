#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();


int incomingByte = 0;
int initFlag = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("12 channel Servo test!");
  pwm.begin();
  pwm.setPWMFreq(50);
}

void loop() {
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    Serial.println(incomingByte, DEC);

    if (incomingByte == 115) {
      if (initFlag == 0) {
        initServo();
        delay(1000);
        initFlag = 1;
      }
      sitUp();
    }
    
    if (incomingByte == 102) {
      forward();
    }
    
    if (incomingByte == 108) {
      leftTurn();
    }
    
    if (incomingByte == 114) {
      rightTurn();
    }
    
    if (incomingByte == 101) {
      turnOff();
      initFlag = 0;
    }
  }
  delay(50);
}
