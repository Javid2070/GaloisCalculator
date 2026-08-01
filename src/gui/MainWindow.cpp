#include "gui/MainWindow.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    setWindowTitle("Galois Field Calculator - GF(2^m)");
    resize(600, 400);
}