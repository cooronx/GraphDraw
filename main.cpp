#include "maingraph.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainGraph mainGraph;
    mainGraph.show();
    return a.exec();
}
