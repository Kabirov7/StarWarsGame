#ifndef STARWARS_VECTOR2D_H
#define STARWARS_VECTOR2D_H

// класс нужен чтобы можно было легко работать с расположениями каждого объекта в игре
// ничего кроме операций как в векторной алгебре он не имеет
class Vector2D {
public:
    Vector2D(float mX, float mY);

    float getX() const;

    void setX(float x);

    float getY() const;

    void setY(float y);

    float length();
    void normalize();

    Vector2D operator + (const Vector2D& v2) const {
        return Vector2D(m_x + v2.m_x, m_y + v2.m_y);
    }

    friend Vector2D& operator +=(Vector2D& v1,const Vector2D& v2 ){
        v1.m_x += v2.m_x;
        v1.m_y += v2.m_y;

        return v1;
    }

    Vector2D operator * (float scalar) const {
        return Vector2D(m_x * scalar, m_y * scalar);
    }


    Vector2D& operator *=(float scalar){
        m_x *= scalar;
        m_y *= scalar;

        return *this;
    }

    Vector2D operator - (const Vector2D& v2) const {
        return Vector2D(m_x - v2.m_x, m_y - v2.m_y);
    }

    friend Vector2D& operator -=(Vector2D& v1,const Vector2D& v2 ){
        v1.m_x -= v2.m_x;
        v1.m_y -= v2.m_y;

        return v1;
    }


    Vector2D operator / (float scalar) const {
        return Vector2D(m_x / scalar, m_y / scalar);
    }


    Vector2D& operator /=(float scalar){
        m_x /= scalar;
        m_y /= scalar;

        return *this;
    }

private:
    float m_x, m_y;
};


#endif
