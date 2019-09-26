#include "binf/io/fastq/FastqEntry.h"

namespace binf::fastq {

FastqEntry::FastqEntry(std::string header, std::string sequence, std::string qualities) :
  header(std::move(header)),
  sequence(std::move(sequence)),
  qualities(std::move(qualities)) {}


std::ostream &operator<<(std::ostream &out, const fastq::FastqEntry &entry) {
  out << "@" << entry.header << "\n" << entry.sequence << "\n+\n" << entry.qualities << "\n";
}

}
