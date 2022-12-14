// Dual channel schmitt trigger.
// Author: Luca Cavicchioli
// Year: 2022
// This code is released under public domain
#include <Arduino.h>

#ifndef HIST1
// hysteresis cycle amplitude for channel 1
#define HIST1 2
#endif

#ifndef HIST2
// hysteresis cycle amplitude for channel 2
#define HIST2 2
#endif

int out1 = 0;
int sig1 = 0;
int ref1 = 0;

int out2 = 0;
int sig2 = 0;
int ref2 = 0;

#ifdef DEBUG
int cycle_cnt = 0;
#endif

void setup() {
  // Channel connections:
  // Channel 1:
  //   - Ref in:  A1
  //   - Sig in:  A0
  //   - Trg out: D10
  // analog pins are set to pull up mode in order to open circuit when input is
  // disconnected. Note that this changes the input response.
  pinMode(A1, INPUT_PULLUP);
  pinMode(A0, INPUT_PULLUP);
  pinMode(10, OUTPUT);
  digitalWrite(10, LOW);

  // Channel 2:
  //   - Ref in:  A2
  //   - Sig in:  A3
  //   - Trg out: D12
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  pinMode(12, OUTPUT);
  digitalWrite(12, LOW);

  Serial.begin(9600);
  analogReference(INTERNAL1V1);
}

void loop() {
  ref1 = analogRead(A1);
  ref2 = analogRead(A2);

  sig1 = analogRead(A0);
  sig2 = analogRead(A3);

  int th_high1 = ref1 + HIST1;
  th_high1 = constrain(th_high1, 0, 1023);
  int th_low1 = ref1 - HIST1;
  th_low1 = constrain(th_low1, 0, 1023);

  int th_high2 = ref2 + HIST2;
  th_high2 = constrain(th_high2, 0, 1023);
  int th_low2 = ref2 - HIST2;
  th_low2 = constrain(th_low2, 0, 1023);

  if (sig1 >= th_high1) {
    out1 = LOW;
  } else if (sig1 < th_low1) {
    out1 = HIGH;
  }

  if (sig2 >= th_high2) {
    out2 = LOW;
  } else if (sig2 < th_low2) {
    out2 = HIGH;
  }

  digitalWrite(10, out1);
  digitalWrite(12, out2);

#ifdef DEBUG
  if (cycle_cnt == 100) {
    cycle_cnt = 0;
    Serial.print("Ref 1:  ");
    Serial.print(ref1);
    Serial.print("    Sig 1:  ");
    Serial.print(sig1);
    Serial.print("    Out 1:  ");
    Serial.print(out1 == HIGH ? "H" : "L");
    delay(10);
    Serial.print("\r");
    Serial.print(
        "                                                             ");
    Serial.print("\r");
  }

  ++cycle_cnt;
#endif
}
