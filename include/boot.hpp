void boot_info()
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
    << "#! Issue :a to see the authors of this program" << endl
    << "#!" << endl
    << "#!" << " Your R working directory is currently set to" << endl
    << "#!" << endl
    << "#! " << bold_on << current_dir << bold_off << endl
    << "#!" << endl
    << "#! Issue " << bold_on << ":w" << bold_off << " to learn how to change it." << endl
    << "#!" << endl
    << "#! Issue " << bold_on << ":e" << bold_off << " for examples on how to use the program." << endl
    << "#! Issue " << bold_on << ":q" << bold_off << " to quit the program." << endl
    << "#!" << endl
    << "#! Please put in the path of your " << bold_on << "data" << bold_off << " file" << endl
    << "#!" << bold_on << " or a command" << bold_off << " (starting with a colon):" << endl;
}
