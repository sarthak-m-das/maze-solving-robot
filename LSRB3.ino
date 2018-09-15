int CenterSensor=49;
int LeftCenterSensor=51;
int LeftFarSensor=53;
int RightCenterSensor=47;
int RightFarSensor=45;

int leftCenterReading;
int CenterReading;
int leftFarReading;
int rightCenterReading;
int rightFarReading;

int replaystage;
float r,l;

#define leapTime 150
int leftMotor1=0;
int leftMotor2=1;
int rightMotor1=3;
int rightMotor2=2;
int enl=6;
int enr=4;
int led=13;
char path[30] = {};
int pathLength;
int readLength;

void setup(){
 pinMode(LeftCenterSensor, INPUT);
 pinMode(CenterSensor, INPUT);
 pinMode(LeftFarSensor, INPUT);
 pinMode(RightCenterSensor, INPUT);
 pinMode(RightFarSensor, INPUT);
 pinMode(leftMotor1, OUTPUT);
 pinMode(leftMotor2, OUTPUT);
 pinMode(rightMotor1, OUTPUT);
 pinMode(rightMotor2, OUTPUT);
 pinMode(enl, OUTPUT);
 pinMode(enr, OUTPUT);
 pinMode(led, OUTPUT);
 digitalWrite(led, HIGH);
 delay(1000);
}
void loop(){
readSensors();
if(leftFarReading==1 && rightFarReading==1 &&
 (leftCenterReading==0 || rightCenterReading==0 || CenterReading==0) ){
 straight();
 }
 else{
 leftHandWall(); 
 }
}
void readSensors(){
 leftCenterReading = digitalRead(LeftCenterSensor);
 CenterReading = digitalRead(CenterSensor);
 leftFarReading = digitalRead(LeftFarSensor);
 rightCenterReading = digitalRead(RightCenterSensor);
 rightFarReading = digitalRead(RightFarSensor);
}
void leftHandWall(){

 if( leftFarReading==0 && rightFarReading==0){
 digitalWrite(leftMotor1, HIGH);
 digitalWrite(leftMotor2, LOW);
 digitalWrite(rightMotor1, HIGH);
 digitalWrite(rightMotor2, LOW);
 analogWrite(enl,130);
 analogWrite(enr,255); 
 delay(leapTime);
 readSensors();
 if(leftFarReading==0 || rightFarReading==0){
 done();
 }
 if(leftFarReading==1 && rightFarReading==1){
 turnLeft();
 }
 }
 if(leftFarReading==0){
 digitalWrite(leftMotor1, HIGH);
 digitalWrite(leftMotor2, LOW);
 digitalWrite(rightMotor1, HIGH);
 digitalWrite(rightMotor2, LOW);
 analogWrite(enl,130);
 analogWrite(enr,255); 
 delay(leapTime);
 readSensors();
 if(leftFarReading==1 && rightFarReading==1){
 turnLeft();
 }
 else{
 done();
 }
 }
 if(rightFarReading==0){
 digitalWrite(leftMotor1, HIGH);
 digitalWrite(leftMotor2, LOW);
 digitalWrite(rightMotor1, HIGH);
 digitalWrite(rightMotor2, LOW);
 analogWrite(enl,130);
 analogWrite(enr,255); 
 delay(30);
 readSensors();
 if(leftFarReading==0){
 delay(leapTime-30);
 readSensors();
 if(rightFarReading==0 && leftFarReading==0){
 done();
 }
 else{
 turnLeft();
 return;
 }
 }
 delay(leapTime-30);
 readSensors();
 if(leftFarReading==1 && leftCenterReading==1 &&
 rightCenterReading==1 && rightFarReading==1 && CenterReading==1) {
 turnRight();
 return;
 }
 path[pathLength]='S';
 pathLength++;
 if(path[pathLength-2]=='B'){
 shortPath();
 }
 straight();
 }
 readSensors();
 if(leftFarReading==1 && leftCenterReading==1 && rightCenterReading==1
 && rightFarReading==1 && CenterReading==1){
 turnAround();
 }
}
void done(){
 digitalWrite(leftMotor1, LOW);
 digitalWrite(leftMotor2, LOW);
 digitalWrite(rightMotor1, LOW);
 digitalWrite(rightMotor2, LOW);
 replaystage=1;
 path[pathLength]='D';
 pathLength++;
 printPath();
delay(10000);
 replay();
}
void turnLeft(){
 while(digitalRead(CenterSensor)==0||digitalRead(RightCenterSensor)==0||digitalRead(LeftCenterSensor)==0){
 digitalWrite(leftMotor1, LOW);
 digitalWrite(leftMotor2, LOW);
 digitalWrite(rightMotor1, HIGH);
 digitalWrite(rightMotor2, LOW);
 analogWrite(enl,130);
 analogWrite(enr,255); 
 delay(20);
 digitalWrite(leftMotor1, LOW);
 digitalWrite(leftMotor2, LOW);
 digitalWrite(rightMotor1, LOW);
 digitalWrite(rightMotor2, LOW);
 delay(10);
 }
 while(digitalRead(CenterSensor)==1){
 digitalWrite(leftMotor1, LOW);
 digitalWrite(leftMotor2, LOW);
 digitalWrite(rightMotor1, HIGH);
 digitalWrite(rightMotor2, LOW);
 analogWrite(enl,130);
 analogWrite(enr,255); 
 delay(20);
 digitalWrite(leftMotor1, LOW);
 digitalWrite(leftMotor2, LOW);
 digitalWrite(rightMotor1, LOW);
 digitalWrite(rightMotor2, LOW);
 delay(10);
 }
 if(replaystage==0){
 path[pathLength]='L';
 pathLength++;
 if(path[pathLength-2]=='B'){
 shortPath();
 }
 }
}
void turnRight(){
 while(digitalRead(RightCenterSensor)==0||digitalRead(CenterSensor)==0 || digitalRead(LeftCenterSensor)==0){
 digitalWrite(leftMotor1, HIGH);
 digitalWrite(leftMotor2, LOW);
 digitalWrite(rightMotor1, LOW);
 digitalWrite(rightMotor2, LOW);
 analogWrite(enl,130);
 analogWrite(enr,255); 
 delay(20);
 digitalWrite(leftMotor1, LOW);
 digitalWrite(leftMotor2, LOW);
 digitalWrite(rightMotor1, LOW);
 digitalWrite(rightMotor2, LOW);
 delay(10);
 }
 while(digitalRead(CenterSensor)==1){
 digitalWrite(leftMotor1, HIGH);
 digitalWrite(leftMotor2, LOW);
 digitalWrite(rightMotor1, LOW);
 digitalWrite(rightMotor2, LOW);
 analogWrite(enl,130);
 analogWrite(enr,255); 
 delay(20);
 digitalWrite(leftMotor1, LOW);
 digitalWrite(leftMotor2, LOW);
 digitalWrite(rightMotor1, LOW);
 digitalWrite(rightMotor2, LOW);
 delay(10);
 }
 if(replaystage==0){
 path[pathLength]='R';
 pathLength++;
 if(path[pathLength-2]=='B'){
 shortPath();
 }
 }
}
void straight(){
if(!digitalRead(LeftCenterSensor) &&digitalRead(CenterSensor) &&digitalRead(RightCenterSensor))
{
digitalWrite(rightMotor1,HIGH);
digitalWrite(rightMotor2,LOW);
digitalWrite(leftMotor1,LOW);
digitalWrite(leftMotor2,LOW);
r=255;
}
  
else if(!digitalRead(LeftCenterSensor) &&!digitalRead(CenterSensor) &&digitalRead(RightCenterSensor))
{
digitalWrite(rightMotor1,HIGH);
digitalWrite(rightMotor2,LOW);
digitalWrite(leftMotor1,HIGH);
digitalWrite(leftMotor2,LOW);
l=100;
r=255;
}

else if(digitalRead(LeftCenterSensor) &&!digitalRead(CenterSensor) &&digitalRead(RightCenterSensor))
{
l=130;
r=255;
digitalWrite(rightMotor1,HIGH);
digitalWrite(rightMotor2,LOW);
digitalWrite(leftMotor1,HIGH);
digitalWrite(leftMotor2,LOW);
}

else if(digitalRead(LeftCenterSensor) &&!digitalRead(CenterSensor) &&!digitalRead(RightCenterSensor))
{
digitalWrite(rightMotor1,HIGH);
digitalWrite(rightMotor2,LOW);
digitalWrite(leftMotor1,HIGH);
digitalWrite(leftMotor2,LOW);
l=130;
r=180;
}

else if(digitalRead(LeftCenterSensor) &&digitalRead(CenterSensor) &&!digitalRead(RightCenterSensor))
{
digitalWrite(rightMotor1,LOW);
digitalWrite(rightMotor2,LOW);
digitalWrite(leftMotor1,HIGH);
digitalWrite(leftMotor2,LOW);
l=130;
}
analogWrite(enl,l);
analogWrite(enr,r);
}
 
