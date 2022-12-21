////////////////////
// CREDIT FOR SONGS GOES TO robsoncouto ON GITHUB (https://github.com/robsoncouto/arduino-songs)
////////////////////

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST 0


int melodyTetris[] = {
  // Based on the arrangement at https://www.flutetunes.com/tunes.php?id=192
 
  NOTE_E5, 4,  NOTE_B4,8,  NOTE_C5,8,  NOTE_D5,4,  NOTE_C5,8,  NOTE_B4,8,
  NOTE_A4, 4,  NOTE_A4,8,  NOTE_C5,8,  NOTE_E5,4,  NOTE_D5,8,  NOTE_C5,8,
  NOTE_B4, -4,  NOTE_C5,8,  NOTE_D5,4,  NOTE_E5,4,
  NOTE_C5, 4,  NOTE_A4,4,  NOTE_A4,8,  NOTE_A4,4,  
};

int melodyLion[] = {
  // Score available at https://musescore.com/user/18545446/scores/5061407

  NOTE_A4, -8, NOTE_A4, 16, NOTE_A4, -8, NOTE_A4, 
};

// change this to make the song slower or faster
int tempo = 140; 
int notes = 0; 
String song = "tetris";

// this calculates the duration of a whole note in ms (60s/tempo)*4 beats
int wholenote = (60000 * 4) / tempo;

int divider = 0, noteDuration = 0;

// get sizes of arrays for each song
int sizeTetris = sizeof(melodyTetris);
int sizeLion = sizeof(melodyLion);


////////////////////
/////////////
////////////////////


// 2 == blue, 3 == green, 4 == yellow, 5 == red, 6 == black
// blue == LED 1, green == LED 2, yellow == LED 3, red == LED 4, black == LED 5
const int buttons[5] = {2, 3, 4, 5, 6};
int buttonValues[5] = {LOW, LOW, LOW, LOW, LOW};

const int ledPins[5] = {7, 8, 9, 11, 12};

// analog pins & values for photoresistors
const int photoresistors[5] = {A0, A1, A2, A3, A4};
int brightnessDefault[5] = {0, 0, 0, 0, 0};

const int piezo = 10;

// manage controls for Knight Rider game (Lightspeed)
bool correctButton = false;
bool failedKnightRider = false;
int chosenLED = 0;
int wrongAttempts = 0;

// manage musical sequence for DJ game (DJ Memory)
bool correctSequence = false;
bool DJlevelUp = false;
bool failedDJ = false;
int DJsequence[5];
int sequenceSize = 1;
int currAttemptDJ = 0;
int correctDJ = 0;

// keep track of which game we're on
bool finishedKnightRider = false;
bool finishedDJ = false;
bool skipDJ = false;

// specify serial monitor vs interactive inputs
char playMode;


// Purpose: runs through once to structure & begin the program
void setup() {
  // set all transducers to input/output
  for (int i = 0; i < 5; i++) {
    pinMode(buttons[i], INPUT_PULLUP);
    pinMode(ledPins[i], OUTPUT);
  }
  pinMode(piezo, OUTPUT);
  
  Serial.begin(9600);

  // introduce game with song
  delay(150);
  playSong(melodyTetris);

  choosePlayMode();

  // get things structured for Knight Rider & DJ games
  setupKnightRider();
  setupDJ();
}

// Purpose: runs through repeatedly to process the program
void loop() {
  // run Lightspeed game
  while (not finishedKnightRider) {
     runKnightRider();
  }
  // return from Lightspeed & process results
  if (finishedKnightRider) {
    delay(500);
    skipDJ = false;
    showKnightRiderScore();

    // if user failed Lightspeed, they can restart all games
    if (failedKnightRider) {
      offerPlayAgain();
      skipDJ = true;
    }
    else {
      offerNextGame();      
    }
  }

  delay(1000);

  // if Lightspeed successful, continue to DJ Memory
  if (not skipDJ) {
    while (not finishedDJ) {
      runDJ();      
    }
    if (finishedDJ) {
      offerPlayAgain(); 
    }   
  }  
}


// Purpose: prompt user to choose whether to play via serial monitor or via interactive inputs
// Notes: assumes user can access serial monitor to decide
void choosePlayMode() {
  delay(200);
  Serial.println(F("********************"));
  Serial.println(F("Welcome! Are you ready to play? To move between games using the serial monitor, type 's'. For a more interactive experience, type 'i'."));
  Serial.println();

  // get user's decision
  while (Serial.available() == 0) { }   
  playMode = Serial.read();

  while (playMode != 115 && playMode != 105) { // 's' == 115, 'i' == 105 in ASCII
    Serial.print(F("You have entered: "));
    Serial.println(playMode);
    
    Serial.println(F("Invalid input"));
    Serial.println();
    
    Serial.println(F("To move between games using the serial monitor, type 's'. For a more interactive experience, type 'i'."));
    Serial.println();
    while (Serial.available() == 0) { }
    playMode = Serial.read();
  }

  // report back their decision
  if (playMode == 's') {
    Serial.println(F("You have entered: s. Let's use the serial monitor!"));
  }
  else {
    Serial.println(F("You have entered: i. Let's make it interactive! When prompted, press any button to continue to a new game."));
  }
  Serial.println();
  delay(1000);
}


