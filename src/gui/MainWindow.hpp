#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <memory>
#include "core/GaloisField.hpp"

class QLineEdit;
class QPushButton;
class QLabel;
class QComboBox;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override = default;

private slots:
    // Slot function triggered when calculate button is clicked
    void onCalculateClicked();
    
private:
    void setupUi();

    // UI Widgets
    QLineEdit *m_inputA;
    QLineEdit *m_inputB;
    QComboBox *m_operatorCombo;
    QPushButton *m_calcButton;
    QLabel *m_resultLabel;

    // Galois Field instance declaration
    std::unique_ptr<GaloisField> m_gf;
};

#endif // MAINWINDOW_HPP