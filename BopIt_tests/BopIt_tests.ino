#define joystickX A1
#define joystickY A2
#define velostat A0
#define LED1 12
#define LED2 13
#define LED3 0
#define empty A5
#define tilt A3
#define redLED 9
#define greenLED 10
#define blueLED 11

//Input test functions
void readJoystick();
void readVelostat();
void readTiltSensor();

//Timer test functions
void testTimer();
int startTimer();
int checkTimer(int);
String getInput();

//Other test functions
void randomTest();
void flashRGB(int color[]);
void testRGB();
void testGetInput();

//Global variables
int lastTiltState = HIGH;
int score;

//Color Assignments
const int RED[3] = {255, 0, 0};
const int GREEN[3] = {0, 255, 0};
const int YELLOW[3] = {255, 255, 0};
const int PURPLE[3] = {147, 112, 219};

void setup() {

  //Initialize pins
  pinMode(joystickX, INPUT);
  pinMode(joystickY, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(empty, INPUT);
  pinMode(tilt, INPUT_PULLUP);
  pinMode(velostat, INPUT_PULLUP);

  //Initialize score to 0
  score = 0;

  //Create a seed for the random numbers
  randomSeed(analogRead(empty));
}

void loop() {
  //Tests the timer and the intervals
  //if(score >= 100) score = 0;
  testTimer();

  //Tests random number generator
  //randomTest();

  //Tests joystick input
  //readJoystick();

  //Tests the velostat input
  //readVelostat();

  //Tests the tilt input
  //readTiltSensor();

  //TestsRGB led
  //testRGB();

  //Tests reading all inputs
  //testGetInput();
  
}

//Tilt sensor test function
void readTiltSensor()
{
  if(analogRead(tilt) > 200)
  {
    digitalWrite(LED2, HIGH);
  }
  else
  {
    digitalWrite(LED2, LOW);
  }
  delay(50);
}
//Joystick test function
void readJoystick()
{
  if(analogRead(joystickX) > 1000)
  { 
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
  }
  else if(analogRead(joystickX) < 200)
  {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
  }
  else if(analogRead(joystickY) > 1000)
  {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, HIGH);
  }
  else if(analogRead(joystickY) < 200)
  {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, HIGH);
  }
  else
  {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
  }
}

void testTimer()
{
  //Initialize the score and 
  int elapsedTime = 0;
  int startTime = startTimer();
  int timeLimit = getTimeLimit(score);
  while(elapsedTime <= timeLimit)
  {
    //Alternate LEDs so wait time is observable
    if(score % 2 == 0) digitalWrite(LED1, HIGH);
    else digitalWrite(LED2, HIGH);

    //Recalculate elapsed time
    elapsedTime = checkTimer(startTime);
  }
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  score += 5;
}

int getTimeLimit(int score)
{
  if(score <= 10) return 3000;
  else if(score <= 20) return 2500;
  else if(score <= 30) return 2000;
  else if(score <= 40) return 1500;
  else if(score <= 50) return 1000;
  else return 500;
}

int startTimer()
{
  return millis();
  
}

int checkTimer(int startTime)
{
  return millis() - startTime;
}

void randomTest()
{
  int num = random(0,3);
  if(num == 1) digitalWrite(LED1, HIGH);
  else if(num == 2) digitalWrite(LED2, HIGH);
  else digitalWrite(LED3, HIGH);
  delay(500);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  delay(500);
  
}

void readVelostat()
{
  //Note: value 190 must be adjusted, they had 150 to detect a step
  //in the firewalker shoe to detect a step, and I figured squeezing would be slightly less pressure
  if(analogRead(velostat) < 150) digitalWrite(LED1, HIGH);
  else digitalWrite(LED1, LOW);
}

void flashRGB(int color[])
{
  analogWrite(redLED, color[0]);
  analogWrite(greenLED, color[1]);
  analogWrite(blueLED, color[2]);
}
void testRGB()
{
 flashRGB(RED);
 delay(1000);
 flashRGB(GREEN);
 delay(1000);
 flashRGB(YELLOW);
 delay(1000);
}

void testGetInput()
{
  //Read joystick input (allows motion in any direction
  if(analogRead(joystickX) > 1000 || analogRead(joystickX) < 200 || analogRead(joystickY) > 1000 || analogRead(joystickY) < 200)
  {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
  }
  else if (analogRead(velostat) < 150)
  {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, LOW);
  }
  else if (analogRead(tilt) > 200)
  {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, HIGH);
  }
  else
  {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
  }
}
