#ifndef YACC_H
#define YACC_H
#include"code.h"
#include<QList>
#include<QDebug>
#include<QStack>
#include"tree.h"
class yacc
{
public:
    yacc();
    void run();
    tree* get_root();
private:
    QStack<struct Node> workingStack;
    QStack<tree*> treeStack;
    tree *root;

};

#endif // YACC_H
