/*
 * CD-ROM Sensored BLDC motor control using Arduino.
 * This is a free software with NO WARRANTY.
 * https://simple-circuit.com/
 */
 
byte bldc_step, motor_speed;
 
void setup() {
  DDRD  |= 0x1C;           // Configure pins 2, 3 and 4 as outputs
  PORTD  = 0x00;
  DDRB  |= 0x0E;           // Configure pins 9, 10 and 11 as outputs
  PORTB  = 0x31;
  // Timer1 module setting: set clock source to clkI/O / 1 (no prescaling)
  TCCR1A = 0;
  TCCR1B = 0x01;
  // Timer2 module setting: set clock source to clkI/O / 1 (no prescaling)
  TCCR2A = 0;
  TCCR2B = 0x01;
  // ADC module configuration
  ADMUX  = 0x60;                     // Configure ADC module and select channel 0
  ADCSRA = 0x84;                     // Enable ADC module with 16 division factor (ADC clock = 1MHz)
  // Pin change interrupt configuration
  PCICR  = 4;                        // Enable pin change interrupt for pins 0 to 7
  PCMSK2 = 0xE0;                     // Enable pin change interrupt for pins 5, 6 and 7
  // BLDC motor first move
  bldc_step = (PIND >> 5) & 7;       // Read hall effect sensors status (PIND: read from PORTD which is arduino pins 0..7)
  bldc_move();                       // Move the BLDC motor (first move)
}
 
ISR (PCINT2_vect){
  bldc_step = (PIND >> 5) & 7;       // Read hall effect sensors status (PIND: read from PORTD which is arduino pins 0..7)
  bldc_move();                       // Move the BLDC motor
}
 
void bldc_move(){        // BLDC motor commutation function
  switch(bldc_step){
    case 1:
      AH_CL();
      break;
    case 2:
      BH_AL();
      break;
    case 3:
      BH_CL();
      break;
    case 4:
      CH_BL();
      break;
    case 5:
      AH_BL();
      break;
    case 6:
      CH_AL();
      break;
    default:
      PORTD = 0;
      break;
  }
}
 
void loop() {
  ADCSRA |= 1 << ADSC;               // Start conversion
  while(ADCSRA & 0x40);              // Wait for conversion complete
  motor_speed = ADCH;                // Read ADC data (8 bits)
  SET_PWM_DUTY(motor_speed);
}
 
void AH_BL(){
  PORTD &= ~0x14;
  PORTD |=  0x08;
  TCCR2A =  0;            // Turn pin 9 (OC1A) PWM ON (pin 10 & pin 11 OFF)
  TCCR1A =  0x81;         //
}
void AH_CL(){
  PORTD &= ~0x0C;
  PORTD |=  0x10;
  TCCR2A =  0;            // Turn pin 9 (OC1A) PWM ON (pin 10 & pin 11 OFF)
  TCCR1A =  0x81;         //
}
void BH_CL(){
  PORTD &= ~0x0C;
  PORTD |=  0x10;
  TCCR2A =  0;            // Turn pin 10 (OC1B) PWM ON (pin 9 & pin 11 OFF)
  TCCR1A =  0x21;         //
}
void BH_AL(){
  PORTD &= ~0x18;
  PORTD |=  0x04;
  TCCR2A =  0;            // Turn pin 10 (OC1B) PWM ON (pin 9 & pin 11 OFF)
  TCCR1A =  0x21;         //
}
void CH_AL(){
  PORTD &= ~0x18;
  PORTD |=  0x04;
  TCCR1A =  0;            // Turn pin 11 (OC2A) PWM ON (pin 9 & pin 10 OFF)
  TCCR2A =  0x81;         //
}
void CH_BL(){
  PORTD &= ~0x14;
  PORTD |=  0x08;
  TCCR1A =  0;            // Turn pin 11 (OC2A) PWM ON (pin 9 & pin 10 OFF)
  TCCR2A =  0x81;         //
}
 
void SET_PWM_DUTY(byte duty){
  OCR1A  = duty;                   // Set pin 9  PWM duty cycle
  OCR1B  = duty;                   // Set pin 10 PWM duty cycle
  OCR2A  = duty;                   // Set pin 11 PWM duty cycle
}
