/* ***************************************************
   file:    servo-movement-w-pad-arduino-due.ino
   author:  Andres Suarez and Nestor Brito
   date:    24/04/2016
   description: program for controlling  a robotic arm
   via gamepad using servos  and an Arduino Due.  This
   project was designed in order  to  be  showcased in
   "Semana  de  las  agrupaciones  AJ16" for  CITE. It
   took a long time but we finaly made it :)
 * ***************************************************
*/

#include <Servo.h>

Servo shoulder_1;
Servo shoulder_2;
Servo elbow_1;
Servo elbow_2;
Servo wrist;
Servo claw;

// gamepad buttons
// **set all buttons with a pull-down resistor
int button_up_shoulder = 32;
int button_down_shoulder = 38;

int button_up_elbow_1 = 34;
int button_down_elbow_1 = 40;

int button_up_elbow_2 = 48;
int button_down_elbow_2 = 49;

int button_right_wrist = 45;
int button_left_wrist = 44;

int claw_trigger = 50;

// position counters
int pos_shoulder_1 = 150;
int pos_shoulder_2 = 10;

int pos_elbow_1 = 165;
int pos_elbow_2 = 150;

int pos_wrist = 10;

int pos_claw = 40;

void setup() {

  // buttons setup
  pinMode(button_up_shoulder, INPUT);
  pinMode(button_down_shoulder, INPUT);

  pinMode(button_up_elbow_1, INPUT);
  pinMode(button_down_elbow_1, INPUT);

  pinMode(button_up_elbow_2, INPUT);
  pinMode(button_down_elbow_2, INPUT);

  pinMode(button_left_wrist, INPUT);
  pinMode(button_right_wrist, INPUT);

  pinMode(claw_trigger, INPUT);

  // attached servos
  shoulder_1.attach(2);
  shoulder_2.attach(3);

  elbow_1.attach(4);
  elbow_2.attach(5);

  wrist.attach(6);

  claw.attach(7);

  //reset servo position to initial value
  shoulder_1.write(pos_shoulder_1);
  shoulder_2.write(pos_shoulder_2);

  elbow_1.write(pos_elbow_1);
  elbow_2.write(pos_elbow_2);

  wrist.write(pos_wrist);

  claw.write(pos_claw);

}

void loop() {

  //SHOULDER MOVEMENT----------------------------------------------------------------------------

  if (digitalRead(button_up_shoulder) == HIGH && pos_shoulder_1 <= 150) {
    pos_shoulder_1 = pos_shoulder_1 + 1;
    pos_shoulder_2 = pos_shoulder_2 - 1;
  }

  if (digitalRead(button_down_shoulder) == HIGH && pos_shoulder_1 >= 10) {
    pos_shoulder_1 = pos_shoulder_1 - 1;
    pos_shoulder_2 = pos_shoulder_2 + 1;
  }

  shoulder_1.write(pos_shoulder_1); // sets the servos positions according to the position values
  shoulder_2.write(pos_shoulder_2);

  //ELBOW MOVEMENT-------------------------------------------------------------------------------

  //-----------Elbow #1-----------
  /*************************************
     HAVE TO FIX THE ANGLE LIMITS HERE
   *************************************/
  if (digitalRead(button_up_elbow_1) == HIGH && pos_elbow_1 <= 180) {
    pos_elbow_1 = pos_elbow_1 + 1;
  }

  if (digitalRead(button_down_elbow_1) == HIGH && pos_elbow_1 >= 10) {
    pos_elbow_1 = pos_elbow_1 - 1;
  }

  elbow_1.write(pos_elbow_1); // sets the servo position according to the position value

  //-----------Elbow #2-----------
  /*************************************
     HAVE TO FIX THE ANGLE LIMITS HERE
   *************************************/
  if (digitalRead(button_up_elbow_2) == HIGH && pos_elbow_2 <= 150) {
    pos_elbow_2 = pos_elbow_2 + 1;
  }

  if (digitalRead(button_down_elbow_2) == HIGH && pos_elbow_2 >= 10) {
    pos_elbow_2 = pos_elbow_2 - 1;
  }

  elbow_2.write(pos_elbow_2); // sets the servo position according to the position value

  //WRIST MOVEMENT-------------------------------------------------------------------------------

  if (digitalRead(button_right_wrist) == HIGH && pos_wrist <= 150) {
    pos_wrist = pos_wrist + 1;
  }

  if (digitalRead(button_left_wrist) == HIGH && pos_wrist >= 10) {
    pos_wrist = pos_wrist - 1;
  }

  wrist.write(pos_wrist); // sets the servo position according to the position value

  //CLAW MOVEMENT--------------------------------------------------------------------------------

  if (digitalRead(claw_trigger) == HIGH) {
    claw.write(105); // it was determined in calibration that an angle of 105 is best
  } else {
    claw.write(40); // returns claw to original position
  }

  delay(7); // waits for the servo to get there
}