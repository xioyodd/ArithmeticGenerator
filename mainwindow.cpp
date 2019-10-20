#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include<cstdlib>
#include<queue>
#include"tnode.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::decompose(int ans,char tmpOp)
{
    std::cout<<"dec"<<endl;

    if(opCnt>=opNum)
    {

        preExpression += std::to_string(ans);
        return;
    }
    if('+' == tmpOp)//ans == a1+a2
    {
        if(1==ans)
        {
            preExpression += std::to_string(ans);
            return;
        }
        int a1 = rand()%(ans-1)+1;
        int a2 = ans-a1;
        preExpression += tmpOp;
        opCnt++;
        char operator1 = op[rand()%4];//随机一个运算符
        decompose(a1,operator1);
        char operator2 = op[rand()%4];
        decompose(a2,operator2);
    }
    if('-' == tmpOp)//ans = a1-a2
    {
        if(99 == ans)
        {
            preExpression += std::to_string(ans);
            return;
        }
        int a1 = rand()%(maxNum-ans-1)+1+ans;//大于ans的被减数
        int a2 = a1-ans;
        preExpression += tmpOp;
        opCnt++;
        char operator1 = op[rand()%4];//随机一个运算符
        decompose(a1,operator1);
        char operator2 = op[rand()%4];
        decompose(a2,operator2);
    }
    if('*' == tmpOp)
    {
        if(!isNotPrime[ans])    //ans是质数
        {
            preExpression += std::to_string(ans);
            return;
        }
        int a1;
        while(true)
        {
            a1 = rand()%(ans-3)+2;
            if(ans%a1 ==0) break;
        }
        int a2 = ans/a1;
        preExpression += tmpOp;
        opCnt++;
        char operator1 = op[rand()%4];//随机一个运算符
        decompose(a1,operator1);
        char operator2 = op[rand()%4];
        decompose(a2,operator2);
    }
    if('/' == tmpOp)
    {
        if(ans>=50)
        {
            preExpression += std::to_string(ans);
            return;
        }
        int a1;
        while(true)
        {
            a1 = rand()%(maxNum-ans-1)+1+ans;//大于ans的被除数
            if(a1%ans == 0) break;
        }
        int a2 = a1/ans;
        preExpression += tmpOp;
        opCnt++;
        char operator1 = op[rand()%4];//随机一个运算符
        decompose(a1,operator1);
        char operator2 = op[rand()%4];
        decompose(a2,operator2);
    }
    return;
}

void MainWindow::generate()
{

    for(int i=0;i<arithNum;i++)
    {
        init2();
        int ans = rand()%(maxNum-1)+1;//随机一个答案
        char operator1 = op[rand()%4];//随机一个运算符
        decompose(ans,operator1);//分解
        std::cout<<preExpression<<endl;
        //getchar();
//        TNode *tree;
//        ExpTree3(tree,preExpression);
//        inOrder(tree);
    }
}

void MainWindow::on_ButtonGenerator_clicked()
{
//    arithNum = ui->spinBox_arithNum->value();
//    opNum = ui->spinBox_opNum->value();
//    printCol = ui->spinBox_printCol->value();
//    minNum = ui->spinBox_min->value();
//    maxNum = ui->spinBox_max->value();
//    haveAdd = ui->checkBox_haveAdd->isChecked();
//    haveSub = ui->checkBox_haveSub->isChecked();
//    haveMul = ui->checkBox_haveMul->isChecked();
//    haveDiv = ui->checkBox_haveDiv->isChecked();
//    showAns = ui->checkBox_showAns->isChecked();
//    std::cout<<arithNum<<"  "<<haveAdd<<std::endl;
    arithNum = 10;
    opNum = 3;
    maxNum = 100;
    generate();
}

