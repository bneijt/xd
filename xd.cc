/*                              xd.cc

   A C++ main()-frame generated by cpp.im for xd.cc

*/

#include "xd.ih"               // program header file

int main(int argc, char **argv)
try
{
    arguments(argc, argv);

    Alternatives alternatives;
    alternatives.viable();              // select viable alternatives

    Arbiter arbiter(alternatives);
    arbiter.select();                   // make the selection

    return arbiter.decided() ? 0 : 1;   // return 0 to the OS if the arbiter
                                        // did do its work 
}
catch(Errno const &err)     // handle exceptions
{
    cerr << err.what() << endl;
    cout << ".\n";          // to prevent a diretory change
    return err.which();
}
catch(int x)
{
    if (x == 0)
        cerr << "No Solutions\n";
    cout << ".\n";
    return x;
}


