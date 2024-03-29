#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include"lex.h"
#include"yacc.h"
#include"meaning.h"
#include"code.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
