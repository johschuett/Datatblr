#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <unordered_map>

using namespace std;

// Define function map
typedef void (*ScriptFunction)(void);
typedef unordered_map<string, ScriptFunction> func_map;

// Create function map for user commands
func_map commands;

#include "headers/formatting.hpp"
#include "headers/globals.hpp"
#include "headers/files.hpp"
#include "headers/boot.hpp"
#include "headers/commands.hpp"

// Class for storing valid user input
class InputData
{
  public:
    string data_file;
    string meta_file;
    int missing_option;
};

// If input == data file
void initiate(string input)
{
  bool abort;
  int num_input;
  string missing_description;
  string* ptr_data;
  InputData currentInput;

  // File either couldn't be found or isn't a csv file (or both)
  // valid_csv() -> headers/files.hpp
  if (!valid_csv(input))
  {
    cout << "#! Your data file either isn't a csv file or doesn't" << endl
      << "#! exist at all (or possibly both)." << endl;
  }
  // File seems fine
  else
  {
    ptr_data = &input;
    currentInput.data_file = *ptr_data;

    cout << "#! Please put in the path of your " << bold_on << "meta" << bold_off << " file" << endl
      << "#! (or :q to abort):" << endl
      << "#~ ";
    cin >> input;

    while (!valid_csv(input))
    {
      if (input == ":q")
      {
        abort = true;
        break;
      }
      cout << "#! Your meta file either isn't a csv file or doesn't" << endl
        << "#! exist at all (or possibly both)." << endl
        << "#! Please put in the path of your " << bold_on << "meta" << bold_off << " file" << endl
        << "#! (or :q to abort):" << endl
        << "#~ ";
      cin >> input;
    }

    if (!abort) {
      ptr_data = &input;
      currentInput.meta_file = *ptr_data;

      cout << "#! Please specify whether missing values" << endl
        << "#! should be summarized (1) or ignored (2):" << endl
        << "#~ ";
      cin >> num_input;

      while (num_input != 1 && num_input != 2)
      {
        if (cin.fail())
        {
          cin.clear();
          cin.ignore();
        }

        cout << "#! Please type 1 or 2!" << endl
          << "#! Please specify whether missing values" << endl
          << "#! should be summarized (1) or ignored (2):" << endl
          << "#~ ";
        cin >> num_input;
      }

      switch (num_input)
      {
        case 1:
          missing_description = "Summarize missing values (1)";
          break;
        case 2:
          missing_description = "Ignore missing values (2)";
          break;
        default:
          missing_description = "Something went wrong!";
          cin.clear();
          break;
      }

      cout << "#! Please check your inputs:" << endl
        << "#!" << endl
        << sep << endl
        << "#! " << bold_on << "Data" << bold_off << " file: " << currentInput.data_file << endl
        << "#! "<< bold_on << "Meta" << bold_off << " file: " << currentInput.meta_file << endl
        << "#! " << bold_on << "Missings"<< bold_off << " : " << missing_description << endl
        << sep << endl
        << "#!" << endl
        << "#! Do you wish to generate a report" << endl
        << "#! based on these settings? <y/n>:" << endl
        << "#~ ";
        cin >> input;

        transform(input.begin(), input.end(), input.begin(), ::tolower);

        while (input != "y" && input != "n")
        {
          cout << "#! Please type y or n!" << endl
            << "#! Do you wish to generate a report" << endl
            << "#! based on these settings? <y/n>:" << endl
            << "#~ ";
          cin >> input;
        }

        if (input == "y")
        {
          cout << "#! Generating ..." << endl;
        }
        else
        {
          cout << "#! Request has been discarded." << endl;
        }
    }
  }
}

// If input = command: Search for input inside commands map
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
    cout << "#! I couldn't find R on your system." << endl
      << "#! Please install R (v.3.6.0 or newer)!" << endl;
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
    cout << "#! I couldn't find LaTeX on your system." << endl
      << "#! Please install a LaTeX distribution!" << endl;
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
    cout << "#! I couldn't find pandoc on your system." << endl
      << "#! Please install pandoc!" << endl;
    sleep(3);
  }
  else
  {
    cout << "#! You have pandoc installed \U0001F4D1" << endl
      << sep << endl
      << "#!" << endl;
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
