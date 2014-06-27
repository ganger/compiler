#include "yacc.h"

yacc::yacc()
{



}

void yacc::run()
{
    NodeReader* nr=new NodeReader();
    QList<struct Node>* head=nr->get_head();
    QList<struct PredictTable>* ptable=nr->get_tablelist();

    Node headNode;
    headNode.sline="0";
    headNode.id=60; //program
    this->root=new tree;
    this->root->set_node(headNode);
    this->workingStack.push(headNode);
    this->treeStack.push(root);
    for(int i=0;i<head->length();i++)
    {
        int currentId=head->at(i).id;
        while(!workingStack.isEmpty())
        {
            Node stackTopNode=workingStack.pop();
            tree *StackTopTree=treeStack.pop();
            if(stackTopNode.id<60) // final symbol
            {
                if(currentId==stackTopNode.id)
                {
                    qDebug()<<"matching!";

                    break;
                }
                else
                {
                    qDebug()<<"err at:";
                    QString qs=QString::fromLocal8Bit(head->at(i).sline.c_str());
                    qDebug()<<qs<<"\n";
                    break;
                }
            }

            int j;
            for(j=0;j<ptable->length();j++)
            {

                if((stackTopNode.id==ptable->at(j).inputId)&&(currentId==ptable->at(j).matchingId))
                {
                        for(int k=ptable->at(j).changingNode.length()-1;k>=0;k--)
                        {
                            Node tmpNode;
                            tree *tmptree=new tree;
                            tmpNode.id=ptable->at(j).changingNode.at(k);
                            if(tmpNode.id!=57)
                            {
                                tmptree->set_node(tmpNode);
                                StackTopTree->append_children(tmptree);
                                treeStack.push(tmptree);
                                this->workingStack.push(tmpNode);

                            }
                            //qDebug()<<tmpNode.id;
                        }
                        break;
                   qDebug()<<"suc";
                }


            }
            stackTopNode=workingStack.pop();
            StackTopTree=treeStack.pop();
            if(stackTopNode.id<60) //final symbol
            {
                if(currentId==stackTopNode.id)
                {

                    qDebug()<<"matching!";
                    break;
                }
                else
                {
                    qDebug()<<"err at:";
                    QString qs=QString::fromLocal8Bit(head->at(i).sline.c_str());
                    qDebug()<<qs<<"\n";
                    break;
                }
            }
            else
            {
                workingStack.push(stackTopNode);
                treeStack.push(StackTopTree);
            }
        }

    }
    root->print_tree();

}
