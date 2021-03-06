#include "alternatives.ih"

size_t Alternatives::set(char const *longKey, 
                         char const *const *const begin, 
                         char const *const *const end, 
                         size_t notFound)
{
    string conf;

    if (!d_arg.option(&conf, longKey))
    {
        msg() << "Option or config: No key " << longKey << info;
        return notFound;
    }

    char const *const *const ret = 
                    find_if(begin, end, bind2nd(equal_to<string>(), conf));

    if (ret != end)
    {
        msg() << "Option or config `" << longKey << " " << conf << "' found" <<
                info;

        return ret - begin;
    }

    msg() << "`" << longKey << " " << conf << 
            "' not supported. Using the default `" << begin[notFound] <<
            "'." << info;

    return notFound;
}






