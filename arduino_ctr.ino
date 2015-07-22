
unsigned long t0;
int thres_UP;
int thres_DOWN;

int aMax=512,aMin=512;


int state=0;
int runState=0;

void set_threshold_up() {
  thres_UP=0.6*(aMax-aMin) + aMin; 
}

void set_threshold_down() {
  thres_DOWN=0.4*(aMax-aMin) + aMin;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(13,OUTPUT);
  Serial.begin(250000);
  digitalWrite(12,LOW);
  aMax=aMin=analogRead(A0);
  
  for(int i=0;i<1000;i++){
    int a=analogRead(A0);
    if(a>aMax) aMax=a;
    if(a<aMin) aMin=a;
    delay(1);
    }

  runState=0;
  set_threshold_down();
  set_threshold_up();
}






void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()>0){
    char c=Serial.read();
    
    if(c=='S' ){
      runState=1;
      t0 = millis();
      //Serial.println(t0);
    }
    if(c=='P' ){
      runState=0;
      Serial.println("END");
      /*for(int i=0;i<n_time_stamps;i++) {
          Serial.print(time_stamps[i]);
          Serial.print(",");
        }*/
      }
    }
  

  int a=analogRead(A0);
  //Serial.println(a);

  if(state==0){
    if(a<aMin) aMin=a;
    if(a>thres_UP){
      set_threshold_down();
      aMax=a;
      state=1;
      //Serial.print("Trig ! ");
      if(runState==1) {
        Serial.println(millis() - t0);
        digitalWrite(13,HIGH);
        digitalWrite(12,HIGH);
        digitalWrite(12,LOW);
      }
      }
    }
  
  else{
     if(a>aMax) aMax=a;
     if(a<thres_DOWN){
      digitalWrite(13,LOW);
      set_threshold_up();
      aMin=a;
      state=0;
      
     }
  }
      
  
  //Serial.print(t);
  //Serial.print(" ");
  //Serial.println(a);
  
  
  //delay(10);
  
  
}
