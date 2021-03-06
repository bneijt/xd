#ifndef _Arbiter_H_
#define _Arbiter_H_

#include <string>

#include "../alternatives/alternatives.h"

class Arbiter
{
    size_t d_index;
    Alternatives const &d_alternatives;
        
    public:
        Arbiter(Alternatives const &alternatives);

        void select();
        inline bool decided() const;

    private:
        void showAlternatives() const;
        size_t show(size_t begin, char first, char last) const;
        void setIndex();
};

bool Arbiter::decided() const
{
    return d_index != d_alternatives.size();
}

#endif
