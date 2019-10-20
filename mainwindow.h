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
    void decompose(int,char);
    void generate();
    void init1()
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
        preExpression = "";
        opCnt = 0;
    }
    Ui::MainWindow *ui;
    int arithNum,opNum,printCol,minNum,maxNum;
    bool haveAdd,haveSub,haveMul,haveDiv,showAns;
    std::queue<char> q;
    char op[4] = {'+','*','-','/'};
    int isNotPrime[100];//0代表是质数
    std::string preExpression;
    int opCnt;
};

#endif // MAINWINDOW_H
