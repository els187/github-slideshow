/*ECE 1895 Design Project: Bop It
 *Meara Murphy, Tom Driscoll, Lizzie Seward
*/

//Pin Assignments
#define velostat A0
#define joystickX A1
#define joystickY A2
#define tilt A3
#define startGame A4
#define randomNumSeed A5
#define hex1A 1
#define hex1B 2
#define hex1C 3
#define hex1D 4
#define hex0A 5
#define hex0B 6
#define hex0C 7
#define hex0D 8
#define redLED 12
#define greenLED 11
#define blueLED 13
#define soundA 0
#define soundB 9
#define soundC 10

//Color Assignments
const int RED[3] = {255, 0, 0};
const int GREEN[3] = {0, 255, 0};
const int YELLOW[3] = {255, 255, 0};
const int BLUE[3] = {0, 0, 255};
const int PURPLE[3] = {147, 112, 219};
const int CLEAR[3] = {0, 0, 0};

//Note frequencies for buzzer
#define C 262
#define D 294
#define E 330
#define G 392



//Game State Configuration
int game;
#define SETUP 0
#define START 1
#define WON 2
#define LOST 3

//Score Configuration
int score;

//Variable to ensure that the sound for each input is played only once
bool soundPlayed;

//Velostat configuration
int velostatRest;

//Sensor List Configuration
const String sensorInputList[3] = {"SqueezeIt", "FlickIt", "ShakeIt"};

//Function prototypes
void startButtonHandler();
void flashRGB(int colors[]);
void setScore(int);
void displayScore(int);
bool userHitNewInputCorrectlyInTime();
String chooseRandomInput(String inputs[]);
int getTimeLimit(int);
int startTimer();
int checkTimer(int);
String getInput();
void sound(String);


