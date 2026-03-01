
#include <gtest/gtest.h>

#include "Vec.h"
#include "Types.h"

using namespace TUI;


TEST(Vec2, DefaultConstructor) {

    const Vec2<s32> signedVec;
    EXPECT_EQ(signedVec.getX(), 0);
    EXPECT_EQ(signedVec.getY(), 0);

    const Vec2<u32> unsignedVec;
    EXPECT_EQ(unsignedVec.getWidth(), 0);
    EXPECT_EQ(unsignedVec.getHeight(), 0);
}


TEST(Vec2, ParameterConstructor) {

    const Vec2<s32> signedVec(11, 27);

    EXPECT_EQ(signedVec.getX(), 11);
    EXPECT_EQ(signedVec.getY(), 27);

    EXPECT_EQ(signedVec.getWidth(), 11);
    EXPECT_EQ(signedVec.getHeight(), 27);

    const Vec2<u32> unsignedVec(99, 100);

    EXPECT_EQ(unsignedVec.getX(), 99);
    EXPECT_EQ(unsignedVec.getY(), 100);
    EXPECT_EQ(unsignedVec.getWidth(), 99);
    EXPECT_EQ(unsignedVec.getHeight(), 100);
}


TEST(Vec2, Destructor) {

    const Vec2<s32>* signedVector = new Vec2<s32>(1, 1);
    delete signedVector;

    const Vec2<u32>* unsignedVector = new Vec2<u32>();
    delete unsignedVector;

    const Vec2<f32>* floatVector = new Vec2<f32>(1.0f, 1.0f);
    delete floatVector;
}


TEST(Vec2, getArea) {

    const Vec2<s32> signedVec(13, 17);

    EXPECT_EQ(signedVec.getArea(), 13 * 17);

    const Vec2<u32> unsignedVec(11, 11);

    EXPECT_EQ(unsignedVec.getArea(), 11 * 11);
}


TEST(Vec2, addOperator) {

    const Vec2<s32> vec1(11, 15);
    const Vec2<s32> vec2(4, 6);

    const Vec2<s32> result = vec1 + vec2;

    EXPECT_EQ(result.getX(), 15);
    EXPECT_EQ(result.getY(), 21);
}


TEST(Vec2, subOperator) {

    const Vec2<s32> vec1(10, 14);
    const Vec2<s32> vec2(17, -3);

    const Vec2<s32> result = vec1 - vec2;

    EXPECT_EQ(result.getX(), -7);
    EXPECT_EQ(result.getY(), 17);
}


TEST(Vec2, multOperator) {

    const Vec2<s32> vec(3, 7);
    const Vec2<s32> result = vec * 2;

    EXPECT_EQ(result.getX(), 6);
    EXPECT_EQ(result.getY(), 14);
}


TEST(Vec2, incrementOperator) {

    Vec2<s32> vec1(6, 9);

    vec1 += Vec2<s32>(11, -4);

    EXPECT_EQ(vec1.getX(), 17);
    EXPECT_EQ(vec1.getY(), 5);

    vec1 += Vec2<s32>(0, 1);

    EXPECT_EQ(vec1.getX(), 17);
    EXPECT_EQ(vec1.getY(), 6);

    vec1 += Vec2<s32>(1, 0);

    EXPECT_EQ(vec1.getX(), 18);
    EXPECT_EQ(vec1.getY(), 6);
}


TEST(Vec2, implicitConversion) {

    { // Signed to unsigned conversion

        const Vec2<s32> vec1(7, 3);
        const Vec2<u32> vec2 = vec1;

        EXPECT_EQ(vec2.getX(), 7);
        EXPECT_EQ(vec2.getY(), 3);
    }

    { // float to int conversion

        const Vec2<f32> vec1(13.4f, 7.7f);
        const Vec2<s32> vec2 = vec1;

        EXPECT_EQ(vec2.getX(), 13);
        EXPECT_EQ(vec2.getY(), 7);
    }
}
