#ifndef EXPBUILDER_H
#define EXPBUILDER_H

#include <iostream>
#include "token.h"

using namespace std;

class ExpBuilder
{
public:
    ExpBuilder();
    virtual ~ExpBuilder();

    virtual token_t process(istream& in) = 0;

protected:
    token_t quat(char& opcode, token_t& a, token_t& b);

    typedef struct tuple4_s {
        char opcode;
        token_t a;
        token_t b;
        token_t r;
    } tuple4_t;

    vector<tuple4_t> tuples;
};

#endif // EXPBUILDER_H
