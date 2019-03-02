#ifndef SignalStorage_hpp
#define SignalStorage_hpp

class SignalStorage {
public:
  struct Signals {
    unsigned int arr[];
  };

  SignalStorage();
  void reset();
  bool full();
  void push(unsigned int);
  Signals getSignals();

private:
  Signals signals;
};

#endif
