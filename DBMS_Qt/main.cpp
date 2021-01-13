#include "DBMS_Qt.h"
#include "qt_index.h"
#include <QtWidgets/QApplication>






int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DBMS_Qt w;
    qt_index qt_idx;
    w.p_toidx = &qt_idx;
    w.show();
    
    return a.exec();
}
