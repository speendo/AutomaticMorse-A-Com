#include "OutputInterface.hpp"
#include <Arduino.h>

void OutputInterface::setup() {
  pinMode(pin, OUTPUT);
  state = WAITING;
  blockActions = false;
}

void OutputInterface::loop() {
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

void OutputInterface::setGrant() {
  state = APPROACHING; // because of the "humanizers" - a human would have to approach the intercom before opening
  blockActions = true;
  actionRandomMs = random(rndApproachMs);
  setActionStartMs();
}

void OutputInterface::setDeny() {
  state = DENYING;
  blockActions = true;
  setActionStartMs();
}

bool OutputInterface::actionsBlocked() {
  return blockActions;
}

void OutputInterface::wait() {
  blockActions = false;
  defaultPinAction();
}

void OutputInterface::approach() {
  defaultPinAction();
  if (millis() - actionStartMs > minApproachMs + actionRandomMs) {
    state = GRANTING;
    actionRandomMs = random(rndGrantMS);
    setActionStartMs();
  }
}

void OutputInterface::grant() {
  if (millis() - actionStartMs > grantMs) {
    state = WAITING;
    defaultPinAction();
  } else {
    grantingPinAction();
  }
}

void OutputInterface::deny() {
  defaultPinAction();

  if (millis() - actionStartMs > denyMs) {
    state = WAITING;
  }
}

void OutputInterface::setActionStartMs() {
  actionStartMs = millis();
}

void OutputInterface::defaultPinAction() { // should be called in any state, just to make sure nothing bad happens
  digitalWrite(pin, LOW);
}

void OutputInterface::grantingPinAction() {
  digitalWrite(pin, HIGH);
}
