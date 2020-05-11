#include "MyClient.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyClient client("localhost", 3425);
    client.show();

    return a.exec();
}
