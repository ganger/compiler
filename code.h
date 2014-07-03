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
    string sline;

};
struct PredictTable
{
    int inputId;
    int matchingId;
    QList<int> changingNode;

};
class NodeReader
{
public:
    NodeReader();
    QList<struct Node>* get_head();
    void initial_predict_table();
    QList<struct PredictTable>* get_tablelist();
private:
    QList<struct Node> *nodeList;
    QList<struct PredictTable> *tableList;

};

#endif // CODE_H
