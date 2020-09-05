#include <fstream>
#include <unistd.h>
#include "utils.h"

void boot_info(bool& args_given)
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
    << "#! License: GNU General Public License v2.0 only" << endl
    << "#!" << endl
    << "#!" << " Your R working directory is currently set to" << endl
    << "#!" << endl
    << "#! " << bold_on << current_dir << bold_off << endl
    << "#!" << endl;

  // Normal mode
  if (!args_given)
  {
    cout << "#! " << bold_on << "/extras/COMMANDS" << bold_off << " contains a list of the" << endl
      << "#! available commands." << endl
      << "#!" << endl
      << "#! Issue " << bold_on << ":q" << bold_off << " to quit the program." << endl
      << "#!" << endl
      << "#! Please put in the path of your " << bold_on << "data" << bold_off << " file" << endl
      << "#!" << bold_on << " or a command" << bold_off << " (starting with a colon):" << endl;
  }
}
