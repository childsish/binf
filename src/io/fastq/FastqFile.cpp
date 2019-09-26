#include <binf/io/fastq/FastqFile.h>

namespace binf::fastq {

FastqFile::FastqFile(std::string filename) :
  filename(std::move(filename))
{
}

ConstFastqIterator FastqFile::cbegin() const {
  return ConstFastqIterator(filename);
}

ConstFastqIterator FastqFile::cend() const {
  return ConstFastqIterator();
}

FastqIterator FastqFile::begin() const {
  return FastqIterator(filename);
}

FastqIterator FastqFile::end() const {
  return FastqIterator();
}

}
