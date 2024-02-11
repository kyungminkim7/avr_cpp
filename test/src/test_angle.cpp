#include <cmath>

#include <gmock/gmock.h>

#include <avr_cpp/angle.h>
#include <avr_cpp/math.h>

using namespace ::testing;
using namespace avr_cpp;

TEST(Angle, DegreeUnderlyingTypeConversion) {
    Degree<float> angle = 4.3f;

    ASSERT_THAT(static_cast<float>(angle), FloatEq(4.3f));
}

TEST(Angle, RadianUnderlyingTypeConversion) {
    Radian<float> angle = 0.3f;

    ASSERT_THAT(static_cast<float>(angle), FloatEq(0.3f));
}

TEST(Angle, DegreeToRadian) {
    Degree<float> degrees = Radian<float>(PI<float>);

    ASSERT_THAT(static_cast<float>(degrees), FloatEq(180.f));
}

TEST(Angle, RadianToDegree) {
    Radian<float> radians = Degree<float>(90.0f);

    ASSERT_THAT(static_cast<float>(radians), FloatEq(PI<float> / 2));
}

TEST(Angle, EqualityReturnsTrue) {
    ASSERT_TRUE(Radian<float>(PI<float> / 4) == Degree<float>(45.0f));
}

TEST(Angle, EqualityReturnsFalse) {
    ASSERT_FALSE(Degree<float>(45.1) == Radian<float>(PI<float> / 4));
}

TEST(Angle, LessThan) {
    ASSERT_THAT(Degree<float>(89.99f), Lt(Radian<float>(PI<float> / 2)));
}

TEST(Angle, LessThanOrEqual) {
    ASSERT_THAT(Degree<float>(89.99f), Le(Radian<float>(PI<float> / 2)));
}

TEST(Angle, GreaterThan) {
    ASSERT_THAT(Radian<float>(PI<float> / 2), Gt(Degree<float>(89.99f)));
}

TEST(Angle, GreaterThanOrEqual) {
    ASSERT_THAT(Radian<float>(PI<float> / 2), Ge(Degree<float>(89.99f)));
}

TEST(Angle, Multiplication) {
    const float product = Radian<float>(PI<float> / 2) * Degree<float>(90.0f);
    ASSERT_THAT(product, FloatEq(std::pow(PI<float> / 2, 2)));
}

TEST(Angle, Division) {
    const float quotient = Degree<float>(180.0f) / Radian<float>(PI<float> / 2);
    ASSERT_THAT(quotient, FloatEq(2.0f));
}

TEST(Angle, Addition) {
    const float sum = Radian<float>(PI<float> / 4) + Degree<float>(90.0f);
    ASSERT_THAT(sum, FloatEq(PI<float> * 3 / 4));
}

TEST(Angle, Subtraction) {
    const Degree<float> difference = Degree<float>(90) - Degree<float>(180);
    ASSERT_THAT(static_cast<float>(difference), FloatEq(270));
}

class AngleDegreeCompoundAssignment : public Test {
public:
    Degree<float> angle = 90.0f;
};

TEST_F(AngleDegreeCompoundAssignment, Addition) {
    angle += Radian<float>(PI<float> / 2);
    
    ASSERT_THAT(static_cast<float>(angle), FloatEq(90 + 90));
}

TEST_F(AngleDegreeCompoundAssignment, Subtraction) {
    angle -= Degree<float>(45.0f);
    
    ASSERT_THAT(static_cast<float>(angle), FloatEq(90 - 45));
}

TEST_F(AngleDegreeCompoundAssignment, Multiplication) {
    angle *= 2.5;
    
    ASSERT_THAT(static_cast<float>(angle), FloatEq(90 * 2.5));
}

TEST_F(AngleDegreeCompoundAssignment, Division) {
    angle /= 2;
    
    ASSERT_THAT(static_cast<float>(angle), FloatEq(90 / 2));
}

