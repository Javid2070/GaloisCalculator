#include "./MainWindow.hpp"
#include "../core/GaloisField.hpp"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QMessageBox>

#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_gf(std::make_unique<GaloisField>(8, 0x11D)) // 1. Initialize GF(2^8) with AES polynomial
{
    setWindowTitle("Galois Field Calculator - GF(2^m)");
    resize(600, 400);

    setupUi(); // 2. Call setupUi to construct GUI elements
}

void MainWindow::setupUi() {
    auto *centralWidget = new QWidget(this);
    auto *mainLayout = new QVBoxLayout(centralWidget);

    // Input layout: [Input A] [ Operator ] [Input B]
    auto *inputLayout = new QHBoxLayout();
    
    m_inputA = new QLineEdit(this);
    m_inputA->setPlaceholderText("Val A (e.g. 0x57 or 87)");

    m_operatorCombo = new QComboBox(this);
    m_operatorCombo->addItems({"+", "-", "*", "/"});

    m_inputB = new QLineEdit(this);
    m_inputB->setPlaceholderText("Val B (e.g. 0x13 or 19)");

    inputLayout->addWidget(m_inputA);
    inputLayout->addWidget(m_operatorCombo);
    inputLayout->addWidget(m_inputB);

    // Calculate Button
    m_calcButton = new QPushButton("Calculate in GF(2^8)", this);

    // Result Display Label
    m_resultLabel = new QLabel("Result: -", this);
    m_resultLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #2b5c8f;");

    // Add elements to main layout
    mainLayout->addLayout(inputLayout);
    mainLayout->addWidget(m_calcButton);
    mainLayout->addWidget(m_resultLabel);

    setCentralWidget(centralWidget);

    // Connect Button click signal to slot function (Qt 5/6 syntax)
    connect(m_calcButton, &QPushButton::clicked, this, &MainWindow::onCalculateClicked);
}

void MainWindow::onCalculateClicked() {
    bool okA = false, okB = false;

    // Parse inputs (supports hex like "0x57" or decimal like "87")
    uint32_t valA = m_inputA->text().toUInt(&okA, 0);
    uint32_t valB = m_inputB->text().toUInt(&okB, 0);

    if (!okA || !okB) {
        QMessageBox::warning(this, "Input Error", "Please enter valid integers or Hex values (e.g., 0x57)!");
        return;
    }

    try {
        // Create GF elements (pass pointer using m_gf.get())
        GFElement a(valA, m_gf.get());
        GFElement b(valB, m_gf.get());
        GFElement res(0, m_gf.get());

        QString op = m_operatorCombo->currentText();

        // Perform calculation using overloaded operators
        if (op == "+") res = a + b;
        else if (op == "-") res = a - b;
        else if (op == "*") res = a * b;
        else if (op == "/") res = a / b;

        // Display results in Hex and Decimal
        m_resultLabel->setText(QString("Result: 0x%1 (%2)")
                                  .arg(res.value(), 2, 16, QChar('0')).toUpper()
                                  .arg(res.value()));

    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Calculation Error", e.what());
    }
}