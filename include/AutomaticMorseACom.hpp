#ifndef AutomaticMorseACom_hpp
#define AutomaticMorseACom_hpp

// MorseStates

enum MorseStates {
  EMPTY = -1,
  DIT,
  DAH
};

const MorseStates PASSWORD[] = {DIT, DIT, DIT, DAH, DAH, DAH, DIT, DIT, DIT};

constexpr unsigned int PASSWORD_LENGTH = sizeof(PASSWORD) / sizeof(MorseStates);

struct Signals {
  unsigned int arr[PASSWORD_LENGTH];
};

struct MorsePW {
  MorseStates arr[PASSWORD_LENGTH];
};

#endif