class AngleRadianCompoundAssignment : public Test {
public:
    Radian<float> angle = Degree<float>(90.0f);
};

TEST_F(AngleRadianCompoundAssignment, Addition) {
    angle += Radian<float>(PI<float> / 2);
    
    ASSERT_THAT(static_cast<float>(angle), FloatEq(PI<float>));
}

TEST_F(AngleRadianCompoundAssignment, Subtraction) {
    angle -= Degree<float>(45.0f);
    
    ASSERT_THAT(static_cast<float>(angle), FloatEq(PI<float> / 4));
}

TEST_F(AngleRadianCompoundAssignment, Multiplication) {
    angle *= 2;
    
    ASSERT_THAT(static_cast<float>(angle), FloatEq(PI<float>));
}

TEST_F(AngleRadianCompoundAssignment, Division) {
    angle /= 2;
    
    ASSERT_THAT(static_cast<float>(angle), FloatEq(PI<float> / 4));
}

TEST(Angle, DegreeConstructorConvertsOutOfBoundAngles) {
    ASSERT_THAT(static_cast<float>(Degree<float>(360 * 3 + 34)), 
                FloatEq(34));
}

TEST(Angle, DegreeAddAssignConvertsOutOfBoundAngles) {
    Degree<float> angle(300);
    angle += (60 + 24);
    ASSERT_THAT(static_cast<float>(angle), 
                FloatEq(24));
}

TEST(Angle, DegreeSubtractAssignConvertsOutOfBoundAngles) {
    Degree<float> angle(0);
    angle -= (360 + 38);
    ASSERT_THAT(static_cast<float>(angle), 
                FloatEq(-38 + 360));
}

TEST(Angle, DegreeMultiplyAssignConvertsOutOfBoundAngles) {
    Degree<float> angle(270);
    angle *= 2;
    ASSERT_THAT(static_cast<float>(angle), 
                FloatEq(270 * 2 % 360));
}

TEST(Angle, DegreeDivideAssignConvertsOutOfBoundAngles) {
    Degree<float> angle(270);
    angle /= 0.5f;
    ASSERT_THAT(static_cast<float>(angle), 
                FloatEq(270 * 2 % 360));
}

TEST(Angle, RadianConstructorConvertsOutOfBoundAngles) {
    ASSERT_THAT(static_cast<float>(Radian<float>(8 * PI<float> + 1.0f)), 
                FloatEq(1.0f));
}

TEST(Angle, RadianAddAssignConvertsOutOfBoundAngles) {
    Radian<float> angle(PI<float>);
    angle += (PI<float> + 2.0f);
    ASSERT_THAT(static_cast<float>(angle), 
                FloatEq(2.0f));
}

TEST(Angle, RadianSubtractAssignConvertsOutOfBoundAngles) {
    Radian<float> angle(0);
    angle -= (2 * PI<float> + 2.0f);
    ASSERT_THAT(static_cast<float>(angle), 
                FloatEq(-2.0f + 2 * PI<float>));
}

TEST(Angle, RadianMultiplyAssignConvertsOutOfBoundAngles) {
    Radian<float> angle(PI<float>);
    angle *= 2;
    ASSERT_THAT(static_cast<float>(angle), 
                FloatEq(0));
}

TEST(Angle, RadianDivideAssignConvertsOutOfBoundAngles) {
    Radian<float> angle(PI<float>);
    angle /= 0.5f;
    ASSERT_THAT(static_cast<float>(angle), 
                FloatEq(0));
}

TEST(Angle, DegreeAssigningNegativeAngleAdjustsToPositive) {
    Degree<int> angle(-45);

    ASSERT_THAT(static_cast<int>(angle), Eq(-45 + 360));
}

TEST(Angle, RadianAssigningNegativeAngleAdjustsToPositive) {
    Radian<float> angle(-PI<float>);

    ASSERT_THAT(static_cast<float>(angle), FloatEq(PI<float>));
}