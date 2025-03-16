#include "s21_tests.h"

TEST(Queue_Constructor, Default) {
  s21::queue<int> q1;
  s21::queue<bool> q2;
  s21::queue<double> q3;

  EXPECT_TRUE(q1.empty());
  EXPECT_TRUE(q2.empty());
  EXPECT_TRUE(q3.empty());
}

TEST(Queue_Constructor, Parameterized_constructor) {
  s21::queue<int> q = {1, 2, 3};

  EXPECT_EQ(q.size(), 3);
}

TEST(Queue_Constructor, Copy_constructor) {

  s21::queue<int> q = {1, 2, 3};
  s21::queue<int> copy(q);

  EXPECT_EQ(copy.size(), 3);
  EXPECT_FALSE(q.empty());
}

TEST(Queue_Constructor, Move_constructor) {
  s21::queue<double> q1{1.1, 2.2, 3.3};
  s21::queue<double> q2(std::move(q1));

  EXPECT_TRUE(q1.empty());
  EXPECT_EQ(q2.size(), 3);
}

TEST(Queue_Operator, Assignment_operator) {
  s21::queue<int> q1{1, 2, 3};
  s21::queue<int> q2;
  q2 = (std::move(q1));

  EXPECT_TRUE(q1.empty());
  EXPECT_EQ(q2.size(), 3);
}

TEST(Queue_Element_access, front) {
  s21::queue<int> q{799343, 971007, 36879};

  EXPECT_EQ(q.front(), 799343);
}

TEST(Queue_Element_access, back) {
  s21::queue<int> q{-3, 3434, 244, 0, 1213};

  EXPECT_EQ(q.back(), 1213);
}

TEST(Queue_Element_access, pop) {
  s21::queue<int> q{3213, -78};

  q.pop();

  EXPECT_EQ(q.back(), -78);
  EXPECT_EQ(q.size(), 1);
}

TEST(Queue_Element_access, swap) {
  s21::queue<int> q1{3213, -78};
  s21::queue<int> q2{878, 23123};

  q1.swap(q2);

  EXPECT_EQ(q1.size(), 2);
  EXPECT_EQ(q2.size(), 2);

  EXPECT_EQ(q1.back(), 23123);
  EXPECT_EQ(q2.front(), 3213);
}

TEST(Queue_Modifiers, InsertManyBack) {
  s21::queue<int> q;

  q.insert_many_back(1, 2, 3, 4, 5);

  EXPECT_EQ(q.size(), 5);

  EXPECT_EQ(q.front(), 1);
  q.pop();
  EXPECT_EQ(q.front(), 2);
  q.pop();
  EXPECT_EQ(q.front(), 3);
  q.pop();
  EXPECT_EQ(q.front(), 4);
  q.pop();
  EXPECT_EQ(q.front(), 5);
}