#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include<cstdlib>
#include<queue>
#include"tnode.h"
#include<algorithm>
#include<sstream>

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
void string_replace( std::string &strBig, const std::string &strsrc, const std::string &strdst)
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
std::string & std_string_format(std::string & _str, const char * _Format, ...) {
    std::string tmp;

    va_list marker = NULL;
    va_start(marker, _Format);

    size_t num_of_chars = _vscprintf(_Format, marker);

    if (num_of_chars > tmp.capacity()) {
        tmp.resize(num_of_chars + 1);
    }

    vsprintf_s((char *)tmp.data(), tmp.capacity(), _Format, marker);

    va_end(marker);

    _str = tmp.c_str();
    return _str;
}
template <typename ...Args>
inline std::string format_string(const char* format, Args... args)
{ constexpr size_t oldlen = BUFSIZ; char buffer[oldlen]; // 默认栈上的缓冲区
    size_t newlen = snprintf(&buffer[0], oldlen, format, args...); newlen++;
    // 算上终止符'\0'
    if (newlen > oldlen) { // 默认缓冲区不够大，从堆上分配
        std::vector<char> newbuffer(newlen); snprintf(newbuffer.data(), newlen, format, args...);
        return std::string(newbuffer.data()); } return buffer; }

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
        int totL = int(sqrt(double(maxNum))+1)*(opNum+2) + opNum;
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
        InorderExpression.resize(totL/2,' ');
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
        std::cout<<InorderExpression<<" = "<<ans<<std::endl;
        //getchar();
//        TNode *tree;
//        ExpTree3(tree,preExpression);
//        inOrder(tree);
    }
}

void MainWindow::on_ButtonGenerator_clicked()
{
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
}

void MainWindow::on_pushButton_copy_clicked()
{
    ui->textEdit->selectAll();
    ui->textEdit->copy();
}
