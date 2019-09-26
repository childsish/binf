#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <tuple>
#include <binf/algorithms/bitap.h>
#include <binf/io/fastq/FastqFile.h>
#include <binf/os/path.h>

using Filter = std::tuple<std::string, int, int>;

bool has_next(std::vector<binf::fastq::FastqIterator> &iterators, const std::vector<binf::fastq::FastqFile> &files) {
  assert(files.size() == iterators.size());
  for (int i = 0; i < files.size(); ++i)
    if (iterators[i] == files[i].end())
      return false;
  return true;
}

int main(int argc, const char** argv) {
  std::vector<Filter> filters;
  std::vector<binf::fastq::FastqFile> files;
  std::vector<binf::fastq::FastqIterator> iterators;
  std::vector<std::ofstream> output_files;
  std::string outdir;

  for (int i = 1; i < argc; ++i) {
    if (std::strcmp(argv[i], "-f") == 0) {
      assert(i + 3 < argc);
      filters.emplace_back(argv[i + 1], strtol(argv[i + 2], NULL, 10), strtol(argv[i + 3], NULL, 10));
      i += 3;
    }
    else if (std::strcmp(argv[i], "-o") == 0) {
      outdir = argv[i + 1];
      i += 1;
    }
    else if (argv[i][0] == '-') {
      std::stringstream message;
      message << "Unrecognised flag: " << argv[i];
      std::cout << message.str() << std::endl;
      return 1;
    }
    else {
      files.emplace_back(argv[i]);
    }
  }

  if (outdir.empty())
    throw std::runtime_error("No output directory provided.");

  std::transform(files.begin(), files.end(), std::back_inserter(iterators),
    [](const binf::fastq::FastqFile &file){ return file.begin(); } );

  std::transform(files.begin(), files.end(), std::back_inserter(output_files),
    [outdir](const binf::fastq::FastqFile &file){
    return std::ofstream(outdir + "/" + binf::os::basename(file.filename));
  } );

  while (has_next(iterators, files)) {
    auto keep = std::all_of(filters.begin(), filters.end(),
      [&iterators](const Filter &filter){
      return binf::algorithms::fuzzy_bitap(iterators[std::get<2>(filter)]->sequence.c_str(), std::get<0>(filter).c_str(), std::get<1>(filter)) != -1;
    });
    if (keep)
      for (int i = 0; i < files.size(); ++i)
        output_files[i] << *iterators[i];
    for (auto &iterator : iterators)
      ++iterator;
  }
}
