#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <sstream>
#include <vector>

#include <cstring>

using namespace std;

typedef struct {
    enum { NUMBER, VARIABLE, OPERATOR, PARENTHESIS, NONE } type;
    int value;
} token_t;

int new_variable_token(string s);

istream& operator >>(istream& in, token_t& token);

ostream& operator << (ostream& out, token_t& token);

#endif // TOKEN_H
