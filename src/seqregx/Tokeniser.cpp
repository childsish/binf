#include <binf/seqregx/Tokeniser.h>

namespace binf::seqregx {

const std::unordered_map<std::string, std::string> Tokeniser::DEFAULT_TYPES{
  {"number", "0123456789"},
  {"sequence", "ACTGN"},
  {"group_bracket", "()"},
  {"mismatch_bracket", "<>"},
  {"cardinality_bracket", "{}"},
  {"cardinality", "+?*"},
  {"wildcard", "."},
  {"comma", ","}
};

Tokeniser::Tokeniser(const std::unordered_map<std::string, std::string> &types) {
  for (const auto &item : types)
    for (auto character : item.second)
      type_map[character] = item.first;
}

std::list<std::pair<std::string, std::string>> Tokeniser::tokenise(const std::string &string) const {
  std::list<std::pair<std::string, std::string>> tokens;
  int fr = 0;
  while (fr < string.length()) {
    auto type = type_map.at(string[fr]);
    auto to = fr;
    while (to < string.length() && type == type_map.at(string[to]))
      to += 1;
    tokens.emplace_back(std::make_pair<std::string, std::string>(std::move(type), string.substr(fr, to - fr)));
    fr = to;
  }
  return tokens;
}

}
