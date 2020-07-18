#include <iostream>
#include <fstream>
#include <unistd.h>

using namespace std;

ostream& bold_on(std::ostream& os)
{
    return os << "\e[1m";
}

ostream& bold_off(std::ostream& os)
{
    return os << "\e[0m";
}

void boot_info(string version) {
  // Get working directory
  string current_dir = "NULL";
  int get_current_dir = system("Rscript -e \"cat(getwd())\" > .current_dir");

  if (get_current_dir != 0) {
    cout << bold_on << "ERROR:" << bold_off << " Couldn't get working directory" << endl;
    cout << "#!" << endl;
  }
  else {
    ifstream dir_file (".current_dir");
    if(!dir_file.is_open()) {
      cout << "#! " << bold_on << "ERROR:" << bold_off << " File Open" << endl;
      cout << "#!" << endl;
    }
    else {
      getline(dir_file, current_dir, '\n');
      dir_file.close();
    }
  }

  cout << "#!" << bold_on << " Hej, this is Datatblr " << version << "!" << bold_off << endl;
  cout << "#! License: GNU General Public License v2.0" << endl;
  cout << "#!" << endl;
  cout << "#!" << " Your R working directory is currently set to" << endl;
  cout << "#!" << endl;
  cout << "#! " << bold_on << current_dir << bold_off << endl;
  cout << "#!" << endl;
  //cout << "#! If you wish to change the current working directory" << endl;
  //cout << "#! you're in, type :q to quit the program and do" << endl;
  //cout << "#! setwd(\"<your-desired-path>\")" << endl;
  //cout << "#!" << endl;
  cout << "#! Issue " << bold_on << ":e" << bold_off << " for examples." << endl;
  cout << "#! Issue " << bold_on << ":q" << bold_off << " to quit the program." << endl;
  cout << "#!" << endl;
  cout << "#!" << bold_on << " Please put in the path of your data file" << bold_off << endl;
  cout << "#!" << bold_on << " or a command (starting with a colon):" << bold_off << endl;
}

void examples()
{
    cout << "#! Examples:" << endl;
    cout << "#! ~/Desktop/data.csv" << endl;
    cout << "#! test1.csv" << endl;
    cout << "#! data/my_data.csv" << endl;
}

void initiate(string input)
{

}

void quit(bool& quit_flag)
{
    quit_flag = true;
    cout << "#! take care!" << endl;
    sleep(1);
}

void s_o_d()
{
  cout << "#! watch?v=XtAhISkoJZc" << endl;
}

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

int main()
{
  bool quit_flag = false;
  string input;
  string version = "stable-1.0";

  cout << "#! -------------------------------------------" << endl;
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
    cout << "#! -------------------------------------------" << endl;
    cout << "#!" << endl;
    boot_info(version);
  }

  // Main Loop
  while (!quit_flag) {
    cout << "#~ ";
    cin >> input;

    if (input == ":e")
      examples();
    else if (input == ":s")
      s_o_d();
    else if (input == ":q")
      quit(quit_flag);
    else if (input == ":t")
      table();
    else
      initiate(input);

  }

  return 0;
}
