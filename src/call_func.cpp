#include "utils.h"

// If input = command: Search for input inside commands map
void call_func(const string& input)
{
    auto iter = commands.find(input);
    if (iter == commands.end())
    {
        cout << "#! Oops, I don't know this command..." << endl;
    }
    else
      (*iter->second)();
}
