#include <iomanip>

#include "expbuilder.h"

ExpBuilder::ExpBuilder()
{
}

ExpBuilder::~ExpBuilder()
{
}

token_t ExpBuilder::quat(char &opcode, token_t &a, token_t &b)
{
    static int count = 0;

    tuple4_t tuple;

    token_t r;
    r.type = token_t::VARIABLE;
    stringstream ss;
    ss << "t" << count++;
    r.value = new_variable_token(ss.str());

    tuple.a = a;
    tuple.b = b;
    tuple.r = r;
    tuple.opcode = opcode;
    tuples.push_back(tuple);

    cout << "quat(" << opcode << ", " << a << ", " << b << ", " << r << ")" << endl;

    return r;
}
