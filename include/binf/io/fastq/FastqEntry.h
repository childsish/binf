#ifndef FASTQ_FASTQENTRY_H
#define FASTQ_FASTQENTRY_H

#include <ostream>
#include <string>

namespace binf::fastq {

class FastqEntry {
public:

  const std::string header;
  const std::string sequence;
  const std::string qualities;

  FastqEntry(std::string header, std::string sequence, std::string qualities);
};

std::ostream &operator<<(std::ostream &out, const FastqEntry &entry);

}

#endif //FASTQ_FASTQENTRY_H
