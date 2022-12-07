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


// class IntRationals : public testing::TestWithParam<std::tuple<Rational<int>, int, int>> {};

// TEST_P(IntRationals, Constructors) {
//   Rational<int> ratio(std::get<0>(GetParam()));
//   int num = std::get<1>(GetParam());
//   int denom = std::get<2>(GetParam());
//   EXPECT_EQ(ratio.num(), num) << "Numerator : " << ratio.num() << " != " << num << " !";
//   EXPECT_EQ(ratio.denom(), denom) << "Denominator : " << ratio.denom() << " != " << denom << " !";
// }

// INSTANTIATE_TEST_SUITE_P(
//     Rationals,
//     IntRationals,
//     testing::Values(
//       std::make_tuple(Rational<int>(4,5),4,5),
//       std::make_tuple(Rational<int>(4,-5),-4,5),
//       std::make_tuple(Rational<int>(-4,-5),4,5),
//       std::make_tuple(Rational<int>(4.52,5.12),4,5)));

// class UintRationals : public testing::TestWithParam<std::tuple<Rational<uint>, uint, uint>> {};

// TEST_P(UintRationals, Constructors) {
//   Rational<uint> ratio(std::get<0>(GetParam()));
//   int num = std::get<1>(GetParam());
//   int denom = std::get<2>(GetParam());
//   EXPECT_EQ(ratio.num(), num) << "Numerator : " << ratio.num() << " != " << num << " !";
//   EXPECT_EQ(ratio.denom(), denom) << "Denominator : " << ratio.denom() << " != " << denom << " !";
// }

// INSTANTIATE_TEST_SUITE_P(
//     Rationals,
//     UintRationals,
//     testing::Values(
//       std::make_tuple(Rational<uint>(4,5),4,5),
//       std::make_tuple(Rational<uint>(4.52,5.12),4,5)));


// By class fixture
template <typename T>
class RationalsTest :public testing::Test {
	protected :

	RationalsTest(){};

	std::vector<T> inputNum;
	std::vector<T> inputDenom;
	std::vector<T> expectedNum;
	std::vector<T> expectedDenom;

	void defaultConstructorTest(){
		Rational<T> r;
		EXPECT_EQ(r.num(), 0) << "Numerator : " << r.num() << ", expected 0 !";
		EXPECT_EQ(r.denom(), 1) << "Denominator : " << r.denom() << ", expected 1 !";
	}

	void singleValueConstructorTest(T innum, T expnum){
		Rational<T> r(innum);
		EXPECT_EQ(r.num(), expnum) << "Inputs : " << innum << ", " << expnum;
		EXPECT_EQ(r.denom(), 1) << "Inputs : " << innum << ", " << expnum;
	}

	void twoValuesConstructorTest(T innum, T indenom, T expnum, T expdenom){
		Rational<T> r(innum, indenom);
		EXPECT_EQ(r.num(), expnum) << "Inputs : " << innum << ", " << indenom << ", " << expnum << ", " << expdenom;
		EXPECT_EQ(r.denom(), expdenom) << "Inputs : " << innum << ", " << indenom << ", " << expnum << ", " << expdenom;
	}
};

using Integers = ::testing::Types<int, long, uint, long uint>;

TYPED_TEST_SUITE(RationalsTest, Integers);

TYPED_TEST(RationalsTest, DefaultConstructorTest){

	RationalsTest<TypeParam>::defaultConstructorTest();

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
// End By class fixture

// TEST(rationals_lib_test_constructor, constructor_int){

// 	/** A rational of integers from 4 and 5 */
// 	Rational<int> ratio(4,5);
// 	EXPECT_EQ(4, ratioInt.num());
// 	EXPECT_EQ(5, ratioInt.denom());

// }

// TEST(rationals_lib_test_constructor, constructor_int_negative_denominator){

// 	/** A rational of integers from 4 and -5 */
// 	Rational<int> ratio(4,-5);
// 	EXPECT_EQ(-4, ratioNeg1.num());
// 	EXPECT_EQ(5, ratioNeg1.denom());

// }

// TEST(rationals_lib_test_constructor, constructor_int_negative_num_and_denom){

// 	/** A rational of integers from -4 and -5 */
// 	Rational<int> ratio(-4,-5);
// 	EXPECT_EQ(4, ratioNeg2.num());
// 	EXPECT_EQ(5, ratioNeg2.denom());

// }

// TEST(rationals_lib_test_constructor, constructor_float_to_int){

// 	/** A rational of integers from 4.56 and 5.2 */
// 	Rational<int> ratio(4.56, 5.2);
// 	EXPECT_EQ(4, ratioFToI.num());
// 	EXPECT_EQ(5, ratioFToI.denom());

// }

// TEST(rationals_lib_test_constructor, constructor_long){

// 	/** A rational of longs from (long)4 and (long)5 */
// 	Rational<long> ratio((long)4, (long)5);
// 	EXPECT_EQ(4, ratioLong.num());
// 	EXPECT_EQ(5, ratioLong.denom());

// }

// TEST(rationals_lib_test_constructor, constructor_uint){

// 	/** A rational of unsigned integers from -3 and 5 */
// 	Rational<uint> ratio(-3, 5);
// 	EXPECT_EQ(-3, ratioUint.num());
// 	EXPECT_EQ(5, ratioUint.denom());

// }

// TEST(rationals_lib_test, namespace){

// 	EXPECT_NO_THROW(Rational<int> ratio2 = rational::simplify(Rational<int>(12,6)));

// }

// TEST(rationals_lib_test, operators){

// 	Rational<int> r1(1,5);
// 	Rational<int> r2(5,2);
// 	Rational<int> r3 = r1;

// 	EXPECT_EQ(r1 == r3, true);
// 	EXPECT_EQ(r1 == r2, false);
// 	// EXPECT_EQ()
// 	// std::cout << "1/5 + 5/2 = " << r1+r2 << std::endl;
// 	// std::cout << "1/5 - 5/2 = " << r1-r2 << std::endl;
// 	// std::cout << "1/5 * 5/2 = " << r1*r2 << std::endl;
// 	// std::cout << "1/5 / 5/2 = " << r1/r2 << std::endl;
// 	// std::cout << "- 1/5 = " << -r1 << std::endl;

// }

int main(int argc, char **argv){

	std::cout << "Running tests upon the rationals minilib." << std::endl << std::endl;

	/** Test about all constructors */

	// std::cout << std::endl;

	testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
