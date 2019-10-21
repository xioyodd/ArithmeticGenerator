#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include "calculator.h"
#include <qtextcodec.h>




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//    QTextCodec *codec = QTextCodec::codecForName("GBK");
//    w.setWindowTitle(codec->toUnicode("四则运算算式生成器"));
    return a.exec();
}
