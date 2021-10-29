#define HOME  9 //pin sensor home
#define BUTTON  8 //pin start button
#define DIRSTEP 7 //pin for stepper for the Direction
#define PULSTEP  6 //pin for the stepper pulse
#define PULSERVO 5 //pin for servo pulse
#define DIRSERVO  4 //pin for servo Direction
#define ENASERVO 3 //define Enable Pin delayServo

const int delayServo = 9;
const int delayStep = 50;
const unsigned long debounceDelay = 30;

const int coilStarterPosition = 1530;
const int servoRotation = 400;

int val = 0;
//int buttonState;
bool lastButtonState = LOW;
unsigned long lastDebounceTime = 0;

void setup() {
  
  pinMode(DIRSTEP, OUTPUT);
  pinMode(PULSTEP, OUTPUT);
  pinMode(PULSERVO, OUTPUT);
  pinMode(DIRSERVO, OUTPUT);
  pinMode(ENASERVO, OUTPUT);
  pinMode(HOME, INPUT);
  pinMode(BUTTON, INPUT);

  starterPosition();
}




void loop()
{
  int reading = digitalRead(BUTTON);
  if (reading != lastButtonState) lastDebounceTime = millis();

  if ((unsigned long)(millis() - lastDebounceTime) > debounceDelay) { //IF debounceDelay has passed
    //if (reading != buttonState) {
    //  buttonState = reading;
    // if (buttonState == HIGH) {
        // { //FIXME: set layer to 34
        //   for (int layer = 0; layer < 2; layer++) //layers number = (34x4)
        //   {
        //     //RIGHT
        //     {
        //       for (int g = 444; g > 8; g--) { //layer length

        //         if(layer == 0){ //SMOOOTH ACCELLERATION
        //           for (int i = 0; i < servoRotation; i++) pulseOutServo(LOW,delayServo*int(g / 8));//1 turn revolutionTime = delayServo * 2 * servoRotation * (g / 8)
        //           for (int i = 0; i < 5; i++) pulseOutStep(LOW, delayStep*int(g/8)); //0.026 mm
        //         }

        //         else{   
        //           rotateServo();
        //           for (int i = 0; i < 5; i++) pulseOutStep(LOW,delayStep); //0.026 mm
        //         }
        //       }
        //     }
        //     //LEFT
        //     {
        //       for (int i = 0; i < 436; i++) {
        //           rotateServo();
        //           for (int i = 0; i < 5; i++) pulseOutStep(HIGH,delayStep); //0.026 mm
        //       }
        //     }
        //     //RIGHT
        //     {
        //       for (int i = 0; i < 436; i++) {
        //         rotateServo();
        //         for (int i = 0; i < 5; i++) pulseOutStep(LOW,delayStep); //0.026 mm
        //       }
        //     }
        //     //LEFT + 1 TURN
        //     {
        //       for (int i = 0; i < 437; i++) {
        //         rotateServo();
        //         for (int i = 0; i < 5; i++) pulseOutStep(HIGH,delayStep); //0.026 mm
        //       }
        //     }
        //   }
        // }

      //}


    for (int layer = 0; layer < 2; layer++) //layers number = (34x4)
          {
            //RIGHT
            {
              for (int g = 444; g > 8; g--) { //layer length

                if(layer == 0){ //SMOOOTH ACCELLERATION
                  //1 turn revolutionTime = delayServo * 2 * servoRotation * (g / 8)
                  rotateServo(delayServo * int(g/8));
                   moveStepper(LOW,stepMove, delayStep*int(g/8));
                }

                else{   
                  rotateServo(delayServo);
                  moveStepper(LOW,stepMove,delayStep);
                }
              }
            }
            //LEFT
            {
              for (int i = 0; i < 436; i++) {
                  rotateServo(delayServo);
                  moveStepper(HIGH,stepMove,delayStep);
              }
            }
            //RIGHT
            {
              for (int i = 0; i < 436; i++) {
                rotateServo(delayServo);
                moveStepper(LOW,stepMove,delayStep);
              }
            }
            //LEFT + 1 TURN
            {
              for (int i = 0; i < 437; i++) {
                rotateServo(delayServo);
                moveStepper(HIGH,stepMove,delayStep);
              }
            }
        }
      
     starterPosition();
  }
  lastButtonState = reading;
}


void pulseOutStep(bool dir,int delayMicro){
  digitalWrite(DIRSTEP, dir);
  digitalWrite(PULSTEP, HIGH);
  delayMicroseconds(delayMicro);
  digitalWrite(PULSTEP, LOW);
  delayMicroseconds(delayMicro);
}

void pulseOutServo(bool dir,int delayMicro){
  digitalWrite(DIRSERVO, dir);
  digitalWrite(ENASERVO, HIGH);
  digitalWrite(PULSERVO, HIGH);
  delayMicroseconds(delayMicro);
  digitalWrite(PULSERVO, LOW);
  delayMicroseconds(delayMicro);
}

void rotateServo(){
  for (int i = 0; i < servoRotation; i++) pulseOutServo(LOW,delayServo);
}

void starterPosition(){
  while(digitalRead(HOME) == LOW) pulseOutStep(HIGH,1000); // move the stepper back to point 0
      for (int i = 0; i < coilStarterPosition; i++) pulseOutStep(LOW,1000); // starter position for the coil
      for (int i = 0; i < servoRotation; i++) pulseOutServo(HIGH,1000); // 1 rotation of bottom servo
    }
}