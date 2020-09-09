#include <fstream>
#include <unistd.h>
#include "utils.h"

void boot_info(bool& args_given, int& arg_error)
{
  // Get working directory and write it into .current_dir file
  current_dir = "NULL";
  int get_current_dir = system("Rscript -e \"cat(getwd())\" > .current_dir");

  // Returned !0 -> Error
  if (get_current_dir != 0)
  {
    quit_flag = true;
    cout << "#! " << bold_on << "ERROR:" << bold_off << " Couldn't get working directory." << endl
      << "#!        Check " << bold_on << ".Rprofile!" << bold_off << endl
      << "#!" << endl;
    sleep(1);
  }
  // Returned 0
  else
  {
    ifstream dir_file (".current_dir");
    // Couldn't open file
    if(!dir_file.is_open())
    {
      cout << "#! " << bold_on << "ERROR:" << bold_off << " File Open" << endl
        << "#!" << endl;
    }
    // Read file
    else
    {
      getline(dir_file, current_dir, '\n');
      dir_file.close();
    }
  }

  // Print infotext
  cout << "#!" << bold_on << "         Hej, this is Datatblr " << version << "!" << bold_off << endl
    << "#!" << endl
    << "#! Copyright (c) 2020" << endl
    << "#! Johannes Schütt, Claudia Saalbach" << endl
    << "#! GNU General Public License v2.0 only" << endl
    << "#!" << endl
    << "#!" << " Your R working directory is currently set to" << endl
    << "#!" << endl
    << "#! " << bold_on << current_dir << bold_off << endl
    << "#!" << endl;

  // Normal mode
  if (!args_given)
  {
    cout << "#! For help you can use these commands:" << endl
      << "#!" << endl
      << "#! :c\tYour current working directory" << endl
      << "#! :w\tHow to change your working directory"<< endl
      << "#! :e\tUsage example" << endl
      << "#! :q\tQuit the program / abort new job" << endl
      << "#!" << endl;

    switch (arg_error)
    {
      case 0:
        // No error
        break;
      case 1:
        // To many / to few arguments were given
        cout << "#! " << bold_on << "Too many / to few arguments" << bold_off <<" (expected 3)." << endl
          << "#! Booted into normal mode." << endl
          << "#!" << endl;
        break;
      case 2:
        // Missing option is not an integer
        cout << "#! " << bold_on << "Missing option is not a whole number." << bold_off << endl
          << "#! Booted into normal mode." << endl
          << "#!" << endl;
        break;
      case 3:
        // Unknown missing option
        cout << "#! " << bold_on << "Unknown missing option." << bold_off << endl
          << "#! Booted into normal mode." << endl
          << "#!" << endl;
        break;
      default:
        break;
    }

    cout << "#! Please put in the path to your " << bold_on << "data" << bold_off << " file" << endl
      << "#!" << bold_on << " or a command" << bold_off << " (starting with a colon):" << endl;
  }
}
