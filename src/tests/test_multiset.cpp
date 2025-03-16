#include "s21_tests.h"
TEST(MultisetConstructor, Default) {
  s21::multiset<int> ms;
  EXPECT_TRUE(ms.empty());
}
TEST(MultisetConstructor, InitializerList) {
  s21::multiset<int> ms = {1, 2, 2, 3};
  EXPECT_EQ(ms.size(), 4);
  EXPECT_TRUE(ms.contains(1));
  EXPECT_TRUE(ms.contains(2));
  EXPECT_TRUE(ms.contains(3));

  EXPECT_EQ(ms.count(1), 1);
  EXPECT_EQ(ms.count(2), 2);
  EXPECT_EQ(ms.count(3), 1);
}
TEST(MultisetConstructor, Copy) {
  s21::multiset<int> ms1 = {1, 2, 2, 3};
  s21::multiset<int> ms2(ms1);

  EXPECT_EQ(ms2.size(), 4);
  EXPECT_TRUE(ms2.contains(1));
  EXPECT_TRUE(ms2.contains(2));
  EXPECT_TRUE(ms2.contains(3));
}
TEST(MultisetConstructor, Move) {
  s21::multiset<int> ms1 = {1, 2, 2, 3};
  s21::multiset<int> ms2(std::move(ms1));

  EXPECT_TRUE(ms1.empty());
  EXPECT_EQ(ms2.size(), 4);
  EXPECT_TRUE(ms2.contains(1));
  EXPECT_TRUE(ms2.contains(2));
  EXPECT_TRUE(ms2.contains(3));
}

TEST(MultisetLookup, Count) {
  s21::multiset<int> ms = {1, 2, 2, 2, 3};
  EXPECT_EQ(ms.count(1), 1);
  EXPECT_EQ(ms.count(2), 3);
  EXPECT_EQ(ms.count(3), 1);
  EXPECT_EQ(ms.count(4), 0);
}
TEST(MultisetLookup, Find) {
  s21::multiset<int> ms = {1, 2, 2, 3};
  auto it = ms.find(2);
  EXPECT_NE(it, ms.end());
  EXPECT_EQ(*it, 2);

  it = ms.find(4);
  EXPECT_EQ(it, ms.end());
}
TEST(MultisetLookup, Contains) {
  s21::multiset<int> ms = {1, 2, 2, 3};
  EXPECT_TRUE(ms.contains(1));
  EXPECT_TRUE(ms.contains(2));
  EXPECT_TRUE(ms.contains(3));
  EXPECT_FALSE(ms.contains(4));
}
TEST(MultisetLookup, EqualRange) {
  s21::multiset<int> ms = {1, 2, 2, 2, 3};
  auto range = ms.equal_range(2);

  int count = 0;
  for (auto it = range.first; it != range.second; ++it) {
    EXPECT_EQ(*it, 2);
    count++;
  }
  EXPECT_EQ(count, 3);
}
TEST(MultisetModifiers, Merge) {
  s21::multiset<int> ms1 = {1, 2, 2};
  s21::multiset<int> ms2 = {2, 3, 3};

  ms1.merge(ms2);

  EXPECT_EQ(ms1.size(), 6);
  EXPECT_EQ(ms1.count(1), 1);
  EXPECT_EQ(ms1.count(2), 3);
  EXPECT_EQ(ms1.count(3), 2);
  EXPECT_TRUE(ms2.empty());
}

TEST(multiset_insert, insert_many_test_0) {
  s21::multiset<int> _multiset({5, 4, 1, 0, 2, 1, 4, 3, 3, 2});
  auto v = _multiset.insert_many(1, 90, 10);
  EXPECT_EQ(_multiset.contains(90), 1);
  EXPECT_EQ(_multiset.contains(10), 1);
}