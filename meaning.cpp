#include "meaning.h"

meaning::meaning()
{
    this->output="";
    this->rCount=0;
    this->numOfT_=0;
    yacc* yaccLoader=new yacc;
    yaccLoader->run();
    this->root=yaccLoader->get_root();
    this->foreach_type(root);

    this->foreach_tree(root);
 //   root->print_tree();
    /*for(int i=0;i<idList->length();i++)
    {
        qDebug()<<QString::fromLocal8Bit(idList->at(i).id.c_str());
        qDebug()<<QString::fromLocal8Bit(idList->at(i).type.c_str());
    }*/
  qDebug()<<QString::number(idList.length());
}

void meaning::foreach_type(tree *t)
{
    int i;
    for(i=0;i<t->get_children_lenth();i++)
    {
        if(t->get_children_lenth()!=0)
        {
            foreach_type(t->get_chindren().at(i));
        }
        if(t->get_node().id==63)//decl
        {

            if(t->get_chindren().at(2)->get_type()=="int")
            {
                bool exit=false;
                for(int i=0;i<idList.length();i++)
                {
                    if(t->get_chindren().at(1)->get_name()==idList.at(i).id)
                    {
                        exit=true;
                        if("int"!=idList.at(i).type)
                        {
                            qDebug()<<"conflicting types ";

                        }
                    }
                }
                if(false==exit)
                {
                    ids *tmpid=new ids;
                    tmpid->type="int";
                    tmpid->id=t->get_chindren().at(1)->get_name();
                    this->idList.append(*tmpid);
                }
            }
            if(t->get_chindren().at(2)->get_type()=="float")
            {
                bool exit=false;
                for(int i=0;i<idList.length();i++)
                {
                    if(t->get_chindren().at(1)->get_name()==idList.at(i).id)
                    {
                        exit=true;
                        if("float"!=idList.at(i).type)
                        {
                            qDebug()<<"conflicting types ";

                        }
                    }
                }
                if(false==exit)
                {
                    ids *tmpid=new ids;
                    tmpid->type="float";
                    tmpid->id=t->get_chindren().at(1)->get_name();
                    this->idList.append(*tmpid);
                }
            }
            if(t->get_chindren().at(2)->get_type()=="char")
            {
            //    t->get_chindren().at(1)->set_type("char");
            }
            if(t->get_chindren().at(2)->get_type()=="void")
            {
             //   t->get_chindren().at(1)->set_type("void");
            }
        }
    }
}

