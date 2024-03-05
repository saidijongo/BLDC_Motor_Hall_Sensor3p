
const byte en_A = 11;
const byte in_A = 5;
const byte en_B = 12;
const byte in_B = 6;
const byte en_C = 13;
const byte in_C = 7;

int speed_motor = 300;

void setup() {
  pinMode(en_A,OUTPUT);
  pinMode(in_A,OUTPUT);
  pinMode(en_B,OUTPUT);
  pinMode(in_B,OUTPUT);
  pinMode(en_C,OUTPUT);
  pinMode(in_C,OUTPUT);

  // start serial port at 9600 bps:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
}

void loop() {
  //increasing speed gradually by loop
  for (int i=0; i<20; i++) {
    motor_run();
  }
  
  if (speed_motor > 3) speed_motor = speed_motor - 1; //increasing speed
  Serial.println(speed_motor);  //print out speed to serial port
}

void motor_run() {
  digitalWrite(en_A,1);
  digitalWrite(in_A,0);
  digitalWrite(en_B,0);
  digitalWrite(in_B,0);
  digitalWrite(en_C,1);
  digitalWrite(in_C,1);
  delay(speed_motor); //Phase 1
  digitalWrite(en_A,1);
  digitalWrite(in_A,0);
  digitalWrite(en_B,1);
  digitalWrite(in_B,1);
  digitalWrite(en_C,0);
  digitalWrite(in_C,0);
  delay(speed_motor); //Phase 2
  digitalWrite(en_A,0);
  digitalWrite(in_A,0);
  digitalWrite(en_B,1);
  digitalWrite(in_B,1);
  digitalWrite(en_C,1);
  digitalWrite(in_C,0);
  delay(speed_motor); //Phase 3
  digitalWrite(en_A,1);
  digitalWrite(in_A,1);
  digitalWrite(en_B,0);
  digitalWrite(in_B,0);
  digitalWrite(en_C,1);
  digitalWrite(in_C,0);
  delay(speed_motor); //Phase 4
  digitalWrite(en_A,1);
  digitalWrite(in_A,1);
  digitalWrite(en_B,1);
  digitalWrite(in_B,0);
  digitalWrite(en_C,0);
  digitalWrite(in_C,0);
  delay(speed_motor); //Phase 5
  digitalWrite(en_A,0);
  digitalWrite(in_A,0);
  digitalWrite(en_B,1);
  digitalWrite(in_B,0);
  digitalWrite(en_C,1);
  digitalWrite(in_C,1);
  delay(speed_motor); //Phase 6
}

