#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "calculator.h"
#include <QMainWindow>
#include <iostream>
#include<queue>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ButtonGenerator_clicked();
    void on_pushButton_copy_clicked();

    void on_pushButton_saveAs_clicked();

private:
    int eval(const std::string& s);

    std::string decompose(int,char,std::string);
    void generate();
    void init1();//质数筛
    void init2();
    int precedenceCmp(char op1,char op2);
    bool haveOp(char op);
    void string_replace( std::string &strBig, const std::string &strsrc, const std::string &strdst);

    Ui::MainWindow *ui;
    int arithNum,opNum,printCol,minNum,maxNum;
    bool haveAdd,haveSub,haveMul,haveDiv,showAns;
    std::queue<char> q;
    char op[4] = {'+','*','-','/'};
    int isNotPrime[100];//0代表是质数
    //std::string preExpression;
    std::string InorderExpression;
    int opCnt;
    bool validArith;
    int ans;
    bool isLeaf;
    int tmpCol;
    struct Operator
    {
        int op;
        int precedence;
        int associativity;
        //左结合 用 'L'
        Operator(int opr, int prec, int assoc) :
            op(opr),
            precedence(prec),
            associativity(assoc)
        {}
    };
};

#endif // MAINWINDOW_H
