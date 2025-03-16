#include "s21_tests.h"

TEST(Map_Constructor, Default) {
  s21::map<int, int> map_;
  EXPECT_TRUE(map_.empty());
}

TEST(Map_Constructor, InitializerList) {
  s21::map<int, int> map_({{3, 30}, {1, 10}, {2, 20}});
  EXPECT_EQ(map_.size(), 3);
  EXPECT_EQ(map_.at(1), 10);
  EXPECT_EQ(map_.at(2), 20);
  EXPECT_EQ(map_.at(3), 30);
}

TEST(Map_Constructor, Copy) {
  s21::map<int, int> map_({{1, 10}, {2, 20}});
  s21::map<int, int> copy(map_);
  EXPECT_EQ(copy.size(), 2);
  EXPECT_EQ(copy.at(1), 10);
  EXPECT_EQ(copy.at(2), 20);
}

TEST(Map_Constructor, Move) {
  s21::map<int, int> map_({{1, 10}, {2, 20}});
  size_t original_size = map_.size();

  s21::map<int, int> moved(std::move(map_));

  EXPECT_EQ(moved.size(), original_size);
  EXPECT_EQ(moved.at(1), 10);
  EXPECT_EQ(moved.at(2), 20);

  EXPECT_TRUE(map_.empty());
  EXPECT_EQ(map_.size(), 0);
  EXPECT_THROW(map_.at(1), std::out_of_range);
  EXPECT_THROW(map_.at(2), std::out_of_range);
}

TEST(Map_Operator, Assignment) {
  s21::map<int, int> map1({{1, 10}, {2, 20}});
  s21::map<int, int> map2;
  map2 = std::move(map1);
  EXPECT_EQ(map2.size(), 2);
  EXPECT_TRUE(map1.empty());
}

TEST(Map_Operator, Brackets) {
  s21::map<int, int> map_;
  map_[1] = 42;
  EXPECT_EQ(map_[1], 42);
  EXPECT_EQ(map_.size(), 1);
}

TEST(Map_Access, At) {
  s21::map<int, int> map_({{1, 10}});
  EXPECT_EQ(map_.at(1), 10);
  EXPECT_THROW(map_.at(2), std::out_of_range);
}

TEST(Map_Capacity, Emptysize) {
  s21::map<int, int> map_;
  EXPECT_TRUE(map_.empty());
  EXPECT_EQ(map_.size(), 0);
  map_.insert({1, 10});
  EXPECT_FALSE(map_.empty());
  EXPECT_EQ(map_.size(), 1);
}

TEST(Map_Modifiers, Insert) {
  s21::map<int, int> map_;
  auto res = map_.insert({1, 10});
  EXPECT_TRUE(res.second);
  EXPECT_EQ(map_.size(), 1);
  EXPECT_FALSE(map_.insert({1, 20}).second);
}

TEST(Map_Modifiers, InsertOrAssignNewNode) {
  s21::map<int, int> map_;

  auto res1 = map_.insert_or_assign(5, 50);
  EXPECT_TRUE(res1.second);
  EXPECT_EQ(map_.at(5), 50);
  EXPECT_EQ(map_.size(), 1);

  auto res2 = map_.insert_or_assign(3, 30);
  EXPECT_TRUE(res2.second);
  EXPECT_EQ(map_.size(), 2);
}

TEST(Map_Modifiers, InsertOrAssign) {
  s21::map<int, int> map_;
  map_.insert_or_assign(1, 10);
  EXPECT_EQ(map_.at(1), 10);
  map_.insert_or_assign(1, 20);
  EXPECT_EQ(map_.at(1), 20);
}

TEST(Map_Modifiers, Erase_Test) {
  s21::map<int, int> map1;
  auto i = map1.insert(5, 9).first;
  map1.erase(i);
  EXPECT_THROW(map1.at(5), std::out_of_range);
}

TEST(Map_Modifiers, Erase_Leaf_Node) {
  s21::map<int, int> map1;
  map1.insert(5, 50);
  map1.insert(3, 30);
  map1.insert(7, 70);

  auto it = map1.find(3);
  map1.erase(it);

  EXPECT_EQ(map1.size(), 2);
  EXPECT_FALSE(map1.contains(3));
  EXPECT_TRUE(map1.contains(5));
  EXPECT_TRUE(map1.contains(7));
  EXPECT_THROW(map1.at(3), std::out_of_range);
}

