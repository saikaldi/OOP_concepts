#include <iostream>
#include <cstring>

using namespace std;

class Fraction
{
private:
    int nominator;
    int denominator;

public:
    Fraction(int n, int d) : nominator(n), denominator(d) {}
    int getNominator()
    {
        return nominator;
    };
    int getDenominator()
    {
        return denominator;
    };
    void setNominator(int n)
    {
        nominator = n;
    };
    void setDenominator(int d)
    {
        denominator = d;
    };
    void print()
    {
        cout << "Nominator= " << nominator << "\n ";
        cout << "Denominator= " << denominator << "\n";
    };
    Fraction add(const Fraction &other) const
    {
        int newNumerator = (nominator * other.denominator) + (other.nominator * denominator);
        int newDenomenator = denominator * other.denominator;
        return Fraction(newNumerator, newDenomenator);
    };
};

int main()
{
    Fraction a(3, 4);
    Fraction b(2, 6);
    a.print();
    b.print();

    Fraction c = a.add(b);
    c.print();

    return 0;
};