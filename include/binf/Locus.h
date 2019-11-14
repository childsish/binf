#ifndef BINF_LOCUS_H
#define BINF_LOCUS_H

#include <string>

#include <binf/Interval.h>


namespace binf {

class Locus {
public:
  Locus(std::string chr, int start, int stop, char strand);

private:
  std::string chr;
  Interval interval;
  char strand;
};

}


#endif //BINF_LOCUS_H
