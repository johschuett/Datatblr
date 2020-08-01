#include "utils.h"

// cout formatting
ostream& bold_on(ostream& os)
{
  return os << "\e[1m";
}

ostream& bold_off(ostream& os)
{
  return os << "\e[0m";
}
