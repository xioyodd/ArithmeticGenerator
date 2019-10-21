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

private:
    int eval(const std::string& s)
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
    std::string decompose(int,char,std::string);
    void generate();
    void init1()//质数筛
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
    void init2()
    {
        //preExpression = "";
        opCnt = 0;
        validArith = true;
        isLeaf = true;
    }
    int precedenceCmp(char op1,char op2)
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
    bool haveOp(char op){
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
    public:

    };
};

#endif // MAINWINDOW_H
