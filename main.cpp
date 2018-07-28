#include "dialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.setFixedHeight(798);
    w.setFixedWidth(955);
    w.setWindowFlags(w.windowFlags() | Qt::WindowMinimizeButtonHint );
    w.setWindowTitle("ice gobang");
    w.show();

    return a.exec();
}