void meaning::foreach_tree(tree* t)
{
    int i;
    for(i=0;i<t->get_children_lenth();i++)
    {
        if(t->get_children_lenth()!=0)
        {
            foreach_tree(t->get_chindren().at(i));
        }


        if((t->get_node().id==78)&&(t->get_chindren().at(0)->get_type()=="")&&(t->get_chindren().at(0)->get_value()==""))
            //t_ and t_.children is null
        {
          //  this->numOfT_++;
            if(t->get_chindren().at(2)->get_node().id==5)//*
            {
                t->set_value(t->get_chindren().at(1)->get_value());
                t->set_type("*");
            }
            if(t->get_chindren().at(2)->get_node().id==6)//  /
            {
                t->set_value(t->get_chindren().at(1)->get_value());
                t->set_type("/");
            }

        }
        if((t->get_node().id==78)&&(t->get_chindren().at(0)->get_type()!="")&&(t->get_chindren().at(0)->get_value()!=""))
            //t_ and t_.children is  not null
        {
          //  this->numOfT_++;
            if(t->get_chindren().at(2)->get_node().id==5)// *
            {
                t->set_type("*");
            }
            if(t->get_chindren().at(2)->get_node().id==6)//  /
            {
                t->set_type("/");
            }
            if(t->get_chindren().at(0)->get_type()=="*")
            {
                int tmpInt1,tmpInt2;
                tmpInt1=atoi(t->get_chindren().at(0)->get_value().c_str());
                tmpInt2=atoi(t->get_chindren().at(1)->get_value().c_str());
                tmpInt1=tmpInt1*tmpInt2;
                stringstream ss;
                ss<<tmpInt1;
                string tmpstr;
                ss>>tmpstr;
                t->set_value(tmpstr);
                static int count=1;
                if(count%3==0)
                {
                   output+="mul r";
                   output+=QString::number(this->rCount-1);
                   output+=" r";
                   output+=QString::number(this->rCount-2);
                   output+="\n";
                   this->numOfT_++;
                }
                count++;
            }
            if(t->get_chindren().at(0)->get_type()=="/")
            {
                int tmpInt1,tmpInt2;
                tmpInt1=atoi(t->get_chindren().at(0)->get_value().c_str());
                tmpInt2=atoi(t->get_chindren().at(1)->get_value().c_str());
                tmpInt1=tmpInt2/tmpInt1;
                stringstream ss;
                ss<<tmpInt1;
                string tmpstr;
                ss>>tmpstr;
                t->set_value(tmpstr);
            }
        }
        if(t->get_node().id==75)//factor
        {
            if(t->get_chindren().at(0)->get_node().id==1)//int
            {
                t->set_value(t->get_chindren().at(0)->get_value());
                output+="mov r";
                output+=QString::number(this->rCount);
                output+=" ";
                output+=QString::fromLocal8Bit(t->get_chindren().at(0)->get_value().c_str());
                output+="\n";
                this->rCount++;
            }
            if(t->get_chindren().at(0)->get_node().id==10)// 10 represents ')',which means (expr)
            {
                t->set_value(t->get_chindren().at(1)->get_value());
            }
        }
        if(t->get_node().id==77)// t
        {

            if(t->get_chindren().at(0)->get_type()=="*")
            {
                int tmpInt1,tmpInt2;
                tmpInt1=atoi(t->get_chindren().at(0)->get_value().c_str());
                tmpInt2=atoi(t->get_chindren().at(1)->get_value().c_str());
                tmpInt1=tmpInt1*tmpInt2;
                stringstream ss;
                ss<<tmpInt1;
                string tmpstr;
                ss>>tmpstr;
                t->set_value(tmpstr);
                if(t->get_chindren().at(1)->get_value()!="")
                {
                   output+="mul r";
                   output+=QString::number(this->rCount-1);
                   output+=" r";
                   output+=QString::number(this->rCount-2);
                   output+="\n";
                   this->numOfT_++;
                }
            }
            if(t->get_chindren().at(0)->get_type()=="/")
            {
                int tmpInt1,tmpInt2;
                tmpInt1=atoi(t->get_chindren().at(0)->get_value().c_str());
                tmpInt2=atoi(t->get_chindren().at(1)->get_value().c_str());
                tmpInt1=tmpInt2/tmpInt1;
                stringstream ss;
                ss<<tmpInt1;
                string tmpstr;
                ss>>tmpstr;
                t->set_value(tmpstr);
            }
            if((t->get_chindren().at(0)->get_value()=="")&&(t->get_chindren().at(0)->get_type()==""))// t_=empty
            {
                t->set_value(t->get_chindren().at(1)->get_value());
            }
        }
        if((t->get_node().id==76)&&(t->get_chindren().at(0)->get_type()=="")&&(t->get_chindren().at(0)->get_value()==""))
            //e_ and e_.children is null
        {
            if(t->get_chindren().at(2)->get_node().id==3) // +
            {
                t->set_value(t->get_chindren().at(1)->get_value());
                t->set_type("+");
            }
            if(t->get_chindren().at(2)->get_node().id==4) // -
            {
                t->set_value(t->get_chindren().at(1)->get_value());
                t->set_type("-");
            }
        }
         if((t->get_node().id==76)&&(t->get_chindren().at(0)->get_type()!="")&&(t->get_chindren().at(0)->get_value()!=""))
             //e_ and e_.children is not null
         {
             if(t->get_chindren().at(2)->get_node().id==3)// +
             {
                 t->set_type("+");


             }
             if(t->get_chindren().at(2)->get_node().id==4)//  -
             {
                 t->set_type("-");
             }
             if(t->get_chindren().at(0)->get_type()=="+")
             {
                 int tmpInt1,tmpInt2;
                 tmpInt1=atoi(t->get_chindren().at(0)->get_value().c_str());
                 tmpInt2=atoi(t->get_chindren().at(1)->get_value().c_str());
                 tmpInt1=tmpInt1+tmpInt2;
                 stringstream ss;
                 ss<<tmpInt1;
                 string tmpstr;
                 ss>>tmpstr;
                 t->set_value(tmpstr);
                 static int count=1;
                 if(count%3==2)
                 {
                    output+="add r";
                    output+=QString::number(this->rCount-1);
                    output+=" r";
                    output+=QString::number(this->rCount-2-this->numOfT_);
                    output+="\n";
                 }
                 count++;
                 qDebug()<<"num:"<<QString::number(this->numOfT_);
                 this->numOfT_=0;
                 if((t->get_chindren().at(0)->get_value()==""))
                 {

                 }
             }
             if(t->get_chindren().at(0)->get_type()=="-")
             {
                 int tmpInt1,tmpInt2;
                 tmpInt1=atoi(t->get_chindren().at(0)->get_value().c_str());
                 tmpInt2=atoi(t->get_chindren().at(1)->get_value().c_str());
                 tmpInt1=tmpInt2-tmpInt1;
                 stringstream ss;
                 ss<<tmpInt1;
                 string tmpstr;
                 ss>>tmpstr;
                 t->set_value(tmpstr);
             }
         }
        if(t->get_node().id==73)// expr
        {
            if(t->get_chindren().at(0)->get_type()=="+")
            {
                int tmpInt1,tmpInt2;
                tmpInt1=atoi(t->get_chindren().at(0)->get_value().c_str());
                tmpInt2=atoi(t->get_chindren().at(1)->get_value().c_str());
                tmpInt1=tmpInt1+tmpInt2;
                stringstream ss;
                ss<<tmpInt1;
                string tmpstr;
                ss>>tmpstr;
                t->set_value(tmpstr);
                if(t->get_chindren().at(1)->get_value()!="")
                {
                   output+="add r";
                   output+=QString::number(this->rCount-1);
                   output+=" r";
                   output+=QString::number(this->rCount-2-this->numOfT_);
                   output+="\n";
             //      qDebug()<<"num:"<<QString::number(this->numOfT_);

                }
                this->numOfT_=0;
            }
            if(t->get_chindren().at(0)->get_type()=="-")
            {
                int tmpInt1,tmpInt2;
                tmpInt1=atoi(t->get_chindren().at(0)->get_value().c_str());
                tmpInt2=atoi(t->get_chindren().at(1)->get_value().c_str());
                tmpInt1=tmpInt2-tmpInt1;
                stringstream ss;
                ss<<tmpInt1;
                string tmpstr;
                ss>>tmpstr;
                t->set_value(tmpstr);
            }
            if((t->get_chindren().at(0)->get_type()=="")&&(t->get_chindren().at(0)->get_value()==""))
            {
                t->set_value(t->get_chindren().at(1)->get_value());
            }
        }
        if((t->get_node().id==65)&&(t->get_chindren().length()==4))//  id=expr
        {
            if(t->get_chindren().at(3)->get_node().id==2)
            {
             //   qDebug()<<"inner:"<<QString::number(idList.length());
                bool declared=false;
                for(int i=0;i<idList.length();i++)
                {

                    if(t->get_chindren().at(3)->get_name()==idList.at(i).id)
                    {
                        declared=true;
                        t->get_chindren().at(3)->set_value(t->get_chindren().at(1)->get_value());
                    }

                }
                if(false==declared||idList.length()==0)
                {
                    qDebug()<<QString::fromLocal8Bit(t->get_chindren().at(3)->get_name().c_str())<<" was not declared";
                }
            }
        }
    }

}

QString meaning::get_output()
{
    return this->output;
}
