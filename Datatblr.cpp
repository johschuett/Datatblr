#include <iostream>
#include <fstream>
#include <unistd.h>

using namespace std;

// cout formatting
ostream& bold_on(std::ostream& os)
{
  return os << "\e[1m";
}

ostream& bold_off(std::ostream& os)
{
  return os << "\e[0m";
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

void boot_info(string version)
{
  // Get working directory
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
  cout << "#!" << bold_on << " Please put in the path of your data file" << bold_off << endl;
  cout << "#!" << bold_on << " or a command (starting with a colon):" << bold_off << endl;
}

// Command :e
void examples()
{
  cout << "#! Examples:" << endl;
  cout << "#! ~/Desktop/data.csv" << endl;
  cout << "#! test1.csv" << endl;
  cout << "#! data/my_data.csv" << endl;
}

// Input = data file
void initiate(string input)
{

}

// Command :q
void quit(bool& quit_flag)
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

    if (input.substr(0, 1) != ":")
      initiate(input);
    else if (input == ":a")
      authors();
    else if (input == ":e")
      examples();
    else if (input == ":s")
      s_o_d();
    else if (input == ":q")
      quit(quit_flag);
    else if (input == ":t")
      table();
    else
      cout << "#! Oops, I don't know this command..." << endl;
  }

  return 0;
}
