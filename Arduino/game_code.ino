int p1Buttons[3] = {3, 5, 7};
int p1Leds[3]    = {8, 11, 12};

int p2Buttons[3] = {A5, A4, A3};
int p2Leds[3]    = {A2, A1, A0};

int startButton = 13;

bool gameRunning = false;
int currentLevel = 0;

int p1Target = 0;
int p2Target = 0;

const int seqLenL2 = 4;
const int seqLenL3 = 8;
int seqArr[seqLenL3];
int activeSeqLen = 0;

int p1Idx = 0;
int p2Idx = 0;

unsigned long roundStart = 0;
unsigned long p1Finish = 0;
unsigned long p2Finish = 0;

int pressCount = 0;
unsigned long firstPressTime = 0;
const unsigned long pressWindowMs = 650;

void allOff() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(p1Leds[i], LOW);
    digitalWrite(p2Leds[i], LOW);
  }
}

void blinkWinner(int player) {
  for (int k = 0; k < 3; k++) {
    if (player == 1) {
      digitalWrite(p1Leds[0], HIGH);
      digitalWrite(p1Leds[1], HIGH);
      digitalWrite(p1Leds[2], HIGH);
    } else if (player == 2) {
      digitalWrite(p2Leds[0], HIGH);
      digitalWrite(p2Leds[1], HIGH);
      digitalWrite(p2Leds[2], HIGH);
    } else {
      digitalWrite(p1Leds[0], HIGH);
      digitalWrite(p1Leds[1], HIGH);
      digitalWrite(p1Leds[2], HIGH);
      digitalWrite(p2Leds[0], HIGH);
      digitalWrite(p2Leds[1], HIGH);
      digitalWrite(p2Leds[2], HIGH);
    }
    delay(200);
    allOff();
    delay(200);
  }
}

void waitRelease(int pin) {
  while (digitalRead(pin) == LOW) {}
  delay(15);
}

int pressedIndex3(int pinA, int pinB, int pinC) {
  if (digitalRead(pinA) == LOW) return 0;
  if (digitalRead(pinB) == LOW) return 1;
  if (digitalRead(pinC) == LOW) return 2;
  return -1;
}

void showSequence() {
  allOff();
  delay(250);
  for (int i = 0; i < activeSeqLen; i++) {
    int idx = seqArr[i];
    digitalWrite(p1Leds[idx], HIGH);
    digitalWrite(p2Leds[idx], HIGH);
    delay(250);
    allOff();
    delay(200);
  }
  delay(150);
}

void printWinnerLine(int winner) {
  if (winner == 1) Serial.println("Winner: P1");
  else if (winner == 2) Serial.println("Winner: P2");
  else Serial.println("Winner: TIE");
}

const char* colorName(int idx) {
  if (idx == 0) return "GREEN";
  if (idx == 1) return "YELLOW";
  return "RED";
}

void printLevel1Result(int winner) {
  unsigned long p1t = (p1Finish > 0) ? (p1Finish - roundStart) : 0;
  unsigned long p2t = (p2Finish > 0) ? (p2Finish - roundStart) : 0;

  Serial.println();
  Serial.println("LEVEL 1");
  Serial.print("P1 target: "); Serial.println(colorName(p1Target));
  Serial.print("P2 target: "); Serial.println(colorName(p2Target));
  Serial.print("P1 reaction (ms): "); Serial.println(p1t);
  Serial.print("P2 reaction (ms): "); Serial.println(p2t);
  printWinnerLine(winner);
  Serial.println();
}

void printLevel23Result(int winner) {
  unsigned long p1t = (p1Finish > 0) ? (p1Finish - roundStart) : 0;
  unsigned long p2t = (p2Finish > 0) ? (p2Finish - roundStart) : 0;

  Serial.println();
  Serial.print("LEVEL "); Serial.println(currentLevel);
  Serial.print("Sequence length: "); Serial.println(activeSeqLen);
  Serial.print("P1 time (ms): "); Serial.println(p1t);
  Serial.print("P2 time (ms): "); Serial.println(p2t);
  printWinnerLine(winner);
  Serial.println();
}

void endRound(int winner) {
  allOff();
  blinkWinner(winner);
  gameRunning = false;
  allOff();
  delay(250);

  if (currentLevel == 1) printLevel1Result(winner);
  else printLevel23Result(winner);

  currentLevel = 0;
}

void startLevel1() {
  allOff();
  delay(random(800, 2000));

  p1Target = random(0, 3);
  p2Target = random(0, 3);

  digitalWrite(p1Leds[p1Target], HIGH);
  digitalWrite(p2Leds[p2Target], HIGH);

  roundStart = millis();
  p1Finish = 0;
  p2Finish = 0;

  gameRunning = true;
  currentLevel = 1;
}

