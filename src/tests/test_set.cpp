#include "s21_tests.h"
TEST(Set_Iterator, Dereference) {
  s21::set<int> set = {42, 2, 3};
  auto it = set.begin();

  int value = *it;
  EXPECT_EQ(value, 2);
  ++it;
  EXPECT_EQ(*it, 3);
}

TEST(Set_Insert, Return_Value) {
  s21::set<int> set;
  auto res = set.insert(42);

  EXPECT_TRUE(res.second);
  int value = *(res.first);
  EXPECT_EQ(value, 42);

  auto res2 = set.insert(42);
  EXPECT_FALSE(res2.second);
  EXPECT_EQ(*(res2.first), 42);
}

TEST(Set_Constructor, MoveConstructor) {
  s21::set<int> s1 = {1, 2, 3};
  s21::set<int> s2(std::move(s1));
  EXPECT_EQ(s2.size(), 3);
  EXPECT_TRUE(s1.empty());
}

TEST(Set_Operator, MoveAssignmentOperator) {
  s21::set<int> s1 = {1, 2, 3};
  s21::set<int> s2;
  s2 = std::move(s1);
  EXPECT_EQ(s2.size(), 3);
  EXPECT_TRUE(s1.empty());
}

TEST(Set_Modifiers, Insert) {
  s21::set<int> s;
  auto res = s.insert(42);
  EXPECT_TRUE(res.second);
  EXPECT_EQ(*res.first, 42);
  EXPECT_EQ(s.size(), 1);

  auto res2 = s.insert(42);
  EXPECT_FALSE(res2.second);
  EXPECT_EQ(s.size(), 1);
}

TEST(Set_Modifiers, Swap) {
  s21::set<int> s1 = {1, 2, 3};
  s21::set<int> s2 = {4, 5, 6};
  s1.swap(s2);
  EXPECT_EQ(s1.size(), 3);
  EXPECT_TRUE(s1.contains(4));
  EXPECT_TRUE(s1.contains(5));
  EXPECT_TRUE(s1.contains(6));
  EXPECT_EQ(s2.size(), 3);
  EXPECT_TRUE(s2.contains(1));
  EXPECT_TRUE(s2.contains(2));
  EXPECT_TRUE(s2.contains(3));
}

TEST(Set_Lookup, Find) {
  s21::set<int> s = {1, 2, 3};
  auto it = s.find(2);
  EXPECT_NE(it, s.end());
  EXPECT_EQ(*it, 2);

  it = s.find(42);
  EXPECT_EQ(it, s.end());
}

TEST(Set_Lookup, Contains) {
  s21::set<int> s = {1, 2, 3};
  EXPECT_TRUE(s.contains(1));
  EXPECT_TRUE(s.contains(2));
  EXPECT_TRUE(s.contains(3));
  EXPECT_FALSE(s.contains(42));
}

TEST(SetTest, Clear) {
  s21::set<int> s = {1, 2, 3};
  s.clear();
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0);
}

TEST(Set_Modifiers, MaxSize) {
  s21::set<int> s;
  EXPECT_GT(s.max_size(), 0);
}

TEST(Set_Iterator, Iterator) {
  s21::set<int> s = {1, 2, 3};
  auto it = s.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(it, s.end());
}

TEST(Set_Iterator, ConstIterator) {
  const s21::set<int> s = {1, 2, 3};
  auto it = s.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(it, s.end());
}

TEST(Set_Modifiers, InsertMany) {
  s21::set<int> s;
  auto results = s.insert_many(1, 2, 3, 2, 4);

  EXPECT_EQ(s.size(), 4);

  EXPECT_TRUE(s.contains(1));
  EXPECT_TRUE(s.contains(2));
  EXPECT_TRUE(s.contains(3));
  EXPECT_TRUE(s.contains(4));

  EXPECT_EQ(results.size(), 5);

  EXPECT_TRUE(results[0].second);
  EXPECT_FALSE(results[1].second);
  EXPECT_TRUE(results[2].second);
  EXPECT_FALSE(results[3].second);
  EXPECT_TRUE(results[4].second);
}