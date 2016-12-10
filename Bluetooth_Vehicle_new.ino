const byte LF = 0;
const byte LB = 64;
const byte RF = 128;
const byte RB = 192;
const int Velocity[11] = {0,34,41,52,68,88,113,142,175,213,255};
const int LFI = 2;
const int LRI = 3;
const int RFI = 4;
const int RRI = 5;
const int STAT = 12;

const int LCtr = 9;
const int RCtr = 10;

void setup() {
  // put your setup code here, to run once:
  pinMode(LCtr,OUTPUT);
  pinMode(RCtr,OUTPUT);
  pinMode(LFI,OUTPUT);
  pinMode(LRI,OUTPUT);
  pinMode(STAT,INPUT_PULLUP);
  digitalWrite(LFI, LOW);
  digitalWrite(LRI, LOW);
  analogWrite(LCtr,0);
  analogWrite(RCtr,0);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  while(digitalRead(STAT)==0){
    analogWrite(LCtr, 0);
    analogWrite(RCtr, 0);
    digitalWrite(13,HIGH);
  }

  digitalWrite(13,LOW);
  
  while(Serial.available()){
    
    byte command = Serial.read();
    delay(2);
    
    byte ctr = command & 192;//获取方向控制
    int index = int(command & 15);//获取速度级别

    if (ctr == LF){
      digitalWrite(LFI, HIGH);
      digitalWrite(LRI, LOW);
      analogWrite(LCtr,Velocity[index]);
    }
    else if (ctr == LB){
      digitalWrite(LFI, LOW);
      digitalWrite(LRI, HIGH);
      analogWrite(LCtr,Velocity[index]);
    }
    else if (ctr == RF){
      digitalWrite(RFI, HIGH);
      digitalWrite(RRI, LOW);
      analogWrite(RCtr,Velocity[index]);
    }
    else if (ctr == RB){
      digitalWrite(RFI, LOW);
      digitalWrite(RRI, HIGH);
      analogWrite(RCtr,Velocity[index]);
    }
  }
}
