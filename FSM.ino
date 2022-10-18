#define LED_W_R 5
#define LED_W_Y 6
#define LED_W_G 7
#define WEST_BUTTON_PIN 2
#define LED_S_R 8
#define LED_S_Y 9
#define LED_S_G 10
#define LED_P_R 11
#define LED_P_G 12
#define SOUTH_BUTTON_PIN 3
#define goW 0
#define waitW 1
#define goS 2
#define waitS 3
#define waitPS 4
#define waitPW 5
#define goP 6
#define brink 7
#define PEOPLE_WALK_PIN 4

struct State {unsigned long ST_Out;    // 6-bit pattern to street output 
unsigned long Time;      // delay in msunits
unsigned long Next[8];}; // next state for inputs 0,1,2,3

typedef const struct State SType;

SType FSM[13]={{B01001100,2000,{goW,goW,waitW,waitW,waitPW,waitPW,waitPW,waitW}},  //goW
	{B01001010,300,{goS,goS,goS,goS,goS,goS,goS,goS}},                               //waitW
	{B01100001,2000,{goS,waitS,goS,waitS,waitPS,waitPS,waitPS,waitPS}},                 //goS
	{B01010001,300,{goW,goW,goW,goW,goW,goW,goW,goW}},                               //waitS
  {B01010001,300,{goP,goP,goP,goP,goP,goP,goP,goP}},                               //waitPS
  {B01001010,300,{goP,goP,goP,goP,goP,goP,goP,goP}},                               //waitPW
  {B10001001,2000,{goP,brink,brink,brink,goP,brink,brink,brink}},                  //goP
  {B00001001,300,{8,8,8,8,8,8,8,8}},                                               //brink
  {B10001001,300,{9,9,9,9,9,9,9,9}},                                               //8
  {B00001001,300,{10,10,10,10,10,10,10,10}},                                       //9
  {B10001001,300,{11,11,11,11,11,11,11,11}},                                       //10
  {B00001001,300,{12,12,12,12,12,12,12,12}},                                       //11
  {B10001001,300,{goP,goW,goS,goW,goP,goW,goS,goW}},                               //12           
};

unsigned long S=0;  // index to the current state   
void setup() {
  pinMode(LED_W_R, OUTPUT);
  pinMode(LED_W_Y, OUTPUT);
  pinMode(LED_W_G, OUTPUT); 
  pinMode(WEST_BUTTON_PIN, INPUT);  
  pinMode(LED_S_R, OUTPUT);
  pinMode(LED_S_Y, OUTPUT);
  pinMode(LED_S_G, OUTPUT);
  pinMode(LED_P_G, OUTPUT); 
  pinMode(LED_P_R, OUTPUT); 
  pinMode(SOUTH_BUTTON_PIN, INPUT);
  pinMode(PEOPLE_WALK_PIN, INPUT);
}

int input,WEST_BUTTON,SOUTH_BUTTON,PEOPLE_BUTTON;
void loop() {
  digitalWrite(LED_W_R, FSM[S].ST_Out& B00000001);
  digitalWrite(LED_W_Y, FSM[S].ST_Out& B00000010);
  digitalWrite(LED_W_G, FSM[S].ST_Out& B00000100);
  digitalWrite(LED_S_R, FSM[S].ST_Out& B00001000);
  digitalWrite(LED_S_Y, FSM[S].ST_Out& B00010000);
  digitalWrite(LED_S_G, FSM[S].ST_Out& B00100000);
  digitalWrite(LED_P_R, FSM[S].ST_Out& B01000000);
  digitalWrite(LED_P_G, FSM[S].ST_Out& B10000000);
  delay(FSM[S].Time);

  WEST_BUTTON = digitalRead(WEST_BUTTON_PIN);
  SOUTH_BUTTON = digitalRead(SOUTH_BUTTON_PIN);
  PEOPLE_BUTTON = digitalRead(PEOPLE_WALK_PIN);
  input = (SOUTH_BUTTON*2)+WEST_BUTTON+(PEOPLE_BUTTON*4);
  S = FSM[S].Next[input]; 
}
