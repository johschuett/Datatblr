#include <fstream>
#include <unistd.h>
#include "utils.h"

// Create unordered map for user commands
func_map commands;

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
