int ledPins[] = {2, 3, 4, 5};
int buttonPins[] = {6, 7, 8, 9};

int gameSequence[100];
int userSequence[100];

int level = 0;
int userIndex = 0;

void setup() {
  randomSeed(analogRead(A0));

  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
    pinMode(buttonPins[i], INPUT_PULLUP);
  }

  startGame();
}

void loop() {
  for (int i = 0; i < 4; i++) {
    if (digitalRead(buttonPins[i]) == LOW) {
      userSequence[userIndex] = i;
      flashLED(i);
      delay(250);
      checkInput();
      while (digitalRead(buttonPins[i]) == LOW); // wait for release
    }
  }
}

void startGame() {
  level = 0;
  userIndex = 0;
  delay(800);
  nextLevel();
}

void nextLevel() {
  userIndex = 0;
  gameSequence[level] = random(0, 4);
  level++;
  playSequence();
}

void playSequence() {
  delay(500);
  for (int i = 0; i < level; i++) {
    flashLED(gameSequence[i]);
    delay(300);
  }
}

void flashLED(int i) {
  digitalWrite(ledPins[i], HIGH);
  delay(250);
  digitalWrite(ledPins[i], LOW);
}

void checkInput() {
  if (userSequence[userIndex] != gameSequence[userIndex]) {
    gameOver();
    return;
  }

  userIndex++;

  if (userIndex == level) {
    delay(500);
    nextLevel();
  }
}

void gameOver() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(ledPins[i], HIGH);
  }
  delay(1000);
  for (int i = 0; i < 4; i++) {
    digitalWrite(ledPins[i], LOW);
  }
  startGame();
}
