#ifndef BINF_PARSER_H
#define BINF_PARSER_H

#include <string>
#include <memory>

#include "Matcher.h"
#include "Tokeniser.h"

/**
 * # Grammar
 * matcher ::= <term> | <matcher> <term>
 * term ::= <sequence_term> |
 *   <sequence_term> <mismatch_term> |
 *   <sequence_term> <cardinality_term> |
 *   <sequence_term> <mismatch_term> <cardinality_term>
 * sequence_term ::= '(' <nucleotide_sequence> ')' | '(' <amino_acid_sequence> ')'
 * nucleotide_sequence ::= <nucleotide> | <nucleotide_sequence> <nucleotide>
 * amino_acid_sequence ::= <amino_acid> | <amino_acid_sequence> <amino_acid>
 * nucleotide ::= 'A' | 'C' | 'G' | 'T'
 * amino_acid ::= 'A'| 'C' | 'D' | 'E' | 'F' | 'G' | 'H' | 'I' | 'K' | 'L' | 'M' | 'N' | 'P' | 'Q' | 'R' | 'S' | 'T' |
 *   'V' | 'W' | 'X' | 'Y'
 * mismatch_term ::= '<' <integer> '>'
 * integer ::= <digit> | <integer> <digit>
 * digit ::= '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9'
 * cardinality_term ::= '{' <integer> '}' | '{' <integer> ',' <integer> '}'
 */

namespace binf::seqregx {

class Parser {
public:
  explicit Parser(std::unique_ptr<ITokeniser> tokeniser = std::make_unique<Tokeniser>());

  [[nodiscard]] Matcher parse(const std::string &expression) const;
private:
  Matcher parse_expression(std::list<Token> &tokens) const;

  Term parse_term(std::list<Token> &tokens) const;

  int parse_mismatch_term(std::list<Token> &tokens) const;

  Cardinality parse_cardinality_term(std::list<Token> &tokens) const;

  void expect(const std::string &expected, const Token &observed) const;

  const std::unique_ptr<ITokeniser> tokeniser;
};

}


#endif //BINF_PARSER_H
