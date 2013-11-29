#include "ri/RiNoise.h"

namespace rt {

  class Initializer {
    Initializer()
    {
      RiInitNoise();
    }
    static Initializer i;
  };

  Initializer Initializer::i;
}
