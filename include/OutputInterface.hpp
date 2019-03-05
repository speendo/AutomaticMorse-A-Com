#ifndef OutputInterface_hpp
#define OutputInterface_hpp

class OutputInterface {
  const int pin;

  const unsigned long grantMs;
  const unsigned long rndGrantMS;
  const unsigned long denyMs;
  const unsigned long minApproachMs;
  const unsigned long rndApproachMs;

  unsigned long actionStartMs;
  unsigned long actionRandomMs;
  bool blockActions;

  enum State {
    WAITING = 0,
    APPROACHING = 1,
    GRANTING = 2,
    DENYING = 3
  } state;

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

public:
  void setup();
  void loop();
  void setGrant();
  void setDeny();
  bool actionsBlocked();

private:
  void wait();
  void approach();
  void grant();
  void deny();
  void setActionStartMs();
  void defaultPinAction();
  void grantingPinAction();
};


#endif
