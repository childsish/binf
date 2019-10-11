#ifndef FASTQ_FASTQITERATOR_H
#define FASTQ_FASTQITERATOR_H

#include <cstring>
#include <fstream>
#include <memory>
#include <sstream>
#include <string>
#include <zstr.hpp>

#include "FastqEntry.h"


namespace binf::fastq {

template <typename ValueType>
class FastqIteratorTemplate : public std::iterator<std::input_iterator_tag, ValueType> {
public:
  FastqIteratorTemplate() : input_stream() {}
  explicit FastqIteratorTemplate(const std::string &filename) :
    input_stream(std::make_unique<zstr::ifstream>(filename))
  {
    if (input_stream->fail()) {
      std::stringstream message;
      message << std::strerror(errno) << ": " << filename;
      throw std::runtime_error(message.str());
    }
    this->operator++();
  }

  FastqEntry & operator*() {
    return *current_entry;
  }

  FastqEntry const & operator*() const {
    return *current_entry;
  }

  std::shared_ptr<FastqEntry> operator->() {
    return current_entry;
  }

  std::shared_ptr<const FastqEntry> operator->() const {
    return current_entry;
  }

  FastqIteratorTemplate & operator++() {
    std::string header, sequence, qualities;

    std::getline(*input_stream, header);
    std::getline(*input_stream, sequence);
    input_stream->ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(*input_stream, qualities);

    current_entry = std::make_shared<FastqEntry>(std::move(header), std::move(sequence), std::move(qualities));

    if (input_stream->eof()) {
      input_stream.reset();
    }

    return *this;
  }

  bool operator==(const FastqIteratorTemplate &that) const {
    return input_stream == that.input_stream;
  }

  bool operator!=(const FastqIteratorTemplate &that) const {
    return input_stream != that.input_stream;
  }

private:
  std::unique_ptr<zstr::ifstream> input_stream;
  std::shared_ptr<FastqEntry> current_entry;
};

typedef FastqIteratorTemplate<FastqEntry> FastqIterator;
typedef FastqIteratorTemplate<const FastqEntry> ConstFastqIterator;

}

#endif //FASTQ_FASTQITERATOR_H