// Purpose: reset all settings so game can restart from beginning
// Notes: only utilized if user chooses it
void resetAll() {
  // reset Knight Rider
  correctButton = false;
  failedKnightRider = false;
  wrongAttempts = 0;
  
  // reset DJ
  correctSequence = false;
  DJlevelUp = false;
  failedDJ = false;
  currAttemptDJ = 0;
  sequenceSize = 1;
  correctDJ = 0;
  
  // reset game settings
  finishedKnightRider = false;
  finishedDJ = false;
  skipDJ = false;

  // introduce new game
  playSong(melodyTetris);
  setupKnightRider();  
}


// Purpose: prompt user to proceed to the next game (i.e. Lightspeed to DJ Memory)
// Notes: turns lights off to prepare for DJ Memory if user chooses to continue
void offerNextGame() {
  String phraseSerial = "Continue to next game? (y/n): ";
  String phraseButton = "Press any button to continue to the next game.";
  
  bool nextGameChoice = promptChoice(phraseSerial, phraseButton);

  // handle user's choice to keep going or quit
  if (nextGameChoice) {
    delay(800);
    Serial.println();
    lightsOff();  
  }
  else {
    Serial.println();
    Serial.println(F("Thanks for playing!"));
    lightsOff();
    delay(500);
    exit(1);
  }
}


// Purpose: prompt user to restart all games anew
// Notes: resets settings if user chooses to play again
void offerPlayAgain() {
  String phraseSerial = "Restart all games from the beginning? (y/n): ";
  String phraseButton = "Press any button to restart all games from the beginning.";
  
  bool newGameChoice = promptChoice(phraseSerial, phraseButton);

  // handle user's choice to restart all games anew or quit
  if (newGameChoice) {
    delay(1200);
    lightsOff();
    resetAll();
    Serial.println();
    Serial.println();
    delay(200);
  }
  else {
    Serial.println();
    Serial.println(F("Thanks for playing!"));
    lightsOff();
    delay(500);
    exit(1);
  }
}


// Purpose: handle general script for prompting continuation of game
// Notes: will make use of either serial monitor or buttons according to user's initial choice
bool promptChoice(String phraseSerial, String phraseButton) {
  bool gameChoice = false;
  bool decided = false;

  // get user's direct written input
  if (playMode == 's') {
    char nextGame = handleSerial(phraseSerial); 
    Serial.print(nextGame);
    delay(30); 
    if (nextGame == 'y') {
      gameChoice = true;
    } 
  }
  else {
    Serial.println();
    Serial.println(phraseButton);
    
    // check if any of the buttons have been pressed to continue
    while (not decided) {
      if (checkButtonsPressed() != -1) {
        gameChoice = true;
        decided = true;
      }
    }   
  } 
  return gameChoice;
}


// Purpose: process input via the serial monitor for continuing game
// Notes: has constraints built in so as to avoid errors
char handleSerial(String phraseSerial) {
  // print the prompt
  Serial.println();
  Serial.print(phraseSerial);
  while (Serial.available() == 0) { }
  char nextGame = Serial.read();

  // handle invalid input
  while (nextGame != 121 && nextGame != 110) { // 'y' == 121, 'n' == 110 in ASCII
    Serial.println();
    Serial.print(F("You have entered: "));
    Serial.println(nextGame);
    
    Serial.println(F("Invalid input"));
    Serial.println();
    
    Serial.print(phraseSerial);
    while (Serial.available() == 0) { }
    nextGame = Serial.read();
  }
  return nextGame;
}


// Purpose: turn off all LEDs
void lightsOff() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(ledPins[i], LOW);
  }
}


// Purpose: structure Lightspeed game by choosing target LED
// Notes: this is the LED that the user will need to hit 
void setupKnightRider() {
  // turn all lights off before Knight Rider
  lightsOff();

  // choose random LED for user to target
  chosenLED = random(0, 5);

  Serial.println(F("Pay attention to which LED flashes. This will be the chosen LED."));

  // flash chosen LED to signal its importance
  for (int i = 0; i < 5; i++) {
    digitalWrite(ledPins[chosenLED], HIGH);
    delay(500);
    digitalWrite(ledPins[chosenLED], LOW);
    delay(500);
  }  
  Serial.println(F("Press the button corresponding to the chosen LED when the LED is lit."));
  delay(50);
}


