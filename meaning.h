#ifndef MEANING_H
#define MEANING_H
#include"yacc.h"
#include"tree.h"
class meaning
{
public:
    meaning();
    void foreach_tree(tree*);
private:
    tree* root;
};

#endif // MEANING_H
