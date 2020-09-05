#pragma once

#include <iostream>
#include <unordered_map>

using namespace std;

// Struct for storing valid user input
struct InputData
{
  string data_file;
  string meta_file;
  int missing_option;
};

// Define function map
typedef void (*ScriptFunction)(void);
typedef unordered_map<string, ScriptFunction> func_map;

// main.cpp
extern func_map commands;

// boot_info.cpp
void boot_info(bool& args_given);

// call_func.cpp
void call_func(const string& input);

// commands.cpp
void authors();
void print_current_dir();
void examples();
void quit();
void s_o_d();
void table();
void wd_info();

// files.cpp
bool file_exists(const string& name);
bool file_extension(const string& file, const string& extension);
bool valid_csv(const string& file);
string split_filename(const string& path);

// formatting.cpp
ostream& bold_on(ostream& os);
ostream& bold_off(ostream& os);

// globals.cpp
extern bool quit_flag;
extern string current_dir;
extern const string sep;
extern const string version;

// initiate.cpp
void initiate(string& input, string& meta_input, int& missing_input, bool& arg_mode);

// integer.cpp
bool is_integer(const string& s);
