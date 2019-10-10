#ifndef BINF_EXPRESSION_H
#define BINF_EXPRESSION_H

#include <string>
#include <tuple>
#include <vector>


namespace binf::seqregx {

using Cardinality = std::pair<int, int>;
using Term = std::tuple<std::string, int, Cardinality>;

class Expression {
public:
  explicit Expression(std::vector<Term> terms);


private:
  std::vector<Term> terms;
};

}


#endif //BINF_EXPRESSION_H
