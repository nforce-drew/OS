#include "MyClient.h"
#include <QApplication>
#include <QStyle>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyClient client("localhost", 5307);
    client.resize(1350,850);
       client.setGeometry(
           QStyle::alignedRect(
               Qt::LeftToRight,
               Qt::AlignCenter,
               client.size(),
               a->screenAt(client.pos())->availableGeometry()
           )
       );
    client.show();

    return a.exec();
}
