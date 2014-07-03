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
        string sid="";
        int i;
        for(i=1;tmpstr[i]!=',';i++)
        {
            sid+=tmpstr[i];
        }
        if(1==sid.length())
        {
             tmpNode->id=sid[0]-'0';
        }
        else if(2==sid.length())
        {
              tmpNode->id=(sid[0]-'0')*10+(sid[1]-'0');
        }
        else
            qDebug()<<"error code 1";

        i++;
        string scontent="";
        for(;tmpstr[i]!=',';i++)
        {
            scontent+=tmpstr[i];
        }
        tmpNode->content=scontent;
        string line="";
        i++;
        for(;i<tmpstr.length();i++)
        {
            line+=tmpstr[i];
        }
        tmpNode->sline=line;
        nodeList->append(*tmpNode);
        free(tmpNode);
     //   QString qs=QString::fromLocal8Bit(scontent.c_str());
       // qDebug()<<qs;
    }

    this->initial_predict_table();
}
QList<struct Node>* NodeReader::get_head()
{
    return nodeList;

}

void NodeReader::initial_predict_table()
{
    tableList=new QList<PredictTable>;
    PredictTable *tmptable;

    tmptable=new PredictTable;
    tmptable->inputId=60;   //program
    tmptable->matchingId=7;// '{'
    tmptable->changingNode.append(61);
    this->tableList->append(*tmptable);
    free(tmptable);

    tmptable=new PredictTable;
    tmptable->inputId=61;       //block
    tmptable->matchingId=7;
    tmptable->changingNode.append(7);
    tmptable->changingNode.append(62);
    tmptable->changingNode.append(64);
    tmptable->changingNode.append(8);
    this->tableList->append(*tmptable);
    free(tmptable);

    tmptable=new PredictTable;
    tmptable->inputId=62;   //decls
    tmptable->matchingId=14;  //type
    tmptable->changingNode.append(63); //decl
    tmptable->changingNode.append(62);
    this->tableList->append(*tmptable);
    free(tmptable);
    for(int i=1;i<60;i++)
    {
        if(14==i)
            continue;
        tmptable=new PredictTable;
        tmptable->inputId=62;   //decls
        tmptable->matchingId=i;
        tmptable->changingNode.append(57); //empty
        this->tableList->append(*tmptable);
        free(tmptable);

    }

    tmptable=new PredictTable;
    tmptable->inputId=63;   //decl
    tmptable->matchingId=14;
    tmptable->changingNode.append(14); //type
    tmptable->changingNode.append(2); //id
    tmptable->changingNode.append(31); //;
    this->tableList->append(*tmptable);
    free(tmptable);
  ///////////////////stmts//////////////////////
    tmptable=new PredictTable;
    tmptable->inputId=64;   //stmts
    tmptable->matchingId=7; //'{'
    tmptable->changingNode.append(65); //stmt
    tmptable->changingNode.append(64);  //stmts
    this->tableList->append(*tmptable);
    free(tmptable);

    tmptable=new PredictTable;
    tmptable->inputId=64;   //stmts
    tmptable->matchingId=2; // id
    tmptable->changingNode.append(65); //stmt
    tmptable->changingNode.append(64);  //stmts
    this->tableList->append(*tmptable);
    free(tmptable);

    tmptable=new PredictTable;
    tmptable->inputId=64;   //stmts
    tmptable->matchingId=22; //if
    tmptable->changingNode.append(65); //stmt
    tmptable->changingNode.append(64);  //stmts
    this->tableList->append(*tmptable);
    free(tmptable);

    tmptable=new PredictTable;
    tmptable->inputId=64;   //stmts
    tmptable->matchingId=29; //while
    tmptable->changingNode.append(65); //stmt
    tmptable->changingNode.append(64);  //stmts
    this->tableList->append(*tmptable);
    free(tmptable);

    tmptable=new PredictTable;
    tmptable->inputId=64;   //stmts
    tmptable->matchingId=12; //break
    tmptable->changingNode.append(65); //stmt
    tmptable->changingNode.append(64);  //stmts
    this->tableList->append(*tmptable);
    free(tmptable);

    ///////////////////stmt//////////////////////
      tmptable=new PredictTable;
      tmptable->inputId=65;   //stmt
      tmptable->matchingId=7; //'{'
      tmptable->changingNode.append(61); //block
      this->tableList->append(*tmptable);
      free(tmptable);

      tmptable=new PredictTable;
      tmptable->inputId=65;   //stmt
      tmptable->matchingId=2; // id
      tmptable->changingNode.append(2); //id
      tmptable->changingNode.append(32);  //=
      tmptable->changingNode.append(73);  //expr
      tmptable->changingNode.append(31);  // ;
      this->tableList->append(*tmptable);
      free(tmptable);

      tmptable=new PredictTable;
      tmptable->inputId=65;   //stmt
      tmptable->matchingId=22; //if
      tmptable->changingNode.append(66); //if_stmt
      tmptable->changingNode.append(67);  //else_part
      this->tableList->append(*tmptable);
      free(tmptable);

      tmptable=new PredictTable;
      tmptable->inputId=65;   //stmt
      tmptable->matchingId=29; //while
      tmptable->changingNode.append(29); //while
      tmptable->changingNode.append(9);  //(
      tmptable->changingNode.append(68);  //bool
      tmptable->changingNode.append(10);  //)
      tmptable->changingNode.append(61);  //block
      this->tableList->append(*tmptable);
      free(tmptable);

      tmptable=new PredictTable;
      tmptable->inputId=65;   //stmt
      tmptable->matchingId=12; //break
      tmptable->changingNode.append(12); // break
      tmptable->changingNode.append(31);  // ;
      this->tableList->append(*tmptable);
      free(tmptable);
    ////////////////////////end stmt////////////////

      tmptable=new PredictTable;
      tmptable->inputId=66;   //if_stmt
      tmptable->matchingId=22; //if
      tmptable->changingNode.append(22); // if
      tmptable->changingNode.append(9);  // (
      tmptable->changingNode.append(68); // bool
      tmptable->changingNode.append(10);  // )
      tmptable->changingNode.append(68); // block
      tmptable->changingNode.append(67);  // else_part
      this->tableList->append(*tmptable);
      free(tmptable);

      tmptable=new PredictTable;
      tmptable->inputId=67;   //else_part
      tmptable->matchingId=19; //else
      tmptable->changingNode.append(19); // else
      tmptable->changingNode.append(68);  // block
      this->tableList->append(*tmptable);
      free(tmptable);

      for(int i=0;i<60;i++)
      {
          if(19==i)
                continue;
          tmptable=new PredictTable;
          tmptable->inputId=67;   //else_part
          tmptable->matchingId=i;
          tmptable->changingNode.append(57); // empty
          this->tableList->append(*tmptable);
          free(tmptable);
      }
/////////////////////////begin bool///////////////////////
      tmptable=new PredictTable;
      tmptable->inputId=68;   //bool
      tmptable->matchingId=2; //id
      tmptable->changingNode.append(70); // rel
      tmptable->changingNode.append(79);  // loprel
      this->tableList->append(*tmptable);
      free(tmptable);

      tmptable=new PredictTable;
      tmptable->inputId=68;   //bool
      tmptable->matchingId=44; // !
      tmptable->changingNode.append(44); // !
      tmptable->changingNode.append(68);  // bool
      this->tableList->append(*tmptable);
      free(tmptable);


//////////////////////////end bool//////////////////////////////
////////////////////////begin loprel////////////////////////////
      tmptable=new PredictTable;
      tmptable->inputId=79;   //loprel
      tmptable->matchingId=55; // ||
      tmptable->changingNode.append(69); // lop
      tmptable->changingNode.append(70);  // rel
      this->tableList->append(*tmptable);
      free(tmptable);

      tmptable=new PredictTable;
      tmptable->inputId=79;   //loprel
      tmptable->matchingId=53; // &&
      tmptable->changingNode.append(69); // lop
      tmptable->changingNode.append(70);  // rel
      this->tableList->append(*tmptable);
      free(tmptable);

      for(int i=0;i<60;i++)
      {
          if((53==i)||(55==i))
               continue;
          tmptable=new PredictTable;
          tmptable->inputId=79;   //loprel
          tmptable->matchingId=i; // &&
          tmptable->changingNode.append(57); // empty
          this->tableList->append(*tmptable);
          free(tmptable);
      }
///////////////////////end loprel////////////////////////////////
      tmptable=new PredictTable;
      tmptable->inputId=69;   //lop
      tmptable->matchingId=55; //||
      tmptable->changingNode.append(55); // ||
      this->tableList->append(*tmptable);
      free(tmptable);

      tmptable=new PredictTable;
      tmptable->inputId=69;   //lop
      tmptable->matchingId=53; //&&
      tmptable->changingNode.append(53); // &&
      this->tableList->append(*tmptable);
      free(tmptable);



      tmptable=new PredictTable;
      tmptable->inputId=70;   //rel
      tmptable->matchingId=2; //id
      tmptable->changingNode.append(73); // expr
      tmptable->changingNode.append(71); // rop
      tmptable->changingNode.append(73); // expr
      this->tableList->append(*tmptable);
      free(tmptable);

      tmptable=new PredictTable;
      tmptable->inputId=71;   //rop
      tmptable->matchingId=23; //<
      tmptable->changingNode.append(23); // <
      tmptable->changingNode.append(72); // rope
      this->tableList->append(*tmptable);
      free(tmptable);
//////////////////////////////////////////////////////
      tmptable=new PredictTable;
      tmptable->inputId=71;   //rop
      tmptable->matchingId=24; //>
      tmptable->changingNode.append(24); // >
      tmptable->changingNode.append(72); // rope
      this->tableList->append(*tmptable);
      free(tmptable);

      tmptable=new PredictTable;
      tmptable->inputId=71;   //rop
      tmptable->matchingId=33; //==
      tmptable->changingNode.append(33); // ==
      this->tableList->append(*tmptable);
      free(tmptable);
////////////////////////////////////////////////////
      tmptable=new PredictTable;
      tmptable->inputId=72;   //rope
      tmptable->matchingId=32; //=
      tmptable->changingNode.append(32); // =
      this->tableList->append(*tmptable);
      free(tmptable);

      for(int i=0;i<60;i++)
      {
          if(32==i)
              continue;
          tmptable=new PredictTable;
          tmptable->inputId=72;   //rope
          tmptable->matchingId=i; //
          tmptable->changingNode.append(57); // empty
          this->tableList->append(*tmptable);
          free(tmptable);
      }
//////////////////expr////////////////////////////
      tmptable=new PredictTable;
      tmptable->inputId=73;   //expr
      tmptable->matchingId=9; //(
      tmptable->changingNode.append(77); // T
      tmptable->changingNode.append(76); // E'

      this->tableList->append(*tmptable);
      free(tmptable);

      tmptable=new PredictTable;
      tmptable->inputId=73;   //expr
      tmptable->matchingId=2; //ID
      tmptable->changingNode.append(77); // T
      tmptable->changingNode.append(76); // E'

      this->tableList->append(*tmptable);
      free(tmptable);

      tmptable=new PredictTable;
      tmptable->inputId=73;   //expr
      tmptable->matchingId=1; //const int
      tmptable->changingNode.append(77); // T
      tmptable->changingNode.append(76); // E'

      this->tableList->append(*tmptable);
      free(tmptable);

      tmptable=new PredictTable;
      tmptable->inputId=73;   //expr
      tmptable->matchingId=56; //const float
      tmptable->changingNode.append(77); // T
      tmptable->changingNode.append(76); // E'

      this->tableList->append(*tmptable);
      free(tmptable);
/////////////////////////end expr/////////////////////////
////////////////////////begin factor/////////////////////
      tmptable=new PredictTable;
      tmptable->inputId=75;   //FACTOR
      tmptable->matchingId=9; //(
      tmptable->changingNode.append(9); // (
      tmptable->changingNode.append(73); // EXPR
      tmptable->changingNode.append(10); // )
      this->tableList->append(*tmptable);
      free(tmptable);


      tmptable=new PredictTable;
      tmptable->inputId=75;   //FACTOR
      tmptable->matchingId=2; //id
      tmptable->changingNode.append(2); // id
      this->tableList->append(*tmptable);
      free(tmptable);


      tmptable=new PredictTable;
      tmptable->inputId=75;   //FACTOR
      tmptable->matchingId=1; //const int
      tmptable->changingNode.append(1); //
      this->tableList->append(*tmptable);
      free(tmptable);

      tmptable=new PredictTable;
      tmptable->inputId=75;   //FACTOR
      tmptable->matchingId=56; //const float
      tmptable->changingNode.append(56); //
      this->tableList->append(*tmptable);
      free(tmptable);
//////////////////////////end factor////////////////////
      tmptable=new PredictTable;
      tmptable->inputId=76;   //_e
      tmptable->matchingId=3; //+
      tmptable->changingNode.append(3); //+
      tmptable->changingNode.append(77); //t
      tmptable->changingNode.append(76); // e'
      this->tableList->append(*tmptable);
      free(tmptable);


      tmptable=new PredictTable;
      tmptable->inputId=76;   //_e
      tmptable->matchingId=4; //-
      tmptable->changingNode.append(4); //-
      tmptable->changingNode.append(77); //t
      tmptable->changingNode.append(76); // e'
      this->tableList->append(*tmptable);
      free(tmptable);

      tmptable=new PredictTable;
      tmptable->inputId=76;   //_e
      tmptable->matchingId=10; //)
      tmptable->changingNode.append(57); //empty
      this->tableList->append(*tmptable);
      free(tmptable);

      tmptable=new PredictTable;
      tmptable->inputId=76;   //_e
      tmptable->matchingId=31; //;
      tmptable->changingNode.append(57); //empty
      this->tableList->append(*tmptable);
      free(tmptable);

      tmptable=new PredictTable;
      tmptable->inputId=76;   //_e
      tmptable->matchingId=23; //  <
      tmptable->changingNode.append(57); //  empty
      this->tableList->append(*tmptable);
      free(tmptable);

      tmptable=new PredictTable;
      tmptable->inputId=76;   //_e
      tmptable->matchingId=24; //  >
      tmptable->changingNode.append(57); //  empty
      this->tableList->append(*tmptable);
      free(tmptable);
///////////////t//////////////////////
      tmptable=new PredictTable;
      tmptable->inputId=77;   //t
      tmptable->matchingId=9; //(
      tmptable->changingNode.append(75); //factor
      tmptable->changingNode.append(78); //_t
      this->tableList->append(*tmptable);
      free(tmptable);

      tmptable=new PredictTable;
      tmptable->inputId=77;   //t
      tmptable->matchingId=2; //id
      tmptable->changingNode.append(75); //factor
      tmptable->changingNode.append(78); //_t
      this->tableList->append(*tmptable);
      free(tmptable);

      tmptable=new PredictTable;
      tmptable->inputId=77;   //t
      tmptable->matchingId=1; //const int
      tmptable->changingNode.append(75); //factor
      tmptable->changingNode.append(78); //_t
      this->tableList->append(*tmptable);
      free(tmptable);

      tmptable=new PredictTable;
      tmptable->inputId=77;   //t
      tmptable->matchingId=56; //const float
      tmptable->changingNode.append(75); //factor
      tmptable->changingNode.append(78); //_t
      this->tableList->append(*tmptable);
      free(tmptable);
/////////////////end t/////////////////////////////////
      tmptable=new PredictTable;
      tmptable->inputId=78;   //_t
      tmptable->matchingId=3; //+
      tmptable->changingNode.append(57); //empty
      this->tableList->append(*tmptable);
      free(tmptable);

      tmptable=new PredictTable;
      tmptable->inputId=78;   //_t
      tmptable->matchingId=4; //-
      tmptable->changingNode.append(57); //empty
      this->tableList->append(*tmptable);
      free(tmptable);

      tmptable=new PredictTable;
      tmptable->inputId=78;   //_t
      tmptable->matchingId=10; //)
      tmptable->changingNode.append(57); //empty
      this->tableList->append(*tmptable);
      free(tmptable);

      tmptable=new PredictTable;
      tmptable->inputId=78;   //_t
      tmptable->matchingId=31; //;
      tmptable->changingNode.append(57); //empty
      this->tableList->append(*tmptable);
      free(tmptable);

      tmptable=new PredictTable;
      tmptable->inputId=78;   //_t
      tmptable->matchingId=5; //*
      tmptable->changingNode.append(5); //*
      tmptable->changingNode.append(75); //factor
      tmptable->changingNode.append(78); //_t
      this->tableList->append(*tmptable);
      free(tmptable);

      tmptable=new PredictTable;
      tmptable->inputId=78;   //_t
      tmptable->matchingId=6; //  /
      tmptable->changingNode.append(6); //  /
      tmptable->changingNode.append(75); //factor
      tmptable->changingNode.append(78); //_t
      this->tableList->append(*tmptable);
      free(tmptable);

      tmptable=new PredictTable;
      tmptable->inputId=78;   //_t
      tmptable->matchingId=23; //  <
      tmptable->changingNode.append(57); //  empty
      this->tableList->append(*tmptable);
      free(tmptable);

      tmptable=new PredictTable;
      tmptable->inputId=78;   //_t
      tmptable->matchingId=24; //  >
      tmptable->changingNode.append(57); //  empty
      this->tableList->append(*tmptable);
      free(tmptable);
}

QList<struct PredictTable>* NodeReader::get_tablelist()
{
    return tableList;
}

