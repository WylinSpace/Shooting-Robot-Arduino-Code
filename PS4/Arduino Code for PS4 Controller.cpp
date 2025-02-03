//Written by Wen//
//ALL RIGHT RESERVED//

#include <Arduino.h>
#include <PS4Controller.h>

// INPUT ZONE PLEASE ONLY TOUCH THE CODE HERE //
const int hybernating = 0;
const int zone_1 = 20;
const int zone_2 = 50;
const int zone_3 = 100;
const int bout_rate = 115200;
const char* MAC_Address = "88:13:bf:0a:02:96";
// INPUT ZONE PLEASE ONLY TOUCH THE CODE HERE // 

// PIN ASSIGNMENTS //
const int PUSH_SWITCH = 34;
const int READY_LED = 25;
const int NOT_READY_LED = 26;
const int ADJUST_MOTOR_SPEED_M1 = 13;
const int ADJUST_MOTOR_SPEED_M2 = 21;
const int SUPPLY_MOTOR_POWER_M1 = 22;
const int SUPPLY_MOTOR_POWER_M2 = 12;
const int SUPPLY_MOTOR_LEFT_WHEEL_M3A = 17;
const int SUPPLY_MOTOR_LEFT_WHEEL_M3B = 18;
const int SUPPLY_MOTOR_RIGHT_WHEEL_M4A = 15;
const int SUPPLY_MOTOR_RIGHT_WHEEL_M4B = 16;
// PIN ASSIGNMENTS //

// BUTTON STATES //
bool last_square_button_state = 0;
bool current_cross_button_state = 0;
bool last_cross_button_state = 0;
bool current_triangle_button_state = 0;
bool last_triangle_button_state = 0;
bool shooter_state = 0;
// BUTTON STATES //

// CODE //

void setup() {
  Serial.begin(bout_rate);
  PS4.begin(MAC_Address);

  pinMode(PUSH_SWITCH, INPUT);
  pinMode(READY_LED, OUTPUT);
  pinMode(NOT_READY_LED, OUTPUT);
  pinMode(ADJUST_MOTOR_SPEED_M1, OUTPUT);
  pinMode(ADJUST_MOTOR_SPEED_M2, OUTPUT);
  pinMode(SUPPLY_MOTOR_POWER_M1, OUTPUT);
  pinMode(SUPPLY_MOTOR_POWER_M2, OUTPUT);
  pinMode(SUPPLY_MOTOR_LEFT_WHEEL_M3A, OUTPUT);
  pinMode(SUPPLY_MOTOR_LEFT_WHEEL_M3B, OUTPUT);
  pinMode(SUPPLY_MOTOR_RIGHT_WHEEL_M4A, OUTPUT);
  pinMode(SUPPLY_MOTOR_RIGHT_WHEEL_M4B, OUTPUT);
}

void handleShooterState(bool &last_state, bool current_state, int zone) {
  if (current_state == 1 && last_state == 0) {
    shooter_state = !shooter_state;
    if (shooter_state) {
      digitalWrite(READY_LED,HIGH);
      Serial.printf("The motor is now shooting at power %i \n",zone);
      digitalWrite(SUPPLY_MOTOR_POWER_M1, HIGH);
      digitalWrite(SUPPLY_MOTOR_POWER_M2, HIGH);
      analogWrite(ADJUST_MOTOR_SPEED_M1, zone);
      analogWrite(ADJUST_MOTOR_SPEED_M2, zone);
    } else {
      digitalWrite(READY_LED,LOW);
      Serial.printf("The motor is now resting. \n");
      digitalWrite(SUPPLY_MOTOR_POWER_M1, LOW);
      digitalWrite(SUPPLY_MOTOR_POWER_M2, LOW);
      analogWrite(ADJUST_MOTOR_SPEED_M1, hybernating);
      analogWrite(ADJUST_MOTOR_SPEED_M2, hybernating);
    }
  }
}

