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
    void set_name(string);
    int get_children_lenth();
    QList<tree*> get_chindren();
    Node get_node();
    string get_value();
    string get_type();
    string get_name();
private:
    Node tnode;
    string type;
    string value;
    string name;
    QList<tree*> children;
};

#endif // TREE_H
