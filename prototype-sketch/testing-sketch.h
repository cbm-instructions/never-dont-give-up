


 
void setup(void) {
  Serial.begin(9600);   // We'll send debugging information via the Serial monitor

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
}

void turnOff() {
  digitalWrite(22, HIGH);
  digitalWrite(24, HIGH);
  digitalWrite(26, HIGH);
  digitalWrite(28, HIGH);
  digitalWrite(30, HIGH);
  digitalWrite(32, HIGH);
  digitalWrite(34, HIGH);
  digitalWrite(36, HIGH);
  digitalWrite(38, HIGH);
  digitalWrite(40, HIGH);
  digitalWrite(42, HIGH);
  digitalWrite(44, HIGH);
  digitalWrite(46, HIGH);
  digitalWrite(48, HIGH);
  digitalWrite(50, HIGH);
  delay(250);
}

void turnViolett(){
  digitalWrite(22, LOW);
  digitalWrite(26, LOW);
  
  digitalWrite(28, LOW);
  digitalWrite(32, LOW);
  
  digitalWrite(34, LOW);
  digitalWrite(38, LOW);
  
  digitalWrite(40, LOW);
  digitalWrite(44, LOW);
  
  digitalWrite(46, LOW);
  digitalWrite(50, LOW);

  delay(250);
}

void turnCyan() {
  digitalWrite(22, HIGH);
  digitalWrite(24, LOW);
  
  digitalWrite(28, HIGH);
  digitalWrite(30, LOW);
  
  digitalWrite(34, HIGH);
  digitalWrite(36, LOW);
  
  digitalWrite(40, HIGH);
  digitalWrite(42, LOW);  
  
  digitalWrite(46, HIGH);
  digitalWrite(48, LOW);
  delay(250);
}

void turnYellow(){
  digitalWrite(22, LOW);
  digitalWrite(26, HIGH);
  
  digitalWrite(28, LOW);
  digitalWrite(32, HIGH);
  
  digitalWrite(34, LOW);
  digitalWrite(38, HIGH);
  
  digitalWrite(40, LOW);
  digitalWrite(44, HIGH);
  
  digitalWrite(46, LOW);
  digitalWrite(50, HIGH);
  delay(250);
}
 
void loop(void) {
  fsrReading = analogRead(fsrAnalogPin);
  fsrReading2 = analogRead(fsrAnalogPin2);
  fsrReading3 = analogRead(fsrAnalogPin3);
  fsrReading4 = analogRead(fsrAnalogPin4);

  fsrReading5 = analogRead(fsrAnalogPin5);
  fsrReading6 = analogRead(fsrAnalogPin6);
  fsrReading7 = analogRead(fsrAnalogPin7);

  Serial.print("Analog reading Bein R = ");
  Serial.println(fsrReading);
  Serial.print("Analog reading Bein L = ");
  Serial.println(fsrReading2);
  Serial.print("Analog reading Arsch R = ");
  Serial.println(fsrReading3);
  Serial.print("Analog reading Arsch L = ");
  Serial.println(fsrReading4);

  Serial.print("Analog reading Lende = ");
  Serial.println(fsrReading5);
  Serial.print("Analog reading Schulter R = ");
  Serial.println(fsrReading6);
  Serial.print("Analog reading Schulter L = ");
  Serial.println(fsrReading7);
  Serial.println("-----------------------------------");
  turnOff();
  turnViolett();  
  turnCyan();
  turnYellow();
 
  delay(1000);
}
