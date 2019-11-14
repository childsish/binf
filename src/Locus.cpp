#include "binf/Locus.h"

namespace binf {

Locus::Locus(std::string chr, int start, int stop, char strand) :
  chr(std::move(chr)),
  interval(start, stop),
  strand(strand) {}

}
