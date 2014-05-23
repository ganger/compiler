#ifndef YACC_H
#define YACC_H
#include"code.h"
#include<QList>
#include<QDebug>
#include<QStack>
class yacc
{
public:
    yacc();
    void run();
private:
    QStack<struct Node> workingStack;

};

#endif // YACC_H
