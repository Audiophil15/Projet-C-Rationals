#ifndef RATIONALS_HPP
#define RATIONALS_HPP

#include <concepts>
#include <string>
#include <numeric>
#include <iostream>
#include <math.h>

/// @brief concept which allows to filter types for the rationals, allowing only integer types
template <typename T>
concept Integer = std::integral<T>;

/*----------------------------------------------*/
/*              Class definition                */

/// @class Rational
/// @brief Class of rationals using int types
/// @tparam T can be any int types from the std : int8_t, int16_t, int32_t, int64_t, uint8_t, uint16_t, uint32_t, uint64_t
template <typename T>
requires Integer<T>
class Rational{

	/**
		Class of rationals that work with any type of integer. It doesn't allow non integer types.
	*/

	private:

		/// Numerator or the rational
		T numerator;
		/// Denominator or the rational
		T denominator;

	public:

		/// Constructor
		Rational(T num=0, T denom=1);

		/// Getter of the numerator
		T& num();
		/// Getter of the numerator
		T num() const;
		/// Getter of the denominator
		T& denom();
		/// Getter of the denominator
		T denom() const;

		/// operator ==
		bool operator ==(Rational const & r) const;
		/// operator ==
		bool operator ==(T n) const;

		/// operator <
		bool operator <(Rational const & r) const;
		/// operator <
		bool operator <(T n) const;

		/// operator >
		bool operator >(Rational const & r) const;
		/// operator >
		bool operator >(T n) const;

		/// operator <=
		bool operator <=(Rational const & r) const;
		/// operator <=
		bool operator <=(T n) const;

		/// operator >=
		bool operator >=(Rational const & r) const;
		/// operator >=
		bool operator >=(T n) const;

		/// operator !=
		bool operator !=(Rational const & r) const;
		/// operator !=
		bool operator !=(T n) const;


		/// operator =
		Rational operator = (Rational const & r);
		/// operator =
		Rational operator = (T n);

		/// operator +
		Rational operator + (Rational const & r) const;
		/// operator +
		Rational operator + (T n) const;

		/// operator - (binary)
		Rational operator - (Rational const & r) const;
		/// operator - (binary)
		Rational operator - (T n) const;

		/// operator - (unary)
		Rational operator - () const;

		/// operator *
		Rational operator * (Rational const & r) const;
		/// operator *
		Rational operator * (T n) const;

		/// operator /
		Rational operator / (Rational const & r) const;
		/// operator /
		Rational operator / (T n) const;

};

/*----------------------------------------------*/
/*  Rational namespace for non-member functions */

namespace rational{

	/// Simplify any Rational using std::gcd()
	/**
		If the gcd of the numerator and denominator is different than 1, returns a new Rational which values are the numerator and denominator of the given Rational divided by their gcd. Otherwise returns the given Rational.
    */
	template <typename T>
	Rational<T> simplify(Rational<T> r){
		int pgcd = std::gcd(r.num(), r.denom());
		if (pgcd != 1){
			return Rational<T>(r.num()/pgcd, r.denom()/pgcd);
		}
		return r;
	}

	/// Computes the inverse of any Rational
	/**
		Returns a new Rational of the same type with the inverse numerator and denominator.
	*/
	template <typename T>
	Rational<T> inverse(Rational<T> r){
		return Rational<T>(r.denom(), r.num());
	}

	/**
		Converts a floating point number in a rational of integers.
	*/
	template<typename T, typename U>
	static Rational<T> decimalToRational(U f){

		/*  a: continued fraction coefficients. */
		T num, denom;
		int a, h[3] = { 0, 1, 0 }, k[3] = { 1, 0, 0 };
		int x, d, n = 1;
		int i, neg = 0;
		int md = 10000;

		if (md <= 1) {
			denom = 1; num = (int) f;
		} else {
			if (f < 0) { neg = 1; f = -f; }

			while (f != floor(f)) { n <<= 1; f *= 2; }
			d = f;

			/* continued fraction and check denominator each step */
			for (i = 0; i < 64; i++) {
				a = n ? d / n : 0;
				if (i && !a) break;

				x = d; d = n; n = x % n;

				x = a;
				if (k[1] * a + k[0] >= md) {
					x = (md - k[0]) / k[1];
					if (x * 2 >= a || k[1] >= md)
						i = 65;
					else
						break;
				}

				h[2] = x * h[1] + h[0]; h[0] = h[1]; h[1] = h[2];
				k[2] = x * k[1] + k[0]; k[0] = k[1]; k[1] = k[2];
			}
			denom = k[1];
			num = neg ? -h[1] : h[1];
		}


		return Rational<T>(num, denom);
	}

