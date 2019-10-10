#include "binf/seqregx/Expression.h"

namespace binf::seqregx {

Expression::Expression(std::vector<Term> terms) :
  terms(std::move(terms))
{
}

}
