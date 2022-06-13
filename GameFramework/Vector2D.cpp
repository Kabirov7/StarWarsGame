#include <cmath>
#include "Vector2D.h"

Vector2D::Vector2D(float x, float y) : m_x(x), m_y(y) {}

float Vector2D::getX() const {
    return m_x;
}

void Vector2D::setX(float x) {
    m_x = x;
}

float Vector2D::getY() const {
    return m_y;
}

void Vector2D::setY(float y) {
    m_y = y;
}

float Vector2D::length() {
    return sqrt(m_x * m_x + m_y * m_y);
}

void Vector2D::normalize() {
    float l = length();
    if (l > 0) {
        (*this) *= 1 / l;
    }
}
