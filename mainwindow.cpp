#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include<cstdlib>
#include<queue>
#include"tnode.h"
#include<algorithm>
#include<sstream>
#include<QFileDialog>
#include<QTextStream>
#include<QMessageBox>
#include<ctime>

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

int MainWindow::eval(const std::string& s)
{
    try
    {
        int res = calculator::eval<int>(s);
        return res;
    }
    catch (calculator::error& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return -1;
}

void MainWindow::init1()
{
    int prime[100];

    int tot = 0;
    memset(isNotPrime, 0, sizeof(isNotPrime));
    for (int i = 2; i < 100; ++i)
    {
        if (!isNotPrime[i])
        {
            prime[tot++] = i;
        }
        for (int j = 0; j < tot; ++j)
        {
            if (i * prime[j] > 100)
            {
                break;
            }
            isNotPrime[i*prime[j]] = 1;
            if (i % prime[j] == 0)
            {
                break;
            }
        }
    }

}

void MainWindow::init2()
{
    //preExpression = "";
    opCnt = 0;
    validArith = true;
    isLeaf = true;
}

int MainWindow::precedenceCmp(char op1,char op2)
{//比较粗糙不严谨的比较方法基于左结合 a op1 b op2 c
    //必须从左到右
    if(op1 == '*' || op1 == '/')
        if(op2 == '+' || op2 == '-')
        return 1;
    //必须从右到左
    if(op1 == '+' || op1 == '-')
        if(op2 == '*' || op2 == '/')
            return -1;
    if(op1 == '-' && op2 == '+')
        return 1;
    return 0;
}
std::string MainWindow::decompose(int ans,char tmpOp, std::string tmpInorderExpression)
{
    //std::cout<<"dec"<<endl;
    if(opCnt>=opNum)
        validArith = true;
    else validArith = false;
    isLeaf = true;
    if(opCnt>=opNum)
    {
        isLeaf = true;
        tmpInorderExpression += std::to_string(ans);
        return tmpInorderExpression;
    }
    int a1=0,a2=0;
    if('+' == tmpOp)//ans = a1+a2
    {
        if(1==ans)
        {
            isLeaf = true;
            tmpInorderExpression += std::to_string(ans);
            return tmpInorderExpression;
        }
        a1 = rand()%(ans-1)+1;
        a2 = ans-a1;
    }
    if('-' == tmpOp)//ans = a1-a2
    {
        if(maxNum-1 == ans)
        {
            isLeaf = true;
            tmpInorderExpression += std::to_string(ans);
            return tmpInorderExpression;
        }
        a1 = rand()%(maxNum-ans-1)+1+ans;//大于ans的被减数
        a2 = a1-ans;
    }
    if('*' == tmpOp)
    {
        if(!isNotPrime[ans])    //ans是质数
        {   //no need to gen 1*n=n
            isLeaf = true;
            tmpInorderExpression += std::to_string(ans);
            return tmpInorderExpression;
        }
        while(true)
        {
            a1 = rand()%(ans-2)+2;
            if(ans%a1 ==0) break;
            //std::cout<<"likely loop death in *"<<std::endl;
        }
        a2 = ans/a1;
    }
    if('/' == tmpOp)//ans = a1/a2
    {
        if(ans>=maxNum/2)
        {
            isLeaf = true;
            tmpInorderExpression += std::to_string(ans);
            return tmpInorderExpression;
        }
        while(true)
        {
            a1 = rand()%(maxNum-ans-1)+1+ans;//大于ans的被除数
            if(a1%ans == 0) break;
            //std::cout<<"likely loop death in /"<<std::endl;
        }
        a2 = a1/ans;
    }

    opCnt++;
    char operator1;
    do{
        operator1 = op[rand()%4];//随机一个运算符
        //std::cout<<"likely loop death in op1 gen"<<std::endl;
    }while(!haveOp(operator1));
    std::string tmpin = decompose(a1,operator1,"");
    if(precedenceCmp(operator1,tmpOp)<0 && !isLeaf){
        tmpInorderExpression += "(";
        tmpInorderExpression += tmpin;
        tmpInorderExpression += ")";
    }
    else tmpInorderExpression += tmpin;

    tmpInorderExpression += tmpOp;

    char operator2;
    do{
        operator2 = op[rand()%4];//随机一个运算符
        //std::cout<<"likely loop death in op2 gen"<<std::endl;
    }while(!haveOp(operator2));
    tmpin = decompose(a2,operator2,"");
    if(precedenceCmp(tmpOp,operator2)>0 && !isLeaf){
        tmpInorderExpression += "(";
        tmpInorderExpression += tmpin;
        tmpInorderExpression += ")";
    }
    else tmpInorderExpression += tmpin;

    if(opCnt>=opNum)
        validArith = true;
    else validArith = false;
    isLeaf = false;
    return tmpInorderExpression;
}

bool MainWindow::haveOp(char op){
    switch(op){
    case '+':
        if(haveAdd) return true;
        break;
    case '-':
        if(haveSub) return true;
        break;
    case '*':
        if(haveMul) return true;
        break;
    case '/':
        if(haveDiv) return true;
        break;
    default:
        return false;
    }
    return false;
}
void MainWindow::string_replace( std::string &strBig, const std::string &strsrc, const std::string &strdst)
{
    std::string::size_type pos = 0;
    std::string::size_type srclen = strsrc.size();
    std::string::size_type dstlen = strdst.size();

    while( (pos=strBig.find(strsrc, pos)) != std::string::npos )
    {
        strBig.replace( pos, srclen, strdst );
        pos += dstlen;
    }
}
void MainWindow::generate()
{
    tmpCol = 0;
    ui->textEdit->clear();
    int totCnt=0;
    for(int i=0;i<arithNum;i++)
    {
        do{
            init1();
            init2();
            ans = rand()%(maxNum-1)+1;//随机一个答案
            char operator1;
            do{
                operator1 = op[rand()%4];//随机一个运算符
                //std::cout<<"likely loop death in op gen"<<std::endl;
               // std::cout<<operator1<<std::endl;
            }while(!haveOp(operator1));

            InorderExpression = decompose(ans,operator1,"");//分解
        }while(!validArith);

        std::string formatExpression;
        int totL = int(pow(double(maxNum),0.1)+1)*(opNum+2) + opNum + 12;
        string_replace(InorderExpression,"*","×");
        string_replace(InorderExpression,"/","÷");
        InorderExpression = to_string(++totCnt) + ". "+InorderExpression;
//        std_string_format(formatExpression,"%d",totL,InorderExpression);
//        formatExpression=format_string("%s",InorderExpression);
//        stringstream ss;
//        ss<<InorderExpression;
//        formatExpression = ss.str(totL);
        if( showAns)
            InorderExpression = InorderExpression + " = " + to_string(ans);
        InorderExpression.resize(totL,' ');
        QString nxt =QString::fromStdString(InorderExpression);
        nxt = nxt + "\t";
        tmpCol++;
        if(tmpCol>=printCol){
            tmpCol = 0;
            nxt = nxt + "\n";
        }
//        nxt.replace("*","×");
//        nxt.replace("/","÷");
        ui->textEdit->insertPlainText(nxt);
//        std::cout<<InorderExpression<<" = "<<ans<<std::endl;
        //getchar();
//        TNode *tree;
//        ExpTree3(tree,preExpression);
//        inOrder(tree);
    }
}

void MainWindow::on_ButtonGenerator_clicked()
{
    //开始计时
    time_t begTimer = time(0);
    arithNum = ui->spinBox_arithNum->value();
    opNum = ui->spinBox_opNum->value();
    printCol = ui->spinBox_printCol->value();
    minNum = ui->spinBox_min->value();
    maxNum = ui->spinBox_max->value();
    haveAdd = ui->checkBox_haveAdd->isChecked();
    haveSub = ui->checkBox_haveSub->isChecked();
    haveMul = ui->checkBox_haveMul->isChecked();
    haveDiv = ui->checkBox_haveDiv->isChecked();
    showAns = ui->checkBox_showAns->isChecked();
    ui->textEdit->setReadOnly(true);
    ui->textEdit->setLineWrapMode(QTextEdit::NoWrap);
//    ui->textEdit->setLineWrapColumnOrWidth(printCol);
//    std::cout<<arithNum<<"  "<<opNum<<" "<<printCol<<" "<<minNum<<" "<<maxNum
//            <<" "<<haveAdd<<" "<<haveSub<<" "<<haveMul<<" "<<haveDiv<<" "<<showAns<<std::endl;
    generate();
    //结束计时
    time_t endTimer = time(0);
    int timeUsed = int(endTimer - begTimer);
    std::string ss = "total time used: " + to_string(timeUsed) + "s";
    QString nxt = QString::fromStdString(ss);
    ui->textEdit->insertPlainText(nxt);
}

void MainWindow::on_pushButton_copy_clicked()
{
    ui->textEdit->selectAll();
    ui->textEdit->copy();
}

void MainWindow::on_pushButton_saveAs_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this,tr("另存"),tr(""),tr("文本文件(*.txt)"));
    if(filePath == "")
            return;
//        CurrentFilePath = filePath;
        QFile file(filePath);
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
//            ShowWarning_WhenSaveFailed();
//            CurrentFilePath = "";
            QMessageBox::warning(this,tr("错误"),tr("打开文件失败"));
            return;
        }
        QTextStream textStream(&file);
        textStream<<ui->textEdit->toPlainText();
        file.close();
}