void controlWheels() {
  if (PS4.LStickY() >= 30) { // Move Forward
    digitalWrite(SUPPLY_MOTOR_LEFT_WHEEL_M3A, HIGH);
    digitalWrite(SUPPLY_MOTOR_LEFT_WHEEL_M3B, LOW);
    digitalWrite(SUPPLY_MOTOR_RIGHT_WHEEL_M4A, LOW);
    digitalWrite(SUPPLY_MOTOR_RIGHT_WHEEL_M4B, HIGH);
  } else if (PS4.LStickY() <= -30) { // Move Backward
    digitalWrite(SUPPLY_MOTOR_LEFT_WHEEL_M3A, LOW);
    digitalWrite(SUPPLY_MOTOR_LEFT_WHEEL_M3B, HIGH);
    digitalWrite(SUPPLY_MOTOR_RIGHT_WHEEL_M4A, HIGH);
    digitalWrite(SUPPLY_MOTOR_RIGHT_WHEEL_M4B, LOW);
  } else if (PS4.RStickX() >= 30) { // Turn Right
    digitalWrite(SUPPLY_MOTOR_LEFT_WHEEL_M3A, LOW);
    digitalWrite(SUPPLY_MOTOR_LEFT_WHEEL_M3B, HIGH);
    digitalWrite(SUPPLY_MOTOR_RIGHT_WHEEL_M4A, LOW);
    digitalWrite(SUPPLY_MOTOR_RIGHT_WHEEL_M4B, HIGH);
  } else if (PS4.RStickX() <= -30) { // Turn Left
    digitalWrite(SUPPLY_MOTOR_LEFT_WHEEL_M3A, HIGH);
    digitalWrite(SUPPLY_MOTOR_LEFT_WHEEL_M3B, LOW);
    digitalWrite(SUPPLY_MOTOR_RIGHT_WHEEL_M4A, HIGH);
    digitalWrite(SUPPLY_MOTOR_RIGHT_WHEEL_M4B, LOW);
  } else { // Stop
    digitalWrite(SUPPLY_MOTOR_LEFT_WHEEL_M3A, LOW);
    digitalWrite(SUPPLY_MOTOR_LEFT_WHEEL_M3B, LOW);
    digitalWrite(SUPPLY_MOTOR_RIGHT_WHEEL_M4A, LOW);
    digitalWrite(SUPPLY_MOTOR_RIGHT_WHEEL_M4B, LOW);
  }
}

void loop() {
  if (digitalRead(PUSH_SWITCH) == HIGH || PS4.isConnected()) {
    digitalWrite(NOT_READY_LED,HIGH);

    controlWheels();

    
  } else {
    Serial.printf("The control devices is not yet connected.\n");
    digitalWrite(READY_LED, LOW);
    digitalWrite(SUPPLY_MOTOR_POWER_M1, LOW);
    digitalWrite(SUPPLY_MOTOR_POWER_M2, LOW);
    digitalWrite(ADJUST_MOTOR_SPEED_M1, LOW);
    digitalWrite(ADJUST_MOTOR_SPEED_M2, LOW);
    digitalWrite(SUPPLY_MOTOR_LEFT_WHEEL_M3A, LOW);
    digitalWrite(SUPPLY_MOTOR_LEFT_WHEEL_M3B, LOW);
    digitalWrite(SUPPLY_MOTOR_RIGHT_WHEEL_M4A, LOW);
    digitalWrite(SUPPLY_MOTOR_RIGHT_WHEEL_M4B, LOW);
    for(int i=0;i<=3;i++){
    digitalWrite(NOT_READY_LED, HIGH);
    delay(1000);
    digitalWrite(NOT_READY_LED, LOW);
    delay(1000);
    }
    delay(3000);
  }
  
  last_square_button_state = current_square_button_state;
  last_cross_button_state = current_cross_button_state;
  last_triangle_button_state = current_triangle_button_state;
  
  delay(50);
}

// CODE //