	/// Inf constant
	template <typename T>
	static const Rational<T> inf = Rational<T>(1, 0);

}




/*----------------------------------------------*/
/*                 Constructor                  */

/**
	Constructor from two integers used as numerator and denominator. Defaults values are 0 for the numerator and 1 for the denominator.
*/
/// @param num : Numerator
/// @param denom : Denominator
template<typename T>
Rational<T>::Rational(T num, T denom){
	if(denom < 0){
		denom *= -1;
		num *= -1;
	}
	if (denom == 0){
		num = 1;
	}
	this->numerator = num;
	this->denominator = denom;
}





/*----------------------------------------------*/
/*            Getters and Setters               */

/**
	Returns a reference to numerator.
*/
template<typename T>
T& Rational<T>::num(){
	return this->numerator;
}

/**
	Returns a copy of the numerator.
*/
template<typename T>
T  Rational<T>::num() const{
	return this->numerator;
}

/**
	Returns a reference to denominator.
*/
template<typename T>
T& Rational<T>::denom(){
	return this->denominator;
}

/**
	Returns a copy of the denominator.
*/
template<typename T>
T  Rational<T>::denom() const{
	return this->denominator;
}





/*----------------------------------------------*/
/*             Operators (comparison)           */

/**
	Compares field by field.
*/
template<typename T>
bool Rational<T>::operator ==(Rational<T> const & r) const{
	return this->numerator == r.numerator && this->denominator == r.denominator;
}

/**
	Compares if denominator is 1, then compares the numerator with the paramater.
*/
template<typename T>
bool Rational<T>::operator ==(T n) const{
	return this->denom() == 1 && this.num() == n;
}

/**
	Compares the numerators once the rationals are set on the same denominator.
*/
template<typename T>
bool Rational<T>::operator <(Rational const & r) const{
	return this.num()*r.denom() < r.num()*this->denom();
}

/**
	Compares the numerator with n multiplied by the denominator.
*/
template<typename T>
bool Rational<T>::operator <(T n) const{
	return this.num() < n*this->denom();
}

/**
	Compares the numerators once the rationals are set on the same denominator.
*/
template<typename T>
bool Rational<T>::operator >(Rational const & r) const{
	return this.num()*r.denom() > r.num()*this->denom();
}

/**
	Compares the numerator with n multiplied by the denominator.
*/
template<typename T>
bool Rational<T>::operator >(T n) const{
	return this.num() > n*this->denom();
}

/**
	Use the previously defined operators
*/
template<typename T>
bool Rational<T>::operator <=(Rational const & r) const{
	return *(this) < r || *(this) == r;
}

/**
	Use the previously defined operators
*/
template<typename T>
bool Rational<T>::operator <=(T n) const{
	return *(this) < n || *(this) == n;
}

/**
	Use the previously defined operators
*/
template<typename T>
bool Rational<T>::operator >=(Rational const & r) const{
	return *(this) > r || *(this) == r;
}

/**
	Use the previously defined operators
*/
template<typename T>
bool Rational<T>::operator >=(T n) const{
	return *(this) > n || *(this) == n;
}

/**
	Negates the == operator
*/
template<typename T>
bool Rational<T>::operator !=(Rational const & r) const{
	return ! (*(this)==r);
}

/**
	Negates the == operator
*/
template<typename T>
bool Rational<T>::operator !=(T n) const{
	return ! (*(this) == n);
}


/*----------------------------------------------*/
/*   Operators (mathematical and assignative)   */

/**
	Assigns field by field and returns also the parameter.
*/
template<typename T>
Rational<T> Rational<T>::operator =(Rational<T> const & r){
	this->numerator = r.numerator;
	this->denominator = r.denominator;
	return r;
}

/**
	Assigns the given number to the numerator and 1 to the denominator.
*/
template<typename T>
Rational<T> Rational<T>::operator =(T n){
	this->numerator = n;
	this->denominator = (T)1;
	return *(this);
}

/**
	Return the sum (simplified).
*/
template<typename T>
Rational<T> Rational<T>::operator +(Rational<T> const & r) const{
	if (this->denom() == 0 || r.denom() == 0){
		return rational::inf<T>;
	}
	return rational::simplify(Rational<T>(this->numerator*r.denominator+r.numerator*this->denominator, this->denominator*r.denominator));
}

/**
	Return the sum (simplified).
*/
template<typename T>
Rational<T> Rational<T>::operator +(T n) const{
	if (this->denom() == 0){
		return rational::inf<T>;
	}
	Rational<T> r(n, 1);
	return rational::simplify(Rational<T>(this->numerator*r.denominator+r.numerator*this->denominator, this->denominator*r.denominator));
}

