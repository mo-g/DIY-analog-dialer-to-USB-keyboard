#include "Keyboard.h"

#define counterButton   3
#define openButton      4
byte clickCounter = 0;
bool lastClickStillOpen = true;

void setup()
{
  pinMode(clickSwitch, INPUT_PULLUP);
  pinMode(atRestSwitch, INPUT_PULLUP);
  Keyboard.begin();
}

void loop()
{
  if (digitalRead(atRestSwitch) == LOW) {
    if (digitalRead(clickSwitch) == LOW) {
      if (!lastClickStillOpen) { // Ensure each click is finished before we count the next.
        lastClickStillOpen = true;
        clickCounter++;
        delay(10);
      }
    }
    else { // When click ends, permit the recording of the next click.
      lastClickStillOpen = false;
    }
  }
  else if (clickCounter > 0) {
    if (clickCounter == 10) { // Transpose 10 clicks to character 0.
      clickCounter = 0;
    }
    Keyboard.print(str(clickCounter)); // Send character to USB Host.
    clickCounter = 0; // Blank clickCounter for next number dial.
  }
}
