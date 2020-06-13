#include "Admin.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Admin w("localhost", 5307);
    w.show();
    return a.exec();
}
