const int RledPin = 9;
const int GledPin = 10;
const int BledPin = 11;

const int buttonPin = 2;

int mood = 0;
const int neutralMood = 10;
int buttonState = 0;
bool ButtonPressed = false;
unsigned long touchedTimer = 0;
unsigned long reducedTimer = 0;
const long unTouchInterval = 5000;
const long reducedInterval = 1000;


void setup() {
  // put your setup code here, to run once:
pinMode(buttonPin,INPUT);
pinMode(RledPin,OUTPUT);
pinMode(GledPin,OUTPUT);
pinMode(BledPin,OUTPUT);

mood = neutralMood;
}

void loop() {
  // put your main code here, to run repeatedly:
 if(mood >= 20){
    rainbowFlash();
  }
  // 心情為 0 → 紅燈閃爍
  else if(mood <= 0){
    redFlash();
  }
  else{
    showLEDState(mood);
  }

buttonState = digitalRead(buttonPin);

if(buttonState == LOW && !ButtonPressed){
  mood = mood + 1;
  if(mood > 20) mood = 20;
  touchedTimer = millis();
  ButtonPressed = true;
}

if(buttonState == HIGH && ButtonPressed){
  ButtonPressed = false;
}

unsigned long currentTimer = millis();
if(currentTimer - touchedTimer > unTouchInterval){
 if(currentTimer - reducedTimer > reducedInterval){
  mood = mood -1;
  if(mood < 0)mood = 0;
  reducedTimer = currentTimer;
 }
}

}

void showLEDState(int state){

  float brightnessInterval = 255 / 10.0;
  int Rvalue, Gvalue, Bvalue;

 if(state >= neutralMood){ // 心情高 → 偏藍
    Rvalue = 0;
    Gvalue = 255 - brightnessInterval * (state - neutralMood);
    Bvalue = brightnessInterval * (state - neutralMood);

    
  } 
  else { // 心情低 → 偏紅
    Rvalue = brightnessInterval * (neutralMood - state);
    Gvalue = 255 - brightnessInterval * (neutralMood - state);
    Bvalue = 0;
  }

  analogWrite(RledPin, 255 - Rvalue);
  analogWrite(GledPin, 255 - Gvalue);
  analogWrite(BledPin, 255 - Bvalue);
}


void rainbowFlash(){
  int colors[6][3] = {
    {255, 0, 0},   // 紅
    {255, 127, 0}, // 橘
    {255, 255, 0}, // 黃
    {0, 255, 0},   // 綠
    {0, 0, 255},   // 藍
    {75, 0, 130}   // 靛
  };

  for(int i = 0; i < 6; i++){
    analogWrite(RledPin, 255 - colors[i][0]);
    analogWrite(GledPin, 255 - colors[i][1]);
    analogWrite(BledPin, 255 - colors[i][2]);
    delay(100); // 每個顏色閃 100ms
  }
}

void redFlash(){
  analogWrite(RledPin, 0);   // 紅全亮
  analogWrite(GledPin, 255); // 綠全暗
  analogWrite(BledPin, 255); // 藍全暗
  delay(200);
  analogWrite(RledPin, 255); // 紅熄滅
  delay(200);
}