void startLevel2or3(int lvl) {
  allOff();
  currentLevel = lvl;
  activeSeqLen = (lvl == 2) ? seqLenL2 : seqLenL3;

  for (int i = 0; i < activeSeqLen; i++) seqArr[i] = random(0, 3);

  showSequence();

  roundStart = millis();
  p1Finish = 0;
  p2Finish = 0;
  p1Idx = 0;
  p2Idx = 0;

  gameRunning = true;
}

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(A5));

  for (int i = 0; i < 3; i++) {
    pinMode(p1Buttons[i], INPUT_PULLUP);
    pinMode(p2Buttons[i], INPUT_PULLUP);
    pinMode(p1Leds[i], OUTPUT);
    pinMode(p2Leds[i], OUTPUT);
  }

  pinMode(startButton, INPUT_PULLUP);
  allOff();

  Serial.println("Start: 1x=Level1, 2x=Level2, 3x=Level3");
}

void loop() {
  if (!gameRunning) {
    if (digitalRead(startButton) == LOW) {
      waitRelease(startButton);

      if (pressCount == 0) {
        pressCount = 1;
        firstPressTime = millis();
      } else {
        if (millis() - firstPressTime <= pressWindowMs) {
          pressCount++;
          if (pressCount > 3) pressCount = 3;
        } else {
          pressCount = 1;
          firstPressTime = millis();
        }
      }
    }

    if (pressCount > 0 && (millis() - firstPressTime > pressWindowMs)) {
      int chosen = pressCount;
      pressCount = 0;

      if (chosen == 1) startLevel1();
      else if (chosen == 2) startLevel2or3(2);
      else startLevel2or3(3);
    }

    return;
  }

  if (currentLevel == 1) {
    int p1Any = pressedIndex3(p1Buttons[0], p1Buttons[1], p1Buttons[2]);
    int p2Any = pressedIndex3(p2Buttons[0], p2Buttons[1], p2Buttons[2]);

    if (p1Any != -1 && p1Finish == 0) {
      if (p1Any == p1Target) {
        p1Finish = millis();
        waitRelease(p1Buttons[p1Any]);
      } else {
        p1Finish = millis();
        if (p2Finish == 0) p2Finish = millis();
        endRound(2);
        return;
      }
    }

    if (p2Any != -1 && p2Finish == 0) {
      if (p2Any == p2Target) {
        p2Finish = millis();
        waitRelease(p2Buttons[p2Any]);
      } else {
        p2Finish = millis();
        if (p1Finish == 0) p1Finish = millis();
        endRound(1);
        return;
      }
    }

    if (p1Finish > 0 && p2Finish > 0) {
      unsigned long p1t = p1Finish - roundStart;
      unsigned long p2t = p2Finish - roundStart;
      if (p1t == p2t) endRound(0);
      else if (p1t < p2t) endRound(1);
      else endRound(2);
      return;
    }

    if (p1Finish > 0 && p2Finish == 0) { endRound(1); return; }
    if (p2Finish > 0 && p1Finish == 0) { endRound(2); return; }

  } else {
    int p1Press = pressedIndex3(p1Buttons[0], p1Buttons[1], p1Buttons[2]);
    if (p1Press != -1 && p1Finish == 0) {
      if (p1Press == seqArr[p1Idx]) {
        p1Idx++;
        digitalWrite(p1Leds[p1Press], HIGH);
        delay(70);
        digitalWrite(p1Leds[p1Press], LOW);
        waitRelease(p1Buttons[p1Press]);
        if (p1Idx >= activeSeqLen) p1Finish = millis();
      } else {
        p1Finish = millis();
        if (p2Finish == 0) p2Finish = millis();
        endRound(2);
        return;
      }
    }

    int p2Press = pressedIndex3(p2Buttons[0], p2Buttons[1], p2Buttons[2]);
    if (p2Press != -1 && p2Finish == 0) {
      if (p2Press == seqArr[p2Idx]) {
        p2Idx++;
        digitalWrite(p2Leds[p2Press], HIGH);
        delay(70);
        digitalWrite(p2Leds[p2Press], LOW);
        waitRelease(p2Buttons[p2Press]);
        if (p2Idx >= activeSeqLen) p2Finish = millis();
      } else {
        p2Finish = millis();
        if (p1Finish == 0) p1Finish = millis();
        endRound(1);
        return;
      }
    }

    if (p1Finish > 0 && p2Finish > 0) {
      unsigned long p1t = p1Finish - roundStart;
      unsigned long p2t = p2Finish - roundStart;
      if (p1t == p2t) endRound(0);
      else if (p1t < p2t) endRound(1);
      else endRound(2);
      return;
    }

    if (p1Finish > 0 && p2Finish == 0) { endRound(1); return; }
    if (p2Finish > 0 && p1Finish == 0) { endRound(2); return; }
  }
}

