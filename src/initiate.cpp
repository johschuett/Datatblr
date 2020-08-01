#include <algorithm>
#include <fstream>
#include "utils.h"

// If input == data file
void initiate(string input)
{
  bool abort;
  int num_input;
  string missing_description;
  InputData currentInput;

  abort = false;

  // File either couldn't be found or isn't a csv file (or both)
  // valid_csv() -> headers/files.hpp
  if (!valid_csv(input))
  {
    cout << "#! Your " << bold_on << "data" << bold_off << " file either isn't a csv file or doesn't" << endl
      << "#! exist at all (or possibly both)." << endl;
  }
  // File seems fine
  else
  {
    currentInput.data_file = input;

    cout << "#! Please put in the path of your " << bold_on << "meta" << bold_off << " file" << endl
      << "#! (or :q to abort):" << endl
      << "#~ ";
    cin >> input;

    while (!valid_csv(input))
    {
      if (input == ":q")
      {
        abort = true;
        break;
      }
      cout << "#! Your " << bold_on << "meta" << bold_off << " file either isn't a csv file or doesn't" << endl
        << "#! exist at all (or possibly both)." << endl
        << "#!" << endl
        << "#! Please put in the path of your " << bold_on << "meta" << bold_off << " file" << endl
        << "#! (or :q to abort):" << endl
        << "#~ ";
      cin >> input;
    }

    if (!abort) {
      currentInput.meta_file = input;

      cout << "#! Please specify whether " << bold_on << "missing values" << bold_off << endl
        << "#! should be "<< bold_on << "summarized (1)" << bold_off << " or " << bold_on
        << "ignored (2)" << bold_off << ":" << endl
        << "#~ ";
      cin >> num_input;

      while (num_input != 1 && num_input != 2)
      {
        if (cin.fail())
        {
          cin.clear();
          cin.ignore();
        }

        cout << "#! " << bold_on << "Please type 1 or 2!" << bold_off << endl
          << "#! Please specify whether " << bold_on << "missing values" << bold_off << endl
          << "#! should be "<< bold_on << "summarized (1)" << bold_off << " or " << bold_on
          << "ignored (2)" << bold_off << ":" << endl
          << "#~ ";
        cin >> num_input;
      }

      switch (num_input)
      {
        case 1:
          currentInput.missing_option = 1;
          missing_description = "Summarize missing values (1)";
          break;
        case 2:
          currentInput.missing_option = 2;
          missing_description = "Ignore missing values (2)";
          break;
        default:
          currentInput.missing_option = 0;
          missing_description = "Something went wrong!";
          break;
      }

      cout << "#! Please check your inputs:" << endl
        << "#!" << endl
        << sep << endl
        << "#! " << bold_on << "Data" << bold_off << " file: " << split_filename(currentInput.data_file) << endl
        << "#! "<< bold_on << "Meta" << bold_off << " file: " << split_filename(currentInput.meta_file) << endl
        << "#! " << bold_on << "Missings"<< bold_off << " : " << missing_description << endl
        << sep << endl
        << "#!" << endl
        << "#! Do you wish to " << bold_on << "generate a report" << bold_off << endl
        << "#! based on these inputs? <y/n>:" << endl
        << "#~ ";
        cin >> input;

        transform(input.begin(), input.end(), input.begin(), ::tolower);

        while (input != "y" && input != "n")
        {
          cout << "#! " << bold_on << "Please type y or n!" << bold_off << endl
            << "#! Do you wish to " << bold_on << "generate a report" << bold_off << endl
            << "#! based on these inputs? <y/n>:" << endl
            << "#~ ";
          cin >> input;

          transform(input.begin(), input.end(), input.begin(), ::tolower);
        }

        if (input == "y")
        {
          cout << "#! Generating \U0001F529 ..." << endl;

          // Write a csv file containing the collected information for the R script
          string job_path = current_dir + "/job.csv";

          ofstream job_file (job_path);
          // Couldn't open file
          if(!job_file.is_open())
          {
            cout << "#! " << bold_on << "ERROR:" << bold_off << " File Open" << endl
              << "#!" << endl;
          }
          // Read file
          else
          {
            job_file << "key\tvalue" << endl
              << "data_file" << "\t" << currentInput.data_file << endl
              << "meta_file" << "\t" << currentInput.meta_file << endl
              << "missings" << "\t" << currentInput.missing_option << endl;
            job_file.close();

            // Run R script
            cout << sep << endl
              << "#! R -------------------------------------------------" << endl
              << endl;
            system("Rscript R/main.R");
            cout << endl
              << "#! R END ---------------------------------------------" << endl
              << sep << endl;
          }
        }
        else
        {
          cout << "#! Request has been discarded." << endl;
        }
    }
  }
}
