#include <binf/os/path.h>

#include <iostream>

namespace binf::os {

std::string basename(const std::string &path) {
#ifdef _WIN32
  char separator = '\\';
#else
  char separator = '/';
#endif

  size_t i = path.rfind(separator);
  if (i != std::string::npos)
    return path.substr(i + 1, path.length() - 1);
  return {};
}

}
