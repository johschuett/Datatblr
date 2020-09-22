#include <unistd.h>
#include "utils.h"

// Command :a
void authors()
{
  cout << "#! Authors:" << endl
    << sep << endl
    << "#! Datatblr " << version << endl
    << "#! was written by Johannes Schütt" << endl
    << "#! and Claudia Saalbach" << endl
    << "#!" << endl
    << "#! Datatblr is part of the survey.codes project" << endl
    << "#! Visit https://survey.codes/datatblr" << endl
    << "#!" << endl
    << "#! Chair of Empirical Social Research" << endl
    << "#! at the University of Potsdam" << endl
    << "#!" << endl
    << "#! Visit the repository for updates:" << endl
    << "#! https://github.com/johschuett/Datatblr" << endl
    << sep << endl;
}

// Command :c
void print_current_dir()
{
  cout << "#! " << current_dir << endl;
}

// Command :e
void example()
{
  cout << "#! Example:" << endl
    << sep << endl
    << "#! First, enter the path to your data file." << endl
    << "#!" << endl
    << "#! For example:" << endl
    << "#!" << endl
    << "#! data.csv" << endl
    << "#! alldata/thisdata.csv" << endl
    << "#! or" << endl
    << "#! ../my_data.csv" << endl
    << "#!" << endl
    << "#! Second, enter the path to your questionnaire" << endl
    << "#! meta file." << endl
    << "#!" << endl
    << "#! For example:" << endl
    << "#!" << endl
    << "#! meta.csv" << endl
    << "#! questionnaire/thismeta.csv" << endl
    << "#! or" << endl
    << "#! ../mymeta.csv" << endl
    << "#!" << endl
    << "#! Third, choose a missing option by typing 1 or 2:" << endl
    << "#!" << endl
    << "#! 1 (Summarize missing values)" << endl
    << "#! 2 (Ignore missing values)" << endl
    << sep << endl;
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

// Comment :w
void wd_info()
{
  cout << "#! Changing the working directory:" << endl
    << sep << endl
    << "#! You can change the default working directory for R" << endl
    << "#! simply by adding the " << bold_on << "path to the project folder" << bold_off << " to"<< endl
    << "#! your " << bold_on << ".Rprofile" << bold_off << " file." << endl
    << "#!" << endl
    << "#! If there is no such file, you can create one and" << endl
    << "#! add the directory." << endl
    << "#!" << endl
    << "#! Place the following command in your .Rprofile file:" << endl
    << "#! " << bold_on << "setwd(\"/path/to/Datatblr\")" << bold_off << "." << endl
    << sep << endl;
}
