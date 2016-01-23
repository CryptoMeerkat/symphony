#pragma once

#include <iostream>

class Vector2
{
    public:
        float x, y;

        Vector2() : Vector2(0.f, 0.f) { }

        Vector2(const float a, const float b)
        {
            x = a;
            y = b;
        }

        ~Vector2() {}

        inline void ToZero()
        {
            x = 0.f;
            y = 0.f;
        }

        inline float Length() const
        {
            return sqrt(LengthSqr());
        }

        //This is faster than Length() because `sqrt` is expensive
        inline float LengthSqr() const
        {
            return (x * x) + (y * y);
        }
    
        inline void Normalise()
        {
            float length = Length();

            if (length == 0.0f)
            {
                std::cerr << "Vector of zeroes can't be normalised" << std::endl;
                return;
            }

            *this /= length;
        }

        inline void Negate()
        {
            *this = -*this;
        }

    #pragma region Operators

        inline Vector2 operator-() const
        {
            return Vector2(-x, -y);
        }

        //http://en.cppreference.com/w/cpp/language/operators
        Vector2& operator+=(const Vector2& rhs) // compound assignment (does not need to be a member,
        {                                       // but often is, to modify the private members)
            this->x += rhs.x;
            this->y += rhs.y;

            return *this; // return the result by reference
        }

        Vector2& operator-=(const Vector2& rhs) // compound assignment (does not need to be a member,
        {                                       // but often is, to modify the private members)
            this->x -= rhs.x;
            this->y -= rhs.y;

            return *this; // return the result by reference
        }

        Vector2& operator*=(const float& rhs)
        {
            this->x *= rhs;
            this->y *= rhs;

            return *this;
        }

        Vector2& operator/=(const float& rhs)
        {
            //TO-DO: This should take into account floating-point precission and stuff...
            if (rhs == 0.0f)
            {
                std::cerr << "Cannot divide by zero" << std::endl;
                return *this;
            }

            this->x /= rhs;
            this->y /= rhs;

            return *this;
        }

        Vector2& operator=(const Vector2& rhs)
        {
            this->x = rhs.x;
            this->y = rhs.y;

            return *this;
        }

    
        //TO-DO: Check if it'd be faster to store the elements of the vector as an array
        float operator[](unsigned int index)
        {
            if (index > 1)
                index %= 2;

            if (index == 0)
                return x;
            if (index == 1)
                return y;
        }




        inline friend std::ostream& operator<<(std::ostream& o, const Vector2& v)
        {
            o << "Vector2(" << v.x << "," << v.y << ")" << std::endl;
            return o;
        }

        // friends defined inside class body are inline and are hidden from non-ADL lookup
        friend Vector2 operator+(Vector2 lhs,        // passing lhs by value helps optimize chained a+b+c
                                 const Vector2& rhs) // otherwise, both parameters may be const references.
        {
            lhs += rhs;
            return lhs;
        }

        friend Vector2 operator-(Vector2 lhs, const Vector2& rhs)
        {
            lhs -= rhs;
            return lhs;
        }

        friend Vector2 operator*(Vector2 lhs, const float& rhs)
        {
            lhs *= rhs;
            return lhs;
        }

        friend Vector2 operator/(Vector2 lhs, const float& rhs)
        {
            lhs /= rhs;
            return lhs;
        }

        friend bool operator==(const Vector2& lhs, const Vector2& rhs)
        {
            return lhs.x == rhs.x && lhs.y == rhs.y;
        }

        friend bool operator!=(const Vector2& lhs, const Vector2& rhs)
        {
            return lhs.x != rhs.x || lhs.y != rhs.y;
        }

    #pragma endregion




    #pragma region Static Functions

        static Vector2 Zero()
        {
            return Vector2(0.0f, 0.0f);
        }

        static Vector2 One()
        {
            return Vector2(1.0f, 1.0f);
        }

        static float Dot(const Vector2 &a, const Vector2 &b)
        {
            return (a.x * b.x) + (a.y * b.y);
        }

    #pragma endregion

};