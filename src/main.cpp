#include <fstream>
#include <unistd.h>
#include <string>
#include "utils.h"

// Create unordered map for user commands
func_map commands;

int main(int argc, char* argv[])
{
  // Arg mode is off by default
  bool args_given = false;

  string data_arg;
  string meta_arg;
  string missing_arg_string = "-1";

  // Checking for parsed arguments
  if (argc > 1)
  {
    // Too many/to few arguments provided
    if (argc != 4)
    {
      cout << "#! 3 arguments needed!" << endl
        << "#! Starting the program in normal mode..." << endl
        << "#!" << endl;
    }
    // 3 arguments provided
    else
    {
      data_arg = argv[1];
      meta_arg = argv[2];
      missing_arg_string = argv[3];

      // Entering arg mode
      args_given = true;
    }
  }

  // Fill the commands map with the available commands
  commands.emplace(":a", &authors);
  commands.emplace(":c", &print_current_dir);
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

  // Checking R packages (dplyr, rio) and install the missing ones

  // Check internet connection
  int connection = system("ping -c 1 cran.us.r-project.org &>/dev/null");
  if (connection != 0)
  {
    // No internet connection, just check for the packages
    // and throw a warning if a package is missing
    system("Rscript -e \"\
    required_packages <- c('dplyr', 'rio');\
    missing_packages <- required_packages[!(required_packages %in% installed.packages()[,'Package'])];\
    if (length(missing_packages)) {\
    cat('#! Packages are missing,\n');\
    cat('#! but I couldn\\'t establish a connection to CRAN.\n');\
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
    required_packages <- c('dplyr', 'rio');\
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
    boot_info(args_given);

    // Change to working directory
    if (chdir(current_dir.c_str()) != 0)
    {
      quit_flag = true;
      cout << "#! I couldn't change to your working directory!" << endl;
      sleep(3);
    }
  }

  // No args given, go into loop
  if (!args_given)
  {
    // Main Loop
    while (!quit_flag)
    {
      cout << "#~ ";
      cin >> input;

      if (input.substr(0, 1) != ":")
      {
        // Treat input as filename
        string empty_str = "";
        int null_value = 0;

        initiate(input, empty_str, null_value, args_given);
      }
      else
      {
        // Treat input as command
        call_func(input);
      }
    }
  }
  // Args given
  else
  {
    if (!is_integer(missing_arg_string))
    {
      cout << missing_arg_string << " is not an integer." << endl;
    }
    else
    {
      int missing_arg = stoi(missing_arg_string);

      switch (missing_arg)
      {
        case 1:
          initiate(data_arg, meta_arg, missing_arg, args_given);
          break;
        case 2:
          initiate(data_arg, meta_arg, missing_arg, args_given);
          break;
        default:
          cout << "#! Oops, unknown missing option..." << endl;
          break;
      }
    }
  }

  return 0;
}
