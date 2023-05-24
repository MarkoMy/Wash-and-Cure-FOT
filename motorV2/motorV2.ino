#define motor_y_stepper 3
#define motor_y_dir 6
#define enablepin 8
#define gombIdoChg_xendstop 9
#define gombStart_xdir 5
#define gombStop_zdir 7

//ledek
#define led1_xstepper 2
#define led2_zendstop 11
#define led3_zstepper 4


float forgasido = 2;
float sv = 100.0;
int IdobuttonState = 0;
int StartbuttonState = 0;
int StopbuttonState = 0;
bool lastState = 0;
bool presentState = 0;
bool stop = 0;

void setup() {
//motor inportja
  pinMode(motor_y_stepper,OUTPUT);
  pinMode(motor_y_dir,OUTPUT);
  pinMode(enablepin,OUTPUT);

//gombok importja
  pinMode(gombIdoChg_xendstop, INPUT_PULLUP);
  pinMode(gombStart_xdir, INPUT_PULLUP);
  pinMode(gombStop_zdir, INPUT_PULLUP);

//ledek inportja
  pinMode(led1_xstepper, OUTPUT);
  pinMode(led2_zendstop, OUTPUT);
  pinMode(led3_zstepper, OUTPUT);

}

void loop() {
  if(stop = 1){
    stop = 0;
  }


// ha LOW akkor mozog, ha HIGH akkor nem.
  digitalWrite(enablepin, HIGH);
// digitalWrite(dir, HIGH); ha LOW akkor jobbra forog, ha HIGH akkor balra.

//beolvassuk a gombok állapotát
  IdobuttonState = digitalRead(gombIdoChg_xendstop);
  StartbuttonState = digitalRead(gombStart_xdir);

if(IdobuttonState == LOW){
  presentState = 1;
}else{
  presentState = 0;
}
//Megnézzük az időkezelő gombnak a gombját, hogy állítson időt
if (presentState != lastState && lastState == 0) {
    if(forgasido ==2){
  forgasido =4;
    }else if(forgasido==4){
  forgasido = 6;
    }else{
  forgasido = 2;
    }
  delay(200); 
}
lastState = presentState;

//Pin-t állítunk át a bizonyos gomb statementre
if(forgasido ==2){
digitalWrite(led1_xstepper, HIGH); digitalWrite(led2_zendstop, LOW); digitalWrite(led3_zstepper, LOW);
}else if(forgasido==4){
digitalWrite(led1_xstepper, LOW); digitalWrite(led2_zendstop, HIGH); digitalWrite(led3_zstepper, LOW);
}else{
digitalWrite(led1_xstepper, LOW); digitalWrite(led2_zendstop, LOW); digitalWrite(led3_zstepper, HIGH);
}

//Megnézzük, hogy van-e start
if(StartbuttonState == LOW){
  start(forgasido);
}

//loopvege
}
  
void start(int forgasido){
  digitalWrite(motor_y_dir, LOW);
  digitalWrite(enablepin, LOW);

  double temp = 0.0;
  double idoszamolo = millis();
  temp = idoszamolo;
  sv = 100.0;

  while(idoszamolo <= temp+((forgasido/2)*60000) && !stop){
  if(sv > 5.0){
    sv -= 0.005;
  }

StopbuttonState = digitalRead(gombStop_zdir);
  if(StopbuttonState == LOW){
    stop = 1;
  }
  
  digitalWrite(motor_y_stepper, LOW);
  delayMicroseconds(sv);
  digitalWrite(motor_y_stepper, HIGH);
  delayMicroseconds(sv);    
  idoszamolo = millis();
  }

  digitalWrite(motor_y_dir, HIGH);

  sv = 100.0;

  idoszamolo = millis();  
  temp = idoszamolo;

  while(idoszamolo <= temp+((forgasido/2)*60000) && !stop){
    if(sv > 12.0){
    sv -= 0.005;
  }
  
  StopbuttonState = digitalRead(gombStop_zdir);
  if(StopbuttonState == LOW){
    stop = 1;
  }

  digitalWrite(motor_y_stepper, LOW);
  delayMicroseconds(sv);
  digitalWrite(motor_y_stepper, HIGH);
  delayMicroseconds(sv); 
  idoszamolo = millis();
  }

  digitalWrite(enablepin, HIGH);
}