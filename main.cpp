#include "dialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.setFixedHeight(850);
    w.setFixedWidth(1050);
    w.setWindowFlags(w.windowFlags() | Qt::WindowMinimizeButtonHint );
    w.setWindowTitle("ice gobang");
    w.show();

    return a.exec();
}
