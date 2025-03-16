#include "s21_tests.h"

TEST(Constructor, Default_Tree) {
  s21::BSTree<int, int> numbers;
  s21::BSTree<std::string, std::string> strings;
  s21::BSTree<int, bool> bools;

  EXPECT_TRUE(numbers.empty());
  EXPECT_EQ(numbers.size(), 0);

  EXPECT_TRUE(strings.empty());
  EXPECT_EQ(strings.size(), 0);

  EXPECT_TRUE(bools.empty());
  EXPECT_EQ(bools.size(), 0);
}

TEST(Constructor, InitializerListConstructor) {
  s21::BSTree<int, int> tree = {{1, 10}, {2, 20}, {3, 30}};
  EXPECT_EQ(tree.size(), 3);
  EXPECT_FALSE(tree.empty());
}

TEST(Constructor, CopyConstructor) {
  s21::BSTree<int, int> tree1 = {{1, 10}, {2, 20}};
  s21::BSTree<int, int> tree2(tree1);
  EXPECT_EQ(tree2.size(), 2);
  EXPECT_FALSE(tree2.empty());
}

TEST(Constructor, MoveAssignmentEmptyTree) {
  s21::BSTree<int, int> tree1;
  s21::BSTree<int, int> tree2;

  tree1 = std::move(tree2);

  EXPECT_TRUE(tree1.empty());
  EXPECT_TRUE(tree2.empty());
  EXPECT_EQ(tree1.size(), 0);
  EXPECT_EQ(tree2.size(), 0);
}

TEST(Tree_Modifiers, Empty) {
  s21::BSTree<int, int> numbers;
  s21::BSTree<std::string, std::string> strings;
  s21::BSTree<int, bool> bools;

  EXPECT_TRUE(numbers.empty());
  EXPECT_EQ(numbers.size(), 0);

  EXPECT_TRUE(strings.empty());
  EXPECT_EQ(strings.size(), 0);

  EXPECT_TRUE(bools.empty());
  EXPECT_EQ(bools.size(), 0);
}

TEST(Tree_Modifiers, Clear) {
  s21::BSTree<int, int> tree = {{1, 10}, {2, 20}};

  EXPECT_FALSE(tree.empty());
  EXPECT_EQ(tree.size(), 2);

  tree.clear();

  EXPECT_TRUE(tree.empty());
  EXPECT_EQ(tree.size(), 0);
}

TEST(Itearator, BeginEnd) {
  s21::BSTree<int, int> tree = {{1, 10}, {2, 20}, {3, 30}};
  auto it = tree.begin();
  EXPECT_NE(it, tree.end());
}

TEST(Tree_Modifiers, MaxSizeInt) {
  s21::BSTree<int, int> tree;
  EXPECT_EQ(tree.max_size(), std::numeric_limits<std::size_t>::max() /
                                 sizeof(std::pair<int, int>));
}

TEST(Tree_Modifiers, MaxSizeDouble) {
  s21::BSTree<int, double> tree;
  EXPECT_EQ(tree.max_size(), std::numeric_limits<std::size_t>::max() /
                                 sizeof(std::pair<int, double>));
}

TEST(Tree_Modifiers, MaxSizeChar) {
  s21::BSTree<int, char> tree;
  EXPECT_EQ(tree.max_size(), std::numeric_limits<std::size_t>::max() /
                                 sizeof(std::pair<int, char>));
}

TEST(Tree_Modifiers, MaxSizeString) {
  s21::BSTree<int, std::string> tree;
  EXPECT_EQ(tree.max_size(), std::numeric_limits<std::size_t>::max() /
                                 sizeof(std::pair<int, std::string>));
}

// TEST(Tree_Operator, BracketsOperatorExistingKey) {
//     s21::BSTree<int, std::string> tree;
//     tree.insert(1, "one");
//     tree.insert(2, "two");

//     EXPECT_EQ(tree[1], "one");
//     EXPECT_EQ(tree[2], "two");
//     EXPECT_EQ(tree.size(), 2);
// }
// TEST(Tree_Operator, BracketsOperatorNewKey) {
//     s21::BSTree<int, std::string> tree;

//     // Insert new element using operator[]
//     tree[1] = "one";
//     EXPECT_EQ(tree.size(), 1);
//     EXPECT_EQ(tree[1], "one");

//     // Check automatic node creation when accessing non-existent key
//     std::string& value = tree[2];
//     EXPECT_EQ(tree.size(), 2);
//     value = "two";
//     EXPECT_EQ(tree[2], "two");
// }
// TEST(Tree_Operator, BracketsOperatorIntKeys) {
//     s21::BSTree<int, std::string> tree;

//     // Test with integer keys
//     tree[42] = "forty-two";
//     tree[100] = "hundred";
//     tree[-1] = "minus one";

//     EXPECT_EQ(tree.size(), 3);
//     EXPECT_EQ(tree[42], "forty-two");
//     EXPECT_EQ(tree[100], "hundred");
//     EXPECT_EQ(tree[-1], "minus one");

//     // Test updating existing values
//     tree[42] = "new forty-two";
//     EXPECT_EQ(tree[42], "new forty-two");
// }

TEST(Tree_Balance, InsertBalance) {
  s21::BSTree<int, int> tree;

  tree.insert(3, 3);
  tree.insert(2, 2);
  tree.insert(1, 1);

  auto it = tree.begin();
  EXPECT_EQ(it->key, 1);
  ++it;
  EXPECT_EQ(it->key, 2);
  ++it;
  EXPECT_EQ(it->key, 3);

  s21::BSTree<int, int> tree2;
  tree2.insert(1, 1);
  tree2.insert(2, 2);
  tree2.insert(3, 3);

  auto it2 = tree2.begin();
  EXPECT_EQ(it2->key, 1);
}
TEST(Tree_Balance, DeleteBalance) {
  s21::BSTree<int, int> tree;

  tree.insert(5, 5);
  tree.insert(3, 3);
  tree.insert(7, 7);
  tree.insert(2, 2);
  tree.insert(4, 4);

  auto it = tree.find(3);
  tree.erase(it);

  it = tree.begin();
  EXPECT_EQ(it->key, 2);
}
TEST(Tree_Balance, ComplexBalance) {
  s21::BSTree<int, int> tree;

  tree.insert(5, 5);
  tree.insert(3, 3);
  tree.insert(7, 7);
  tree.insert(2, 2);
  tree.insert(4, 4);
  tree.insert(6, 6);
  tree.insert(8, 8);
  tree.insert(1, 1);

  auto it = tree.begin();
  EXPECT_EQ(it->key, 1);

  tree.erase(tree.find(3));
  it = tree.begin();
  EXPECT_EQ(it->key, 1);
}

TEST(Tree_Balance, BigRotateLeft) {
  s21::BSTree<int, int> tree;

  tree.insert(10, 10);
  tree.insert(15, 15);
  tree.insert(12, 12);

  EXPECT_EQ(tree.begin()->key, 10);
  auto it = tree.begin();
  ++it;
  EXPECT_EQ(it->key, 12);
  ++it;
  EXPECT_EQ(it->key, 15);

  it = tree.begin();
  ++it;
  EXPECT_EQ(it->key, 12);

  it = tree.begin();
  EXPECT_EQ(it->key, 10);

  it = tree.begin();
  ++it;
  ++it;
  EXPECT_EQ(it->key, 15);
  EXPECT_EQ(tree.size(), 3);
}