#include <Arduino.h>

class OutputInterface {
  const int pin;

  const unsigned long grantMs;
  const unsigned long rndGrantMS;
  const unsigned long denyMs;
  const unsigned long minApproachMs;
  const unsigned long rndApproachMs;

  enum State {
    WAITING = 0,
    APPROACHING = 1,
    GRANTING = 2,
    DENYING = 3
  } state;

  unsigned long actionStartMs;
  unsigned long actionRandomMs;
  bool blockActions;

public:
  OutputInterface(int attachTo, unsigned long grantMs, unsigned long denyMs=0, unsigned long minApproachMs=0, unsigned long rndApproachMs=0, unsigned long rndGrantMS=0) :
  pin(attachTo),
  grantMs(grantMs),
  rndGrantMS(rndGrantMS),
  denyMs(denyMs),
  minApproachMs(minApproachMs),
  rndApproachMs(rndApproachMs)
  {
  };


  void setup() {
    pinMode(pin, OUTPUT);
    state = WAITING;
    blockActions = false;
  }

  void loop() {
    switch (state) {
      case WAITING:
        wait();
        break;
      case APPROACHING:
        approach();
        break;
      case GRANTING:
        grant();
        break;
      case DENYING:
        deny();
        break;
    }
  }

  void setGrant() {
    state = APPROACHING; // because of the "humanizers" - a human would have to approach the intercom before opening
    blockActions = true;
    actionRandomMs = random(rndApproachMs);
    setActionStartMs();
  }

  void setDeny() {
    state = DENYING;
    blockActions = true;
    setActionStartMs();
  }

  bool actionsBlocked() {
    return blockActions;
  }

private:
  void wait() {
    blockActions = false;
    defaultPinAction();
  }

  void approach() {
    defaultPinAction();
    if (millis() - actionStartMs > minApproachMs + actionRandomMs) {
      state = GRANTING;
      actionRandomMs = random(rndGrantMS);
      setActionStartMs();
    }
  }

  void grant() {
    if (millis() - actionStartMs > grantMs) {
      state = WAITING;
      defaultPinAction();
    } else {
      grantingPinAction();
    }
  }

  void deny() {
    defaultPinAction();

    if (millis() - actionStartMs > denyMs) {
      state = WAITING;
    }
  }

  void setActionStartMs() {
    actionStartMs = millis();
  }

  void defaultPinAction() { // should be called in any state, just to make sure nothing bad happens
    digitalWrite(pin, LOW);
  }

  void grantingPinAction() {
    digitalWrite(pin, HIGH);
  }
};