void setup()
{ 
  //Initialize the state to setup
  game = SETUP;

  //Initialize pins
  pinMode(velostat, INPUT_PULLUP);
  pinMode(joystickX, INPUT);
  pinMode(joystickY, INPUT);
  pinMode(tilt, INPUT_PULLUP);
  pinMode(startGame, INPUT_PULLUP);
  pinMode(hex1A, OUTPUT);
  pinMode(hex1B, OUTPUT);
  pinMode(hex1C, OUTPUT);
  pinMode(hex1D, OUTPUT);
  pinMode(hex0A, OUTPUT);
  pinMode(hex0B, OUTPUT);
  pinMode(hex0C, OUTPUT);
  pinMode(hex0D, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(soundA, OUTPUT);
  pinMode(soundB, OUTPUT);
  pinMode(soundC, OUTPUT);
  
  digitalWrite(hex1A, 0);
  digitalWrite(hex1B, 0);
  digitalWrite(hex1C, 0);
  digitalWrite(hex1D, 0);
  digitalWrite(hex0A, 0);
  digitalWrite(hex0B, 0);
  digitalWrite(hex0C, 0);
  digitalWrite(hex0D, 0);
  //digitalWrite(soundA, 0);
  //digitalWrite(soundB, 0);
  //digitalWrite(soundC, 0);

  //Initialize seed for random number generator
  //Noise from unconnected analog pin will result in a new random number being generated each time
  randomSeed(analogRead(randomNumSeed));

  //Initialize soundPlayed to 0
  soundPlayed = 0;

}
void loop()
{
  //Sample the resting position of the velostat
  int sum = 0;
  for (int i = 0; i<10; i++)
  {
    sum += analogRead(velostat);
  }

  //Make the velostat rest the resting position
  velostatRest = sum/10;
 
  //Wait Until Button Pressed Event Occurs
  while(game != START) startButtonHandler();

  //Play Game
  while(game != LOST && game != WON)
  {
    if(userHitNewInputCorrectlyInTime() == true)
    {
      soundPlayed = 0;
      sound("CorrectInput");
      flashRGB(GREEN);
      
      if(score == 99)
      {
        sound("WinGame");
        flashRGB(BLUE);
        game = WON;
      }
      setScore(score+1);
    }
    else
    {
      sound("LoseGame");
      flashRGB(RED);
      game = LOST;
    }
  }  
}

void startButtonHandler()
{
  if (analogRead(startGame) < 100)
  {
    //Set the game state to start
    game = START;

    //Emit the start game sound
    sound("StartGame");

    //Clear the LED state
    flashRGB(CLEAR);

    //Set the score to 0
    setScore(0);
  }
}

void flashRGB(int color[])
{
  analogWrite(redLED, color[0]);
  analogWrite(greenLED, color[1]);
  analogWrite(blueLED, color[2]);
}

void setScore(int scoreVal)
{
  //Set the score to the parameter
  score = scoreVal;

  //Display the score
  displayScore(score);
}

void displayScore(int scoreVal)
{
  //Convert the score to 2 BCD numbers
  int hex1, hex0;
  hex1 = (scoreVal/10) % 10;
  hex0 = scoreVal % 10;

  //Write the score to the hex displays
  digitalWrite(hex1A, (hex1 >> 0) & 0x1);
  digitalWrite(hex1B, (hex1 >> 1) & 0x1);
  digitalWrite(hex1C, (hex1 >> 2) & 0x1);
  digitalWrite(hex1D, (hex1 >> 3) & 0x1);
  digitalWrite(hex0A, (hex0 >> 0) & 0x1);
  digitalWrite(hex0B, (hex0 >> 1) & 0x1);
  digitalWrite(hex0C, (hex0 >> 2) & 0x1);
  digitalWrite(hex0D, (hex0 >> 3) & 0x1);
}

void sound(String soundName)
{    
    if(soundName == "StartGame" || soundName == "CorrectInput")
    {
      tone(soundB, C, 500);
      delay(100);
      tone(soundB, E, 500);
      delay(100);
      tone(soundB, G, 500);
      delay(500);
    }
    else if(soundName == "WinGame")
    {
      tone(soundB, C, 500);
      delay(100);
      tone(soundB, D, 500);
      delay(100);
      tone(soundB, E, 500);
      delay(100);
      tone(soundB, C, 500);
      delay(100);
      tone(soundB, D, 500);
      delay(100);
      tone(soundB, E, 500);
      delay(100);
      tone(soundB, C, 500);
      delay(100);
      tone(soundB, D, 700);
      delay(100);
      tone(soundB, C, 900);
      delay(100);
    }
    else if(soundName == "LoseGame")
    {
      tone(soundB, G, 500);
      delay(100);
      tone(soundB, E, 500);
      delay(100);
      tone(soundB, C, 500);
      delay(500);
    }
    else if(soundName == "FlickIt")
    {
      tone(soundB, C, 500);
      delay(100);
      tone(soundB, G, 500);
      delay(100);
      tone(soundB, C, 500);
      delay(500);
    }
    else if(soundName == "SqueezeIt")
    {
      tone(soundB, E, 500);
      delay(100);
      tone(soundB, E, 500);
      delay(100);
      tone(soundB, E, 500);
      delay(500);
    }
    else if(soundName == "ShakeIt")
    {
      tone(soundB, G, 500);
      delay(100);
      tone(soundB, C, 500);
      delay(100);
      tone(soundB, G, 500);
      delay(500);
  }
}

bool userHitNewInputCorrectlyInTime()
{
  //Get next action for user to do
  String sensorToPress = chooseRandomInput(sensorInputList);
  sound(sensorToPress);

  //Initialize the user input to 0
  String userInput = "Nothing";

  //Set the elapsed time to 0
  int elapsedTime = 0;

  //Start the timer to determine the action deadline
  int startTime = startTimer();

  //Determine the time limit
  int timeLimit = getTimeLimit(score);

  //Wait until user does action or runs out of time
  while(userInput == "Nothing" && elapsedTime <= timeLimit)
  {
    //Recalculate the elapsed time
    elapsedTime = checkTimer(startTime);
    
    //Get the user input
    userInput = getInput();
  }

  if(userInput == sensorToPress) return true;
  else return false;
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
  else return 1600*4;
}

int startTimer()
{
  return millis();
}

int checkTimer(int startTime)
{
  return millis() - startTime;
}

String chooseRandomInput(String inputs[])
{
  int index = random(0,3);
  sound(inputs[index]);
  return inputs[index];
}

String getInput()
{
  if(analogRead(joystickX) > 990 || analogRead(joystickX) < 50 || analogRead(joystickY) > 990 || analogRead(joystickY) < 50)
  {
    return sensorInputList[1];
  }
  else if (analogRead(velostat) < velostatRest-75)
  {
    return sensorInputList[0];
  }
  else if (analogRead(tilt) > 200)
  {
    //Start the timer
    int start = startTimer();

    //Initialize the elapsed variable
    int elapsed = 0;

    //Ensure that tilt has been activated for 500 ms
    while (elapsed < 500)
    {
      elapsed = checkTimer(start);
      if(analogRead(tilt) < 200) return "Nothing";
    }

    //Once the timer is complete, if the tilt is still activated, return shake it as the input
    if(analogRead(tilt) > 200) return sensorInputList[2];
    else return "Nothing";
  }
  else
  {
    return "Nothing";
  }
}
