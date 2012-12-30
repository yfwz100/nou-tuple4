#ifndef REXPBUILDER_H
#define REXPBUILDER_H

#include <iostream>
#include "expbuilder.h"
#include "token.h"

class RExpBuilder:public ExpBuilder
{
public:
    RExpBuilder();

    virtual token_t process(istream& in);

protected:
    token_t processE(istream& in);
    token_t processT(istream&);
    token_t processF(istream& in);
};

#endif // REXPBUILDER_H
