#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10  // RFID SS_PIN
#define RST_PIN 9   // RFID RST_PIN

#define TRIGGER_PIN_1 3  // Ultrasonic sensor 1 trigger pin
#define ECHO_PIN_1 2     // Ultrasonic sensor 1 echo pin

#define TRIGGER_PIN_2 7  // Ultrasonic sensor 2 trigger pin
#define ECHO_PIN_2 6     // Ultrasonic sensor 2 echo pin

#define MIN_DISTANCE 20  // Minimum distance to follow the user (adjust as needed)

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  pinMode(TRIGGER_PIN_1, OUTPUT);
  pinMode(ECHO_PIN_1, INPUT);
  pinMode(TRIGGER_PIN_2, OUTPUT);
  pinMode(ECHO_PIN_2, INPUT);
  // Initialize motor control pins and other hardware as needed
}

void loop() {
  // RFID user identification
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    String uid = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      uid.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""));
      uid.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    // Check if the detected RFID tag is associated with a user and fetch user information.
    
    // Perform user identification and set user-specific behavior.
  }

  // Ultrasonic distance measurement for sensor 1
  long duration_1, distance_1;
  digitalWrite(TRIGGER_PIN_1, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN_1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN_1, LOW);
  duration_1 = pulseIn(ECHO_PIN_1, HIGH);
  distance_1 = (duration_1 / 2) / 29.1;  // Calculate distance in centimeters.

  // Ultrasonic distance measurement for sensor 2
  long duration_2, distance_2;
  digitalWrite(TRIGGER_PIN_2, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN_2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN_2, LOW);
  duration_2 = pulseIn(ECHO_PIN_2, HIGH);
  distance_2 = (duration_2 / 2) / 29.1;  // Calculate distance in centimeters.

  if (distance_1 < MIN_DISTANCE || distance_2 < MIN_DISTANCE) {
    // User is too close according to either sensor, follow the user.
    
    // Implement motor control to follow the user.
  } else {
    // User is out of range, stop or wait.
    
    // Implement motor control to stop or wait.
  }
}
