#include <QApplication>
#include <QDebug>
#include "gui/MainWindow.hpp"
#include "core/GaloisField.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    try {
        GaloisField gf8(8, 0x11D);
        qDebug() << "GF(2^8) Size:" << gf8.getFieldSize();
        qDebug() << "Add (0x57 + 0x83):" << gf8.add(0x57, 0x83);
        qDebug() << "Multiply (0x57 * 0x13):" << gf8.multiply(0x57, 0x13);
    } catch (const std::exception& e) {
        qDebug() << "Error:" << e.what();
    }

    MainWindow w;
    w.show();

    return app.exec();
}