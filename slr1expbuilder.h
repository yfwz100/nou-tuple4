#ifndef SLR1EXPBUILDER_H
#define SLR1EXPBUILDER_H

#include <stack>
#include "expbuilder.h"

class SLR1ExpBuilder : public ExpBuilder
{
public:
    SLR1ExpBuilder();

    token_t process(istream &in);

protected:
    token_t quat_(char &opr, stack<token_t> &numStack);
};

#endif // SLR1EXPBUILDER_H
