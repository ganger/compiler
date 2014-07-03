#ifndef MEANING_H
#define MEANING_H
#include"yacc.h"
#include"tree.h"
#include<sstream>
#include"code.h"
#include<QList>
using namespace std;
class meaning
{
public:
    meaning();
    void foreach_tree(tree*);
private:
    tree* root;
};

#endif // MEANING_H
