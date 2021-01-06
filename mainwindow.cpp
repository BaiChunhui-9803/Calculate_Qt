#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QString>
#include "Calculator.h"

Calculator cal;
int flag=0;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("Calculator"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{s+="1";
    ui->lineEdit->setText(s);
}

void MainWindow::on_pushButton_2_clicked()
{s+="2";
    ui->lineEdit->setText(s);
}

void MainWindow::on_pushButton_3_clicked()
{s+="3";
    ui->lineEdit->setText(s);
}

void MainWindow::on_pushButton_4_clicked()
{s+="4";
    ui->lineEdit->setText(s);
}

void MainWindow::on_pushButton_5_clicked()
{
    s+="5";
        ui->lineEdit->setText(s);
}

void MainWindow::on_pushButton_6_clicked()
{
    s+="6";
        ui->lineEdit->setText(s);
}

void MainWindow::on_pushButton_7_clicked()
{
    s+="7";
        ui->lineEdit->setText(s);
}

void MainWindow::on_pushButton_8_clicked()
{
    s+="8";
        ui->lineEdit->setText(s);
}

void MainWindow::on_pushButton_9_clicked()
{
    s+="9";
        ui->lineEdit->setText(s);
}

void MainWindow::on_pushButton_10_clicked()
{
    s+="0";
        ui->lineEdit->setText(s);
}

void MainWindow::on_pushButton_11_clicked()
{
    s+="+";
        ui->lineEdit->setText(s);
}

void MainWindow::on_pushButton_12_clicked()
{
    if(ui->lineEdit->text().isEmpty()){

    }
    else{
        if(cal.isWarning()){
            cal.handleWarning();
        }

        else{
            s+="=";
            ui->lineEdit->setText(s);
            ui->textEdit->append(s);//记住内存
            string exp = s.toStdString();
            ui->lineEdit->clear();
            result=cal.doIt(exp);
            if(result < 0.00001 && result > -0.00001){
                result = 0;
            }
            s=QString::number(result);
            ui->lineEdit->setText(s);
            ui->textEdit->append(s);
        }
    }
}

void MainWindow::on_pushButton_13_clicked()
{
    s+="-";
        ui->lineEdit->setText(s);
}

void MainWindow::on_pushButton_14_clicked()
{
    s+="*";
        ui->lineEdit->setText(s);
}

void MainWindow::on_pushButton_15_clicked()
{
    s+="/";
        ui->lineEdit->setText(s);
}

void MainWindow::on_pushButton_16_clicked()
{
    s+="(";
        ui->lineEdit->setText(s);
}

void MainWindow::on_pushButton_17_clicked()
{
    s+=")";
        ui->lineEdit->setText(s);
}

void MainWindow::on_pushButton_18_clicked()
{
    s+="sin";
        ui->lineEdit->setText(s);
}

void MainWindow::on_pushButton_19_clicked()
{
    s+="cos";
        ui->lineEdit->setText(s);
}

void MainWindow::on_pushButton_20_clicked()
{
    s+="tan";
        ui->lineEdit->setText(s);
}

void MainWindow::on_pushButton_21_clicked()
{
    s+="arcsin";
        ui->lineEdit->setText(s);
}

void MainWindow::on_pushButton_22_clicked()
{
    s+="arccos";
        ui->lineEdit->setText(s);
}

void MainWindow::on_pushButton_23_clicked()
{
    s+="arctan";
        ui->lineEdit->setText(s);
}

void MainWindow::on_pushButton_24_clicked()
{
    s+=".";
        ui->lineEdit->setText(s);
}

void MainWindow::on_pushButton_25_clicked()
{
    s+="^";
        ui->lineEdit->setText(s);
}

void MainWindow::on_pushButton_26_clicked()
{
    s+="sqrt";
        ui->lineEdit->setText(s);
}

void MainWindow::on_pushButton_27_clicked()
{
    s+="pi";
        ui->lineEdit->setText(s);
}

void MainWindow::on_pushButton_28_clicked()
{
    s=s.left(s.size()-1);
    ui->lineEdit->setText(s);
}


void MainWindow::on_pushButton_29_clicked()
{
     ui->lineEdit->clear();
     s=s.left(s.size()-s.size());
     ui->textEdit->clear();
}

void MainWindow::on_pushButton_30_clicked()
{
     s=s.left(s.size()-s.size());
     ui->lineEdit->clear();
}

void MainWindow::on_pushButton_31_clicked()
{
     s+="e";
     ui->lineEdit->setText(s);
}

void MainWindow::on_pushButton_32_clicked()
{
     s+="lg";
     ui->lineEdit->setText(s);
}

void MainWindow::on_pushButton_33_clicked()
{
     s+="ln";
     ui->lineEdit->setText(s);
}

void MainWindow::on_pushButton_34_clicked()
{
     s+="%";
     ui->lineEdit->setText(s);
}

void MainWindow::on_pushButton_35_clicked()
{
     s+="abs";
     ui->lineEdit->setText(s);
}

void MainWindow::on_lineEdit_returnPressed()
{
    on_pushButton_12_clicked();
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    s=ui->lineEdit->text();
}
