#include "alternatives.ih"

void Alternatives::generalizedGlob(string initial, GlobContext &context)
{
        // create the command consisting of all cmd line args
    string searchCmd = d_command.accumulate();
    searchCmd.resize(searchCmd.length() - 1);           // remove trailing /


    msg() << "Merged search command: `" << searchCmd << '\'' << info;
    //globHead(initial, searchCmd, context);
    recurse(0, searchCmd, initial, context); 
}
