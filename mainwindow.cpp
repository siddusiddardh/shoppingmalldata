#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTableWidget>
#include<QFile>
#include<QTextStream>
#include<QIntValidator>
#include<QMessageBox>
int row=0;
int i;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->tableWidget,SIGNAL(cellDoubleClicked(int,int)),
                    this,SLOT(on_doubleclicked(int,int)));

    //ui->lineEdit_2->setValidator( new QIntValidator(0,100,this));
    ui->lineEdit->setValidator(new QRegExpValidator( QRegExp("[A-Z a-z0-9_]*"), this ));
    ui->lineEdit_2->setValidator(new QRegExpValidator( QRegExp("[0-9_]*"), this ));
    ui->lineEdit_3->setValidator(new QDoubleValidator(0.0, 5.0, 3));
   // ui->lineEdit_3->setValidator(new QRegExpValidator( QRegExp("[0-9]*.?[0-9]*"), this ));

    QDoubleValidator *credit=new QDoubleValidator(this);
    ui->lineEdit_4->setValidator(credit);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    row++;



    QString name =ui->lineEdit->text();
    QString volume =ui->lineEdit_2->text();
    QString market =ui->lineEdit_3->text();
    QString credit =ui->lineEdit_4->text();
    if(name.isEmpty()||volume.isEmpty()||market.isEmpty()||credit.isEmpty())
    {
        QMessageBox::warning(this,"Error","fill all blocks");
    }
else
    {
     ui->tableWidget->insertRow(ui->tableWidget->rowCount());
     i=ui->tableWidget->rowCount()-1;

     ui->tableWidget->setItem(i,0,new QTableWidgetItem(name));
     ui->tableWidget->setItem(i,1,new QTableWidgetItem(volume));
     ui->tableWidget->setItem(i,2,new QTableWidgetItem(market));
     ui->tableWidget->setItem(i,3,new QTableWidgetItem(credit));

     ui->lineEdit->setText("");
     ui->lineEdit_2->setText("");
     ui->lineEdit_3->setText("");
     ui->lineEdit_4->setText("");
}
}

void MainWindow::on_pushButton_2_clicked()
{
    row--;
    ui->tableWidget->setRowCount(row);

}

void MainWindow::on_pushButton_3_clicked()
{
    int row,col;
    QString info;
    QFile fp("/home/siddu/Desktop/dolatcapital.csv");
    if(fp.open(QFile::ReadOnly|QFile::Append))
    {
        info=fp.readAll();
    }
    QTextStream out(&fp);
    for(row=0;row<=i;row++)
    {
        for(col=0;col<4;col++)
        {
         out<<ui->tableWidget->item(row,col)->text()<<",";
         fp.flush();
        }
         //out<<ui->tableWidget->item(row,1)->text()<<",";
         //out<<ui->tableWidget->item(row,2)->text()<<",";
         //out<<ui->tableWidget->item(row,3)->text()<<",";
         out<<"\n";
         fp.flush();

    }
    fp.close();
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    ui->lineEdit_3->setText("");
    ui->lineEdit_4->setText("");
}


void MainWindow::on_doubleclicked(int row,int)
{
QString i=ui->tableWidget->item(row,0)->text();
ui->lineEdit->setText(i);

i=ui->tableWidget->item(row,1)->text();
ui->lineEdit_2->setText(i);

i=ui->tableWidget->item(row,2)->text();
ui->lineEdit_3->setText(i);

i=ui->tableWidget->item(row,3)->text();
ui->lineEdit_4->setText(i);
}
