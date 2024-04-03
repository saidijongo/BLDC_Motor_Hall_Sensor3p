#define DIR_PIN 7

void setup() {
   pinMode(DIR_PIN, OUTPUT); 
   digitalWrite(DIR_PIN, HIGH);
   Serial.begin(9600); // Initialize serial communication
}

void loop() {
  delay(2000);
  digitalWrite(DIR_PIN, LOW);
  delay(5000);
  digitalWrite(DIR_PIN, HIGH);
  
  // Read serial input and execute corresponding commands
  if (Serial.available() > 0) {
    char command = Serial.read();
    switch (command) {
      case 'C': // Clockwise rotation
        digitalWrite(DIR_PIN, HIGH);
        Serial.println("Motor rotates Clockwise");
        break;
      case 'W': // Counter-clockwise rotation
        digitalWrite(DIR_PIN, LOW);
        Serial.println("Motor rotates Counter-clockwise");
        break;
      case 'S': // Stop motor
        digitalWrite(DIR_PIN, HIGH); // Stop by default (choose HIGH or LOW according to your motor)
        Serial.println("Motor stopped");
        break;
      default:
        Serial.println("Invalid command");
        break;
    }
  }
}
