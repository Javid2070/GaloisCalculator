# Galois Field $GF(2^8)$ GUI Calculator

A C++ GUI-based Galois Field calculator built with Qt and CMake. This tool provides arithmetic operations over the finite field $GF(2^8)$ using a fixed irreducible polynomial ($0x11D$).

## Features

- **Field Arithmetic:** Supports addition, subtraction, multiplication, and division over $GF(2^8)$.
- **Polynomial Representation:** Utilizes the fixed irreducible polynomial $p(x) = x^8 + x^4 + x^3 + x + 1$ (`0x11D`).
- **GUI Interface:** Simple interactive user interface created with Qt.
- **Cross-Platform Build:** Uses CMake for simple configuration and compilation across systems.

## Roadmap / Planned Features

- Support for custom irreducible polynomials.
- Operations over variable polynomials and arbitrary finite field sizes.
- Detailed step-by-step calculation logs.

## Building and Running

### Prerequisites

- **C++ Compiler:** Supporting C++17 or higher.
- **CMake:** Version 3.16 or higher.
- **Qt SDK:** Version 5.15 or Qt 6.x.

### Build Instructions

1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/galois-calculator.git
   cd galois-calculator
   ```

2. Create a build directory and configure CMake:
   ```bash
   mkdir build && cd build
   cmake ..
   ```

3. Build the project:
   ```bash
   cmake --build .
   ```

4. Run the application:
   ```bash
   ./GaloisCalculator
   ```

## License

This project is licensed under the MIT License - see the `LICENSE` file for details.