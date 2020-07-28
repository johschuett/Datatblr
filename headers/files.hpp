// File exists function
inline bool file_exists(const string& name)
{
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0);
}

// File extension
bool file_extension(string file, string extension)
{
  return file.substr(file.find_last_of(".") + 1) == extension;
}

bool valid_csv(string file)
{
  return (file_exists(file) && file_extension(file, "csv"));
}
