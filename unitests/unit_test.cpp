#include <tuple>
#include <vector>
#include <limits>
#include <iostream>
#include <typeinfo>
#include <type_traits>
#include <gtest/gtest.h>
#include <gtest/gtest-spi.h>

#include "Rationals.hpp"

// template <typename T>

// By class fixture
template <typename T>
class RationalsTest :public testing::Test {
	protected :

	RationalsTest(){};

	std::vector<T> inputNum;
	std::vector<T> inputDenom;
	std::vector<T> expectedNum;
	std::vector<T> expectedDenom;

	void defaultConstructorIsZeroTest(){
		Rational<T> r;
		EXPECT_EQ(r.num(), 0) << "Numerator : " << r.num() << ", expected 0 !";
		EXPECT_EQ(r.denom(), 1) << "Denominator : " << r.denom() << ", expected 1 !";
	}

	void singleValueConstructorTest(T innum, T expectedNum){
		Rational<T> r(innum);
		EXPECT_EQ(r.num(), expectedNum) << "Inputs : " << innum << ", " << expectedNum;
		EXPECT_EQ(r.denom(), 1) << "Inputs : " << innum << ", " << expectedNum;
	}

	void twoValuesConstructorTest(T innum, T indenom, T expectedNum, T expectedDenom){
		Rational<T> r(innum, indenom);
		EXPECT_EQ(r.num(), expectedNum) << "Inputs : " << innum << ", " << indenom << ", " << expectedNum << ", " << expectedDenom;
		EXPECT_EQ(r.denom(), expectedDenom) << "Inputs : " << innum << ", " << indenom << ", " << expectedNum << ", " << expectedDenom;
	}

	void verifyValues(Rational<T> r, T expectedNum, T expectedDenom){
		EXPECT_EQ(r.num(), expectedNum) << "r = " << r << " != " << expectedNum << ", " << expectedDenom;
		EXPECT_EQ(r.denom(), expectedDenom) << "r = " << r << " != " << expectedNum << ", " << expectedDenom;
	}

};

using Integers = ::testing::Types<int8_t, int16_t, int32_t, int64_t, uint8_t, uint16_t, uint32_t, uint64_t>;

TYPED_TEST_SUITE(RationalsTest, Integers);

	/** Test about all constructors */

TYPED_TEST(RationalsTest, DefaultConstructorIsZeroTest){

	RationalsTest<TypeParam>::defaultConstructorIsZeroTest();

}

TYPED_TEST(RationalsTest, SingleValueConstructorTest){

	RationalsTest<TypeParam>::singleValueConstructorTest(0, 0);
	RationalsTest<TypeParam>::singleValueConstructorTest(12, 12);

	if (std::numeric_limits<TypeParam>::is_signed){
		RationalsTest<TypeParam>::singleValueConstructorTest(-12, -12);

	}

}

TYPED_TEST(RationalsTest, TwoValuesConstructorTest){

	RationalsTest<TypeParam>::twoValuesConstructorTest(4,5,4,5);
	RationalsTest<TypeParam>::twoValuesConstructorTest(4.25,5.12,4,5);

	if (std::numeric_limits<TypeParam>::is_signed){
		RationalsTest<TypeParam>::twoValuesConstructorTest(4,-5,-4,5);
		RationalsTest<TypeParam>::twoValuesConstructorTest(-4,-5,4,5);
	}

}

TYPED_TEST(RationalsTest, simplifyTest){

	Rational<TypeParam> ratio = rational::simplify(Rational<TypeParam>(12,6));
	EXPECT_EQ(2, ratio.num());
	EXPECT_EQ(1, ratio.denom());

	if (std::numeric_limits<TypeParam>::is_signed){
		Rational<TypeParam> ratio = rational::simplify(Rational<TypeParam>(-12,6));
		EXPECT_EQ(-2, ratio.num());
		EXPECT_EQ(1, ratio.denom());
	}

}

TYPED_TEST(RationalsTest, operatorPlus){

	Rational<TypeParam> r = Rational<TypeParam>(5,2) + Rational<TypeParam>(3,4);
	RationalsTest<TypeParam>::verifyValues(r, 13, 4);

	if (std::numeric_limits<TypeParam>::is_signed){
		r = Rational<TypeParam>(-5,2) + Rational<TypeParam>(3,4);
		RationalsTest<TypeParam>::verifyValues(r, -7, 4);
	}

}

TYPED_TEST(RationalsTest, operatorMinus){

	Rational<TypeParam> r = Rational<TypeParam>(5,2) - Rational<TypeParam>(3,4);
	RationalsTest<TypeParam>::verifyValues(r, 7, 4);

	if (std::numeric_limits<TypeParam>::is_signed){
		r = Rational<TypeParam>(-5,2) - Rational<TypeParam>(3,4);
		RationalsTest<TypeParam>::verifyValues(r, -13, 4);
	}

}

TYPED_TEST(RationalsTest, operatorMultiply){

	Rational<TypeParam> r = Rational<TypeParam>(5,2) * Rational<TypeParam>(2,3);
	RationalsTest<TypeParam>::verifyValues(r, 5,3);

	if (std::numeric_limits<TypeParam>::is_signed){
		r = Rational<TypeParam>(-5,2) * Rational<TypeParam>(2,3);
		RationalsTest<TypeParam>::verifyValues(r, -5,3);
	}
}

TYPED_TEST(RationalsTest, operatorDivide){

	Rational<TypeParam> r = Rational<TypeParam>(5,2) / Rational<TypeParam>(3,2);
	RationalsTest<TypeParam>::verifyValues(r, 5, 3);

	if (std::numeric_limits<TypeParam>::is_signed){
		r = Rational<TypeParam>(-5,2) / Rational<TypeParam>(3,2);
		RationalsTest<TypeParam>::verifyValues(r, -5, 3);
	}
}

// End By class fixture

int main(int argc, char **argv){

	std::cout << "Running tests upon the rationals minilib." << "\n" << "\n";

	std::cout << rational::inf<long long int> << "\n";
	std::cout << rational::inf<int>*Rational(5,1) << "\n";
	std::cout << Rational(1,5)/Rational(0, 2) << "\n";
	std::cout << 5/Rational(0, 2) << "\n";
	std::cout << rational::decimalToRational<int, double>(5.2) << "\n";



	testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
