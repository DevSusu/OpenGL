#ifndef _VEC_H_
#define _VEC_H_
template<typename T, int DIM>
class Vec {
public:
    Vec() {}
    
    Vec<T, DIM> operator+(const Vec& a) {
        Vec<T, DIM> temp;
        for (int i = 0; i<DIM; i++) {
            temp.val[i] = val[i] + a.val[i];
        }
        return temp;
    }
    Vec<T, DIM> operator-(const Vec& a) {
        Vec<T, DIM> temp;
        for (int i = 0; i<DIM; i++) {
            temp.val[i] = val[i] - a.val[i];
        }
        return temp;
    }
    Vec<T, DIM> operator*(const float& a) {
        Vec<T, DIM> temp;
        for (int i = 0; i<DIM; i++) {
            temp.val[i] = val[i] * a;
        }
        return temp;
    }
    Vec<T, DIM> operator/(const float& a) {
        Vec<T, DIM> temp;
        for (int i = 0; i<DIM; i++) {
            temp.val[i] = val[i] / a;
        }
        return temp;
    }
    
    //operator overloading
    Vec<T, DIM>& operator=(const Vec& a) {
        for (int i = 0; i<DIM; i++) {
            val[i] = a.val[i];
        }
        return *this;
    }
    Vec<T, DIM>& operator+=(const Vec& a) {
        *this = *this + a;
        return *this;
    }
    Vec<T, DIM>& operator-=(const Vec& a) {
        *this = *this - a;
        return *this;
    }
    
    
    T& operator[](const size_t i) {
        return val[i];
    }
    
    T val[DIM];
};
template<typename T, int DIM>
Vec<T, DIM> operator*(const float& s, const Vec<T, DIM>& v) {
    Vec<T, DIM> temp;
    for (int i = 0; i<DIM; i++) {
        temp.val[i] = s * v.val[i];
    }
    return temp;
}

template<typename T, int DIM>
T dotoperator(Vec<T, DIM> vec1, Vec<T, DIM> vec2) {
    T sum = 0;
    for (int i = 0; i<DIM; i++) {
        sum += vec1[i] * vec2[i];
    }
    return sum;
}

#endif