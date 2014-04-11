#ifndef LEX_H
#define LEX_H
#include<QString>
#include<string>
#include<QDebug>
#include<iostream>
#include<sstream>
using namespace std;
class lex
{
private:
    QString lexOutputQStr;
    string lexOutputStr;
public:
    lex();
    void load(QString srcCode);
    QString get_lex_qstr();
    string get_lex_str();
    void run(string code);
    void keeped_words(string kWords);
    bool isNUmber(char);
    bool isLetter(char);


};

#endif // LEX_H