// Purpose: handle flow of Lightspeed game
// Notes: written feedback during game is only available via the serial monitor
void runKnightRider() {
  // cycle through Knight Rider
  knightRider();

  // check to see if user maxed out their mistakes
  if (failedKnightRider) {
    Serial.println(F("You've made 5 mistakes! Better luck next time."));
    finishedKnightRider = true;
    return;
  }

  // we've returned from knightRider which means user was successful
  if (correctButton) {
    Serial.println(F("You hit the correct button; great work!"));
    finishedKnightRider = true;    
    delay(500);

    // flash chosen LED to show that it’s been hit
    for (int i = 0; i < 5; i++) {
      digitalWrite(ledPins[chosenLED], HIGH);
      delay(500);
      digitalWrite(ledPins[chosenLED], LOW);
      delay(500);
    }
    // celebrate with enjoyable song
    playSong(melodyTetris);  
  }  
}


// Purpose: replicate Knight Rider pattern by flashing LEDs back & forth
// Notes: checks to see if buttons have been pressed while iterating
void knightRider() {
  // have lights rush back & forth repeatedly (Knight Rider)  
  for (int i = 0; i < 5; i++) {
    digitalWrite(ledPins[i], HIGH);
    if (i != 4) {
      delay(200);
      digitalWrite(ledPins[i], LOW);
    }
    
    // check to see if button pressed, indicates either correct hit (win) or maxed attempts (fail)
    checkAttempt(i);
    if (correctButton or failedKnightRider) {
      return;
    }    
  }
  // same structure as above, but flashing the other way (while still checking buttons)
  for (int i = 5; i > 0; i--) {
    digitalWrite(ledPins[i], HIGH);
    delay(200);
    digitalWrite(ledPins[i], LOW);

    checkAttempt(i);
    if (correctButton or failedKnightRider) {
      return;
    }   
  }  
}


// Purpose: checks whether any buttons have been correctly pressed to match chosen LED
// Notes: keeps track of failed attempts during Lightspeed game
void checkAttempt(int i) {
  // check if correct button has been pressed to match target LED
  if (chosenLED == i) {
    if (checkButtonsPressed() == chosenLED) {
      correctButton = true;
    }
    // the user pressed a button but it wasn't the correct one
    else if (checkButtonsPressed() != -1) {
      wrongAttempts++;
      
      // signal mistake with unpleasant song
      song = "lion";
      playSong(melodyLion);
      song = "tetris";

      // if they've maxed out on failed attempts, the game ends
      if (wrongAttempts == 5) {
        failedKnightRider = true;
      }
    }
  }  
}


// Purpose: checks whether any of the 5 buttons have been pressed
// Notes: if nothing has been pressed, -1 is returned
int checkButtonsPressed() {
  // see if a button has been pressed
  for (int i = 0; i < 5; i++) {
    buttonValues[i] = digitalRead(buttons[i]);
    if (buttonValues[i] == HIGH) {
      return i;
    }
  }
  // no button was pressed
  return -1;
}


// Purpose: display score for Lightspeed game
// Notes: score is calculated as follows: (number LEDs - number mistakes)
void showKnightRiderScore() { 
  int numFlashes = 4;
  int numCorrect = 5 - wrongAttempts;
  
  // flash each LED earned then leave on to represent total score
  for (int i = 0; i < numCorrect; i++) {
    while (numFlashes > 0) {
      digitalWrite(ledPins[i], HIGH);
      delay(200);
      digitalWrite(ledPins[i], LOW);
      delay(200);
      numFlashes--;
    }
    numFlashes = 4;
    digitalWrite(ledPins[i], HIGH);
    delay(200);
  }

  // if perfect game (no mistakes) celebrate with enjoyable song
  if (numCorrect == 5) {
    Serial.println(F("You made no mistakes and beat the game on your first try. Well done!"));
    playSong(melodyTetris);
  } 
  // otherwise write specific level they've reached
  else {
    if (numCorrect != 0) {
      Serial.print(F("Nice work! "));
    }
    Serial.print(F("You made it to level "));
    Serial.println(numCorrect);
  } 
}


// Purpose: structure DJ Memory game by reading initial photoresistor values
// Notes: initial photoresistor values will be referenced throughout game to detect user's hand waving
void setupDJ() {
  // read photoresistors, where darkness yields higher value & brightness yields lower value
  for (int i = 0; i < 5; i++) {
    brightnessDefault[i] = analogRead(photoresistors[i]);
    delay(700);    
  }
  Serial.println();  
}


// Purpose: choose random sequence of notes based on current sequence length
// Notes: selected notes will be played & stored for the user to mimic
void getDJSequence() {
  delay(1000);

  // increase sequence length if previous attempt successful
  if (DJlevelUp) {
    sequenceSize++;    
  }

  // get random sequence of notes for user to copy
  for (int i = 0; i < sequenceSize; i++) {
    DJsequence[i] = random(0, 5);
    playNote(DJsequence[i]);
    delay(800);
  } 

  Serial.println();
  Serial.println(F("Now it's your turn! Match the sequence."));  
}


