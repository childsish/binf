#include "fasta/FastaFile.h"

namespace fasta {

FastaFile::FastaFile(std::string filename, unsigned int chunk_size) :
  filename(std::move(filename))
{
}

FastaIterator FastaFile::begin() const {
  return FastaIterator(filename);
}

FastaIterator FastaFile::end() const {
  return FastaIterator();
}

}
