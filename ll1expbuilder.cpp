#include "ll1expbuilder.h"

#include <stack>
#include <map>
#include <cstdlib>

#include "token.h"

using namespace std;

LL1ExpBuilder::LL1ExpBuilder()
{
}

int token_type_map(const token_t &token)
{
    switch (token.type) {
    case token_t::NUMBER:
    case token_t::VARIABLE:
        return 0;
    case token_t::OPERATOR:
        return (token.value=='+'||token.value=='-')? 1: 2;
    case token_t::PARENTHESIS:
        return token.value=='('? 4: 5;
    default:
        return 3;
    }
}

class DItem
{
public:
    enum state_e {NT, T, R, E};

    DItem(int item, state_e state=NT):value(item), type(state)
    {
    }

    DItem(): value(0), type(E)
    {
    }

    DItem(const DItem &it): value(it.value), type(it.type)
    {
    }

    int value;
    state_e type;
};

token_t LL1ExpBuilder::process(istream &in)
{
    token_t token;

    DItem deduction[][4] = {
        {DItem(1, DItem::NT), DItem(2, DItem::NT)},
        {DItem(1, DItem::NT), DItem(0, DItem::R), DItem(2, DItem::NT), DItem(1, DItem::T)},
        {DItem(0, DItem::E)},
        {DItem(3, DItem::NT), DItem(4, DItem::NT)},
        {DItem(3, DItem::NT), DItem(1, DItem::R), DItem(4, DItem::NT), DItem(2, DItem::T)},
        {DItem(0, DItem::E)},
        {DItem(0, DItem::T)},
        {DItem(5, DItem::T), DItem(0, DItem::NT), DItem(4, DItem::T)}
    };

    int ll[5][6] = {
        {1, 0, 0, 0, 1, 0},
        {0, 2, 0, 3, 0, 3},
        {4, 0, 0, 0, 4, 0},
        {0, 6, 5, 6, 0, 6},
        {7, 0, 0, 0, 8, 0}
    };

    stack<DItem*> synStack;
    stack<token_t> numStack;
    stack<token_t> oprStack;

    synStack.push(new DItem(0, DItem::NT));
    int t, nt, dd;

    do {
        in >> token;
        t = token_type_map(token);

        if (! synStack.empty()) {
            DItem *it = synStack.top();

            while (it->type != DItem::T) {
                if (it->type == DItem::R) {
                    reduction(numStack, oprStack);
                    synStack.pop();
                } else {
                    nt = it->value;
                    dd = ll[nt][t] - 1;

                    if (dd < 0) {
                        cout << "Error! " << "(" << nt << "," << t << ")" << token << endl;
                        exit(1);
                    }

                    synStack.pop();
                    for (int i=0; deduction[dd][i].type != DItem::E && i < 4; i++) {
                        synStack.push(new DItem(deduction[dd][i]));
                    }
                }

                if (! synStack.empty()) {
                    it = synStack.top();
                } else {
                    return token;
                }
            }

            if (it->type == DItem::T && it->value == t) {
                synStack.pop();

                if (token.type == token_t::NUMBER || token.type == token_t::VARIABLE) {
                    numStack.push(token);
                } else if (token.type == token_t::OPERATOR) {
                    oprStack.push(token);
                }
            } else {
                cerr << "Error in parsing tokens. Expect type "<< it->type << ". Got " << token << endl;
            }
        } else {
            cerr << "synStack is empty?" << endl;
            break;
        }
    }
    while (!in.eof());

    return token;
}

void LL1ExpBuilder::reduction(stack<token_t> &numStack, stack<token_t> &oprTokens)
{
    if (numStack.size() < 2) return;

    token_t b = numStack.top(); numStack.pop();
    token_t a = numStack.top(); numStack.pop();
    token_t o = oprTokens.top(); oprTokens.pop();

    if (o.type != token_t::OPERATOR) {
        cerr << "Error!" << endl;
    }
    token_t r = quat((char&) o.value, a, b);
    numStack.push(r);
}
