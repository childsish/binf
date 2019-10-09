#ifndef BINF_ITOKENISER_H
#define BINF_ITOKENISER_H

#include <list>


namespace binf::seqregx {

class ITokeniser {
public:
  [[nodiscard]] virtual std::list<std::pair<std::string, std::string>> tokenise(const std::string &string) const = 0;
};

}


#endif //BINF_ITOKENISER_H
