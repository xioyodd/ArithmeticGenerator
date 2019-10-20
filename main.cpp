#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include "calculator.h"
#include <qtextcodec.h>




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
//    QTextCodec *codec = QTextCodec::codecForName("GBK");//修改这两行
//    w.setWindowTitle(codec->toUnicode("四则运算生成器"));
    w.show();
    return a.exec();
}
