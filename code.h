#ifndef CODE_H
#define CODE_H
#include<string>
#include<QList>
#include<fstream>
using namespace std;
struct Node
{
    int id;
    string content;

};
class NodeReader
{
public:
    NodeReader();
    QList<struct Node>* get_head();
private:
    QList<struct Node> *nodeList;

};

#endif // CODE_H
