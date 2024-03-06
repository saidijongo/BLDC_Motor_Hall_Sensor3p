// Define motor control pins
const byte en_A = 2;
const byte in_A1 = 3;
const byte in_A2 = 5;
const byte en_B = 4;
const byte in_B1 = 7;
const byte in_B2 = 8;

// Define Hall sensor pins
const byte hall_U = 9;
const byte hall_V = 10;
const byte hall_W = 11;

// Define serial command constants
const char CMD_CW = 'C';
const char CMD_CCW = 'W';
const char CMD_STOP = 'S';

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Set motor control pins as outputs
  pinMode(en_A, OUTPUT);
  pinMode(in_A1, OUTPUT);
  pinMode(in_A2, OUTPUT);
  pinMode(en_B, OUTPUT);
  pinMode(in_B1, OUTPUT);
  pinMode(in_B2, OUTPUT);

  // Set Hall sensor pins as inputs
  pinMode(hall_U, INPUT);
  pinMode(hall_V, INPUT);
  pinMode(hall_W, INPUT);

  // Initialize motor to stop
  motorStop();
}

void loop() {
  // Check if serial data is available
  if (Serial.available() > 0) {
    char command = Serial.read();
    switch (command) {
      case CMD_CW:
        Serial.print("CW");
        motorCW();
        break;
      case CMD_CCW:
        Serial.print("CCW");
        motorCCW();
        break;
      case CMD_STOP:
        Serial.print("STOP");
        motorStop();
        break;
      default:
        break;
    }
  }
}

void motorCW() {
  // Rotate motor clockwise
  digitalWrite(in_A1, HIGH);
  digitalWrite(in_A2, LOW);
  digitalWrite(en_A, 255); 
  digitalWrite(in_B1, HIGH);
  digitalWrite(in_B2, LOW);
  digitalWrite(en_B, 255); 
}

void motorCCW() {
  // Rotate motor counter-clockwise
  digitalWrite(in_A1, LOW);
  digitalWrite(in_A2, HIGH);
  digitalWrite(en_A, 255); 
  digitalWrite(in_B1, LOW);
  digitalWrite(in_B2, HIGH);
  digitalWrite(en_B, 255); 
}

void motorStop() {
  // Stop the motor
  digitalWrite(in_A1, LOW);
  digitalWrite(in_A2, LOW);
  digitalWrite(en_A, 0);
  digitalWrite(in_B1, LOW);
  digitalWrite(in_B2, LOW);
  digitalWrite(en_B, 0);
}
