#include "FastaEntry.h"

namespace fasta {

FastaEntry::FastaEntry(std::string header, std::string sequence, std::string qualities) :
  header(std::move(header)),
  sequence(std::move(sequence)),
  qualities(std::move(qualities)) {}

}
