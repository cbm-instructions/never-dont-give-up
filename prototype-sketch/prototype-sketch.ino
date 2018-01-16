
/*
    Dieses Setup läuft mit 6 Drucksensoren auf den analogen Pins 0-5,
    drei LEDs auf den digitalen Pins 0-2 und zwei Motoren auf digital 3 und 4.
    Zusätzlich ist ein Timer eingebaut um die Vibration zu triggern.
    Die LEDs werden bei Nichtkontakt sofort getriggert.
*/

int fsrLeg0;
int fsrLeg1;
int fsrButt0;
int fsrButt1;
int fsrLowerBack;
int fsrBack0;
int fsrBack1;

int legColour = 22;
int buttColour = 28;
int lowerBackColour = 34;
int backColour = 40;
int headColour = 46;


int vibration = 3;
int echo = 5;
int trigger = 6;
//Uss = Ultrasonic sensor
int timeForUss = 0;
int distance = 0;
//array to store distance values
int array[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int counter = 0;


int sekunden = 3;
unsigned long intervall = sekunden  * 1000UL;
unsigned long posTimer = 0;
unsigned long time = 0;
boolean wrongPos = false;



void setup(void) {
  //Fuß
  pinMode(22, OUTPUT);  //R
  pinMode(24, OUTPUT);  //G
  pinMode(26, OUTPUT);  //B

  //Po
  pinMode(28, OUTPUT);  //R
  pinMode(30, OUTPUT);  //G
  pinMode(32, OUTPUT);  //B

  //Lende
  pinMode(34, OUTPUT);
  pinMode(36, OUTPUT);
  pinMode(38, OUTPUT);

  //Rücken
  pinMode(40, OUTPUT);
  pinMode(42, OUTPUT);
  pinMode(44, OUTPUT);

  //Kopf
  pinMode(46, OUTPUT);
  pinMode(48, OUTPUT);
  pinMode(50, OUTPUT);


  //Vibrationsmotor
  pinMode(vibration, OUTPUT);

  //Ultraschallsensor
  pinMode(echo, INPUT);
  pinMode(trigger, OUTPUT);
  Serial.begin(9600);
}
void trigger_vibration() {
  posTimer = time;
  Serial.println("Activating Vibration");
  digitalWrite(3, HIGH);
  delay(1000);
  digitalWrite(3, LOW);
  delay(300);
  digitalWrite(3, HIGH);
  delay(1000);
  digitalWrite(3, LOW);
}
int checkForWrongPos(int pos, int pin) {
  if ((pos < 50)) {
    wrongPos = true;
    digitalWrite(pin, LOW);
    digitalWrite(pin + 2, HIGH);
    digitalWrite(pin + 4, HIGH);
    posTimer = millis();
  }
}
int checkForUltrasonicPos(int array[], int pin){
  int check = 1;
  for(int i = 0; i < 10; i++){
    if(array[i] >= 5 || array[i] <= 0){
      check--;
    } else {
      check++;
    }
  }
   if(check < 5){
    wrongPos = true;
    digitalWrite(pin, LOW);
    digitalWrite(pin + 2, HIGH);
    digitalWrite(pin + 4, HIGH);
  } else {
    digitalWrite(pin, HIGH);
    digitalWrite(pin + 2, LOW);
    digitalWrite(pin + 4, HIGH);
  }
}
int checkForRightPos(int pos1, int pos2, int pin){
  if ((pos1 > 20) && (pos2 > 20)) {

    digitalWrite(pin, HIGH);
    digitalWrite(pin + 2, LOW);
    digitalWrite(pin + 4, HIGH);
    
  }
}
int checkForRightPos(int pos, int pin){
  if (pos > 50) {
    
    digitalWrite(pin, HIGH);
    digitalWrite(pin + 2, LOW);
    digitalWrite(pin + 4, HIGH);
    
  }
}

void loop(void) {
  fsrLeg0 = analogRead(0);
  fsrLeg1 = analogRead(1);
  fsrButt0 = analogRead(2);
  fsrButt1 = analogRead(3);
  fsrLowerBack = analogRead(5);
  fsrBack0 = analogRead(6);
  fsrBack1 = analogRead(7);
  
  time = millis();

  digitalWrite(trigger, LOW); 
  delay(10); 
  digitalWrite(trigger, HIGH); 
  delay(20);
  digitalWrite(trigger, LOW);
  timeForUss = pulseIn(echo, HIGH); 
  distance = (timeForUss/2) * 0.03432;
  array[counter] = distance;

  counter++;
  if(counter == 10){
    counter = 0;
  }
  
  if(wrongPos == false){
    checkForWrongPos(fsrLeg0, legColour);
    checkForWrongPos(fsrLeg1, legColour);
    checkForWrongPos(fsrButt0, buttColour);
    checkForWrongPos(fsrButt1, buttColour);
    checkForWrongPos(fsrLowerBack, lowerBackColour);
    checkForWrongPos(fsrBack0, backColour);
    checkForWrongPos(fsrBack1, backColour);
    checkForUltrasonicPos(array, headColour);
  }
  
  checkForRightPos(fsrLeg0, fsrLeg1, legColour);
  checkForRightPos(fsrButt0, fsrButt1, buttColour);
  checkForRightPos(fsrLowerBack, lowerBackColour);
  checkForRightPos(fsrBack0, fsrBack1, backColour);

  
  if ((time - posTimer > intervall) && (wrongPos == true) && (counter >= 5)) {
    wrongPos = false;
    trigger_vibration();
  }

  digitalWrite(0, LOW);
  delay(250);
}


