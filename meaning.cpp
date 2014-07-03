#include "meaning.h"

meaning::meaning()
{
    yacc* yaccLoader=new yacc;
    yaccLoader->run();
    this->root=yaccLoader->get_root();
    this->foreach_tree(root);
    root->print_tree();

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

        if(t->get_node().id==63)//decl
        {
   //             string s=t->get_chindren().at(2)->get_type();
     //           qDebug()<<QString::fromLocal8Bit(s.c_str());
            if(t->get_chindren().at(2)->get_type()=="int")
            {
                t->get_chindren().at(1)->set_type("int");
            }
            if(t->get_chindren().at(2)->get_type()=="float")
            {
                t->get_chindren().at(1)->set_type("float");
            }
            if(t->get_chindren().at(0)->get_type()=="char")
            {
                t->get_chindren().at(1)->set_type("char");
            }
            if(t->get_chindren().at(0)->get_type()=="void")
            {
                t->get_chindren().at(1)->set_type("void");
            }
        }
        if((t->get_node().id==78)&&(t->get_chindren().at(0)->get_type()=="")&&(t->get_chindren().at(0)->get_value()==""))
            //t_ and t_.children is null
        {
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
        if((t->get_node().id==65)&&(t->get_chindren().length()==4))// = statement
        {
            if(t->get_chindren().at(3)->get_node().id==2)
            {
                t->get_chindren().at(3)->set_value(t->get_chindren().at(1)->get_value());
            }
        }
    }
}
