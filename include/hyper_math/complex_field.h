#pragma once

class ComplexV{
private:
    double a;
    double b;
public:
    ComplexV(double, double);

    void set_re(double);
    void set_im(double);
    double re() const;
    double im() const;

    ComplexV operator+(const ComplexV&);
    ComplexV operator-(const ComplexV&);
    ComplexV operator*(const ComplexV&);
    ComplexV operator/(const ComplexV&);
    bool operator=(const ComplexV&);
};
