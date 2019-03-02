#ifndef InputSignal_hpp
#define InputSignal_hpp

class InputSignal {
public:
  InputSignal(unsigned int waitMs, unsigned int minEventMs, unsigned int maxSigMs);
  void setup();
  void loop();
  void reset();
  bool getError();

protected:
  const unsigned int waitMs;
  const unsigned int minEventMs;
  const unsigned int maxSigMs;

  bool getSmoothSignal();
  virtual bool getSignal();
};
#endif
