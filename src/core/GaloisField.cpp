#include "core/GaloisField.hpp"

// Galois Field logic will go here

GaloisField::GaloisField(uint8_t m, uint32_t primitivePolynomial) : m_m(m), m_primitivePolynomial(primitivePolynomial), m_fieldSize(1 << m) {
    if (m == 0 || m > 16) {
        throw std::invalid_argument("m must be between 1 and 16.");
    }
    generateTables();
}

void GaloisField::generateTables() {
    m_expTable.resize(m_fieldSize * 2, 0);
    m_logTable.resize(m_fieldSize, 0);

    uint32_t x = 1;
    for (size_t i = 0; i < m_fieldSize - 1; ++i) {
        m_expTable[i] = x;
        m_logTable[x] = static_cast<uint32_t>(i);
        
        x <<= 1;
        if (x & m_fieldSize) {
            x ^= m_primitivePolynomial;
        }
    }

    for (size_t i = m_fieldSize - 1; i < m_fieldSize * 2 - 1; ++i) {
        m_expTable[i] = m_expTable[i - (m_fieldSize - 1)];
    }
}

uint32_t GaloisField::add(uint32_t a, uint32_t b) const {
    return a ^ b;
}

uint32_t GaloisField::subtract(uint32_t a, uint32_t b) const {
    return add(a, b); // In GF(2^m), addition and subtraction are the same
}

uint32_t GaloisField::multiply(uint32_t a, uint32_t b) const {
    if (a == 0 || b == 0) return 0;
    return m_expTable[m_logTable[a] + m_logTable[b]];
}

uint32_t GaloisField::divide(uint32_t a, uint32_t b) const {
    if (b == 0) throw std::invalid_argument("Division by zero in GF");
    if (a == 0) return 0;
    
    int logSum = static_cast<int>(m_logTable[a]) - static_cast<int>(m_logTable[b]);
    if (logSum < 0) {
        logSum += static_cast<int>(m_fieldSize - 1);
    }
    return m_expTable[logSum];
}

uint32_t GaloisField::inverse(uint32_t a) const {
    if (a == 0) throw std::invalid_argument("Zero has no multiplicative inverse");
    return m_expTable[(m_fieldSize - 1) - m_logTable[a]];
}

uint32_t GaloisField::power(uint32_t base, int exp) const {
    if (base == 0) return 0;
    if (exp == 0) return 1;
    
    int logVal = (static_cast<int>(m_logTable[base]) * exp) % static_cast<int>(m_fieldSize - 1);
    if (logVal < 0) logVal += (m_fieldSize - 1);
    return m_expTable[logVal];
}