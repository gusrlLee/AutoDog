#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// 초기 값 0~180을 펄스길이150~600으로 매핑해주고, rad의 최소,최대를 150,600을 넘지 않게 해준다.
// Front Left up -> beta down, gamma up
//int fl_a = constrain(map(A, 0, 180, 150, 600), 150, 600);
int fl_b = constrain(map(80, 0, 180, 150, 600), 150, 600);
int fl_g = constrain(map(0, 0, 180, 150, 600), 150, 600);
// Front right up -> beta up, gamma down
//int fr_a = constrain(map(A, 0, 180, 150, 600), 150, 600);
int fr_b = constrain(map(30, 0, 180, 150, 600), 150, 600);
int fr_g = constrain(map(120, 0, 180, 150, 600), 150, 600);
// Hind Left up -> beta down, gamma up
//int hl_a = constrain(map(A, 0, 180, 150, 600), 150, 600);
int hl_b = constrain(map(100, 0, 180, 150, 600), 150, 600);
int hl_g = constrain(map(0, 0, 180, 150, 600), 150, 600);
// Hind right up -> beta up, gamma down
//int hr_a = constrain(map(A, 0, 180, 150, 600), 150, 600);
int hr_b = constrain(map(30, 0, 180, 150, 600), 150, 600);
int hr_g = constrain(map(110, 0, 180, 150, 600), 150, 600);

int initFlag = 0;

void  initServo(){
  pwm.setPWM(10,0,hl_g); 
  pwm.setPWM(14,0,hr_g);
  pwm.setPWM(9,0,hl_b); 
  pwm.setPWM(13,0,hr_b); 
  pwm.setPWM(1,0,fl_b); 
  pwm.setPWM(5,0,fr_b);
  pwm.setPWM(2,0,fl_g); 
  pwm.setPWM(6,0,fr_g);
}

void Forward_flb(){
  pwm.setPWM(1,0,fl_b-15);
  delay(500);
  pwm.setPWM(1,0,fl_b);
}
void Forward_frb(){
  pwm.setPWM(9,0,hl_b-15); 
  delay(500);
  pwm.setPWM(9,0,hl_b); 
}
void Forward_hlb(){
  pwm.setPWM(5,0,fr_b+15);
  delay(500);
  pwm.setPWM(5,0,fr_b);
}
void Forward_hrb(){ 
  pwm.setPWM(13,0,hr_b+15);
  delay(500);
  pwm.setPWM(13,0,hr_b);
}

void setup() {
  Serial.begin(115200);
  Serial.println("12 channel Servo test!");
  pwm.begin();
  pwm.setPWMFreq(50);
}

void loop() {
  if (initFlag == 0){
    initServo();
    initFlag = 1;
  }

  Forward_hlb();
  Forward_frb();
  Forward_flb();
  Forward_hrb();
  
  delay(10);
}
