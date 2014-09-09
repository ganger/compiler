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
    void foreach_type(tree*);
    QString get_output();
private:
    tree* root;
    QList<ids> idList;
    QString output;
    int rCount;
    int numOfT_;
    int labelCount;
};

#endif // MEANING_H
