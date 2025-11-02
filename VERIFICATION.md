# Solution Code Verification Report

**Date:** 2025-11-02  
**Repository:** ttpu-iot/lab1-zplay80  
**File Checked:** `src/esp32_lab1.ino`

## Summary
All 6 exercises have been verified against the requirements in README.md. The solution code is **CORRECT** and fully complies with all specifications.

---

## Detailed Verification

### Configuration Verification
✅ **Pin Definitions** (Lines 2-7)
- RED: D15 ✓
- GREEN: D4 ✓
- BLUE: D22 ✓
- YELLOW: D23 ✓
- BUTTON: D14 ✓
- LIGHT (sensor): D33 ✓

---

### Exercise 1: Blink RED LED
**Requirements:**
- Turn RED (D15) ON for 500 ms, then OFF for 500 ms in a loop
- Serial: Print `RED ON` / `RED OFF` whenever it changes

**Implementation (Lines 28-35):**
```cpp
void exercise1() {
  digitalWrite(RED, HIGH);
  Serial.println("RED ON");
  delay(500);
  digitalWrite(RED, LOW);
  Serial.println("RED OFF");
  delay(500);
}
```

**Status:** ✅ **CORRECT**
- RED LED turns ON for 500ms (line 29-31)
- RED LED turns OFF for 500ms (line 32-34)
- Serial prints "RED ON" and "RED OFF" correctly

---

### Exercise 2: Button toggles GREEN
**Requirements:**
- Press BUTTON (D14) to toggle GREEN (D4)
- Serial: Print `GREEN=1` or `GREEN=0` only when the state changes

**Implementation (Lines 37-47):**
```cpp
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
```

**Status:** ✅ **CORRECT**
- Button press detection with debouncing (lines 38-39)
- Toggle logic implemented correctly (line 40)
- LED state updated (line 41)
- Serial output format matches requirement (lines 42-43)
- Only prints when state changes

---

### Exercise 3: Read light sensor
**Requirements:**
- Every 500 ms, read LIGHT (D33) using `analogRead()`
- Serial: Print the raw value, e.g. `raw=1835`

**Implementation (Lines 49-54):**
```cpp
void exercise3() {
  int val = analogRead(LIGHT);
  Serial.print("raw=");
  Serial.println(val);
  delay(500);
}
```

**Status:** ✅ **CORRECT**
- Reads light sensor using `analogRead()` (line 50)
- Prints in correct format "raw=xxxx" (lines 51-52)
- Executes every 500ms (line 53)

---

### Exercise 4: Light sensor → LED band
**Requirements:**
- Read LIGHT (D33) and turn ON exactly one LED based on value (0–4095):
  - 0–1023 → BLUE (D22)
  - 1024–2047 → GREEN (D4)
  - 2048–3071 → YELLOW (D23)
  - 3072–4095 → RED (D15)
- Serial: Print `band=BLUE/GREEN/YELLOW/RED`

**Implementation (Lines 56-79):**
```cpp
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
```

**Status:** ✅ **CORRECT**
- Reads light sensor (line 57)
- Turns OFF all LEDs first (lines 58-61)
- Correctly maps ranges to LEDs:
  - 0-1023 → BLUE (lines 63-65)
  - 1024-2047 → GREEN (lines 66-68)
  - 2048-3071 → YELLOW (lines 69-71)
  - 3072-4095 → RED (lines 72-75)
- Serial output format matches requirement (lines 76-77)
- Only ONE LED is ON at a time

---

### Exercise 5: Snapshot on button
**Requirements:**
- Do nothing until BUTTON (D14) is pressed
- On press, read LIGHT (D33) once and print `snapshot=xxxx`
- Flash YELLOW (D23) for 100 ms to acknowledge

**Implementation (Lines 81-93):**
```cpp
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
```

**Status:** ✅ **CORRECT**
- Waits for button press (lines 82-83)
- Reads light sensor once on button press (line 84)
- Prints in correct format "snapshot=xxxx" (lines 85-86)
- Flashes YELLOW LED for 100ms (lines 87-89)
- Button debouncing included (line 90)

---

### Exercise 6: Minimal serial control
**Requirements:**
- If serial receives a character:
  - `'B'` → turn BLUE (D22) ON
  - `'b'` → turn BLUE (D22) OFF
- Serial: Print `BLUE=1` or `BLUE=0` after each command

**Implementation (Lines 95-108):**
```cpp
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
```

**Status:** ✅ **CORRECT**
- Checks for serial input (line 96)
- Reads character (line 97)
- 'B' command turns BLUE ON (lines 98-101)
- 'b' command turns BLUE OFF (lines 102-105)
- Serial output format matches requirement (lines 101, 105)

---

## Additional Features

The solution includes a well-designed exercise selector system (lines 110-149):
- Users can switch between exercises by sending '1'-'6' via serial
- Properly resets LED states when switching exercises
- Clear feedback messages

---

## Conclusion

**Overall Status:** ✅ **ALL EXERCISES PASS**

The solution code in `src/esp32_lab1.ino` correctly implements all 6 exercises according to the specifications in README.md. There are no issues, no commented-out conflicting code, and the implementation follows Arduino best practices.

### Summary:
- ✅ Exercise 1: Blink RED LED - **CORRECT**
- ✅ Exercise 2: Button toggles GREEN - **CORRECT**
- ✅ Exercise 3: Read light sensor - **CORRECT**
- ✅ Exercise 4: Light sensor → LED band - **CORRECT**
- ✅ Exercise 5: Snapshot on button - **CORRECT**
- ✅ Exercise 6: Minimal serial control - **CORRECT**

**No changes required.**
