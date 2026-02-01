
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
