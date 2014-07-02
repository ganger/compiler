#include "meaning.h"

meaning::meaning()
{
    yacc* yaccLoader=new yacc;
    yaccLoader->run();
    this->root=yaccLoader->get_root();
    this->foreach_tree(root);
  //  root->print_tree();

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

            if(t->get_node().id==63)//decls
            {
             //   string s=t->get_chindren().at(2)->get_type();
            //    qDebug()<<QString::fromLocal8Bit(s.c_str());
                if(t->get_chindren().at(0)->get_type()=="int")
                {

                    t->get_chindren().at(1)->set_type("int");
                }
                if(t->get_chindren().at(0)->get_node().content=="float")
                {
                    t->get_chindren().at(1)->set_type("float");
                }
                if(t->get_chindren().at(0)->get_node().content=="char")
                {
                    t->get_chindren().at(1)->set_type("char");
                }
                if(t->get_chindren().at(0)->get_node().content=="void")
                {
                    t->get_chindren().at(1)->set_type("void");
                }

        }
    }
}
