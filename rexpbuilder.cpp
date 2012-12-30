#include "rexpbuilder.h"

#include <iomanip>

RExpBuilder::RExpBuilder()
{
}

token_t RExpBuilder::process(istream &in)
{
    return processE(in);
}

token_t RExpBuilder::processF(istream &in)
{
    token_t token;
    in >> token;
    if (token.type == token_t::PARENTHESIS) {
        token = processE(in);

        token_t c;
        in >> c;
        if (c.value != ')') {
            cerr << "Nothing more than error!!!!" << endl;
        }

        return token;
    } else if (token.type == token_t::NUMBER || token.type == token_t::VARIABLE) {
        return token;
    }
    token.type = token_t::NONE;

    cerr << endl << "[Error in processing F...]" << endl;
    return token;
}

token_t RExpBuilder::processT(istream &in)
{
    token_t a = processF(in);
    token_t c;
    in >> c;
    while (c.type == token_t::OPERATOR) {
        if (c.value == '*' || c.value == '/') {
            char opcode = (char) c.value;

            token_t b = processF(in);

            // create the quat
            token_t r = quat(opcode, a, b);

            a = r;
            in >> c;
            if (in.eof()) return r;
        } else {
            in.putback(c.value);
            return a;
        }
    }
    if (! in.eof()) {
        if (c.type == token_t::PARENTHESIS) {
            in.putback(c.value);
        }
    }
    return a;
}

token_t RExpBuilder::processE(istream &in)
{
    token_t a = processT(in);
    token_t c;
    in >> c;
    while (c.type == token_t::OPERATOR) {
        char opcode = (char) c.value;

        token_t b = processT(in);

        // create the quat
        token_t r = quat(opcode, a, b);

        a = r;
        in >> c;
        if (in.eof()) return r;
    }
    if (c.type == token_t::PARENTHESIS) {
        in.putback(c.value);
    }
    return a;
}
