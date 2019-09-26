#ifndef FASTA_FASTAFILE_H
#define FASTA_FASTAFILE_H

#include <string>

#include "../../src/FastaIterator.h"


namespace fasta {

class FastaFile {
public:
  explicit FastaFile(std::string filename, unsigned int block_size = 1 << 28);

  [[nodiscard]] FastaIterator begin() const;

  [[nodiscard]] FastaIterator end() const;

private:
  const std::string filename;
};

}

#endif //FASTA_FASTAFILE_H
