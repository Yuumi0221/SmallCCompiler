#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Yuumi's Compiler");
    w.setWindowIcon(QIcon(":Yuumi.ico"));
    w.show();
    return a.exec();
}
