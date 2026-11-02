#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
    ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
    ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
    ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
    TDynamicMatrix<int> m(5);

    ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
    TDynamicMatrix<int> m(3);

    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            m[i][j] = i * 3 + j;

    TDynamicMatrix<int> m1(m);

    EXPECT_TRUE(m == m1);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
    TDynamicMatrix<int> m(3);

    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            m[i][j] = i + j;

    TDynamicMatrix<int> m1(m);

    m[0][0] = 99;

    EXPECT_NE(m[0][0], m1[0][0]);
}

TEST(TDynamicMatrix, can_get_size)
{
    TDynamicMatrix<int> m(4);

    EXPECT_NO_THROW(m.at(3));
    EXPECT_ANY_THROW(m.at(4));
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
    TDynamicMatrix<int> m(3);

    m[0][0] = 1;
    m[1][2] = 5;
    m[2][1] = 10;

    EXPECT_EQ(1, m[0][0]);
    EXPECT_EQ(5, m[1][2]);
    EXPECT_EQ(10, m[2][1]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
    TDynamicMatrix<int> m(3);

    EXPECT_ANY_THROW(m.at(-1));
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
    TDynamicMatrix<int> m(3);

    EXPECT_ANY_THROW(m.at(3));
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
    TDynamicMatrix<int> m(3);

    m[0][0] = 10;
    m[1][1] = 20;
    m[2][2] = 30;

    ASSERT_NO_THROW(m = m);

    EXPECT_EQ(10, m[0][0]);
    EXPECT_EQ(20, m[1][1]);
    EXPECT_EQ(30, m[2][2]);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
    TDynamicMatrix<int> m1(3);
    TDynamicMatrix<int> m2(3);

    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            m1[i][j] = i + j;

    m2 = m1;

    EXPECT_TRUE(m1 == m2);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
    TDynamicMatrix<int> m1(2);
    TDynamicMatrix<int> m2(4);

    m2[3][3] = 100;

    m1 = m2;

    EXPECT_NO_THROW(m1[3]);
    EXPECT_ANY_THROW(m1.at(4));
    EXPECT_TRUE(m1 == m2);
    EXPECT_EQ(100, m1[3][3]);
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
    TDynamicMatrix<int> m1(2);
    TDynamicMatrix<int> m2(3);

    m2[0][0] = 10;
    m2[1][1] = 20;
    m2[2][2] = 30;

    ASSERT_NO_THROW(m1 = m2);

    EXPECT_EQ(30, m1[2][2]);
    EXPECT_TRUE(m1 == m2);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
    TDynamicMatrix<int> m1(3);
    TDynamicMatrix<int> m2(3);

    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
        {
            m1[i][j] = i + j;
            m2[i][j] = i + j;
        }

    EXPECT_TRUE(m1 == m2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
    TDynamicMatrix<int> m(3);

    EXPECT_TRUE(m == m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
    TDynamicMatrix<int> m1(2);
    TDynamicMatrix<int> m2(3);

    EXPECT_FALSE(m1 == m2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
    TDynamicMatrix<int> m1(2);
    TDynamicMatrix<int> m2(2);

    m1[0][0] = 1;
    m1[0][1] = 2;
    m1[1][0] = 3;
    m1[1][1] = 4;

    m2[0][0] = 5;
    m2[0][1] = 6;
    m2[1][0] = 7;
    m2[1][1] = 8;

    TDynamicMatrix<int> res = m1 + m2;

    EXPECT_EQ(6, res[0][0]);
    EXPECT_EQ(8, res[0][1]);
    EXPECT_EQ(10, res[1][0]);
    EXPECT_EQ(12, res[1][1]);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
    TDynamicMatrix<int> m1(2);
    TDynamicMatrix<int> m2(3);

    EXPECT_ANY_THROW(m1 + m2);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
    TDynamicMatrix<int> m1(2);
    TDynamicMatrix<int> m2(2);

    m1[0][0] = 5;
    m1[0][1] = 6;
    m1[1][0] = 7;
    m1[1][1] = 8;

    m2[0][0] = 1;
    m2[0][1] = 2;
    m2[1][0] = 3;
    m2[1][1] = 4;

    TDynamicMatrix<int> res = m1 - m2;

    EXPECT_EQ(4, res[0][0]);
    EXPECT_EQ(4, res[0][1]);
    EXPECT_EQ(4, res[1][0]);
    EXPECT_EQ(4, res[1][1]);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
    TDynamicMatrix<int> m1(2);
    TDynamicMatrix<int> m2(3);

    EXPECT_ANY_THROW(m1 - m2);
}

