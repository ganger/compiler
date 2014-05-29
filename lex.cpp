#include "lex.h"

lex::lex()
{
    lexOutputStr="";
    lexOutputQStr="";
}

 void lex::load(QString srcCode)
{
    string src=srcCode.toStdString();
    this->run(src);
    ofstream outFile;
    outFile.open("lex.tmp",ios::out);
    outFile<<lexOutputStr;
    outFile.close();
  //  qDebug()<<"ok";
}
 void lex::run(string code)
 {
     int i;
     int line=1;
     string sline="1";
     for(i=0;i<code.size();i++)
     {
         switch(code[i])
         {
         // the '/'
            case '/':
            {
                if(code[i+1]=='/')//   case //
                {
                    while(code[i]!='\n')
                    {
                        i++;
                    }

                }else if(code[i+1]=='*')  //  case /*
                {
                    i=i+2;
                    while(true)
                    {
                        if(code[i]=='*'&&code[i+1]=='/')
                        {
                            i++;
                            break;
                        }
                        i++;
                    }

                }else
                {

                    lexOutputStr.append("<6,_,"+sline+"\n");
                }
            }break;
             // the '+'
            case '+':
            {
             if(code[i+1]=='+')
             {

                 lexOutputStr.append("<50,_,"+sline+"\n");
                 i++;
             }else
             {

                 lexOutputStr.append("<3,_,"+sline+"\n");
             }
            }break;
             // the '-'
            case '-':
            {
                if(code[i+1]=='-')
                {
                    lexOutputStr.append("<51,_,"+sline+"\n");
                    i++;
                }else
                {
                  lexOutputStr.append("<4,_,"+sline+"\n");
                }
             }break;
             //the "*"
              case '*': lexOutputStr.append("<5,_,"+sline+"\n");break;
              case '{': lexOutputStr.append("<7,_,"+sline+"\n");break;
              case '}': lexOutputStr.append("<8,_,"+sline+"\n");break;
              case '(': lexOutputStr.append("<9,_,"+sline+"\n");break;
              case ')': lexOutputStr.append("<10,_,"+sline+"\n");break;
              case '\\': lexOutputStr.append("<11,_,"+sline+"\n");break;//  the '\'
              case '.': lexOutputStr.append("<30,_,"+sline+"\n");break;
              case ';': lexOutputStr.append("<31,_,"+sline+"\n");break;
              case ',': lexOutputStr.append("<49,_,"+sline+"\n");break;
              case '>': lexOutputStr.append("<24,_,"+sline+"\n");break;
              case '<': lexOutputStr.append("<23,_,"+sline+"\n");break;
              case ' ':break;
             //the "="
            case '=':
            {
                if(code[i+1]=='=')
                {
                    lexOutputStr.append("<33,_,"+sline+"\n");
                    i++;
                }else
                {
                    lexOutputStr.append("<32,_,"+sline+"\n");
                }
            }break;
             case '!':
             {
                if(code[i+1]=='+')
                {
                    lexOutputStr.append("<43,_,"+sline+"\n");
                    i++;
                }else
                {
                    lexOutputStr.append("<44,_,"+sline+"\n");
                }
             }break;
            case '"':
            {
                string tmpstr="";
                while(code[i+1]!='"')
                {
                    i++;
                    tmpstr+=code[i];
                }
                i++;
                lexOutputStr.append("<48,"+tmpstr+","+sline+"\n");
            }break;

         case '\'':
         {
             string tmpstr="";
             while(code[i+1]!='\'')
             {
                 i++;
                 tmpstr+=code[i];
             }
             i++;
             lexOutputStr.append("<47,"+tmpstr+","+sline+"\n");
         }break;
         case '&':
         {
             if(code[i+1]=='&')
             {
                 lexOutputStr.append("<53,_,"+sline+"\n");
                 i++;
             }else
             {
                 lexOutputStr.append("<52,_,"+sline+"\n");
             }break;
            case '|':
             {
                 if(code[i+1]=='|')
                 {
                     lexOutputStr.append("<55,_,"+sline+"\n");
                     i++;
                 }else
                 {
                     lexOutputStr.append("<54,_,"+sline+"\n");
                 }
             }
         }break;
            default:
            {
                if(this->isNUmber(code[i])) //number
                {
                    //qDebug()<<code[i];
                    double number=0.0;
                    double tmpNumber=0.0;
                    int tmpInt=int(code[i]-'0');

                    while(this->isNUmber(code[i+1]))
                    {
                        tmpInt=tmpInt*10+int(code[i+1]-'0');
                        i++;
                        //qDebug()<<tmpInt;
                    }
                    number=tmpInt;
                    if(code[i+1]=='.')
                    {
                        i++;
                        double n=0.1;
                        while(this->isNUmber(code[i+1]))
                        {
                            tmpNumber=tmpNumber+int(code[i+1]-'0')*n;
                            n=n/10;
                            i++;
                        }
                        //  qDebug()<<tmpNumber;
                        number=tmpInt+tmpNumber;
                        stringstream ss;
                        ss<<number;
                        string tmpstr;
                        ss>>tmpstr;
                        lexOutputStr.append("<56,"+tmpstr+","+sline+"\n");

                    }else
                    {
                     stringstream ss;
                     ss<<number;
                     string tmpstr;
                     ss>>tmpstr;
                     lexOutputStr.append("<1,"+tmpstr+","+sline+"\n");

                    }

             }else if(this->isLetter(code[i]))//letter
                {
                    string tmpstr="";
                    tmpstr+=code[i];

                    while(isLetter(code[i+1])||isNUmber(code[i+1])||('_'==code[i+1]))
                    {
                        tmpstr+=code[i+1];
                        i++;
                    }
                    this->keeped_words(tmpstr,sline);

                }else
                {
                    if(code[i]!='\n'&&code[i]!='\t')
                    {
                        lexOutputStr.append("invalid character:");
                        lexOutputStr+=code[i];
                        lexOutputStr.append(" in line "+sline+"\n");
                     //   qDebug()<<code[i];
                    }else if('\n'==code[i])
                    {
                        line++;
                        stringstream ss;
                        ss<<line;
                        ss>>sline;
                    }
                }

            }

         }

     }

 }

 void lex::keeped_words(string kWords,string sline)
 {
     if(kWords=="break")
         lexOutputStr.append("<12,_,"+sline+"\n");
     else if(kWords=="case")
         lexOutputStr.append("<13,_,"+sline+"\n");
     else if(kWords=="char")
         lexOutputStr.append("<14,char,"+sline+"\n");
     else if(kWords=="continue")
         lexOutputStr.append("<15,_,"+sline+"\n");
     else if(kWords=="default")
         lexOutputStr.append("<16,_,"+sline+"\n");
     else if(kWords=="do")
         lexOutputStr.append("<17,_,"+sline+"\n");
     else if(kWords=="double")
         lexOutputStr.append("<14,double,"+sline+"\n");
     else if(kWords=="else")
         lexOutputStr.append("<19,_,"+sline+"\n");
     else if(kWords=="float")
         lexOutputStr.append("<14,float,"+sline+"\n");
     else if(kWords=="for")
         lexOutputStr.append("<21,_,"+sline+"\n");
     else if(kWords=="if")
         lexOutputStr.append("<22,_,"+sline+"\n");
     else if(kWords=="int")
         lexOutputStr.append("<14,int,"+sline+"\n");
     else if(kWords=="long")
         lexOutputStr.append("<14,long,"+sline+"\n");
     else if(kWords=="return")
         lexOutputStr.append("<25,_,"+sline+"\n");
     else if(kWords=="short")
         lexOutputStr.append("<14,short,"+sline+"\n");
     else if(kWords=="sizeof")
         lexOutputStr.append("<27,_,"+sline+"\n");
     else if(kWords=="void")
         lexOutputStr.append("<14,void,"+sline+"\n");
     else if(kWords=="while")
         lexOutputStr.append("<29,_,"+sline+"\n");
     else
         lexOutputStr.append("<2,"+kWords+","+sline+"\n");

 }

 QString lex::get_lex_qstr()
 {
    lexOutputQStr=QString::fromLocal8Bit(lexOutputStr.c_str());
     return lexOutputQStr;
 }

 string lex::get_lex_str()
 {
     return lexOutputStr;
 }

 bool lex::isNUmber(char c)
 {
     if(c>=48&&c<=57)
         return true;
     else
         return false;

 }

 bool lex::isLetter(char c)
 {
     if((c>64&&c<91)||(c>96&&c<123))
         return true;
     else
         return false;

 }
