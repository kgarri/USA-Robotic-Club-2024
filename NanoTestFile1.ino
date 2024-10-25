#define PWM1 3
#define PWM2 5
#define PWM3 6
#define PWM4 9
//#define HALLPIN1 2
//#define HALLPIN2 4

volatile int count1 = 0;
volatile int count2 = 0;

void setup() {
  Serial.begin(9600);
  pinMode(PWM1,OUTPUT);
  pinMode(PWM2,OUTPUT);
  pinMode(PWM3,OUTPUT);
  pinMode(PWM4,OUTPUT);
  //pinMode(HALLPIN1, INPUT);
  //pinMode(HALLPIN2, INPUT);
  //attachInterrupt(digitalPinToInterrupt(HALLPIN1), incrementCount, RISING);
  //attachInterrupt(digitalPinToInterrupt(HALLPIN2), incrementCount, RISING);
}

void loop() {
   Serial.println(count1);
   Serial.println(count2);
   delay(100);
   analogWrite(PWM1, 128);
   analogWrite(PWM2, 128);
   analogWrite(PWM3, 128);
   analogWrite(PWM4, 128);

}