#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <unordered_map>

using namespace std;

typedef void (*ScriptFunction)(void);
typedef unordered_map<string, ScriptFunction> func_map;

// Global
bool quit_flag = false;
func_map commands;

// cout formatting
ostream& bold_on(ostream& os)
{
  return os << "\e[1m";
}

ostream& bold_off(ostream& os)
{
  return os << "\e[0m";
}

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

void boot_info(string version)
{
  // Get working directory and write it into .current_dir file
  string current_dir = "NULL";
  int get_current_dir = system("Rscript -e \"cat(getwd())\" > .current_dir");

  // Returned !0
  if (get_current_dir != 0) {
    cout << bold_on << "ERROR:" << bold_off << " Couldn't get working directory" << endl;
    cout << "#!" << endl;
  }
  // Returned 0
  else {
    ifstream dir_file (".current_dir");
    // Couldn't open file
    if(!dir_file.is_open()) {
      cout << "#! " << bold_on << "ERROR:" << bold_off << " File Open" << endl;
      cout << "#!" << endl;
    }
    // Read file
    else {
      getline(dir_file, current_dir, '\n');
      dir_file.close();
    }
  }

  // Print infotext
  cout << "#!" << bold_on << " Hej, this is Datatblr " << version << "!" << bold_off << endl;
  cout << "#! License: GNU General Public License v2.0 only" << endl;
  cout << "#!" << endl;
  cout << "#!" << " Your R working directory is currently set to" << endl;
  cout << "#!" << endl;
  cout << "#! " << bold_on << current_dir << bold_off << endl;
  cout << "#!" << endl;
  cout << "#! Issue " << bold_on << ":e" << bold_off << " for examples." << endl;
  cout << "#! Issue " << bold_on << ":q" << bold_off << " to quit the program." << endl;
  cout << "#!" << endl;
  cout << "#! Please put in the path of your " << bold_on << "data" << bold_off << " file" << endl;
  cout << "#!" << bold_on << " or a command" << bold_off << " (starting with a colon):" << endl;
}

// Command line functions
void authors()
{
  cout << "#! Datatblr was written by Johannes Schütt" << endl;
  cout << "#! Co-author: Claudia Saalbach" << endl;
  cout << "#!" << endl;
  cout << "#! Written for the Chair of Empirical Social Research" << endl;
  cout << "#! at the University of Potsdam" << endl;
}

// Command :e
void examples()
{
  cout << "#! Examples:" << endl;
  cout << "#! /Users/<your-user-name>/Desktop/data.csv" << endl;
  cout << "#! test1.csv" << endl;
  cout << "#! data/my_data.csv" << endl;
  cout << "#! ../mystuff/somefile.csv" << endl;
}

// Command :q
void quit()
{
  quit_flag = true;
  cout << "#! take care!" << endl;
  sleep(1);
}

// Joke area

// Command :s
void s_o_d()
{
  cout << "#! watch?v=XtAhISkoJZc" << endl;
}

// Command :t
void table()
{
  cout << "#!      _____________________" << endl;
  cout << "#!     /                    /|" << endl;
  cout << "#!    /                    / |" << endl;
  cout << "#!   /____________________/ /" << endl;
  cout << "#!  |_____________________|/|" << endl;
  cout << "#!   || ||              || ||" << endl;
  cout << "#!   || ||              || ||" << endl;
  cout << "#!   || ||              || ||" << endl;
  cout << "#!   ||                 ||" << endl;
  cout << "#!   ||                 ||" << endl;
}

// Yeah that was very funny

// Input = data file
void initiate(string input)
{
  // File couldn't be found
  if (!file_exists(input)) {
    cout << "#! Oops, I couldn't find your file..." << endl;
  }
  // File is not a CSV file
  else if (!file_extension(input, "csv")) {
    cout << "#! Oops, I only eat .csv files... (case sensitive)" << endl;
  }
  // File seems fine
  else {
    // Get adress of input
    string* ptr_data = &input;
    // Write value from adress
    string data_file = *ptr_data;

    cout << "#! Please put in the path of your " << bold_on << "meta" << bold_off << " file:" << endl;
    cout << "#~ ";
    cin >> input;
  }
}

// Search for input inside commands map
void call_func(const std::string& input)
{
    auto iter = commands.find(input);
    if (iter == commands.end()) {
        cout << "#! Oops, I don't know this command..." << endl;
    }
    else
      (*iter->second)();
}

int main()
{
  // Fill the commands map with the available commands
  commands.emplace(":a", &authors);
  commands.emplace(":e", &examples);
  commands.emplace(":q", &quit);
  commands.emplace(":s", &s_o_d);
  commands.emplace(":t", &table);

  string input;
  string version = "stable-1.0";

  cout << "#! ---------------------------------------------" << endl;
  cout << "#! Checking your R installation..." << endl;
  int r_check = system("R --version > /dev/null");
  if (r_check != 0) {
    quit_flag = true;
    cout << "#! I couldn't find R on your system." << endl;
    cout << "#! Please install R (v.3.6.0 or newer)!" << endl;
    sleep(3);
  }
  else {
    cout << "#! You have R installed on your system \U0001F389" << endl;
    cout << "#! ---------------------------------------------" << endl;
    cout << "#!" << endl;
    boot_info(version);
  }

  // Main Loop
  while (!quit_flag) {
    cout << "#~ ";
    cin >> input;

    if (input.substr(0, 1) != ":")
      // Treat input as filename
      initiate(input);
    else
      // Treat input as command
      call_func(input);
  }

  return 0;
}
