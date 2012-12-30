
#include "token.h"

static vector<string> kl;

int new_variable_token(string s) {
    kl.push_back(s);
    return kl.size() - 1;
}

istream& operator>>(istream& in, token_t& token)
{
    char c = in.get();
    if (c == -1) {
        token.type = token_t::NONE;
        token.value = 0;
        return in;
    } else {
        if (c >= '0' && c <= '9') {
            // if it's a number.
            int number = 0;
            do {
                number = number*10 + (c-'0');
                in >> c;
            }
            while(c >='0' && c <='9' && !in.eof());
            in.putback(c);

            token.type = token_t::NUMBER;
            token.value = number;
        } else if (c == '(' || c == ')'){
            token.type = token_t::PARENTHESIS;
            token.value = c;
        } else if (strchr("+-*/=", c) != NULL) {
            token.type = token_t::OPERATOR;
            token.value = c;
        } else {
            unsigned int i;
            stringstream ss;

            // Read a variable token: replace it with elegant code!!!
            do {
                ss << c;
                c == in.get();
            }
            while(strchr("+-*/=()", c) == NULL && !in.eof());
            if (! in.eof()) {
                in.putback(c);

                string s = ss.str();

                token.type = token_t::VARIABLE;
                for(i=0; i<kl.size(); i++) {
                    if (kl[i] == s) {
                        token.value = i;
                        return in;
                    }
                }
                token.value = new_variable_token(s);
            } else {
                token.type = token_t::NONE;
                token.value = 0;
            }
        }
    }
    return in;
}

ostream& operator << (ostream& out, token_t& token)
{
    switch (token.type) {
    case token_t::VARIABLE:
        out << "[" << kl[token.value] << "]";
        break;
    case token_t::NONE:
        out << "[None]";
        break;
    default:
        out << "[" << token.value << "]";
    }
    return out;
}
