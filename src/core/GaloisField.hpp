#ifndef GALOISFIELD_HPP
#define GALOISFIELD_HPP

#include <cstdint>
#include <vector>
#include <stdexcept>

class GaloisField {
public:
    GaloisField(uint8_t m, uint32_t primitivePolynomial);

    ~GaloisField() = default;

    uint32_t add(uint32_t a, uint32_t b) const;
    uint32_t subtract(uint32_t a, uint32_t b) const;
    uint32_t multiply(uint32_t a, uint32_t b) const;
    uint32_t divide(uint32_t a, uint32_t b) const;
    uint32_t inverse(uint32_t a) const;
    uint32_t power(uint32_t base, int exp) const;

    // Getters
    uint8_t getM() const { return m_m; }
    uint32_t getFieldSize() const { return m_fieldSize; }

private:
    uint8_t m_m; // Degree of the field
    uint32_t m_primitivePolynomial; // Primitive polynomial for GF(2^m)
    uint32_t m_fieldSize; // Size of the field (2^m)

    void generateTables();

    std::vector<uint32_t> m_expTable; // Alpha / Anti-Log
    std::vector<uint32_t> m_logTable; // Logarithm
};

class GFElement {
public:
    GFElement(uint32_t val = 0, const GaloisField* field = nullptr) 
        : m_value(val), m_field(field) {}

    uint32_t value() const { return m_value; }

    // Overloading operators using pointer to field
    GFElement operator+(const GFElement& rhs) const {
        checkField(rhs);
        return GFElement(m_field->add(m_value, rhs.m_value), m_field);
    }

    GFElement operator-(const GFElement& rhs) const {
        checkField(rhs);
        return GFElement(m_field->subtract(m_value, rhs.m_value), m_field);
    }

    GFElement operator*(const GFElement& rhs) const {
        checkField(rhs);
        return GFElement(m_field->multiply(m_value, rhs.m_value), m_field);
    }

    GFElement operator/(const GFElement& rhs) const {
        checkField(rhs);
        return GFElement(m_field->divide(m_value, rhs.m_value), m_field);
    }

private:
    void checkField(const GFElement& rhs) const {
        if (!m_field || m_field != rhs.m_field) {
            throw std::invalid_argument("Operands must belong to the same non-null Galois Field.");
        }
    }

    uint32_t m_value;
    const GaloisField* m_field; // Using pointer to support default assignment operator
};

#endif // GALOISFIELD_HPP