void turnAround(){
 digitalWrite(leftMotor1, HIGH);
 digitalWrite(leftMotor2, LOW);
 digitalWrite(rightMotor1, HIGH);
 digitalWrite(rightMotor2, LOW);
 analogWrite(enl,130);
 analogWrite(enr,255); 
 delay(150);
 while(digitalRead(CenterSensor)==1){
 digitalWrite(leftMotor1, HIGH);
 digitalWrite(leftMotor2, LOW);
 digitalWrite(rightMotor1, LOW);
 digitalWrite(rightMotor2, HIGH);
 analogWrite(enl,130);
 analogWrite(enr,255); 
 delay(2);
 digitalWrite(leftMotor1, LOW);
 digitalWrite(leftMotor2, LOW);
 digitalWrite(rightMotor1, LOW);
 digitalWrite(rightMotor2, LOW );
 delay(1);
 }
 path[pathLength]='B';
 pathLength++;
 straight();
}
void shortPath(){
int shortDone=0;
 if(path[pathLength-3]=='L' && path[pathLength-1]=='R'){
 pathLength-=3;
 path[pathLength]='B';
 shortDone=1;
 }
if(path[pathLength-3]=='L' && path[pathLength-1]=='S' && shortDone==0){
 pathLength-=3;
 path[pathLength]='R';
 shortDone=1;
 }
 if(path[pathLength-3]=='R' && path[pathLength-1]=='L' && shortDone==0){
 pathLength-=3;
 path[pathLength]='B';
 shortDone=1;
 }
 if(path[pathLength-3]=='S' && path[pathLength-1]=='L' && shortDone==0){
 pathLength-=3;
 path[pathLength]='R';
 shortDone=1;
 }
 if(path[pathLength-3]=='S' && path[pathLength-1]=='S' && shortDone==0){
 pathLength-=3;
 path[pathLength]='B';
 shortDone=1;
 }
 if(path[pathLength-3]=='L' && path[pathLength-1]=='L' && shortDone==0){
 pathLength-=3;
 path[pathLength]='S';
 shortDone=1;
 }
 path[pathLength+1]='D';
 path[pathLength+2]='D';
 pathLength++;
 
 }
