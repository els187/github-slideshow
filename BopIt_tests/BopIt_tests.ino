#define joystickX A0
#define joystickY A1
#define velostat A2
#define LED1 8
#define LED2 9
#define empty A3
#define tilt A4

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

//Global variables
int lastTiltState = HIGH;
int score;

void setup() {

  //Initialize pins
  pinMode(joystickX, INPUT);
  pinMode(joystickY, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(empty, INPUT);
  pinMode(tilt, INPUT_PULLUP);

  //Initialize score to 0
  score = 0;

  //Create a seed for the random numbers
  randomSeed(analogRead(empty));
}

void loop() {
  //Tests the timer and the intervals
  //if(score >= 100) score = 0;
  //testTimer();

  //Tests random number generator
  //randomTest();

  //Tests joystick input
  //readJoystick();

  //Tests the velostat input
  //readVelostat();

  //Tests the tilt input
  //readTiltSensor();
  
}

//Tilt sensor test function
void readTiltSensor()
{
  long lastDebounceTime = 0;
  long debounceDelay = 50;
  int sensorValue = digitalRead(tilt);
  if (sensorValue == lastTiltState) lastDebounceTime = millis();
  if ((millis() - lastDebounceTime) > debounceDelay) lastTiltState = sensorValue;
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
  else if(score <= 20) return 2900;
  else if(score <= 30) return 2700;
  else if(score <= 40) return 2500;
  else if(score <= 50) return 2300;
  else if(score <= 60) return 2000;
  else if(score <= 70) return 1900;
  else if(score <= 80) return 1800;
  else if(score <= 90) return 1700;
  else return 1600;
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
  int num = random(0,2);
  if(num == 1) digitalWrite(LED1, HIGH);
  else digitalWrite(LED2, HIGH);
  delay(500);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  delay(500);
  
}

void readVelostat()
{
  //Note: value 190 must be adjusted, they had 150 to detect a step
  //in the firewalker shoe to detect a step, and I figured squeezing would be slightly less pressure
  if(analogRead(velostat) < 190) digitalWrite(LED1, HIGH);
  else digitalWrite(LED2, LOW);
}
