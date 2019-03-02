#ifndef OutputInterface_hpp
#define OutputInterface_hpp

class OutputInterface {
public:
  OutputInterface(int attachTo, unsigned long grantMs, unsigned long denyMs=0, unsigned long minApproachMs=0, unsigned long rndApproachMs=0, unsigned long rndGrantMS=0);
  void setup();
  void loop();
  void setGrant();
  void setDeny();
  bool actionsBlocked();

private:
  const int pin;

  const unsigned long grantMs;
  const unsigned long rndGrantMS;
  const unsigned long denyMs;
  const unsigned long minApproachMs;
  const unsigned long rndApproachMs;

  void wait();
  void approach();
  void grant();
  void deny();
  void setActionStartMs();
  void defaultPinAction();
  void grantingPinAction();
};

#endif
