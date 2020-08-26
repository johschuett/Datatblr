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
void boot_info();

// call_func.cpp
void call_func(const string& input);

// commands.cpp
void authors();
void examples();
void quit();
void s_o_d();
void table();
void wd_info();

// initiate.cpp
void initiate(string input);

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
