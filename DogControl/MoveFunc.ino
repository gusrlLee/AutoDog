void forward(){
  if (flFlag==1) {
    pwm.setPWM(1,0,fl_b-15);
    delay(80);
    hrFlag = 1;
    pwm.setPWM(1,0,fl_b);
    flFlag = 0;
  }
  if (hrFlag==1) { 
    pwm.setPWM(13,0,hr_b+15);
    delay(80);
    frFlag = 1;
    pwm.setPWM(13,0,hr_b);
    hrFlag = 0;
  }
  if (frFlag == 1) {
    pwm.setPWM(5,0,fr_b+15);
    delay(80);
    hlFlag = 1;
    pwm.setPWM(5,0,fr_b);
    frFlag = 0;
  }
  if (hlFlag == 1) {
    pwm.setPWM(9,0,hl_b-15); 
    delay(80);
    flFlag = 1;
    pwm.setPWM(9,0,hl_b);
    hlFlag = 0;
  }
}

void leftTurn() {
  Serial.println("left turn");
}

void rightTurn() {
  Serial.println("right turn");
}

void turnOff() {
  Serial.println("turn off");
  sitDown();
}

void sitUp() {
  if (sitFlag == 0) {
    for (int i = 0; i < 130; i++) {
      pwm.setPWM(10,0,hl_g--);
      pwm.setPWM(14,0,hr_g++);
      pwm.setPWM(2,0,fl_g--);
      pwm.setPWM(6,0,fr_g++);
      delay(10);
    }
    sitFlag = 1;
  }
}

void sitDown() {
  if (sitFlag == 1) {
    for (int i = 0; i < 130; i++) {
      pwm.setPWM(10,0,hl_g++);
      pwm.setPWM(14,0,hr_g--);
      pwm.setPWM(2,0,fl_g++);
      pwm.setPWM(6,0,fr_g--);
      delay(10);
    }
    sitFlag = 0;
  }
}
