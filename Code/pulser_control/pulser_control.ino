

volatile float voltIn;
float total_error = 0;

float KP = 400;
float KI = 250;
float setpoint = 1.1;
float volt;
float PWM;
float error;


void setup() {
  // put your setup code here, to run once:
  pinMode(5, OUTPUT);
  Serial.begin(115200);
  TCCR0B = TCCR0B & B11111000 | B00000001;
}

void loop() {
  // put your main code here, to run repeatedly:
  float dataIn = analogRead(A5);
  voltIn = dataIn * 5 / 1023;

  volt = voltIn;
  error = setpoint - volt;
  total_error = total_error + 0.001 * error;
  PWM = error * KP + KI * total_error;


  if (PWM >= 220) {
    PWM = 220;
  }
  if (error < -0.8) {
    PWM = 10;
  }

  while (voltIn > 1.6) {
    PWM = 5;
  }
  Serial.print(voltIn);
  Serial.print(" : ");
  Serial.print(voltIn * 91.9);
  Serial.print(" : ");
  Serial.print(error);
  Serial.print(" : ");
  Serial.println(PWM);

  analogWrite(5,PWM);
}



