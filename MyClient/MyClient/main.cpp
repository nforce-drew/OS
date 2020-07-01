#include "MyClient.h"
#include <QApplication>
#include <QStyle>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyClient client("localhost", 5308);
//    client.show();

    return a.exec();
}
