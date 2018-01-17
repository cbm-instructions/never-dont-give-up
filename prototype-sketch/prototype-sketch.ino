int fsrLeg0;
int fsrLeg1;
int fsrButt0;
int fsrButt1;
int fsrLowerBack;
int fsrUpperBack0;
int fsrUpperBack1;

//this will be used to store the states of all fsrs (state = true = sittingRight)
bool fsrStates [5] = {false, false, false, false, false};

//first output slot of each LED which represents the color 'red'
int LEDLeg = 22;
int LEDButt = 28;
int LEDLowerBack = 34;
int LEDUpperBack = 40;
int LEDHead = 46;

int vibration = 3;

//configuration for UltraSonicSensor (USS)
int echo = 5;
int trigger = 6;
int timeForUss = 0;
int distance = 0;
//array to store distance values
int ussValues[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int ussValuesIndex = 0;

//time to wait to trigger vibration when user is not sitting right
int seconds = 3;
unsigned long intervall = seconds  * 1000UL;
unsigned long lastTimeSittingRight = 0;

void setup(void) {
  //LED Legs
  pinMode(22, OUTPUT);  //R
  pinMode(24, OUTPUT);  //G
  pinMode(26, OUTPUT);  //B

  //LED Butt
  pinMode(28, OUTPUT);  //R
  pinMode(30, OUTPUT);  //G
  pinMode(32, OUTPUT);  //B

  //LED LowerBack
  pinMode(34, OUTPUT);
  pinMode(36, OUTPUT);
  pinMode(38, OUTPUT);

  //LED UpperBack
  pinMode(40, OUTPUT);
  pinMode(42, OUTPUT);
  pinMode(44, OUTPUT);

  //LED Head
  pinMode(46, OUTPUT);
  pinMode(48, OUTPUT);
  pinMode(50, OUTPUT);

  //Vibration
  pinMode(vibration, OUTPUT);

  //Ultrasonicsensor
  pinMode(echo, INPUT);
  pinMode(trigger, OUTPUT);
}

void triggerVibration() {
  digitalWrite(3, HIGH);
  delay(1000);
  digitalWrite(3, LOW);
  delay(300);
  digitalWrite(3, HIGH);
  delay(1000);
  digitalWrite(3, LOW);
}

bool getUSSState(int array[], int pin){
  bool state = true;

  for(int i = 0; i < 10; i++){
    if(array[i] < 0){
      state = false;
    }
  }
  
  return state;
}

bool getFsrState(int pos, int pin) {
  bool state = false;
  
  if (pos > 10) {
    state = true;
  } 
    
  return state;
}

bool getFsrState(int pos1, int pos2, int pin) {
  bool state = false;
  
  if ((pos1 > 20) && (pos2 > 20)) {
    state = true;
  }
  
  return state;
}

void setStates() { 
  fsrStates[0] = getFsrState(fsrLeg0, fsrLeg1, LEDLeg);
  fsrStates[1] = getFsrState(fsrButt0, fsrButt1, LEDButt);
  fsrStates[2] = getFsrState(fsrLowerBack, LEDLowerBack);
  fsrStates[3] = getFsrState(fsrUpperBack0, fsrUpperBack1, LEDUpperBack);
  fsrStates[4] = getUSSState(ussValues, LEDHead);
}

void setLEDs() {
  for(int i = 0, pin = 22; i < sizeof(fsrStates); i++, pin += 6){
    if(fsrStates[i]){
      digitalWrite(pin, HIGH);
      digitalWrite(pin + 2, LOW);
      digitalWrite(pin + 4, HIGH);
    }else{
      digitalWrite(pin, LOW);
      digitalWrite(pin + 2, HIGH);
      digitalWrite(pin + 4, HIGH);
    }
  }
}

// determine if someone is sitting on the chair to trigger the vibration
bool isUsingChair() {
  bool isUsingChair = false;
  
  for(int i = 0; i < sizeof(fsrStates) - 1; i++) {
    if(fsrStates[i]) {
      isUsingChair = true;
    }
  }

  return isUsingChair;
}

bool isSittingWrong() {
  bool isSittingWrong = false;
  
  for(int i = 0; i < sizeof(fsrStates) - 1; i++){
    if(fsrStates[i] == false){
      isSittingWrong = true;
    }
  }

  return isSittingWrong;
}

void loop(void) {
  fsrLeg0 = analogRead(0);
  fsrLeg1 = analogRead(1);
  fsrButt0 = analogRead(2);
  fsrButt1 = analogRead(3);
  fsrLowerBack = analogRead(5);
  fsrUpperBack0 = analogRead(6);
  fsrUpperBack1 = analogRead(7);

  digitalWrite(trigger, LOW); 
  delay(10); 
  digitalWrite(trigger, HIGH); 
  delay(20);
  digitalWrite(trigger, LOW);
  timeForUss = pulseIn(echo, HIGH); 
  distance = (timeForUss/2) * 0.03432;
  ussValues[ussValuesIndex] = distance;

  //store 10 values of uss sensor before determining state to improve the accuracy of measurement
  ussValuesIndex++;
  if(ussValuesIndex == 10){
    ussValuesIndex = 0;
  }

  setStates();
  setLEDs();

  if(isUsingChair() && isSittingWrong()){
    if(millis() - lastTimeSittingRight > intervall){
      triggerVibration();
      lastTimeSittingRight = millis();
    }
  } else {
    lastTimeSittingRight = millis();
  }
  
  digitalWrite(0, LOW);
}


