#ifndef BINF_MATCHER_H
#define BINF_MATCHER_H

#include <string>
#include <tuple>
#include <vector>


namespace binf::seqregx {

using Cardinality = std::pair<int, int>;
using Term = std::tuple<std::string, int, Cardinality>;

class Matcher {
public:
  explicit Matcher(std::vector<Term> terms);


private:
  std::vector<Term> terms;
};

}


#endif //BINF_MATCHER_H
