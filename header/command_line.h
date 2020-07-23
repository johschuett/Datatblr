// Command :a
void authors()
{
  cout << "#! Credits:" << endl
    << sep << endl
    << "#! Datatblr " << version << endl
    << "#! was written by Johannes Schütt" << endl
    << "#! Co-author: Claudia Saalbach" << endl
    << "#!" << endl
    << "#! Datatblr is part of the survey.codes project" << endl
    << "#! Visit https://www.survey.codes" << endl
    << "#!" << endl
    << "#! Chair of Empirical Social Research" << endl
    << "#! at the University of Potsdam" << endl
    << "#!" << endl
    << "#! Visit the repository for updates:" << endl
    << "#! https://www.github.com/johschuett/Datatblr" << endl
    << sep << endl;
}

// Command :e
void examples()
{
  cout << "#! Examples:" << endl
    << sep << endl
    << "#! /Users/<your-user-name>/Desktop/data.csv" << endl
    << "#! test1.csv" << endl
    << "#! data/my_data.csv" << endl
    << "#! ../mystuff/somefile.csv" << endl
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
    << "#! simply by adding the path to your desired directory" << endl
    << "#! to your " << bold_on << ".Rprofile" << bold_off << " inside your root directory." << endl
    << "#! If there is no such file, you can simply create one" << endl
    << "#! and add your desired directory." << endl
    << "#!" << endl
    << "#! Place the following command in .Rprofile:" << endl
    << "#! " << bold_on << "setwd(\"/your/desired/directory\")" << bold_off << "." << endl
    << sep << endl;
}
