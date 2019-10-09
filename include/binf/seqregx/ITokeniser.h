#ifndef BINF_ITOKENISER_H
#define BINF_ITOKENISER_H

namespace binf::seqregx {

class ITokeniser {
public:
  virtual std::vector<std::pair<std::string, std::string>> tokenise(const std::string &string) const = 0;
};

}


#endif //BINF_ITOKENISER_H
