#include "Easy.h"
#include <QtWidgets/QApplication>
#include "Protocol.h"

int main(int argc, char *argv[])
{
    qDebug() << RawSolution::Protocol::Instance()->getUser("admin").name;
    RawSolution::Protocol::Instance()->addChatRoom("admin", "test");

    return 0;
}
