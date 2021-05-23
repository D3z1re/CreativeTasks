#include "graph.h"
#include <QApplication>
#include <QFile>
#include <queue>
#include <iostream>
#include <Windows.h>
using namespace std;


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    //Применение темы
    QFile styleSheetFile(":/styles/style_sheets/Style.qss");
    styleSheetFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(styleSheetFile.readAll());
    a.setStyleSheet(styleSheet);

    Graph w;
    w.show();
    return a.exec();
}
