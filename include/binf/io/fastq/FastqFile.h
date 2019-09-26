#ifndef FASTQ_FASTQFILE_H
#define FASTQ_FASTQFILE_H

#include <string>

#include "FastqIterator.h"

namespace binf::fastq {

class FastqFile {
public:
  const std::string filename;

  explicit FastqFile(std::string filename);

  [[nodiscard]] ConstFastqIterator cbegin() const;

  [[nodiscard]] ConstFastqIterator cend() const;

  [[nodiscard]] FastqIterator begin() const;

  [[nodiscard]] FastqIterator end() const;
};

}

#endif //FASTQ_FASTQFILE_H
