#include "binf/seqregx/Parser.h"

#include <algorithm>
#include <sstream>

namespace binf::seqregx {

Parser::Parser(std::unique_ptr<ITokeniser> tokeniser) :
  tokeniser(std::move(tokeniser))
{
}

Matcher Parser::parse(const std::string &expression) const {
  auto tokens = this->tokeniser->tokenise(expression);
  return this->parse_expression(tokens);
}

Matcher Parser::parse_expression(std::list<Token> &tokens) const {
  std::vector<Term> terms;
  while (!tokens.empty())
    terms.emplace_back(this->parse_term(tokens));
  return Matcher(std::move(terms));
}

Term Parser::parse_term(std::list<Token> &tokens) const {
  std::string pattern;
  int mismatch = 0;
  Cardinality cardinality{1, 1};

  this->expect({"open_bracket", "wildcard"}, tokens.front());
  if (tokens.front().first == "open_bracket") {
    this->expect({"open_bracket"}, tokens.front());
    tokens.pop_front();
    this->expect({"sequence", "wildcard"}, tokens.front());
    pattern = tokens.front().second;
    tokens.pop_front();
    this->expect({"close_bracket"}, tokens.front());
    tokens.pop_front();
  }
  else if (tokens.front().first == "wildcard") {
    pattern = tokens.front().second;
    tokens.pop_front();
  }

  if (!tokens.empty() && tokens.front().first == "open_triangular_bracket")
    mismatch = this->parse_mismatch_term(tokens);
  if (!tokens.empty() && (tokens.front().first == "cardinality" || tokens.front().first == "open_brace"))
    cardinality = this->parse_cardinality_term(tokens);

  return Term(pattern, mismatch, cardinality);
}

int Parser::parse_mismatch_term(std::list<Token> &tokens) const {
  this->expect({"open_triangular_bracket"}, tokens.front());
  tokens.pop_front();
  this->expect({"number"}, tokens.front());
  int mismatch = std::stoi(tokens.front().second);
  tokens.pop_front();
  this->expect({"close_triangular_bracket"}, tokens.front());
  tokens.pop_front();
  return mismatch;
}

Cardinality Parser::parse_cardinality_term(std::list<Token> &tokens) const {
  int fr = 1;
  int to = 1;
  this->expect({"open_brace", "cardinality"}, tokens.front());
  if (tokens.front().first == "cardinality") {
    if (tokens.front().second == "?") {
      fr = 0;
      to = 1;
    }
    else if (tokens.front().second == "*") {
      fr = 0;
      to = -1;
    }
    else if (tokens.front().second == "+") {
      fr = 1;
      to = -1;
    }
    tokens.pop_front();
  }
  else {
    tokens.pop_front();
    this->expect({"number"}, tokens.front());
    fr = std::stoi(tokens.front().second);
    to = std::stoi(tokens.front().second);
    tokens.pop_front();
    if (tokens.front().first == "comma") {
      tokens.pop_front();
      this->expect({"number"}, tokens.front());
      to = std::stoi(tokens.front().second);
      tokens.pop_front();
    }
    this->expect({"close_brace"}, tokens.front());
    tokens.pop_front();
  }

  return Cardinality{fr, to};
}

void Parser::expect(const std::vector<std::string> &expected, const Token &observed) const {
  if (std::find(expected.begin(), expected.end(), observed.first) == expected.end()) {
    std::stringstream message;
    message << "Expected " << expected.front();
    for (int i = 1; i < expected.size() - 1; ++i)
      message << ", " << expected.at(i);
    if (expected.size() > 1)
      message << " or " << expected.back();
    message << ". Got " << observed.first << ":" << observed.second;
    throw std::runtime_error(message.str());
  }
}

}
