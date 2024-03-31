#include <QApplication>
#include"mainwindow.h"
int main(int argc, char *argv[])
{

    /**
         * @brief creation d'un interface graphique et l'affiché
         */
        QApplication a(argc, argv);
        MainWindow w;
        w.show();
    return a.exec();
}
