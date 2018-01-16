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

//this will be used to store the states of all fsrs (state = true = sittingRight)
bool fsrStates [5] = {false, false, false, false, false};

//first pin for the colour red
int legColour = 22;
int buttColour = 28;
int lowerBackColour = 34;
int backColour = 40;
int headColour = 46;

int vibration = 3;

//values for UltraSonicSensor (USS)
int echo = 5;
int trigger = 6;
int timeForUss = 0;
int distance = 0;
//array to store distance values
int ultrasonicValues[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int counter = 0;

int sekunden = 3;
unsigned long intervall = sekunden  * 1000UL;
unsigned long lastTimeSittingRight = 0;

void setup(void) {
  //Legs
  pinMode(22, OUTPUT);  //R
  pinMode(24, OUTPUT);  //G
  pinMode(26, OUTPUT);  //B

  //Butt
  pinMode(28, OUTPUT);  //R
  pinMode(30, OUTPUT);  //G
  pinMode(32, OUTPUT);  //B

  //Lower back
  pinMode(34, OUTPUT);
  pinMode(36, OUTPUT);
  pinMode(38, OUTPUT);

  //Back
  pinMode(40, OUTPUT);
  pinMode(42, OUTPUT);
  pinMode(44, OUTPUT);

  //Head
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
  Serial.println("Activating Vibration");
  digitalWrite(3, HIGH);
  delay(1000);
  digitalWrite(3, LOW);
  delay(300);
  digitalWrite(3, HIGH);
  delay(1000);
  digitalWrite(3, LOW);
}

bool getUltrasonicState(int array[], int pin){
  bool state = true;

  for(int i = 0; i < 10; i++){
    if(array[i] < 0){
      state = false;
    }
  }

  if(state){
    digitalWrite(pin, HIGH);
    digitalWrite(pin + 2, LOW);
    digitalWrite(pin + 4, HIGH);
  } else {
    digitalWrite(pin, LOW);
    digitalWrite(pin + 2, HIGH);
    digitalWrite(pin + 4, HIGH);
  }
  
  return state;
}

bool getFsrState(int pos, int pin) {
  bool state = false;
  
  if (pos > 10) {
    state = true;
    digitalWrite(pin, HIGH);
    digitalWrite(pin + 2, LOW);
    digitalWrite(pin + 4, HIGH);
  } else {
    digitalWrite(pin, LOW);
    digitalWrite(pin + 2, HIGH);
    digitalWrite(pin + 4, HIGH);
  }   
  return state;
}

bool getFsrState(int pos1, int pos2, int pin) {
  bool state = false;
  
  if ((pos1 > 20) && (pos2 > 20)) {
    state = true;
    digitalWrite(pin, HIGH);
    digitalWrite(pin + 2, LOW);
    digitalWrite(pin + 4, HIGH);
  } else {
    digitalWrite(pin, LOW);
    digitalWrite(pin + 2, HIGH);
    digitalWrite(pin + 4, HIGH);
  }  
  return state;
}

bool isUsingChair() {
  bool isUsingChair = false;
  
  for(int i = 0; i < sizeof(fsrStates); i++) {
    if(fsrStates[i]) {
      isUsingChair = true;
    }
  }

  return isUsingChair;
}

void loop(void) {
  fsrLeg0 = analogRead(0);
  fsrLeg1 = analogRead(1);
  fsrButt0 = analogRead(2);
  fsrButt1 = analogRead(3);
  fsrLowerBack = analogRead(5);
  fsrBack0 = analogRead(6);
  fsrBack1 = analogRead(7);

  digitalWrite(trigger, LOW); 
  delay(10); 
  digitalWrite(trigger, HIGH); 
  delay(20);
  digitalWrite(trigger, LOW);
  timeForUss = pulseIn(echo, HIGH); 
  distance = (timeForUss/2) * 0.03432;
  ultrasonicValues[counter] = distance;

  Serial.println(distance);
  
  counter++;
  if(counter == 10){
    counter = 0;
  }

  fsrStates[0] = getFsrState(fsrLeg0, fsrLeg1, legColour);
  fsrStates[1] = getFsrState(fsrButt0, fsrButt1, buttColour);
  fsrStates[2] = getFsrState(fsrLowerBack, lowerBackColour);
  fsrStates[3] = getFsrState(fsrBack0, fsrBack1, backColour);
  fsrStates[4] = getUltrasonicState(ultrasonicValues, headColour);

  bool isSittingWrong = false;
  
  for(int i = 0; i < sizeof(fsrStates); i++){
    if(fsrStates[i] == false){
      isSittingWrong = true;
    }
  }

  if(isUsingChair() && (isSittingWrong)){
    if(millis() - lastTimeSittingRight > intervall){
      trigger_vibration();
      lastTimeSittingRight = millis();
    }
  } else {
    lastTimeSittingRight = millis();
  }
  
  digitalWrite(0, LOW);
}


