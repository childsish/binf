#ifndef FASTA_FASTAITERATOR_H
#define FASTA_FASTAITERATOR_H

#include <cstring>
#include <fstream>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <string>

#include "FastaEntry.h"


namespace fasta {

template <typename ValueType>
class FastaIteratorTemplate : public std::iterator<std::input_iterator_tag, ValueType> {
public:
  FastaIteratorTemplate() : input_stream() {}
  explicit FastaIteratorTemplate(const std::string &filename) :
    input_stream(std::make_unique<std::ifstream>(filename))
  {
    if (input_stream->fail())
      throw std::runtime_error(std::strerror(errno));
    this->operator++();
  }

  FastaEntry & operator*() {
    return *current_entry;
  }

  FastaEntry const & operator*() const {
    return *current_entry;
  }

  std::shared_ptr<FastaEntry> operator->() {
    return current_entry;
  }

  std::shared_ptr<const FastaEntry> operator->() const {
    return current_entry;
  }

  FastaIteratorTemplate & operator++() {
    std::string header, sequence, qualities;

    std::getline(*input_stream, header);
    std::getline(*input_stream, sequence);
    input_stream->ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(*input_stream, qualities);

    current_entry = std::make_shared<FastaEntry>(std::move(header), std::move(sequence), std::move(qualities));

    if (input_stream->eof()) {
      input_stream->close();
      input_stream.reset();
    }

    return *this;
  }

  bool operator==(const FastaIteratorTemplate &that) const {
    return input_stream == that.input_stream;
  }

  bool operator!=(const FastaIteratorTemplate &that) const {
    return input_stream != that.input_stream;
  }

private:
  std::unique_ptr<std::ifstream> input_stream;
  std::shared_ptr<FastaEntry> current_entry;
};

typedef FastaIteratorTemplate<FastaEntry> FastaIterator;
typedef FastaIteratorTemplate<const FastaEntry> ConstFastaIterator;

}

#endif //FASTA_FASTAITERATOR_H