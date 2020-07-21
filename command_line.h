// Command :a
void authors()
{
  cout << "#! Credits:" << endl;
  cout << sep << endl;
  cout << "#! Datatblr " << version << endl;
  cout << "#! was written by Johannes Schütt" << endl;
  cout << "#! Co-author: Claudia Saalbach" << endl;
  cout << "#!" << endl;
  cout << "#! Datatblr is part of the survey.codes project" << endl;
  cout << "#! Visit https://www.survey.codes" << endl;
  cout << "#!" << endl;
  cout << "#! Chair of Empirical Social Research" << endl;
  cout << "#! at the University of Potsdam" << endl;
  cout << "#!" << endl;
  cout << "#! Visit the repository for updates:" << endl;
  cout << "#! https://www.github.com/johschuett/Datatblr" << endl;
  cout << sep << endl;
}

// Command :e
void examples()
{
  cout << "#! Examples:" << endl;
  cout << sep << endl;
  cout << "#! /Users/<your-user-name>/Desktop/data.csv" << endl;
  cout << "#! test1.csv" << endl;
  cout << "#! data/my_data.csv" << endl;
  cout << "#! ../mystuff/somefile.csv" << endl;
  cout << sep << endl;
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
  cout << "#! Changing the working directory:" << endl;
  cout << sep << endl;
  cout << "#! You can change the default working directory for R" << endl;
  cout << "#! simply by adding the path to your desired directory" << endl;
  cout << "#! to your " << bold_on << ".Rprofile" << bold_off << " inside your root directory." << endl;
  cout << "#! If there is no such file, you can simply create one" << endl;
  cout << "#! and add your desired directory." << endl;
  cout << "#!" << endl;
  cout << "#! Place the following command in .Rprofile:" << endl;
  cout << "#! " << bold_on << "setwd(\"/your/desired/directory\")" << bold_off << "." << endl;
  cout << sep << endl;
}
