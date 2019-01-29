class SignalStorage {
public:
  SignalStorage();
  void reset();
  bool full();
  void push(unsigned int);
};