// Purpose: handle flow of DJ Memory game
// Notes: function calls itself when it loops for higher levels (i.e. longer sequences)
void runDJ() {
  delay(500);

  // randomize & play a sequence
  getDJSequence();

  while (not correctSequence) {
    measureUserDJ();  

    // check to see if user messed up sequence
    if (failedDJ) {
      finishedDJ = true;
      return;
    }
  }

  // we've returned from DJ which means user was successful
  if (correctSequence) {
    delay(500); 

    // they've successfully done all 5 levels
    if (sequenceSize == 5) {
      Serial.println();
      Serial.println(F("You successfully completed all 5 levels.. fantastic job!"));
      finishedDJ = true;
      showDJScore();
      return;
    }
    // there are more levels, so we go up a level & make it harder
    else {     
      DJlevelUp = true;
      correctSequence = false;
      currAttemptDJ = 0;
      runDJ();
    }           
  }  
}


// Purpose: check if user has waved hand over photoresistor & respond accordingly
// Notes: initial photoresistor values read at start of program serve as comparison throughout game
void measureUserDJ() {
  // keep track of order in which user must wave hand over photoresistors
  int nextNote = DJsequence[currAttemptDJ];
  
  for (int i = 0; i < 5; i++) {
    int currBrightness = analogRead(photoresistors[i]);
    delay(20);

    // check if user has passed hand over photoresistor & play corresponding note if so
    if (currBrightness - brightnessDefault[i] > 30) {
      playNote(i);

      // user messed up, so exit this & terminate game
      if (i != nextNote) {
        Serial.print(F("Uh oh, you made a mistake in the sequence! You made it to level "));
        Serial.println(correctDJ);        

        // signal mistake with unpleasant song
        song = "lion";
        playSong(melodyLion);
        song = "tetris";

        failedDJ = true;
        delay(500);
        showDJScore();
        return;       
      }
      
      // get the next note in the current sequence 
      currAttemptDJ++;
      if (currAttemptDJ < sequenceSize) {
        nextNote = DJsequence[currAttemptDJ];
      }
      // we've reached the end of the sequence without any errors, so now they level up
      else {
        Serial.println(F("Great job, you matched the sequence! It's time for the next level."));
        correctSequence = true;
        correctDJ++;
        delay(1000);
        
        // celebrate with enjoyable song
        playSong(melodyTetris);
        delay(300);
      }      
    }        
    delay(20);   
  }  
}


// Purpose: display score for DJ Memory game
// Notes: each level completed (sequence length) earns an additional LED
void showDJScore() {
  // flash each LED earned then leave on to represent total score
  int numFlashes = 4;
  for (int i = 0; i < correctDJ; i++) {
    while (numFlashes > 0) {
      digitalWrite(ledPins[i], HIGH);
      delay(200);
      digitalWrite(ledPins[i], LOW);
      delay(200);
      numFlashes--;
    }
    numFlashes = 4;
    digitalWrite(ledPins[i], HIGH);
    delay(200);
  }

  // if perfect game (all 5 levels) celebrate with enjoyable song
  if (correctDJ == 5) {
    playSong(melodyTetris);
  }     
}


// Purpose: play specified music note to piezo
// Notes: each note corresponds to a photoresistor for DJ Memory
void playNote(int photoresistorI) {
  char names[] = {'c', 'd', 'e', 'f', 'g'};
  int tones[] = {1915, 1700, 1519, 1432, 1275};

  // play note coresponding to specific photoresistor
  digitalWrite(ledPins[photoresistorI], HIGH);
  tone(piezo, tones[photoresistorI], 1000);
  delay(1500);
  digitalWrite(ledPins[photoresistorI], LOW); 
}


// Purpose: select the appropriate song to play, then play it
// Notes: all credit for latter half of function (the process of playing the music) belongs to robsoncouto on GitHub
void playSong(int songChoice[]) {
  // identify the song to play
  if (song == "tetris") {
    notes = sizeTetris / sizeof(melodyTetris[0]) / 2;
  }
  else if (song == "lion") {
    notes = sizeLion / sizeof(melodyLion[0]) / 2;
  }
  
  ////////////////////
  // ALL CREDIT FOR BELOW FUNCTIONALITY GOES TO robsoncouto ON GITHUB (https://github.com/robsoncouto/arduino-songs)
  ////////////////////
  
  // iterate over the notes of the melody
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = songChoice[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } 
    else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(piezo, songChoice[thisNote], noteDuration*0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);
    
    // stop the waveform generation before the next note.
    noTone(piezo);
  }   
}
