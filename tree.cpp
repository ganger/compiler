#include "tree.h"

tree::tree()
{
}


void tree::set_node(Node n)
{
    this->tnode=n;
}

void tree::set_type(string t)
{
    this->type=t;
}

void tree::set_value(string v)
{
    this->value=v;
}

void tree::append_children(tree* t)
{

    this->children.append(t);
}

void tree::print_tree() //test function
{
    qDebug()<<"{";
    qDebug()<<"id:"<<this->tnode.id;
    qDebug()<<"children_num:"<<this->children.length();
    qDebug()<<"type:"<<QString::fromLocal8Bit(this->type.c_str());
    qDebug()<<"}";
    for(int i=0;i<this->children.length();i++)
    {
        this->children[i]->print_tree();
    }
}

int tree::get_children_lenth()
{
    return children.length();
}

QList<tree*> tree::get_chindren()
{
    return this->children;
}

Node tree::get_node()
{
    return this->tnode;
}
