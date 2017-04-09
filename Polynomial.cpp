// Tin Huynh
// Homework 5
// Completed 11/12/2015

#include "Polynomial.h"
#include <cstring>
#include <sstream>
#include <cmath>

Polynomial::Polynomial() : coeff(new double[1]), size(1)
{
	coeff[0] = 0;
}

Polynomial::Polynomial(double* arr, int arrsize) : coeff(new double[arrsize]), size(arrsize)
{
	for (int i = 0; i < arrsize; i++){
		coeff[i] = arr[i];
	}
}

Polynomial::Polynomial(const Polynomial& other){
	size = other.size;
	coeff = new double[size];
	for (int i = 0; i < size; i++){
		coeff[i] = other.coeff[i];
	}
}

Polynomial::Polynomial(int x) : coeff(new double[1]), size(1)
{
	coeff[0] = (double) x;
}

Polynomial::Polynomial(double x) : coeff(new double[1]), size(1)
{
	coeff[0] = x;
}

Polynomial& Polynomial::operator=(const Polynomial& right){ 
	if (this == &right){
		return *this;
	}
	if (coeff != nullptr){
		delete [] coeff;
	}
	size = right.size;
	coeff = new double[right.size];
	for (int i = 0; i < size; i++){
		coeff[i] = right.coeff[i];
	}
	return *this;
}

Polynomial::~Polynomial()
{
	if (coeff != nullptr)
        delete [] coeff;
    coeff = nullptr;
    size = 0;
}

int Polynomial::getSize() const{
	return size;
}

int Polynomial::degree() const{
	int degree = 0;
	for (int i = 0; i < size; i ++){
		if (coeff[i] != 0){
			degree = i;
		}
	}
	return degree;
}

std::string Polynomial::str() const{
	Polynomial p(*this);
    std::stringstream s;
	for (int i = p.degree(); i >= 0; i--){
		if (i == p.degree()){
			if (p.coeff[i] != 0 && i > 1)
			{
				if (p.coeff[i] != 1 && p.coeff[i] != -1)
				{
					s << p.coeff[i];  
				}
				if (p.coeff[i] == -1){
					s << "-";
				}
				s << "x^" << i; 
			}
			else if (p.coeff[i] != 0 && i == 1){
				if (p.coeff[i] != 1 && p.coeff[i] != -1)
				{
					s << p.coeff[i]; 
				}
				if (p.coeff[i] == -1){
					s << "-";
				}
				s << "x";
			}
			else {
				s << p.coeff[i];
			}
		}
		else{
			if (p.coeff[i] > 0){
				s << " + ";
				if (p.coeff[i] != 1){
					s << p.coeff[i];
				}
			}
			if (p.coeff[i] < 0){
				s << " - ";
				if (p.coeff[i] != -1){
					s << -(p.coeff[i]);
				}
			}
			if (p.coeff[i] != 0)
			{
				if (i > 1){
					s << "x^" << i;
				}
				if (i == 1){
					s << "x";
				} 
			}
		}
	}
    return s.str();
}

double Polynomial::solve(double x) const{
	double result = 0;
	for (int i = this->degree(); i >= 0; i--){
		result += coeff[i] * pow(x,i);
	}
	return result;
}

double& Polynomial::operator[](int index){
	if (index >= size){
		double* arr = new double[index + 1];
		for (int i = 0; i < index + 1; i++){
			arr[i] = 0;
		}
		for (int i = 0; i <= this->degree(); i++){
			arr[i] = coeff[i];
		}
		delete[] coeff;
		size = index + 1;
		coeff = arr;
		
	}
	return coeff[index];
}

inline int max( int x, int y ){
	return x > y ? x : y;
}

Polynomial Polynomial::operator+(const Polynomial& right) const{
	Polynomial result;
	int highestdegree = max(this->degree(),right.degree());
	result.size = highestdegree+1;
	result.coeff = new double[result.size];
	for (int i = 0; i < result.size; i++){
		result.coeff[i] = 0;
	}
	for (int i = 0; i <= this->degree(); i++){
		result.coeff[i] = coeff[i];
	}
	for (int i = 0; i <= right.degree(); i++){
		result.coeff[i] += right.coeff[i];
	}
	return result;
}

Polynomial Polynomial::operator-(const Polynomial& right) const{
	Polynomial result;
	int highestdegree = max(this->degree(),right.degree());
	result.size = highestdegree+1;
	result.coeff = new double[result.size];
	for (int i = 0; i < result.size; i++){
		result.coeff[i] = 0;
	}
	for (int i = 0; i <= this->degree(); i++){
		result.coeff[i] = coeff[i];
	}
	for (int i = 0; i <= right.degree(); i++){
		result.coeff[i] -= right.coeff[i];
	}
	return result;
}

Polynomial Polynomial::operator*(const Polynomial& right) const{
    
	Polynomial result;
	int highestdegree = this->degree() + right.degree();
	result.size = highestdegree + 1;
	result.coeff = new double[result.size];
	for (int i = 0; i < result.size; i++){
		result.coeff[i] = 0;
	}
	for( int i = 0; i <= this->degree(); i++ ){
		for( int j = 0; j <= right.degree(); j++ ){
			result.coeff[i + j] += coeff[i] * right.coeff[ j ];
		}
	}
	return result;
}

Polynomial Polynomial::operator*(const double x) const {
	Polynomial result;
	result.size = size;
	result.coeff = new double[result.size];
	for (int i = 0; i < result.size; i++){
		result.coeff[i] = coeff[i] * x;
	}
	return result;
}

Polynomial& Polynomial::operator+=(const Polynomial& right){
	*this = (*this) + right;
	return *this;
}

Polynomial& Polynomial::operator-=(const Polynomial& right){
	*this = (*this) - right;
	return *this;
}

Polynomial& Polynomial::operator*=(const Polynomial& right){
	*this = (*this) * right;
	return *this;
}

bool Polynomial::operator==(const Polynomial& right) const{
	if (this->degree() != right.degree())
        return false;

	for (int i = 0; i <= this->degree(); i++)
    {
		if (coeff[i] != right.coeff[i])
        {
            return false;
        }
    }
    return true;
}

bool Polynomial::operator!=(const Polynomial& right) const{
	return !((*this) == right);
}

std::ostream& operator<<(std::ostream& os, const Polynomial& p)
{
    os << p.str();
    return os;
}

