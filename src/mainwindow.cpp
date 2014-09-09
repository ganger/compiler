#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    lex *lexLoader=new lex;
    lexLoader->load(ui->inputText->toPlainText());
    ///
    meaning *m=new meaning;
  //  NodeReader *nr=new NodeReader;
   // ui->outputText->setPlainText(lexLoader->get_lex_qstr());
    ui->outputText->setPlainText(m->get_output());
}
