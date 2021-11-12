#include "mainwindow.h"
#include "iostream"
#include <QApplication>

int main(int argc, char *argv[])
{std::cout << "cox";
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
