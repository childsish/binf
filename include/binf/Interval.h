#ifndef BINF_INTERVAL_H
#define BINF_INTERVAL_H

namespace binf {

class Interval {
public:
  Interval(int start, int stop);

private:
  int start;
  int stop;
};

}

#endif //BINF_INTERVAL_H
