#ifndef FASTA_FASTQENTRY_H
#define FASTA_FASTQENTRY_H

#include <string>

namespace fasta {

class FastaEntry {
public:

  const std::string header;
  const std::string sequence;

  FastaEntry(std::string header, std::string sequence, std::string qualities);

};

}

#endif //FASTA_FASTQENTRY_H
