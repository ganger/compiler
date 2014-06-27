#ifndef TREE_H
#define TREE_H
#include"code.h"
#include<string>
#include<QList>
#include<QDebug>
using namespace std;
class tree
{
public:
    tree();
    void set_node(Node);
    void set_type(string);
    void set_value(string);
    void append_children(tree *);
    void print_tree();
private:
    Node tnode;
    string type;
    string value;
    QList<tree*> children;
};

#endif // TREE_H