void printPath(){
 Serial.println("+++++++++++++++++");
 int x;
 while(x<=pathLength){
 Serial.println(path[x]);
 x++;
 }
 Serial.println("+++++++++++++++++");
}
void replay(){
 readSensors();
 if(leftFarReading==1 && rightFarReading==1){
 straight();
 }
 else{
 if(path[readLength]=='D'){
 digitalWrite(leftMotor1, HIGH);
 digitalWrite(leftMotor2, LOW);
 digitalWrite(rightMotor1, HIGH);
 digitalWrite(rightMotor2, LOW);
 analogWrite(enl,130);
 analogWrite(enr,255); 
 delay(100);
 digitalWrite(leftMotor1, LOW);
 digitalWrite(leftMotor2, LOW);
 digitalWrite(rightMotor1, LOW);
 digitalWrite(rightMotor2, LOW); 
 endMotion();
 }
 if(path[readLength]=='L'){
 digitalWrite(leftMotor1, HIGH);
 digitalWrite(leftMotor2, LOW);
 digitalWrite(rightMotor1, HIGH);
 digitalWrite(rightMotor2, LOW);
 analogWrite(enl,130);
 analogWrite(enr,255);  
 delay(leapTime);
 turnLeft();
 }
 if(path[readLength]=='R'){
 digitalWrite(leftMotor1, HIGH);
 digitalWrite(leftMotor2, LOW);
 digitalWrite(rightMotor1, HIGH);
 digitalWrite(rightMotor2, LOW);
 analogWrite(enl,130);
 analogWrite(enr,255); 
 delay(leapTime);
 turnRight();
 }
 if(path[readLength]=='S'){
 digitalWrite(leftMotor1, HIGH);
 digitalWrite(leftMotor2, LOW);
 digitalWrite(rightMotor1, HIGH);
 digitalWrite(rightMotor2, LOW);
 analogWrite(enl,130);
 analogWrite(enr,255); 
 delay(leapTime);
 straight();
 }
 readLength++;
 }
 replay();
}
void endMotion(){
 digitalWrite(led, LOW);
 delay(500);
 digitalWrite(led, HIGH);
 delay(200);
 digitalWrite(led, LOW);
 delay(200);
 digitalWrite(led, HIGH);
 delay(500);
 endMotion();
}
