#ifndef BINF_TOKENISER_H
#define BINF_TOKENISER_H

#include <unordered_map>

#include "ITokeniser.h"


using Token = std::pair<std::string, std::string>;

namespace binf::seqregx {

class Tokeniser :public ITokeniser {
public:
  static const std::unordered_map<std::string, std::string> DEFAULT_TYPES;

  explicit Tokeniser(const std::unordered_map<std::string, std::string> &types = DEFAULT_TYPES);

  std::list<Token> tokenise(const std::string &string) const override;
private:
  std::unordered_map<char, std::string> type_map;
};

}

#endif //BINF_TOKENISER_H
