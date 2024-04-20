
//include the library code:
//#include <NewPing.h>
//#include <AFMotor.h>

//IR sensor pins
#define LEFT 2            // Right IR sensor connected to analog pin A2 of Arduino Uno:
#define RIGHT 3           // Left IR sensor connected to analog pin A3 of Arduino Uno:

//Ultrasonic sensor pins
#define TRIGGER_PIN A2    // Trigger pin connected to analog pin A1 of Arduino Uno:
#define ECHO_PIN A3       // Echo pin connected to analog pin A0 of Arduino Uno:

//motor driver pins
#define IN4 12
#define IN3 11
// motor 1 control pins
#define IN2 10
#define IN1 9

int directn;

float pduration_us;

unsigned int distanceRead = 0;  //Variable to store ultrasonic sensor distance:
unsigned int Right_Value = 0;   //Variable to store Right IR sensor value:
unsigned int Left_Value = 0;    //Variable to store Left IR sensor value:
float startRange = 15.0, bufferRange = 60.0;

void setup() {  // the setup function runs only once when power on the board or reset the board:

  Serial.begin(115200);   //initailize serial communication at 9600 bits per second:
  pinMode(RIGHT, INPUT);  //set analog pin RIGHT as an input:
  pinMode(LEFT, INPUT);   //set analog pin RIGHT as an input:
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(TRIGGER_PIN, OUTPUT);  //set analog pin RIGHT as an input:
  pinMode(ECHO_PIN, INPUT);
  
}

void loop() {
  delay(50);                       //wait 50ms between pings:
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
 
  pduration_us = pulseIn(ECHO_PIN, HIGH);
  distanceRead = 0.017 * pduration_us;
  
  Serial.print("distance: ");
  Serial.print(distanceRead);
  Serial.println(" cm");

  Right_Value = !digitalRead(RIGHT);  // read the value from Right IR sensor:
  Left_Value = !digitalRead(LEFT);    // read the value from Left IR sensor:

  Serial.print("RIGHT: ");
  Serial.println(Right_Value);  // print the right IR sensor value in serial monitor:
  Serial.print("LEFT: ");
  Serial.println(Left_Value);  //print the left IR sensor value in serial monitor:

  if ((distanceRead > 1) && (distanceRead < startRange)) {
    Serial.println("Stop");
    haltMotion();

  } else if ((distanceRead > startRange) && (distanceRead < bufferRange)) {
    Serial.println("Move Forward");
    forward();

  } else if (distanceRead > bufferRange) {

    if ((Right_Value == 1) && (Left_Value == 0)) {
      //Turn right
      Serial.println("Turn right");
      rightward();

    } else if ((Right_Value == 0) && (Left_Value == 1)) {
      //Turn left
      Serial.println("Turn left");
      leftward();

    } else  if ((Right_Value == 0) && (Left_Value == 0)) {
      //Turn left
      Serial.println("Do nothing");
      haltMotion();
    }
    else  if ((Right_Value == 1) && (Left_Value == 1)) {
      //Turn left
      Serial.println("Do nothing");
      haltMotion();
    }
  } else {
    Serial.println("Do nothing");
    haltMotion();
  }
}
void backward() {
  // motor 1 run Clockwise
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  // motor 2 run Anticlockwise
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void forward() {
  // motor 1 run Anticlock wise
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  // motor 2 run Clockwise
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void rightward() {
  // motor 1 run
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  // motor 2 stop
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void leftward() {
  // motor 1 stop
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  // motor 2 run
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void haltMotion() {
  // All motor stops
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
