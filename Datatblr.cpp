#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <unordered_map>

using namespace std;

typedef void (*ScriptFunction)(void);
typedef unordered_map<string, ScriptFunction> func_map;

// Globals
bool quit_flag = false;
func_map commands;
string sep = "#! ---------------------------------------------------";
string version = "stable-1.0";

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

void boot_info()
{
  // Get working directory and write it into .current_dir file
  string current_dir = "NULL";
  int get_current_dir = system("Rscript -e \"cat(getwd())\" > .current_dir");

  // Returned !0 -> Error
  if (get_current_dir != 0)
  {
    quit_flag = true;
    cout << "#! " << bold_on << "ERROR:" << bold_off << " Couldn't get working directory." << endl;
    cout << "#!        Check " << bold_on << ".Rprofile!" << bold_off << endl;
    cout << "#!" << endl;
    sleep(1);
  }
  // Returned 0
  else
  {
    ifstream dir_file (".current_dir");
    // Couldn't open file
    if(!dir_file.is_open())
    {
      cout << "#! " << bold_on << "ERROR:" << bold_off << " File Open" << endl;
      cout << "#!" << endl;
    }
    // Read file
    else
    {
      getline(dir_file, current_dir, '\n');
      dir_file.close();
    }
  }

  // Print infotext
  cout << "#!" << bold_on << "         Hej, this is Datatblr " << version << "!" << bold_off << endl;
  cout << "#!" << endl;
  cout << "#! License: GNU General Public License v2.0 only" << endl;
  cout << "#! Issue :a to see the authors of this program" << endl;
  cout << "#!" << endl;
  cout << "#!" << " Your R working directory is currently set to" << endl;
  cout << "#!" << endl;
  cout << "#! " << bold_on << current_dir << bold_off << endl;
  cout << "#!" << endl;
  cout << "#! Issue " << bold_on << ":w" << bold_off << " to learn how to change it." << endl;
  cout << "#!" << endl;
  cout << "#! Issue " << bold_on << ":e" << bold_off << " for examples on how to use the program." << endl;
  cout << "#! Issue " << bold_on << ":q" << bold_off << " to quit the program." << endl;
  cout << "#!" << endl;
  cout << "#! Please put in the path of your " << bold_on << "data" << bold_off << " file" << endl;
  cout << "#!" << bold_on << " or a command" << bold_off << " (starting with a colon):" << endl;
}

// Include the command line functions
#include "header/command_line.h"

// Input = data file
void initiate(string input)
{
  // File couldn't be found
  if (!file_exists(input))
  {
    cout << "#! Oops, I couldn't find your file..." << endl;
  }
  // File is not a CSV file
  else if (!file_extension(input, "csv"))
  {
    cout << "#! Oops, I only eat .csv files... (case sensitive)" << endl;
  }
  // File seems fine
  else
  {
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
    if (iter == commands.end())
    {
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
  commands.emplace(":w", &wd_info);

  string input;

  cout << sep << endl;

  // Checking dependencies
  cout << "#! Checking your R installation..." << endl;
  int r_check = system("R --version > /dev/null");
  if (r_check != 0)
  {
    quit_flag = true;
    cout << "#! I couldn't find R on your system." << endl;
    cout << "#! Please install R (v.3.6.0 or newer)!" << endl;
    sleep(3);
  }
  else
  {
    cout << "#! You have R installed \U0001F4CA" << endl;
  }

  // Checking R packages (dplyr, knitr, pkcond, rio) and install the missing ones

  // Check internet connection
  int connection = system("ping -c 1 r-project.org 2>&1 >/dev/null");
  if (connection != 0)
  {
    // No internet connection, just check for the packages
    // and throw a warning if a package is missing
    system("Rscript -e \"\
    required_packages <- c('dplyr', 'knitr', 'pkgcond', 'rio');\
    missing_packages <- required_packages[!(required_packages %in% installed.packages()[,'Package'])];\
    if (length(missing_packages)) {\
    cat('#! Missing packages; no internet connection.')\
    }\
    else {\
    cat('#! You have all required R packages installed \U0001F5C3\n');\
    }\"");
  }
  else
  {
    // Internet connection, Check for the packages
    // and try to install missing packages
    system("Rscript -e \"\
    required_packages <- c('dplyr', 'knitr', 'pkgcond', 'rio');\
    missing_packages <- required_packages[!(required_packages %in% installed.packages()[,'Package'])];\
    if (length(missing_packages)) {\
    cat('#! Installing missing R package(s)...\n');\
    cat('#! ---------------------------------------------------\n');\
    cat('#! R -------------------------------------------------\n');\
    cat('\n');\
    install.packages(missing_packages, repos = 'http://cran.us.r-project.org');\
    cat('\n');\
    cat('#! R END ---------------------------------------------\n');\
    cat('#! ---------------------------------------------------\n');\
    cat('#! Missing package(s) have been installed \U0001F5C3\n')\
    }\
    else {\
    cat('#! You have all required R packages installed \U0001F5C3\n');\
    }\"");
  }

  cout << "#! Checking your LaTeX installation..." << endl;
  int latex_check = system("latex --version > /dev/null");
  if (latex_check != 0)
  {
    quit_flag = true;
    cout << "#! I couldn't find LaTeX on your system." << endl;
    cout << "#! Please install a LaTeX distribution!" << endl;
    sleep(3);
  }
  else
  {
    cout << "#! You have a LaTeX distribution installed \U0001F4C4" << endl;
  }

  cout << "#! Checking your pandoc installation..." << endl;
  int pandoc_check = system("pandoc --version > /dev/null");
  if (pandoc_check != 0)
  {
    quit_flag = true;
    cout << "#! I couldn't find pandoc on your system." << endl;
    cout << "#! Please install pandoc!" << endl;
    sleep(3);
  }
  else
  {
    cout << "#! You have pandoc installed \U0001F4D1" << endl;
    cout << sep << endl;
    cout << "#!" << endl;
    // All dependencies are installed, so show the boot info
    boot_info();
  }

  // Main Loop
  while (!quit_flag)
  {
    cout << "#~ ";
    cin >> input;

    if (input.substr(0, 1) != ":")
    {
      // Treat input as filename
      initiate(input);
    }
    else
    {
      // Treat input as command
      call_func(input);
    }
  }

  return 0;
}
