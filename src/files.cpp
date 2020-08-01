#include <sys/stat.h>
#include "utils.h"

// File exists function
inline bool file_exists(const string& name)
{
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0);
}

// File extension
bool file_extension(const string& file, const string& extension)
{
  return file.substr(file.find_last_of(".") + 1) == extension;
}

// Combination of the two functions above
bool valid_csv(const string& file)
{
  return (file_exists(file) && file_extension(file, "csv"));
}

string split_filename(const string& path)
{
  size_t slash = path.find_last_of("/");
  return path.substr(slash + 1);
}
