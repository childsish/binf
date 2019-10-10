#include "binf/seqregx/Parser.h"

#include <cassert>
#include <iostream>
#include <sstream>

namespace binf::seqregx {

Parser::Parser(std::unique_ptr<ITokeniser> tokeniser) :
  tokeniser(std::move(tokeniser))
{
}

void Parser::parse(const std::string &expression) const {
  auto tokens = this->tokeniser->tokenise(expression);
  this->parse_expression(tokens);
}

void Parser::parse_expression(std::list<Token> &tokens) const {
  this->parse_term(tokens);
//  auto term = this->parse_term(tokens);
//  while (tokens.size() > 0) {
//    term = this->parse_term(tokens);
//  }
}

void Parser::parse_term(std::list<Token> &tokens) const {
  std::string pattern;
  int mismatch = 0;
  Cardinality cardinality{1, 1};

  this->expect("open_bracket", tokens.front());
  tokens.pop_front();
  this->expect("sequence", tokens.front());
  pattern = tokens.front().second;
  tokens.pop_front();
  this->expect("close_bracket", tokens.front());
  tokens.pop_front();

  if (tokens.front().first == "open_triangular_bracket")
    mismatch = this->parse_mismatch_term(tokens);
  if (tokens.front().first == "open_brace")
    cardinality = this->parse_cardinality_term(tokens);

  //return Term(pattern, mismatch, cardinality);
}

int Parser::parse_mismatch_term(std::list<Token> &tokens) const {
  this->expect("open_triangular_bracket", tokens.front());
  tokens.pop_front();
  this->expect("number", tokens.front());
  int mismatch = std::stoi(tokens.front().second);
  tokens.pop_front();
  this->expect("close_triangular_bracket", tokens.front());
  tokens.pop_front();
  return mismatch;
}

Cardinality Parser::parse_cardinality_term(std::list<Token> &tokens) const {
  this->expect("open_brace", tokens.front());
  tokens.pop_front();
  this->expect("number", tokens.front());
  int fr = std::stoi(tokens.front().second);
  int to = std::stoi(tokens.front().second);
  tokens.pop_front();
  if (tokens.front().first == "comma") {
    tokens.pop_front();
    this->expect("number", tokens.front());
    to = std::stoi(tokens.front().second);
    tokens.pop_front();
  }
  this->expect("close_brace", tokens.front());
  tokens.pop_front();

  return Cardinality{fr, to};
}

void Parser::expect(const std::string &expected, const Token &observed) const {
  if (observed.first != expected) {
    std::stringstream message;
    message << "Expected " << expected << ". Got " << observed.first << ":" << observed.second;
    throw std::runtime_error(message.str());
  }
}

}
