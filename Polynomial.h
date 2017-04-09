// Tin Huynh
// Homework 5
// Completed 11/12/2015

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include <iostream>
#include <string>

class PolyTester;
class Polynomial
{
	friend class PolyTester;
private:
	double* coeff;
	int size;
public:
	Polynomial();
	Polynomial(double* arr, int arrsize);
	Polynomial(const Polynomial& other);
	Polynomial(int x);
	Polynomial(double x);
	Polynomial& operator=(const Polynomial& right);
	~Polynomial();

	int getSize() const;
	int degree() const;
	std::string str() const;
	double solve(double x) const;
	double& operator[](int index);
	Polynomial operator+(const Polynomial& right) const;
	Polynomial operator-(const Polynomial& right) const;
	Polynomial operator*(const Polynomial& right) const;
	Polynomial operator*(const double x) const;
	Polynomial& operator+=(const Polynomial& right);
	Polynomial& operator-=(const Polynomial& right);
	Polynomial& operator*=(const Polynomial& right);
	bool operator==(const Polynomial& right) const;
	bool operator!=(const Polynomial& right) const;

};
std::ostream& operator<<(std::ostream& os, const Polynomial& s);
#endif