#include <string>
#include "gtest/gtest.h"
#include "../include/bigint.h"
int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
TEST(AssigningTest, ZerosAhead) {
	BigInt a("00123");
	EXPECT_EQ(static_cast<int>(a), 123);
}
TEST(AssigningTest, ZerosAhead2) {
	BigInt a("-0001002");
	EXPECT_EQ(static_cast<int>(a), -1002);
}
TEST(AssigningTest, AssigningBigInt) {
	BigInt a("+2543");
	BigInt b;
	b = a;
	EXPECT_EQ(b, a);
}
TEST(ReductionToIntTest, ReductionToPositiveInt) {
	BigInt a("2543");
	int ans = int(a);
	int true_ans = 2543;
	EXPECT_EQ(ans, true_ans);
}
TEST(ReductionToIntTest, ReductionToNegativeInt) {
	BigInt a("-2543");
	int ans = int(a);
	int true_ans = -2543;
	EXPECT_EQ(ans, true_ans);
}
TEST(ReductionToIntTest, ReductionToOverflowPositiveInt) {
	BigInt a("221342144353343543");
	int ans = int(a);
	int true_ans = 353343543;
	EXPECT_EQ(ans, true_ans);
}
TEST(ReductionToIntTest, ReductionToOverflowNegativeInt) {
	BigInt a("-221342144353343543");
	int ans = int(a);
	int true_ans = -353343543;
	EXPECT_EQ(ans, true_ans);
}
TEST(ReductionToStringTest, ReductionToString) {
	BigInt a("221342144353343543");
	std::string ans = std::string(a);
	std::string true_ans = "221342144353343543";
	EXPECT_EQ(ans, true_ans);
}
TEST(ReductionToStringTest, ReductionToString2) {
	BigInt a("-221342144353343543");
	std::string ans = std::string(a);
	std::string true_ans = "-221342144353343543";
	EXPECT_EQ(ans, true_ans);
}
TEST(SumTest, TwoPositiveBigInt) {
	BigInt a("2543521223443251234");
	BigInt b("1245213999934324232");
	BigInt true_ans("3788735223377575466");
	BigInt ans = a + b;
	EXPECT_EQ(ans, true_ans);
}
TEST(SumTestInt, TwoPositiveBigInt) {
	BigInt a(99645);
	BigInt b(234542);
	EXPECT_EQ(static_cast<int>(a + b), 99645 + 234542); 
}
TEST(SumTest, TwoPositiveBigInt2) {
	BigInt a("999999999");
	BigInt b(1);
	BigInt true_ans("1000000000");
	BigInt ans = a + b;
	EXPECT_EQ(ans, true_ans);
}
TEST(SumTest, TwoPositiveBigInt3) {
	BigInt a("999999999");
	BigInt b(1);
	BigInt true_ans("1000000000");
	BigInt ans = b + a;
	EXPECT_EQ(ans, true_ans);
}
TEST(SumTest, TwoNegativeBigInt) {
	BigInt a("-2543521223443251234");
	BigInt b("-1245213999934324232");
	BigInt true_ans("-3788735223377575466");
	BigInt ans = a + b;
	EXPECT_EQ(ans, true_ans);
}
TEST(SumTestInt, TwoNegativeBigInt) {
	BigInt a(-99345);
	BigInt b(-412345);
	EXPECT_EQ(static_cast<int>(a + b), -99345 + -412345);
}
TEST(SumTest, OneNegativeBigInt) {
	BigInt a("-2543521223443251234");
	BigInt b("1245213999934324232");
	BigInt true_ans("-1298307223508927002");
	BigInt ans = a + b;
	EXPECT_EQ(ans, true_ans);
}
TEST(SumTest, OneNegativeBigInt2) {
	BigInt a("2543521223443251234");
	BigInt b("-1245213999934324232");
	BigInt true_ans("1298307223508927002");
	BigInt ans = a + b;
	EXPECT_EQ(ans, true_ans);
}
TEST(SumTestInt, OneNegativeBigInt){
	BigInt a(-1345);
	BigInt b(412346);
	EXPECT_EQ(static_cast<int>(a + b), -1345 + 412346);
}
TEST(SubTest, TwoPositiveBigIntPositiveAns) {
	BigInt a("4212543521223443251234");
	BigInt b("1245213999934324232");
	BigInt true_ans("4211298307223508927002");
	BigInt ans = a - b;
	EXPECT_EQ(ans, true_ans);
}
TEST(SubTestInt, TwoPositiveBigIntPositiveAns) {
	BigInt a(421254);
	BigInt b(7585);
	EXPECT_EQ(static_cast<int>(a - b), 421254 - 7585);
}
TEST(SubTest, TwoPositiveBigIntNegativeAns) {
	BigInt a("1245213999934324232");
	BigInt b("4212543521223443251234");
	BigInt true_ans("-4211298307223508927002");
	BigInt ans = a - b;
	EXPECT_EQ(ans, true_ans);
}
TEST(SubTestInt, TwoPositiveBigIntNegativeAns) {
	BigInt a(421254);
	BigInt b(7585);
	EXPECT_EQ(static_cast<int>(b - a), 7585 - 421254);
}
TEST(SubTest, TwoNegativeBigIntPositiveAns) {
	BigInt a("-12452133452999934324232");
	BigInt b("-42125435211234223443251234");
	BigInt true_ans("42112983077781223508927002");
	BigInt ans = a - b;
	EXPECT_EQ(ans, true_ans);
}
TEST(SubTestInt, TwoNegativeBigIntPositiveAns) {
	BigInt a(-421254);
	BigInt b(-7585);
	EXPECT_EQ(static_cast<int>(b - a), -7585 - -421254);
}
TEST(SubTest, TwoNegativeBigIntNegativeAns) {
	BigInt a("-121129452133452999934324232");
	BigInt b("-42125435211234223443251234");
	BigInt true_ans("-79004016922218776491072998");
	BigInt ans = a - b;
	EXPECT_EQ(ans, true_ans);
}
TEST(SubTest, OneNegativeBigIntNegativeAns) {
	BigInt a("-121129452133452999934324232");
	BigInt b("42125435211234223443251234");
	BigInt true_ans("-163254887344687223377575466");
	BigInt ans = a - b;
	EXPECT_EQ(ans, true_ans);
}
TEST(SubTest, OneNegativeBigIntPositiveAns) {
	BigInt a("121129452133452999934324232");
	BigInt b("-42125435211234223443251234");
	BigInt true_ans("163254887344687223377575466");
	BigInt ans = a - b;
	EXPECT_EQ(ans, true_ans);
}
TEST(MulTest, Zero) {
	BigInt a("121129452133452999934324232");
	BigInt b(0);
	BigInt true_ans(0);
	BigInt ans = a * b;
	EXPECT_EQ(ans, true_ans);
}
TEST(MulTest, TwoPositveBigInt) {
	BigInt a("121129452133452999934324232");
	BigInt b("42125435211234223443251234");
	BigInt true_ans("5102630888020071431804795584083925078482870790102288");
	BigInt ans = a * b;
	EXPECT_EQ(ans, true_ans);
}
TEST(MulTestInt, TwoPositveBigInt) {
	BigInt a(4212);
	BigInt b(85);
	EXPECT_EQ(static_cast<int>(b * a), 4212 * 85);
}
TEST(MulTest, TwoNegativeBigInt) {
	BigInt a("-121129452133452999934324232");
	BigInt b("-4212543521123400003251234");
	BigInt true_ans("510263088802004437018439262394451413017272710102288");
	BigInt ans = a * b;
	EXPECT_EQ(ans, true_ans);
}
TEST(MulTest, OneNegativeBigInt) {
	BigInt a("-121129452133452999934324232");
	BigInt b("42125435211234000032511218998234");
	BigInt true_ans("-5102630888020044370184256837614757916892122725674791406288");
	BigInt ans = a * b;
	EXPECT_EQ(ans, true_ans);
}
TEST(MulTestInt, OnePositveBigInt) {
	BigInt a(-4212);
	BigInt b(85);
	EXPECT_EQ(static_cast<int>(b * a), -4212 * 85);
}
TEST(DivTest, TwoPositiveBigInt1) {
	BigInt a("121129452133452999934324232");
	BigInt b("1218998234");
	BigInt true_ans("99368029218533716");
	BigInt ans = a / b;
	EXPECT_EQ(ans, true_ans);
}
TEST(DivTestInt, TwoPositiveBigInt) {
	BigInt a(412212);
	BigInt b(12);
	EXPECT_EQ(static_cast<int>(a / b), 412212 / 12);
}
TEST(DivTest, TwoPositiveBigInt2) {
	BigInt a("1218998234");
	BigInt b("121129452133452999934324232");
	BigInt true_ans(0);
	BigInt ans = a / b;
	EXPECT_EQ(ans, true_ans);
}
TEST(DivTest, TwoPositiveBigInt3) {
	BigInt a("100002");
	BigInt b(2);
	BigInt true_ans("50001");
	BigInt ans = a / b;
	EXPECT_EQ(ans, true_ans);
}
TEST(DivTest, TwoPositiveBigInt4) {
	BigInt a("100000");
	BigInt b(1);
	BigInt true_ans("100000");
	BigInt ans = a / b;
	EXPECT_EQ(ans, true_ans);
}
TEST(DivTest, OneNegativeBigInt1) {
	BigInt a("-10000000000001230000");
	BigInt b(12);
	BigInt true_ans("-833333333333435833");
	BigInt ans = a / b;
	EXPECT_EQ(ans, true_ans);
}
TEST(DivTestInt, OneNegativeBigInt) {
	BigInt a(-9345624);
	BigInt b(13);
	EXPECT_EQ(static_cast<int>(a / b), -9345624 / 13);
}
TEST(DivTest, OneNegativeBigInt2) {
	BigInt a(100000);
	BigInt b(-12);
	BigInt true_ans(-8333);
	BigInt ans = a / b;
	EXPECT_EQ(ans, true_ans);
}
TEST(DivTest, TwoPositiveBigInt5) {
	BigInt a("10000000000001230000");
	BigInt b(12);
	BigInt true_ans("833333333333435833");
	BigInt ans = a / b;
	EXPECT_EQ(ans, true_ans);
}
TEST(RemTest, TwoPositiveBigInt1) {
	BigInt a(100000);
	BigInt b("12");
	BigInt true_ans(4);
	BigInt ans = a % b;
	EXPECT_EQ(ans, true_ans);
}
TEST(RemTestInt, TwoPositiveBigInt) {
	BigInt a(9345624);
	BigInt b(13);
	EXPECT_EQ(static_cast<int>(a % b), 9345624 % 13);
}
TEST(RemTest, TwoPositiveBigInt2) {
	BigInt a("12443212341134352243434343231");
	BigInt b("121237");
	BigInt true_ans("43102");
	BigInt ans = a % b;
	EXPECT_EQ(ans, true_ans);
}
TEST(RemTest, TwoPositiveBigInt3) {
	BigInt a("121237");
	BigInt b("12443212341134352243434343231");
	BigInt true_ans("121237");
	BigInt ans = a % b;
	EXPECT_EQ(ans, true_ans);
}
TEST(RemTest, TwoPositiveBigInt4) {
	BigInt a(1224);
	BigInt b(12);
	BigInt true_ans(0);
	BigInt ans = a % b;
	EXPECT_EQ(ans, true_ans);
}
TEST(RemTest, TwoPositiveBigInt5) {
	BigInt a("100000");
	BigInt b(1);
	BigInt true_ans(0);
	BigInt ans = a % b;
	EXPECT_EQ(ans, true_ans);
}
TEST(RemTest, TwoPositiveBigInt6) {
	BigInt a("1000002");
	BigInt b(10);
	BigInt true_ans(2);
	BigInt ans = a % b;
	EXPECT_EQ(ans, true_ans);
}
TEST(RemTest, TwoPositiveBigInt7) {
	BigInt a("10000000000001230000");
	BigInt b(12);
	BigInt true_ans(4);
	BigInt ans = a % b;
	EXPECT_EQ(ans, true_ans);
}
TEST(RemTest, OneNegativeBigInt) {
	BigInt a("-921436645656556655665566565243242523141237");
	BigInt b("12443212341134352243434343231");
	BigInt true_ans("-7956844134326472672663656386");
	BigInt ans = a % b;
	EXPECT_EQ(ans, true_ans);
}
TEST(RemTestInt, OneNegativeBigInt) {
	BigInt a(-100002);
	BigInt b(412);
	EXPECT_EQ(static_cast<int>(a % b), -100002 % 412);
}
TEST(XorTest, TwoPositiveBigInt) {
	BigInt a("921436645656556655665566565243242523141237");
	BigInt b("12443212341134352243434343231");
	BigInt true_ans("921436645656564145228194997085735668051786");
	BigInt ans = a ^ b;
	EXPECT_EQ(ans, true_ans);
}
TEST(XorTestInt, TwoPositiveBigInt) {
	BigInt a(1001102);
	BigInt b(41242);
	EXPECT_EQ(static_cast<int>(a ^ b), 1001102 ^ 41242);
}
TEST(XorTest, TwoPositiveBigInt2) {
	BigInt a("92143664565655665242222");
	BigInt b("12443212341134352243434343231");
	BigInt true_ans("12443299761846394490031946577");
	BigInt ans = a ^ b;
	EXPECT_EQ(ans, true_ans);
}
TEST(XorTest, OneNegativeBigInt) {
	BigInt a("921436645656556655665566565243242523141237");
	BigInt b("-12443212341134352243434343231");
	BigInt true_ans("-921436645656564145228194997085735668051788");
	BigInt ans = a ^ b;
	EXPECT_EQ(ans, true_ans);
}
TEST(XorTest, TwoNegativeBigInt) {
	BigInt a("-52143664565655665599665566565243242523141237");
	BigInt b("-12443212341134352243431234343231");
	BigInt true_ans("52143664565663663369320655619041373735892298");
	BigInt ans = a ^ b;
	EXPECT_EQ(ans, true_ans);
}
TEST(XorTestInt, TwoNegativeBigInt) {
	BigInt a(-199102);
	BigInt b(-41243);
	EXPECT_EQ(static_cast<int>(a ^ b), -199102 ^ -41243);
}
TEST(AndTest, TwoPositiveBigInt) {
	BigInt a("921436645656556655665566565243242523141237");
	BigInt b("12443212341134352243434343231");
	BigInt true_ans("2476824856351254875144716341");
	BigInt ans = a & b;
	EXPECT_EQ(ans, true_ans);
}
TEST(AndTestInt, TwoPositiveBigInt) {
	BigInt a(199102);
	BigInt b(41243);
	EXPECT_EQ(static_cast<int>(a & b), 199102 & 41243);
}
TEST(AndTest, TwoPositiveBigInt2) {
	BigInt a("92143664565655665242222");
	BigInt b("12443212341134352243434343231");
	BigInt true_ans("2361476261704533819438");
	BigInt ans = a & b;
	EXPECT_EQ(ans, true_ans);
}
TEST(AndTest, OneNegativeBigInt) {
	BigInt a("921436645656556655665566565243242523141237");
	BigInt b("-12443212341134352243434343231");
	BigInt true_ans("921436645656554178840710213988367378424897");
	BigInt ans = a & b;
	EXPECT_EQ(ans, true_ans);
}
TEST(AndTest, TwoNegativeBigInt) {
	BigInt a("-52143664565655665599665566565243242523141237");
	BigInt b("-12443212341134352243431234343231");
	BigInt true_ans("-52143664565665886090663678268264023746688383");
	BigInt ans = a & b;
	EXPECT_EQ(ans, true_ans);
}
TEST(AndTestInt, TwoNegativeBigInt) {
	BigInt a(-19902);
	BigInt b(-41243);
	EXPECT_EQ(static_cast<int>(a & b), -19902 & -41243);
}
TEST(OrTest, TwoPositiveBigInt) {
	BigInt a("921436645656556655665566565243242523141237");
	BigInt b("12443212341134352243434343231");
	BigInt true_ans("921436645656566622053051348340610812768127");
	BigInt ans = a | b;
	EXPECT_EQ(ans, true_ans);
}
TEST(OrTestInt, TwoPositiveBigInt) {
	BigInt a(19902);
	BigInt b(41243);
	EXPECT_EQ(static_cast<int>(a | b), 19902 | 41243);
}
TEST(OrTest, TwoPositiveBigInt2) {
	BigInt a("92143664565655665242222");
	BigInt b("12443212341134352243434343231");
	BigInt true_ans("12443302123322656194565766015");
	BigInt ans = a | b;
	EXPECT_EQ(ans, true_ans);
}
TEST(OrTest, OneNegativeBigInt) {
	BigInt a("921436645656556655665566565243242523141237");
	BigInt b("-12443212341134352243434343231");
	BigInt true_ans("-9966387484783097368289626891");
	BigInt ans = a | b;
	EXPECT_EQ(ans, true_ans);
}
TEST(OrTest, TwoNegativeBigInt) {
	BigInt a("-52143664565655665599665566565243242523141237");
	BigInt b("-12443212341134352243431234343231");
	BigInt true_ans("-2222721343022649222650010796085");
	BigInt ans = a | b;
	EXPECT_EQ(ans, true_ans);
}
TEST(OrTest, TwoNegativeBigInt2) {
	BigInt a(-256);
	BigInt b(-1241347);
	BigInt true_ans(-3);
	BigInt ans = a | b;
	EXPECT_EQ(ans, true_ans);
}
TEST(OrTestInt, TwoNegativeBigInt) {
	BigInt a(-198872);
	BigInt b(-4243);
	EXPECT_EQ(static_cast<int>(a | b), -198872 | -4243);
}
TEST(InvTest, PositiveBigInt) {
	BigInt a("2143664565655665599665566565243242523141237");
	BigInt true_ans("-2143664565655665599665566565243242523141238");
	BigInt ans = ~a;
	EXPECT_EQ(ans, true_ans);
}
TEST(InvTestInt, PositiveBigInt) {
	BigInt a(198872);
	EXPECT_EQ(static_cast<int>(~a), ~198872);
}
TEST(InvTest, NegativeBigInt) {
	BigInt a("-2143664565655665599665566565243242523141237");
	BigInt true_ans("2143664565655665599665566565243242523141236");
	BigInt ans = ~a;
	EXPECT_EQ(ans, true_ans);
}
TEST(InvTestInt, NegativeBigInt) {
	BigInt a(-4312);
	EXPECT_EQ(static_cast<int>(~a), ~(-4312));
}
TEST(SizeTest, OneBigInt) {
	BigInt a("652432314123721233221331");
	int true_ans = 25;
	int ans = a.size();
	EXPECT_EQ(ans, true_ans);
}
TEST(CmpTest, EqualTrue) {
	BigInt a("123456789");
	BigInt b(123456789);
	bool true_ans = 1;
	bool ans = (a == b);
	EXPECT_EQ(ans, true_ans);
}
TEST(CmpTest, EqualFalse) {
	BigInt a("1233456789");
	BigInt b(123456789);
	bool true_ans = 0;
	bool ans = (a == b);
	EXPECT_EQ(ans, true_ans);
}
TEST(CmpTest, NotEqualTrue) {
	BigInt a("1233456789");
	BigInt b(123456789);
	bool true_ans = 1;
	bool ans = (a != b);
	EXPECT_EQ(ans, true_ans);
}
TEST(CmpTest, NotEqualFalse) {
	BigInt a( "-123456789");
	BigInt b(-123456789);
	bool true_ans = 0;
	bool ans = (a != b);
	EXPECT_EQ(ans, true_ans);
}
TEST(CmpTest, LessTwoPositiveBigIntTrue) {
	BigInt a("12332123");
	BigInt b(123456789);
	bool true_ans = 1;
	bool ans = (a < b);
	EXPECT_EQ(ans, true_ans);
}
TEST(CmpTest, LessTwoPositiveBigIntFalse) {
	BigInt a("121224332123");
	BigInt b(123456789);
	bool true_ans = 0;
	bool ans = (a < b);
	EXPECT_EQ(ans, true_ans);
}
TEST(CmpTest, LessTwoNegativeBigIntTrue) {
	BigInt a("-3142134212332123");
	BigInt b("-12356789");
	bool true_ans = 1;
	bool ans = (a < b);
	EXPECT_EQ(ans, true_ans);
}
TEST(CmpTest, LessTwoNegativeBigIntTrue2) {
	BigInt a("-12371341");
	BigInt b("-12356789");
	bool true_ans = 1;
	bool ans = (a < b);
	EXPECT_EQ(ans, true_ans);
}
TEST(CmpTest, LessTwoNegativeBigIntFalse2) {
	BigInt a("-12371341");
	BigInt b("-12356789");
	bool true_ans = 0;
	bool ans = (b < a);
	EXPECT_EQ(ans, true_ans);
}
TEST(CmpTest, LessTwoNegativeBigIntFalse) {
	BigInt a("-314213");
	BigInt b("-12356789");
	bool true_ans = 0;
	bool ans = (a < b);
	EXPECT_EQ(ans, true_ans);
}
TEST(CmpTest, LessOneNegativeBigIntTrue) {
	BigInt a("-314232123");
	BigInt b("12356789");
	bool true_ans = 1;
	bool ans = (a < b);
	EXPECT_EQ(ans, true_ans);
}
TEST(CmpTest, LessOneNegativeBigIntFalse) {
	BigInt a("314232123");
	BigInt b("-12356789");
	bool true_ans = 0;
	bool ans = (a < b);
	EXPECT_EQ(ans, true_ans);
}
TEST(CmpTest, MoreTwoPositiveBigIntTrue) {
	BigInt a("12332123");
	BigInt b(123456789);
	bool true_ans = 1;
	bool ans = (b > a);
	EXPECT_EQ(ans, true_ans);
}
TEST(CmpTest, MoreTwoPositiveBigIntFalse2) {
	BigInt a("-12371341");
	BigInt b("-12356789");
	bool true_ans = 0;
	bool ans = (a > b);
	EXPECT_EQ(ans, true_ans);
}
TEST(CmpTest, MoreTwoPositiveBigIntTrue2) {
	BigInt a("-12371341");
	BigInt b("-12356789");
	bool true_ans = 1;
	bool ans = (b > a);
	EXPECT_EQ(ans, true_ans);
}
TEST(CmpTest, MoreTwoPositiveBigIntFalse) {
	BigInt a("121224332123");
	BigInt b(123456789);
	bool true_ans = 0;
	bool ans = (b > a);
	EXPECT_EQ(ans, true_ans);
}
TEST(CmpTest, MoreTwoNegativeBigIntTrue) {
	BigInt a("-3142134212332123");
	BigInt b("-12356789");
	bool true_ans = 1;
	bool ans = (b > a);
	EXPECT_EQ(ans, true_ans);
}
TEST(CmpTest, MoreTwoNegativeBigIntFalse) {
	BigInt a("-314213");
	BigInt b("-12356789");
	bool true_ans = 0;
	bool ans = (b > a);
	EXPECT_EQ(ans, true_ans);
}
TEST(CmpTest, MoreOneNegativeBigIntTrue) {
	BigInt a("-314232123");
	BigInt b("12356789");
	bool true_ans = 1;
	bool ans = (b > a);
	EXPECT_EQ(ans, true_ans);
}
TEST(CmpTest, MoreOneNegativeBigIntFalse) {
	BigInt a("314232123");
	BigInt b("-12356789");
	bool true_ans = 0;
	bool ans = (b > a);
	EXPECT_EQ(ans, true_ans);
}
TEST(CmpTest, LessEqTwoPositiveBigIntTrue) {
	BigInt a( "12332123");
	BigInt b(123456789);
	bool true_ans = 1;
	bool ans = (a <= b);
	EXPECT_EQ(ans, true_ans);
}
TEST(CmpTest, LessEqTwoPositiveBigIntFalse) {
	BigInt a("121224332123");
	BigInt b(123456789);
	bool true_ans = 0;
	bool ans = (a <= b);
	EXPECT_EQ(ans, true_ans);
}
TEST(CmpTest, LessEqTwoPositiveBigIntTrue2) {
	BigInt a("12331232112371341");
	BigInt b("12331781231231239");
	bool true_ans = 1;
	bool ans = (a <= b);
	EXPECT_EQ(ans, true_ans);
}
TEST(CmpTest, LessEqTwoPositiveBigIntFalse2) {
	BigInt a("123713415434354354312");
	BigInt b("123723124512356789123");
	bool true_ans = 0;
	bool ans = (b <= a);
	EXPECT_EQ(ans, true_ans);
}
TEST(CmpTest, LessEqTwoNegativeBigIntTrue2) {
	BigInt a("-12371341");
	BigInt b("-12356789");
	bool true_ans = 1;
	bool ans = (a <= b);
	EXPECT_EQ(ans, true_ans);
}
TEST(CmpTest, LessEqTwoNegativeBigIntFalse2) {
	BigInt a("-12371341");
	BigInt b("-12356789");
	bool true_ans = 0;
	bool ans = (b <= a);
	EXPECT_EQ(ans, true_ans);
}
TEST(CmpTest, LessEqTwoNegativeBigIntTrue) {
	BigInt a("-3142134212332123");
	BigInt b("-12356789");
	bool true_ans = 1;
	bool ans = (a <= b);
	EXPECT_EQ(ans, true_ans);
}
TEST(CmpTest, LessEqTwoNegativeBigIntFalse) {
	BigInt a("-314213");
	BigInt b("-12356789");
	bool true_ans = 0;
	bool ans = (a <= b);
	EXPECT_EQ(ans, true_ans);
}
TEST(CmpTest, LessEqOneNegativeBigIntTrue) {
	BigInt a("-314232123");
	BigInt b("12356789");
	bool true_ans = 1;
	bool ans = (a <= b);
	EXPECT_EQ(ans, true_ans);
}
TEST(CmpTest, LessEqOneNegativeBigIntFalse) {
	BigInt a("314232123");
	BigInt b("-12356789");
	bool true_ans = 0;
	bool ans = (a <= b);
	EXPECT_EQ(ans, true_ans);
}
TEST(CmpTest, LessEqTwoEqualBigIntTrue) {
	BigInt a("12356789");
	BigInt b("12356789");
	bool true_ans = 1;
	bool ans = (a <= b);
	EXPECT_EQ(ans, true_ans);
}
TEST(CmpTest, MoreEqTwoPositiveBigIntTrue) {
	BigInt a("12332123");
	BigInt b(123456789);
	bool true_ans = 1;
	bool ans = (b >= a);
	EXPECT_EQ(ans, true_ans);
}
TEST(CmpTest, MoreEqTwoPositiveBigIntFalse) {
	BigInt a("121224332123");
	BigInt b(123456789);
	bool true_ans = 0;
	bool ans = (b >= a);
	EXPECT_EQ(ans, true_ans);
}
TEST(CmpTest, MoreEqTwoPositiveBigIntTrue2) {
	BigInt a("12331932112371341");
	BigInt b("12331781231231239");
	bool true_ans = 1;
	bool ans = (a >= b);
	EXPECT_EQ(ans, true_ans);
}
TEST(CmpTest, MoreEqTwoPositiveBigIntFalse2) {
	BigInt a("123713415434354354312");
	BigInt b("123712124512356789123");
	bool true_ans = 0;
	bool ans = (b >= a);
	EXPECT_EQ(ans, true_ans);
}
TEST(CmpTest, MoreEqTwoNegativeBigIntTrue2) {
	BigInt a("-12331341");
	BigInt b("-12356789");
	bool true_ans = 1;
	bool ans = (a >= b);
	EXPECT_EQ(ans, true_ans);
}
TEST(CmpTest, MoreEqTwoNegativeBigIntFalse2) {
	BigInt a("-12371341");
	BigInt b("-12396789");
	bool true_ans = 0;
	bool ans = (b >= a);
	EXPECT_EQ(ans, true_ans);
}
TEST(CmpTest, MoreEqTwoNegativeBigIntTrue) {
	BigInt a("-3142134212332123");
	BigInt b("-12356789");
	bool true_ans = 1;
	bool ans = (b >= a);
	EXPECT_EQ(ans, true_ans);
}
TEST(CmpTest, MoreEqTwoNegativeBigIntFalse) {
	BigInt a("-314213");
	BigInt b("-12356789");
	bool true_ans = 0;
	bool ans = (b >= a);
	EXPECT_EQ(ans, true_ans);
}
TEST(CmpTest, MoreEqOneNegativeBigIntTrue) {
	BigInt a("-314232123");
	BigInt b("12356789");
	bool true_ans = 1;
	bool ans = (b >= a);
	EXPECT_EQ(ans, true_ans);
}
TEST(CmpTest, MoreEqOneNegativeBigIntFalse) {
	BigInt a("314232123");
	BigInt b("-12356789");
	bool true_ans = 0;
	bool ans = (b >= a);
	EXPECT_EQ(ans, true_ans);
}
TEST(CmpTest, MoreEqTwoEqualBigIntTrue) {
	BigInt a("-12356789");
	BigInt b("-12356789");
	bool true_ans = 1;
	bool ans = (b >= a);
	EXPECT_EQ(ans, true_ans);
}
TEST(IncremTest, PostInc) {
	BigInt a("199999999999999999");
	BigInt true_ans("199999999999999999");
	BigInt ans = a++;
	EXPECT_EQ(ans, true_ans);
	EXPECT_EQ(a, BigInt("200000000000000000"));
}
TEST(IncremTest, PrefInc) {
	BigInt a("199999999999999999");
	BigInt true_ans("200000000000000000");
	BigInt ans = ++a;
	EXPECT_EQ(ans, true_ans);
	EXPECT_EQ(a, true_ans);
}
TEST(DecremTest, PostInc) {
	BigInt a("1234324000");
	BigInt true_ans("1234324000");
	BigInt ans = a--;
	EXPECT_EQ(ans, true_ans);
	EXPECT_EQ(a, BigInt("1234323999"));
}
TEST(DecremTest, PrefInc) {
	BigInt a("1234324000");
	BigInt true_ans("1234323999");
	BigInt ans = --a;
	EXPECT_EQ(ans, true_ans);
	EXPECT_EQ(a, true_ans);
}
TEST(SumEqTest, TwoPositiveBigInt) {
	BigInt a("2543521223443251234");
	BigInt b("1245213999934324232");
	BigInt true_ans("3788735223377575466");
	a += b;
	EXPECT_EQ(a, true_ans);
}
TEST(SumEqTestInt, TwoPositiveBigInt) {
	BigInt a(99645);
	BigInt b(234542);
	a += b;
	EXPECT_EQ(static_cast<int>(a), 99645 + 234542);
}
TEST(SumEqTest, TwoNegativeBigInt) {
	BigInt a("-2543521223443251234");
	BigInt b("-1245213999934324232");
	BigInt true_ans("-3788735223377575466");
	a += b;
	EXPECT_EQ(a, true_ans);
}
TEST(SumEqTest, OneNegativeBigInt1) {
	BigInt a("-2543521223443251234");
	BigInt b("1245213999934324232");
	BigInt true_ans("-1298307223508927002");
	a += b;
	EXPECT_EQ(a, true_ans);
}
TEST(SumEqTestInt, OneNegativeBigInt) {
	BigInt a(99645);
	BigInt b(-234542);
	a += b;
	EXPECT_EQ(static_cast<int>(a), 99645 + -234542);
}
TEST(SumEqTest, OneNegativeBigInt2) {
	BigInt a("25435212000000443251234");
	BigInt b("-1245213999934324232");
	BigInt true_ans("25433966786000508927002");
	a += b;
	EXPECT_EQ(a, true_ans);
}
TEST(SubEqTest, TwoPositiveBigIntPositiveAns) {
	BigInt a("4212543521223443251234");
	BigInt b("1245213999934324232");
	BigInt true_ans("4211298307223508927002");
	a -= b;
	EXPECT_EQ(a, true_ans);
}
TEST(SubEqTestInt, TwoPositiveBigInt) {
	BigInt a(9439235);
	BigInt b(234542);
	a -= b;
	EXPECT_EQ(static_cast<int>(a), 9439235 - 234542);
}
TEST(SubEqTest, TwoPositiveBigIntNegativeAns) {
	BigInt a("1245213999934324232");
	BigInt b("4212543521223443251234");
	BigInt true_ans("-4211298307223508927002");
	a -= b;
	EXPECT_EQ(a, true_ans);
}
TEST(SubEqTest, TwoNegativeBigIntPositiveAns) {
	BigInt a("-12452133452999934324232");
	BigInt b("-42125435211234223443251234");
	BigInt true_ans("42112983077781223508927002");
	a -= b;
	EXPECT_EQ(a, true_ans);
}
TEST(SubEqTestInt, TwoNegativeBigInt) {
	BigInt a(-39235);
	BigInt b(-234542);
	a -= b;
	EXPECT_EQ(static_cast<int>(a), -39235 - -234542);
}
TEST(SubEqTest, TwoNegativeBigIntNegativeAns) {
	BigInt a("-121129452133452999934324232");
	BigInt b("-42125435211234223443251234");
	BigInt true_ans("-79004016922218776491072998");
	a -= b;
	EXPECT_EQ(a, true_ans);
}
TEST(SubEqTest, OneNegativeBigIntPositiveAns) {
	BigInt a("121129452133452999934324232");
	BigInt b("-42125435211234223443251234");
	BigInt true_ans("163254887344687223377575466");
	a -= b;
	EXPECT_EQ(a, true_ans);
}
TEST(SubEqTestInt, OneNegativeBigInt) {
	BigInt a(-39235);
	BigInt b(234542);
	a -= b;
	EXPECT_EQ(static_cast<int>(a), -39235 - 234542);
}
TEST(SubEqTest, OneNegativeBigIntNegativeAns) {
	BigInt a("-121129452133452999934324232");
	BigInt b("42125435211234223443251234");
	BigInt true_ans("-163254887344687223377575466");
	a -= b;
	EXPECT_EQ(a, true_ans);
}
TEST(MulEqTest, Zero) {
	BigInt a("121129452133452999934324232");
	BigInt b(0);
	BigInt true_ans(0);
	a *= b;
	EXPECT_EQ(a, true_ans);
}
TEST(MulEqTest, TwoPositveBigInt) {
	BigInt a("121129452133452999934324232");
	BigInt b("42125435211234223443251234");
	BigInt true_ans("5102630888020071431804795584083925078482870790102288");
	a *= b;
	EXPECT_EQ(a, true_ans);
}
TEST(MulEqTestInt, TwoPositveBigInt) {
	BigInt a(235);
	BigInt b(9952);
	a *= b;
	EXPECT_EQ(static_cast<int>(a), 235 * 9952);
}
TEST(MulEqTest, TwoNegativeBigInt) {
	BigInt a("-121129452133452999934324232");
	BigInt b("-4212543521123400003251234");
	BigInt true_ans("510263088802004437018439262394451413017272710102288");
	a *= b;
	EXPECT_EQ(a, true_ans);
}
TEST(MulEqTest, OneNegativeBigInt) {
	BigInt a("-121129452133452999934324232");
	BigInt b("42125435211234000032511218998234");
	BigInt true_ans("-5102630888020044370184256837614757916892122725674791406288");
	a *= b;
	EXPECT_EQ(a, true_ans);
}
TEST(MulEqTestInt, OneNegativeBigInt) {
	BigInt a(-1311);
	BigInt b(765);
	a *= b;
	EXPECT_EQ(static_cast<int>(a), -1311 * 765);
}
TEST(DivEqTest, TwoPositiveBigInt1) {
	BigInt a("121129452133452999934324232");
	BigInt b("1218998234");
	BigInt true_ans("99368029218533716");
	a /= b;
	EXPECT_EQ(a, true_ans);
}
TEST(DivEqTestInt, TwoPositiveBigInt) {
	BigInt a(131211);
	BigInt b(7651);
	a /= b;
	EXPECT_EQ(static_cast<int>(a), 131211 / 7651);
}
TEST(DivEqTest, TwoPositiveBigInt2) {
	BigInt a("1218998234");
	BigInt b("121129452133452999934324232");
	BigInt true_ans(0);
	a /= b;
	EXPECT_EQ(a, true_ans);
}
TEST(DivEqTest, OneNegativeBigInt1) {
	BigInt a("-10000000000001230000");
	BigInt b(12);
	BigInt true_ans("-833333333333435833");
	a /= b;
	EXPECT_EQ(a, true_ans);
}
TEST(DivEqTestInt, OneNegativeBigInt) {
	BigInt a(132212);
	BigInt b(-42);
	a /= b;
	EXPECT_EQ(static_cast<int>(a), 132212 / -42);
}
TEST(DivEqTest, OneNegativeBigInt2) {
	BigInt a(100000);
	BigInt b(-12);
	BigInt true_ans(-8333);
	a /= b;
	EXPECT_EQ(a, true_ans);
}
TEST(RemEqTest, TwoPositiveBigInt1) {
	BigInt a(100000);
	BigInt b(12);
	BigInt true_ans(4);
	a %= b;
	EXPECT_EQ(a, true_ans);
}
TEST(RemEqTestInt, TwoPositiveBigInt) {
	BigInt a(132212);
	BigInt b(42);
	a %= b;
	EXPECT_EQ(static_cast<int>(a), 132212 % 42);
}
TEST(RemEqTest, TwoPositiveBigInt2) {
	BigInt a("12443212341134352243434343231");
	BigInt b("121237");
	BigInt true_ans("43102");
	a %= b;
	EXPECT_EQ(a, true_ans);
}
TEST(RemEqTest, TwoPositiveBigInt3) {
	BigInt a("121237");
	BigInt b("12443212341134352243434343231");
	BigInt true_ans("121237");
	a %= b;
	EXPECT_EQ(a, true_ans);
}
TEST(RemEqTest, TwoPositiveBigInt4) {
	BigInt a("1224");
	BigInt b(12);
	BigInt true_ans(0);
	a %= b;
	EXPECT_EQ(a, true_ans);
}
TEST(RemEqTest, TwoPositiveBigInt5) {
	BigInt a("100000");
	BigInt b(1);
	BigInt true_ans(0);
	a %= b;
	EXPECT_EQ(a, true_ans);
}
TEST(RemEqTest, TwoPositiveBigInt6) {
	BigInt a(1000002);
	BigInt b(10);
	BigInt true_ans(2);
	a %= b;
	EXPECT_EQ(a, true_ans);
}
TEST(RemEqTest, TwoPositiveBigInt7) {
	BigInt a("10000000000001230000");
	BigInt b(12);
	BigInt true_ans(4);
	a %= b;
	EXPECT_EQ(a, true_ans);
}
TEST(RemEqTest, OneNegativeBigInt) {
	BigInt a("-921436645656556655665566565243242523141237");
	BigInt b("12443212341134352243434343231");
	BigInt true_ans("-7956844134326472672663656386");
	a %= b;
	EXPECT_EQ(a, true_ans);
}
TEST(RemEqTestInt, OneNegativeBigInt) {
	BigInt a(-5555);
	BigInt b(5);
	a %= b;
	EXPECT_EQ(static_cast<int>(a), -5555 % 5);
}
TEST(XorEqTest, TwoPositiveBigInt) {
	BigInt a("921436645656556655665566565243242523141237");
	BigInt b("12443212341134352243434343231");
	BigInt true_ans("921436645656564145228194997085735668051786");
	a ^= b;
	EXPECT_EQ(a, true_ans);
}
TEST(XorEqTestInt, TwoPositiveBigInt) {
	BigInt a(5555);
	BigInt b(15);
	a ^= b;
	EXPECT_EQ(static_cast<int>(a), 5555 ^ 15);
}
TEST(XorEqTest, TwoPositiveBigInt2) {
	BigInt a("92143664565655665566556");
	BigInt b("12443212341134352243434343231");
	BigInt true_ans("12443299761846394490032007267");
	a ^= b;
	EXPECT_EQ(a, true_ans);
}
TEST(XorEqTest, OneNegativeBigInt) {
	BigInt a("921436645656556655665566565243242523141237");
	BigInt b("-12443212341134352243434343231");
	BigInt true_ans("-921436645656564145228194997085735668051788");
	a ^= b;
	EXPECT_EQ(a, true_ans);
}
TEST(XorEqTest, TwoNegativeBigInt) {
	BigInt a("-52143664565655665599665566565243242523141237");
	BigInt b("-12443212341134352243431234343231");
	BigInt true_ans("52143664565663663369320655619041373735892298");
	a ^= b;
	EXPECT_EQ(a, true_ans);
}
TEST(XorEqTestInt, TwoNegativeBigInt) {
	BigInt a(-51575);
	BigInt b(-244);
	a ^= b;
	EXPECT_EQ(static_cast<int>(a), -51575 ^ -244);
}
TEST(AndEqTest, TwoPositiveBigInt) {
	BigInt a("921436645656556655665566565243242523141237");
	BigInt b("12443212341134352243434343231");
	BigInt true_ans("2476824856351254875144716341");
	a &= b;
	EXPECT_EQ(a, true_ans);
}
TEST(AndEqTestInt, TwoPositiveBigInt) {
	BigInt a(51575);
	BigInt b(244);
	a &= b;
	EXPECT_EQ(static_cast<int>(a), 51575 & 244);
}
TEST(AndEqTest, TwoPositiveBigInt2) {
	BigInt a("921436645656556655665566562");
	BigInt b("12443212341134352243434343242");
	BigInt true_ans("58030886184353414281970498");
	a &= b;
	EXPECT_EQ(a, true_ans);
}
TEST(AndEqTest, OneNegativeBigInt) {
	BigInt a("921436645656556655665566565243242523141237");
	BigInt b("-12443212341134352243434343231");
	BigInt true_ans("921436645656554178840710213988367378424897");
	a &= b;
	EXPECT_EQ(a, true_ans);
}
TEST(AndEqTest, TwoNegativeBigInt) {
	BigInt a("-52143664565655665599665566565243242523141237");
	BigInt b("-12443212341134352243431234343231");
	BigInt true_ans("-52143664565665886090663678268264023746688383");
	a &= b;
	EXPECT_EQ(a, true_ans);
}
TEST(AndEqTestInt, TwoNegativeBigInt) {
	BigInt a(-51575);
	BigInt b(-244);
	a &= b;
	EXPECT_EQ(static_cast<int>(a), -51575 & -244);
}
TEST(OrEqTest, TwoPositiveBigInt) {
	BigInt a("921436645656556655665566565243242523141237");
	BigInt b("12443212341134352243434343231");
	BigInt true_ans("921436645656566622053051348340610812768127");
	a |= b;
	EXPECT_EQ(a, true_ans);
}
TEST(OrEqTestInt, TwoPositiveBigInt) {
	BigInt a(51575);
	BigInt b(244);
	a |= b;
	EXPECT_EQ(static_cast<int>(a), 51575 | 244);
}
TEST(OrEqTest, TwoPositiveBigInt2) {
	BigInt a("921436645656556655665566562");
	BigInt b("12443212341134352243434343242");
	BigInt true_ans("13306618100606555484817939306");
	a |= b;
	EXPECT_EQ(a, true_ans);
}
TEST(OrEqTest, OneNegativeBigInt) {
	BigInt a("921436645656556655665566565243242523141237");
	BigInt b("-12443212341134352243434343231");
	BigInt true_ans("-9966387484783097368289626891");
	a |= b;
	EXPECT_EQ(a, true_ans);
}
TEST(OrEqTest, TwoNegativeBigInt) {
	BigInt a("-52143664565655665599665566565243242523141237");
	BigInt b("-12443212341134352243431234343231");
	BigInt true_ans("-2222721343022649222650010796085");
	a |= b;
	EXPECT_EQ(a, true_ans);
}
TEST(OrEqTestInt, TwoNegativeBigInt) {
	BigInt a(-575);
	BigInt b(-134244);
	a |= b;
	EXPECT_EQ(static_cast<int>(a), -575 | -134244);
}
TEST(OrEqTest, TwoNegativeBigInt2) {
	BigInt a("-52143664565655665599665566565243242523141237");
	BigInt b("-12443212341134352243431234343231");
	BigInt true_ans("-2222721343022649222650010796085");
	a |= b;
	EXPECT_EQ(a, true_ans);
}
TEST(OrEqTest, TwoNegativeBigInt3) {
	BigInt a(-256);
	BigInt b(-1241347);
	BigInt true_ans(-3);
	a |= b;
	EXPECT_EQ(a, true_ans);
}
TEST(UnaryPlus, UnaryPlus) {
	BigInt a("+52143664565655665599665566565243242523141237");
	BigInt b = +a;
	BigInt true_ans("52143664565655665599665566565243242523141237");
	EXPECT_EQ(b, true_ans);
}
TEST(UnaryPlusInt, UnaryPlus) {
	BigInt a(575);
	EXPECT_EQ(static_cast<int>(+a), +575);
}
TEST(UnaryMinusInt, UnaryMinus) {
	BigInt a(575);
	EXPECT_EQ(static_cast<int>(-a), -575);
}
TEST(InvTest, InvStr) {
	EXPECT_THROW(BigInt a("521t43664565655665599665566565243242523141237"), std::invalid_argument);
}
TEST(InvTest, InvStr2) {
	EXPECT_THROW(BigInt a(""), std::invalid_argument);
}
TEST(InvTest, InvStr3) {
	EXPECT_THROW(BigInt a("-"), std::invalid_argument);
}
TEST(InvTest, DivZero) {
	BigInt a("453345435");
	BigInt b(0);
	EXPECT_THROW(a/b, std::invalid_argument);
}
TEST(InvTest, DivEqZero) {
	BigInt a("453345435");
	BigInt b(0);
	EXPECT_THROW(a /= b, std::invalid_argument);
}
TEST(InvTest, RemZero) {
	BigInt a("453345435");
	BigInt b(0);
	EXPECT_THROW(a % b, std::invalid_argument);
}
TEST(InvTest, RemEqZero) {
	BigInt a("453345435");
	BigInt b(0);
	EXPECT_THROW(a %= b, std::invalid_argument);
}
TEST(OutTest, OutTest) {
	BigInt a("-123456789999999");
	std::string true_ans = "-123456789999999";
	std::ostringstream s;
	s << a;
	EXPECT_EQ(s.str(), true_ans);
}