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

#include "include/formatting.hpp"
#include "include/globals.hpp"
#include "include/files.hpp"
#include "include/boot.hpp"
#include "include/commands.hpp"

// Struct for storing valid user input
struct InputData
{
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
  InputData currentInput;

  abort = false;

  // File either couldn't be found or isn't a csv file (or both)
  // valid_csv() -> headers/files.hpp
  if (!valid_csv(input))
  {
    cout << "#! Your " << bold_on << "data" << bold_off << " file either isn't a csv file or doesn't" << endl
      << "#! exist at all (or possibly both)." << endl;
  }
  // File seems fine
  else
  {
    currentInput.data_file = input;

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
      cout << "#! Your " << bold_on << "meta" << bold_off << " file either isn't a csv file or doesn't" << endl
        << "#! exist at all (or possibly both)." << endl
        << "#!" << endl
        << "#! Please put in the path of your " << bold_on << "meta" << bold_off << " file" << endl
        << "#! (or :q to abort):" << endl
        << "#~ ";
      cin >> input;
    }

    if (!abort) {
      currentInput.meta_file = input;

      cout << "#! Please specify whether " << bold_on << "missing values" << bold_off << endl
        << "#! should be "<< bold_on << "summarized (1)" << bold_off << " or " << bold_on
        << "ignored (2)" << bold_off << ":" << endl
        << "#~ ";
      cin >> num_input;

      while (num_input != 1 && num_input != 2)
      {
        if (cin.fail())
        {
          cin.clear();
          cin.ignore();
        }

        cout << "#! " << bold_on << "Please type 1 or 2!" << bold_off << endl
          << "#! Please specify whether " << bold_on << "missing values" << bold_off << endl
          << "#! should be "<< bold_on << "summarized (1)" << bold_off << " or " << bold_on
          << "ignored (2)" << bold_off << ":" << endl
          << "#~ ";
        cin >> num_input;
      }

      switch (num_input)
      {
        case 1:
          currentInput.missing_option = 1;
          missing_description = "Summarize missing values (1)";
          break;
        case 2:
          currentInput.missing_option = 2;
          missing_description = "Ignore missing values (2)";
          break;
        default:
          currentInput.missing_option = 0;
          missing_description = "Something went wrong!";
          break;
      }

      cout << "#! Please check your inputs:" << endl
        << "#!" << endl
        << sep << endl
        << "#! " << bold_on << "Data" << bold_off << " file: " << split_filename(currentInput.data_file) << endl
        << "#! "<< bold_on << "Meta" << bold_off << " file: " << split_filename(currentInput.meta_file) << endl
        << "#! " << bold_on << "Missings"<< bold_off << " : " << missing_description << endl
        << sep << endl
        << "#!" << endl
        << "#! Do you wish to " << bold_on << "generate a report" << bold_off << endl
        << "#! based on these inputs? <y/n>:" << endl
        << "#~ ";
        cin >> input;

        transform(input.begin(), input.end(), input.begin(), ::tolower);

        while (input != "y" && input != "n")
        {
          cout << "#! " << bold_on << "Please type y or n!" << bold_off << endl
            << "#! Do you wish to " << bold_on << "generate a report" << bold_off << endl
            << "#! based on these inputs? <y/n>:" << endl
            << "#~ ";
          cin >> input;

          transform(input.begin(), input.end(), input.begin(), ::tolower);
        }

        if (input == "y")
        {
          cout << "#! Generating \U0001F529 ..." << endl;

          // Write a csv file containing the collected information for the R script
          string job_path = current_dir + "/job.csv";

          ofstream job_file (job_path);
          // Couldn't open file
          if(!job_file.is_open())
          {
            cout << "#! " << bold_on << "ERROR:" << bold_off << " File Open" << endl
              << "#!" << endl;
          }
          // Read file
          else
          {
            job_file << "key\tvalue" << endl
              << "data_file" << "\t" << currentInput.data_file << endl
              << "meta_file" << "\t" << currentInput.meta_file << endl
              << "missings" << "\t" << currentInput.missing_option << endl;
            job_file.close();

            // Run R script
            cout << sep << endl
              << "#! R -------------------------------------------------" << endl
              << endl;
            system("Rscript R/main.R");
            cout << endl
              << "#! R END ---------------------------------------------" << endl
              << sep << endl;
          }
        }
        else
        {
          cout << "#! Request has been discarded." << endl;
        }
    }
  }
}

// If input = command: Search for input inside commands map
void call_func(const string& input)
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

  // Checking R packages (dplyr, pkgcond, rio) and install the missing ones

  // Check internet connection
  int connection = system("ping -c 1 r-project.org 2>&1 >/dev/null");
  if (connection != 0)
  {
    // No internet connection, just check for the packages
    // and throw a warning if a package is missing
    system("Rscript -e \"\
    required_packages <- c('dplyr', 'pkgcond', 'rio');\
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
    required_packages <- c('dplyr', 'pkgcond', 'rio');\
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
    cout << "#! You have a LaTeX distribution installed \U0001F4C4" << endl
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
