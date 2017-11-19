// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!

#include <AFMotor.h>

AF_DCMotor motorA(1);
AF_DCMotor motorB(2);
AF_DCMotor motorC(3);
AF_DCMotor motorD(4);

boolean packetEnded = false;
boolean backward = false;
int steps = 0;
AF_DCMotor activeMotor;

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Connected!");
}

void loop() {
  while(Serial.available() > 0){
    // Read the incoming data, check if negative, or end of command, of motor letter
    char aChar = Serial.read();
    if(aChar == '-'){
      backward = true;
    }
    else if(aChar == ';'){
      packetEnded = true;
    }
    else if(aChar >='0' && aChar <= '9'){
      steps *= 10;
      steps += aChar -'0';
    }
    else if(aChar == 'a'){
      activeMotor = motorA;
    }
    else if(aChar == 'b'){
      activeMotor = motorB;
    }
    else if(aChar == 'c'){
      activeMotor = motorC;
    }
    else if(aChar == 'd'){
      activeMotor = motorD;
    }
  }

  if(packetEnded){
    activeMotor.setSpeed(steps);
    if(backward){
      activeMotor.run(BACKWARD);
    } else {
      activeMotor.run(FORWARD);
    }

    //Reset control values.
    steps = 0;
    backward = false;
    packetEnded = false;
  }
}
