#ifndef LL1EXPBUILDER_H
#define LL1EXPBUILDER_H

#include "expbuilder.h"
#include <stack>

class LL1ExpBuilder : public ExpBuilder
{
public:
    LL1ExpBuilder();

    token_t process(istream &in);

protected:
    void reduction(stack<token_t> &numStack, stack<token_t> &oprTokens);
};

#endif // LL1EXPBUILDER_H
