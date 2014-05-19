#include "yacc.h"

yacc::yacc()
{
    NodeReader* nr=new NodeReader();
    QList<struct Node>* head=nr->get_head();
    for(int i=0;i<head->length();i++)
    {
        //qDebug()<<head->at(i).id;
    }

}
