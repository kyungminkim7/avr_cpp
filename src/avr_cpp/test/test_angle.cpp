#include <cmath>

#include <gmock/gmock.h>

#include <avr_cpp/angle.h>
#include <avr_cpp/math.h>

using namespace ::testing;
using namespace avr_cpp;

TEST(DegreeConversion, UnderlyingType) {
    Degree<float> angle = 4.3f;

    ASSERT_THAT(static_cast<float>(angle), FloatEq(4.3f));
}

TEST(RadianConversion, UnderlyingType) {
    Radian<float> angle = 0.3f;

    ASSERT_THAT(static_cast<float>(angle), FloatEq(0.3f));
}

TEST(Conversion, DegreeToRadian) {
    Degree<float> degrees = Radian<float>(PI<float>);

    ASSERT_THAT(static_cast<float>(degrees), FloatEq(180.f));
}

TEST(Conversion, RadianToDegree) {
    Radian<float> radians = Degree<float>(90.0f);

    ASSERT_THAT(static_cast<float>(radians), FloatEq(PI<float> / 2));
}

TEST(Equality, ReturnsTrue) {
    ASSERT_TRUE(Radian<float>(PI<float> / 4) == Degree<float>(45.0f));
}

TEST(Equality, ReturnsFalse) {
    ASSERT_FALSE(Degree<float>(45.1) == Radian<float>(PI<float> / 4));
}

TEST(Comparison, LessThan) {
    ASSERT_THAT(Degree<float>(89.99f), Lt(Radian<float>(PI<float> / 2)));
}

TEST(Comparison, LessThanOrEqual) {
    ASSERT_THAT(Degree<float>(89.99f), Le(Radian<float>(PI<float> / 2)));
}

TEST(Comparison, GreaterThan) {
    ASSERT_THAT(Radian<float>(PI<float> / 2), Gt(Degree<float>(89.99f)));
}

TEST(Comparison, GreaterThanOrEqual) {
    ASSERT_THAT(Radian<float>(PI<float> / 2), Ge(Degree<float>(89.99f)));
}

TEST(Math, Multiplication) {
    const float product = Radian<float>(PI<float> / 2) * Degree<float>(90.0f);
    ASSERT_THAT(product, FloatEq(std::pow(PI<float> / 2, 2)));
}

TEST(Math, Division) {
    const float quotient = Degree<float>(180.0f) / Radian<float>(PI<float> / 2);
    ASSERT_THAT(quotient, FloatEq(2.0f));
}

TEST(Math, Addition) {
    const float sum = Radian<float>(PI<float> / 4) + Degree<float>(90.0f);
    ASSERT_THAT(sum, FloatEq(PI<float> * 3 / 4));
}

TEST(Math, Subtraction) {
    const Degree<float> difference = Degree<float>(90) - Degree<float>(180);
    ASSERT_THAT(static_cast<float>(difference), FloatEq(270));
}

class DegreeCompoundAssignment : public Test {
public:
    Degree<float> angle = 90.0f;
};

TEST_F(DegreeCompoundAssignment, Addition) {
    angle += Radian<float>(PI<float> / 2);
    
    ASSERT_THAT(static_cast<float>(angle), FloatEq(90 + 90));
}

TEST_F(DegreeCompoundAssignment, Subtraction) {
    angle -= Degree<float>(45.0f);
    
    ASSERT_THAT(static_cast<float>(angle), FloatEq(90 - 45));
}

TEST_F(DegreeCompoundAssignment, Multiplication) {
    angle *= 2.5;
    
    ASSERT_THAT(static_cast<float>(angle), FloatEq(90 * 2.5));
}

TEST_F(DegreeCompoundAssignment, Division) {
    angle /= 2;
    
    ASSERT_THAT(static_cast<float>(angle), FloatEq(90 / 2));
}

class RadianCompoundAssignment : public Test {
public:
    Radian<float> angle = Degree<float>(90.0f);
};

TEST_F(RadianCompoundAssignment, Addition) {
    angle += Radian<float>(PI<float> / 2);
    
    ASSERT_THAT(static_cast<float>(angle), FloatEq(PI<float>));
}

TEST_F(RadianCompoundAssignment, Subtraction) {
    angle -= Degree<float>(45.0f);
    
    ASSERT_THAT(static_cast<float>(angle), FloatEq(PI<float> / 4));
}

TEST_F(RadianCompoundAssignment, Multiplication) {
    angle *= 2;
    
    ASSERT_THAT(static_cast<float>(angle), FloatEq(PI<float>));
}

TEST_F(RadianCompoundAssignment, Division) {
    angle /= 2;
    
    ASSERT_THAT(static_cast<float>(angle), FloatEq(PI<float> / 4));
}

TEST(DegreeOutOfBounds, Construction) {
    ASSERT_THAT(static_cast<float>(Degree<float>(360 * 3 + 34)), 
                FloatEq(34));
}

TEST(DegreeOutOfBounds, AddAssign) {
    Degree<float> angle(300);
    angle += (60 + 24);
    ASSERT_THAT(static_cast<float>(angle), 
                FloatEq(24));
}

TEST(DegreeOutOfBounds, SubtractAssign) {
    Degree<float> angle(0);
    angle -= (360 + 38);
    ASSERT_THAT(static_cast<float>(angle), 
                FloatEq(-38 + 360));
}

TEST(DegreeOutOfBounds, MultiplyAssign) {
    Degree<float> angle(270);
    angle *= 2;
    ASSERT_THAT(static_cast<float>(angle), 
                FloatEq(270 * 2 % 360));
}

TEST(DegreeOutOfBounds, DivideAssign) {
    Degree<float> angle(270);
    angle /= 0.5f;
    ASSERT_THAT(static_cast<float>(angle), 
                FloatEq(270 * 2 % 360));
}

TEST(RadianOutOfBounds, Construction) {
    ASSERT_THAT(static_cast<float>(Radian<float>(8 * PI<float> + 1.0f)), 
                FloatEq(1.0f));
}

TEST(RadianOutOfBounds, AddAssign) {
    Radian<float> angle(PI<float>);
    angle += (PI<float> + 2.0f);
    ASSERT_THAT(static_cast<float>(angle), 
                FloatEq(2.0f));
}

TEST(RadianOutOfBounds, SubtractAssign) {
    Radian<float> angle(0);
    angle -= (2 * PI<float> + 2.0f);
    ASSERT_THAT(static_cast<float>(angle), 
                FloatEq(-2.0f + 2 * PI<float>));
}

TEST(RadianOutOfBounds, MultiplyAssign) {
    Radian<float> angle(PI<float>);
    angle *= 2;
    ASSERT_THAT(static_cast<float>(angle), 
                FloatEq(0));
}

TEST(RadianOutOfBounds, DivideAssign) {
    Radian<float> angle(PI<float>);
    angle /= 0.5f;
    ASSERT_THAT(static_cast<float>(angle), 
                FloatEq(0));
}

TEST(AssigningNegativeAngleAdjustsToPositive, Degree) {
    Degree<int> angle(-45);

    ASSERT_THAT(static_cast<int>(angle), Eq(-45 + 360));
}

TEST(AssigningNegativeAngleAdjustsToPositive, Radian) {
    Radian<float> angle(-PI<float>);

    ASSERT_THAT(static_cast<float>(angle), FloatEq(PI<float>));
}