TEST(Map_Modifiers, Erase_One_Child_Node) {
  s21::map<int, int> map1;
  map1.insert(5, 50);
  map1.insert(3, 30);
  map1.insert(7, 70);
  map1.insert(6, 60);

  auto it = map1.find(7);
  map1.erase(it);

  EXPECT_EQ(map1.size(), 3);
  EXPECT_FALSE(map1.contains(7));
  EXPECT_TRUE(map1.contains(5));
  EXPECT_TRUE(map1.contains(3));
  EXPECT_TRUE(map1.contains(6));
  EXPECT_THROW(map1.at(7), std::out_of_range);
}
TEST(Map_Modifiers, Erase_Node_With_Two_Children) {
  s21::map<int, int> map1;
  map1.insert(5, 50);
  map1.insert(3, 30);
  map1.insert(7, 70);
  map1.insert(2, 20);
  map1.insert(4, 40);
  map1.insert(6, 60);
  map1.insert(8, 80);

  auto it = map1.find(3);
  map1.erase(it);

  EXPECT_EQ(map1.size(), 6);
  EXPECT_FALSE(map1.contains(3));
  EXPECT_TRUE(map1.contains(2));
  EXPECT_TRUE(map1.contains(4));
  EXPECT_TRUE(map1.contains(5));
  EXPECT_TRUE(map1.contains(6));
  EXPECT_TRUE(map1.contains(7));
  EXPECT_TRUE(map1.contains(8));
}
TEST(Map_Modifiers, Erase_Root_Node) {
  s21::map<int, int> map1;
  map1.insert(5, 50);
  map1.insert(3, 30);
  map1.insert(7, 70);

  auto it = map1.find(5);
  map1.erase(it);

  EXPECT_EQ(map1.size(), 2);
  EXPECT_FALSE(map1.contains(5));
  EXPECT_TRUE(map1.contains(3));
  EXPECT_TRUE(map1.contains(7));
}

TEST(Map_Modifiers, Erase_Successor_Node) {
  s21::map<int, int> map1;
  map1.insert(5, 50);
  map1.insert(3, 30);
  map1.insert(8, 80);
  map1.insert(7, 70);
  map1.insert(9, 90);

  auto it = map1.find(5);
  map1.erase(it);

  EXPECT_EQ(map1.size(), 4);
  EXPECT_FALSE(map1.contains(5));
  EXPECT_TRUE(map1.contains(3));
  EXPECT_TRUE(map1.contains(7));
  EXPECT_TRUE(map1.contains(8));
  EXPECT_TRUE(map1.contains(9));
}

TEST(Map_Modifiers, Swap) {
  s21::map<int, int> map1({{1, 10}});
  s21::map<int, int> map2({{2, 20}});
  map1.swap(map2);
  EXPECT_EQ(map1.at(2), 20);
  EXPECT_EQ(map2.at(1), 10);
}

TEST(Map_Modifiers, Merge) {
  s21::map<int, int> map1({{1, 10}});
  s21::map<int, int> map2({{2, 20}});
  map1.merge(map2);
  EXPECT_EQ(map1.size(), 2);
  EXPECT_TRUE(map2.empty());
}

TEST(Map_Lookup, Contains) {
  s21::map<int, int> map_({{1, 10}});
  EXPECT_TRUE(map_.contains(1));
  EXPECT_FALSE(map_.contains(2));
}

TEST(Map_Operator, BracketsTreeTraversal) {
  s21::map<int, int> map_;

  map_[5] = 50;
  EXPECT_EQ(map_[5], 50);
  EXPECT_EQ(map_.size(), 1);

  map_[3] = 30;
  EXPECT_EQ(map_[3], 30);
  EXPECT_EQ(map_.size(), 2);

  map_[7] = 70;
  EXPECT_EQ(map_[7], 70);
  EXPECT_EQ(map_.size(), 3);

  EXPECT_EQ(map_[5], 50);
  EXPECT_EQ(map_[3], 30);
  EXPECT_EQ(map_[7], 70);

  map_[3] = 35;
  EXPECT_EQ(map_[3], 35);
  EXPECT_EQ(map_.size(), 3);
}

TEST(Map_Modifiers, InsertMany) {
  s21::map<int, int> map_;
  auto results = map_.insert_many(std::make_pair(1, 10), std::make_pair(2, 20),
                                  std::make_pair(3, 30));

  EXPECT_EQ(results.size(), 3);

  EXPECT_TRUE(results[0].second);
  EXPECT_TRUE(results[1].second);
  EXPECT_TRUE(results[2].second);

  EXPECT_EQ(map_.at(1), 10);
  EXPECT_EQ(map_.at(2), 20);
  EXPECT_EQ(map_.at(3), 30);

  auto duplicate_results =
      map_.insert_many(std::make_pair(1, 100), std::make_pair(4, 40));

  EXPECT_EQ(duplicate_results.size(), 2);
  EXPECT_FALSE(duplicate_results[0].second);
  EXPECT_TRUE(duplicate_results[1].second);
}