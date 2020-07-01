#include "Admin.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Admin w("localhost", 5308);
    w.show();
    return a.exec();
}
