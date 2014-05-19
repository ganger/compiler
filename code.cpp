#include "code.h"
#include<QString>
#include<QDebug>
NodeReader::NodeReader()
{
    ifstream lexTmpFile;
    lexTmpFile.open("lex.tmp",ios::in);
    string tmpstr;
    string str1="";
    nodeList=new QList<struct Node>;
    while(!lexTmpFile.eof())
    {
        lexTmpFile>>tmpstr;
        struct Node *tmpNode=new struct Node;
        if(','==tmpstr[2])
        {

            tmpNode->id=tmpstr[1]-'0';
            for(int i=3;tmpstr[i]!='>';i++)
            {
                str1+=tmpstr[i];
            }
           // QString qs=QString::fromLocal8Bit(str1.c_str());
          //  qDebug()<<qs<<tmpNode->id;
            str1="";
            tmpNode->content=str1;
            nodeList->append(*tmpNode);
            free(tmpNode);
        }
        else if(','==tmpstr[3])
        {
            tmpNode->id=(tmpstr[1]-'0')*10+(tmpstr[2]-'0');
            for(int i=4;tmpstr[i]!='>';i++)
            {
                str1+=tmpstr[i];
            }
           // QString qs=QString::fromLocal8Bit(str1.c_str());
           // qDebug()<<qs<<tmpNode->id;
            str1="";
            tmpNode->content=str1;
            nodeList->append(*tmpNode);
            free(tmpNode);


        }
    }
}
QList<struct Node>* NodeReader::get_head()
{
    return nodeList;

}
