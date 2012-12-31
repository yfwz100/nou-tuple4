#include "slr1expbuilder.h"
#include <stack>

SLR1ExpBuilder::SLR1ExpBuilder()
{
}

static int token_type_map(const token_t &token)
{
    switch (token.type) {
    case token_t::NUMBER:
    case token_t::VARIABLE:
        return 0;
    case token_t::OPERATOR:
        return (token.value=='+'||token.value=='-')? 1: 2;
    case token_t::PARENTHESIS:
        return token.value=='('? 3: 4;
    default:
        return 5;
    }
}

class RItem
{
public:
    RItem(int token, int state):token(token), state(state)
    {
    }

    RItem():token(-2), state(0) // unavailable state.
    {
    }

    int token;
    int state;
};

token_t SLR1ExpBuilder::process(istream &in)
{
    token_t token;

    int lr[][9] = {
        { 9,  0,  0, 10,  0,  0,  2,  5,  8},
        { 0,  3,  0,  0,  0, -1,  0,  0,  0},
        { 9,  0,  0, 10,  0,  0,  0,  4,  8},
        { 0, -2,  6,  0, -2, -2,  0,  0,  0},
        { 0, -3,  6,  0, -3, -3,  0,  0,  0},
        { 9,  0,  0, 10,  0,  0,  0,  0,  7},
        {-4, -4, -4, -4, -4, -4,  0,  0,  0},
        {-5, -5, -5, -5, -5, -5,  0,  0,  0},
        {-7, -7, -7, -7, -7, -7,  0,  0,  0},
        { 9,  0,  0, 10,  0,  0, 11,  5,  8},
        { 0,  3,  0,  0, 12,  0,  0,  0,  0},
        {-6, -6, -6, -6, -6, -6,  0,  0,  0}
    };

    int dr[] = {0, 6, 6, 7, 7, 8, 8};

    stack<token_t> numStack, oprStack;

    stack<RItem> synStack;
    int lstate, state, symbol, t;
    char opr;

    synStack.push(RItem(5, 0));

    do {
        in >> token;
        t = token_type_map(token);

        if (token.type == token_t::NUMBER || token.type == token_t::VARIABLE) {
            numStack.push(token);
        }

        while(!synStack.empty()) {
            RItem it = synStack.top();
            lstate = it.state;

            state = lr[lstate][t];
            if (state > 0) { // shift
                state --;
                if (token.type == token_t::OPERATOR) {
                    synStack.push(RItem(token.value, state));
                } else {
                    synStack.push(RItem(t, state));
                }
                break;
            } else if (state < 0) { // reduct
                state = -state-1;

                switch (state) {
                case 0:
                    return numStack.top();

                case 1:
                    synStack.pop();
                    opr = (char) synStack.top().token;
                    synStack.pop();
                    synStack.pop();

                    quat_(opr, numStack);

                    break;
                case 2:
                    synStack.pop();
                    break;

                case 3:
                    synStack.pop();
                    opr = (char) synStack.top().token;
                    synStack.pop();
                    synStack.pop();

                    quat_(opr, numStack);

                    break;
                case 4:
                    synStack.pop();
                    break;

                case 5:
                    synStack.pop();
                    synStack.pop();
                    synStack.pop();
                    break;

                case 6:
                    synStack.pop();
                    break;
                }

                symbol = dr[state];
                state = lr[synStack.top().state][symbol]-1;
                synStack.push(RItem(symbol, state));
            }
        }
    }
    while (! in.eof());
    return token;
}

token_t SLR1ExpBuilder::quat_(char &opr, stack<token_t> &numStack)
{
    token_t b = numStack.top(); numStack.pop();
    token_t a = numStack.top(); numStack.pop();

    numStack.push(quat(opr, a, b));
}
