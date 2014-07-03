#ifndef MEANING_H
#define MEANING_H
#include"yacc.h"
#include"tree.h"
#include<sstream>
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
