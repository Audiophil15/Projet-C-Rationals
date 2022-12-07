#ifndef RATIONALS_HPP
#define RATIONALS_HPP

#include <concepts>
#include <string>
#include <numeric>
#include <iostream>

template <typename T>
concept Integer = std::integral<T>;

template <typename T>
requires Integer<T>
class Rational{

	/** Class of rationals that work with any type of integer. It doesn't allow non integer types. */

	private:
		T numerator;
		T denominator;

	public:
		Rational(T num=0, T denom=1);

		T& num();
		T num() const;
		T& denom();
		T denom() const;

		bool operator ==(Rational<T> const & r) const;
		Rational<T> operator =(Rational<T> const & r) const;
		Rational<T> operator +(Rational<T> const & r) const;
		Rational<T> operator -(Rational<T> const & r) const;
		Rational<T> operator *(Rational<T> const & r) const;
		Rational<T> operator /(Rational<T> const & r) const;
		Rational<T> operator -() const;
};

/** Send to stream operator */

template<class T>
std::ostream& operator << (std::ostream& stream, const Rational<T> & r){
	stream << r.num() << "/" << r.denom();
	return stream;
}

/** Rational namespace for non-member functions */

namespace rational{

	template <typename T>
	Rational<T> simplify(Rational<T> r){
		/** Simplify any Rational using std::gcd() */
		int pgcd = std::gcd(r.num(), r.denom());
		if (pgcd != 1){
			return Rational<T>(r.num()/pgcd, r.denom()/pgcd);
		}
		return r;
	}

	template <typename T>
	Rational<T> inverse(Rational<T> r){
		/** Computes the inverse of any Rational */
		return Rational<T>(r.denom(), r.num());
	}

}

/** Constructor. Defaults parameters are 0 for the numerator and 1 for the denominator. */

template<typename T>
Rational<T>::Rational(T num, T denom){
	/** Constructor from two integers used as numerator and denominator */
	if(denom < 0){
		denom *= -1;
		num *= -1;
	}
	this->numerator = num;
	this->denominator = denom;
}

/** Getters and Setters*/

template<typename T>
T& Rational<T>::num(){
	/** Returns a reference to numerator */
	return this->numerator;
}

template<typename T>
T  Rational<T>::num() const{
	/** Returns a copy of the numerator */
	return this->numerator;
}

template<typename T>
T& Rational<T>::denom(){
	/** Returns a reference to denominator */
	return this->denominator;
}

template<typename T>
T  Rational<T>::denom() const{
	/** Returns a copy of the denominator */
	return this->denominator;
}

/** Operators */

template<typename T>
bool Rational<T>::operator ==(Rational<T> const & r) const{
	/** Compares field by field */
	return this->numerator == r.numerator && this->denominator == r.denominator;

}
template<typename T>
Rational<T> Rational<T>::operator =(Rational<T> const & r) const{
	/** Assigns field by field and returns also the parameter */
	this->numerator = r.numerator;
	this->denominator = r.denominator;
	return r;
}
template<typename T>
Rational<T> Rational<T>::operator +(Rational<T> const & r) const{
	/** Return the simplification of the sum */
	return rational::simplify(Rational<T>(this->numerator*r.denominator+r.numerator*this->denominator, this->denominator*r.denominator));
}
template<typename T>
Rational<T> Rational<T>::operator -(Rational<T> const & r) const{
	/** Returns the simplification of the difference */
	return rational::simplify(Rational<T>(this->numerator*r.denominator-r.numerator*this->denominator, this->denominator*r.denominator));
}
template<typename T>
Rational<T> Rational<T>::operator *(Rational<T> const & r) const{
	/** Returns the simplification of the product */
	return rational::simplify(Rational<T>(this->numerator*r.numerator, this->denominator*r.denominator));
}
template<typename T>
Rational<T> Rational<T>::operator /(Rational<T> const & r) const{
	/** Returns the simplification of the division. Multiplies the inverse */
	return (*this)*rational::inverse(r);
}
template<typename T>
Rational<T> Rational<T>::operator -() const{
	/** Negates the numerator */
	return Rational<T>(-this->numerator, this->denominator);
}

#endif