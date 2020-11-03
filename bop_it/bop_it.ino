/*ECE 1895 Design Project: Bop It
 * Meara Murphy, Tom Driscoll, Lizzie Seward
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
#define redLED 9
#define greenLED 10
#define blueLED 11
#define soundA 0
#define soundB 12
#define soundC 13

//Color Assignments
const int RED[3] = {255, 0, 0};
const int GREEN[3] = {0, 255, 0};
const int YELLOW[3] = {255, 255, 0};

//Game State Configuration
int game;
#define SETUP 0
#define START 1
#define WON 2
#define LOST 3

//Score Configuration
int score;

//Sensor List Configuration
const String sensorInputList[3] = {"SqueezeIt", "ShakeIt", "FlickIt"};

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
String getInput();
void playSound();
void sound();


void setup()
{ 
  //Initialize the state to setup
  game = SETUP;

  //Initialize pins
  pinMode(velostat, INPUT);
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

  //Initialize seed for random number generator
  //Noise from unconnected analog pin will result in a new random number being generated each time
  randomSeed(analogRead(randomNumSeed));
}

void loop()
{
  //Wait Until Button Pressed Event Occurs
  while(game != START) startButtonHandler();

  //Initialize Game
  setScore(0);
  sound("StartGame");

  //Play Game
  while(game != LOST && game != WON)
  {
    if(userHitNewInputCorrectlyInTime() == true)
    {
      sound("CorrectInput");
      flashRGB(GREEN);
      setScore(score+1);

      if(score == 99)
      {
        sound("WinGame");
        flashRGB(YELLOW);
        game = WON;
      }
      else
      {
        sound("LoseGame");
        flashRGB(RED);
        game = LOST;
      }
    }
  }  
}

void startButtonHandler()
{
  if (analogRead(startGame) > 200) game = START;
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
  digitalWrite(hex1A, hex1 >> 0);
  digitalWrite(hex1A, hex1 >> 1);
  digitalWrite(hex1A, hex1 >> 2);
  digitalWrite(hex1A, hex1 >> 3);
  digitalWrite(hex0A, hex0 >> 0);
  digitalWrite(hex0A, hex0 >> 1);
  digitalWrite(hex0A, hex0 >> 2);
  digitalWrite(hex0A, hex0 >> 3);
}

void sound(String soundName)
{      
  if(soundName == "StartGame")
  {
    //manipulate soundA, soundB, soundC here
  }
  else if(soundName == "CorrectInput")
  {
    //manipulate soundA, soundB, soundC here
  }
  else if(soundName == "LoseGame")
  {
    //manipulate soundA, soundB, soundC here
  }
  else if(soundName == "WinGame")
  {
    //manipulate soundA, soundB, soundC here
  }
  else if(soundName == "FlickIt")
  {
    //manipulate soundA, soundB, soundC here
  }
  else if(soundName == "SqueezeIt")
  {
    //manipulate soundA, soundB, soundC here
  }
  else if(soundName == "ShakeIt")
  {
    //manipulate soundA, soundB, soundC here
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

  //Wait until user does action or runs out of time
  while(userInput = "Nothing" && elapsedTime <= getTimeLimit(score))
  {
    //Recalculate the elapsed time
    elapsedTime = checkTimer(startTime);

    //Get the user input
    userInput = getInput();
  }

  //Check if the action was entered correcly and on time
  if(userInput == sensorToPress && elapsedTime <= getTimeLimit(score)) return true;
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

String chooseRandomInput(String inputs[])
{
  int index = random(0,3);
  sound(inputs[index]);
}

String getInput()
{
  //Read joystick input (allows motion in any direction
  if(analogRead(joystickX) > 1000 || analogRead(joystickX) < 200 || analogRead(joystickY) > 1000 || analogRead(joystickY) < 200) return sensorInputList[3];
  //else if velostat return sensorInputList[1];
  //else if tilt sensor return sensorInputList[2];
  else return "Nothing";
}
