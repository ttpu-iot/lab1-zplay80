#include "Arduino.h"
#define RED 15
#define GREEN 4
#define BLUE 22
#define YELLOW 23
#define BUTTON 14
#define LIGHT 33

int greenState = 0;
int lastButtonState = HIGH;
int blueState = 0;
int currentExercise = 0;

void setup(void) {
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  Serial.begin(115200);
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
  digitalWrite(YELLOW, LOW);
  Serial.println("Enter exercise number (1-6):");
}

void exercise1() {
  digitalWrite(RED, HIGH);
  Serial.println("RED ON");
  delay(500);
  digitalWrite(RED, LOW);
  Serial.println("RED OFF");
  delay(500);
}

void exercise2() {
  int buttonState = digitalRead(BUTTON);
  if (buttonState == LOW && lastButtonState == HIGH) {
    greenState = !greenState;
    digitalWrite(GREEN, greenState ? HIGH : LOW);
    Serial.print("GREEN=");
    Serial.println(greenState);
    delay(50);
  }
  lastButtonState = buttonState;
}

void exercise3() {
  int val = analogRead(LIGHT);
  Serial.print("raw=");
  Serial.println(val);
  delay(500);
}

void exercise4() {
  int val = analogRead(LIGHT);
  digitalWrite(BLUE, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(YELLOW, LOW);
  digitalWrite(RED, LOW);
  String band;
  if (val <= 1023) {
    band = "BLUE";
    digitalWrite(BLUE, HIGH);
  } else if (val <= 2047) {
    band = "GREEN";
    digitalWrite(GREEN, HIGH);
  } else if (val <= 3071) {
    band = "YELLOW";
    digitalWrite(YELLOW, HIGH);
  } else {
    band = "RED";
    digitalWrite(RED, HIGH);
  }
  Serial.print("band=");
  Serial.println(band);
  delay(100);
}

void exercise5() {
  int buttonState = digitalRead(BUTTON);
  if (buttonState == LOW && lastButtonState == HIGH) {
    int val = analogRead(LIGHT);
    Serial.print("snapshot=");
    Serial.println(val);
    digitalWrite(YELLOW, HIGH);
    delay(100);
    digitalWrite(YELLOW, LOW);
    delay(50);
  }
  lastButtonState = buttonState;
}

void exercise6() {
  if (Serial.available() > 0) {
    char c = Serial.read();
    if (c == 'B') {
      digitalWrite(BLUE, HIGH);
      blueState = 1;
      Serial.println("BLUE=1");
    } else if (c == 'b') {
      digitalWrite(BLUE, LOW);
      blueState = 0;
      Serial.println("BLUE=0");
    }
  }
}

void loop(void) {
  if (Serial.available() > 0) {
    char input = Serial.read();
    if (input >= '1' && input <= '6') {
      currentExercise = input - '0';
      Serial.print("Running Exercise ");
      Serial.println(currentExercise);
      digitalWrite(RED, LOW);
      digitalWrite(GREEN, LOW);
      digitalWrite(BLUE, LOW);
      digitalWrite(YELLOW, LOW);
      greenState = 0;
      blueState = 0;
      lastButtonState = HIGH;
    }
  }

  switch (currentExercise) {
    case 1:
      exercise1();
      break;
    case 2:
      exercise2();
      break;
    case 3:
      exercise3();
      break;
    case 4:
      exercise4();
      break;
    case 5:
      exercise5();
      break;
    case 6:
      exercise6();
      break;
    default:
      break;
  }
}
