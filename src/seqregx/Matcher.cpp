#include "binf/seqregx/Matcher.h"

namespace binf::seqregx {

Matcher::Matcher(std::vector<Term> terms) :
  terms(std::move(terms))
{
}

}