/**
	Returns the difference (simplified).
*/
template<typename T>
Rational<T> Rational<T>::operator -(Rational<T> const & r) const{
	if (this->denom() == 0 || r.denom() == 0){
		return rational::inf<T>;
	}
	return rational::simplify(Rational<T>(this->numerator*r.denominator-r.numerator*this->denominator, this->denominator*r.denominator));
}

/**
	Returns the difference (simplified).
*/
template<typename T>
Rational<T> Rational<T>::operator -(T n) const{
	if (this->denom() == 0){
		return rational::inf<T>;
	}
	Rational<T> r(n, 1);
	return rational::simplify(Rational<T>(this->numerator*r.denominator-r.numerator*this->denominator, this->denominator*r.denominator));
}

/**
	Returns the product (simplified).
*/
template<typename T>
Rational<T> Rational<T>::operator *(Rational<T> const & r) const{
	if (this->denom() == 0 || r.denom() == 0){
		return rational::inf<T>;
	}
	if (this->num() == 0 || r.num() == 0){
		return Rational<T>(1,1);
	}
	return rational::simplify(Rational<T>(this->numerator*r.numerator, this->denominator*r.denominator));
}

/**
	Returns the product (simplified).
*/
template<typename T>
Rational<T> Rational<T>::operator *(T n) const{
	if (this->denom() == 0 && n){
		return rational::inf<T>;
	}
	Rational<T> r(n, 1);
	return rational::simplify(Rational<T>(this->numerator*r.denominator+r.numerator*this->denominator, this->denominator*r.denominator));
}

/**
	Returns the division (simplified). Multiplies the inverse.
*/
template<typename T>
Rational<T> Rational<T>::operator /(Rational<T> const & r) const{
	return (*this)*rational::inverse(r);
}

/**
	Returns the division (simplified). Multiplies the inverse.
*/
template<typename T>
Rational<T> Rational<T>::operator /(T n) const{
	if (this->denom() == 0){
		return rational::inf<T>;
	}
	Rational<T> r(n, 1);
	return (*this)*rational::inverse(r);
}

/**
	Negates the numerator.
*/
template<typename T>
Rational<T> Rational<T>::operator -() const{
	return Rational<T>(-this->numerator, this->denominator);
}





/*----------------------------------------------*/
/*             "Outside" Operators              */

/**
	Send to stream operator.
*/
template<typename T>
std::ostream& operator << (std::ostream& stream, const Rational<T> & r){
	if (r.denom() == 0) {
		stream << "inf";
	} else {
		stream << r.num() << "/" << r.denom();
	}
	return stream;
}


/*   Operators (mathematical)   */

/// Division operator when the Rational is the second operand.
template<typename T>
Rational<T> operator / (const T x, const Rational<T> & r){
	return rational::simplify(Rational<T>(r.denom()*x, r.num()));
}

/// Multiplication operator when the Rational is the second operand.
template<typename T>
Rational<T> operator * (const T x, const Rational<T> & r){
	return rational::simplify(Rational<T>(r.num()*x, r.denom()));
}

/**
	Plus operator when the Rational is the second operand.
*/
template<typename T>
Rational<T> operator + (const T x, const Rational<T> & r){
	return rational::simplify(Rational<T>(x, 1)+r);
}

/**
	Minus operator when the Rational is the second operand.
*/
template<typename T>
Rational<T> operator - (const T x, const Rational<T> & r){
	return rational::simplify(Rational<T>(x, 1)-r);
}


/*   Operators (comparison)   */

/**
	Reverses the operands to use the member operator.
*/
template<typename T>
Rational<T> operator == (const T x, const Rational<T> & r){
	return r == x;
}

/**
	Reverses the operands to use the member operator.
*/
template<typename T>
Rational<T> operator != (const T x, const Rational<T> & r){
	return r != x;
}

/**
	Does the reverse comparison to use the member operator.
*/
template<typename T>
Rational<T> operator < (const T x, const Rational<T> & r){
	return r > x;
}

/**
	Does the reverse comparison to use the member operator.
*/
template<typename T>
Rational<T> operator > (const T x, const Rational<T> & r){
	return r < x;
}

/**
	Does the reverse comparison to use the member operator.
*/
template<typename T>
Rational<T> operator <= (const T x, const Rational<T> & r){
	return r >= x;
}

/**
	Does the reverse comparison to use the member operator.
*/
template<typename T>
Rational<T> operator >= (const T x, const Rational<T> & r){
	return r <= x;
}

#endif