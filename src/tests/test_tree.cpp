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

// TEST(Constructor, InitializerListConstructor) {
//     s21::BSTree<int, int> tree = {{1, 10}, {2, 20}, {3, 30}};
//     EXPECT_EQ(tree.size(), 3);
//     EXPECT_FALSE(tree.empty());
// }

// TEST(Constructor, CopyConstructor) {
//     s21::BSTree<int, int> tree1 = {{1, 10}, {2, 20}};
//     s21::BSTree<int, int> tree2(tree1);
//     EXPECT_EQ(tree2.size(), 2);
//     EXPECT_FALSE(tree2.empty());
// }

// TEST(Constructor, MoveConstructor) {
//     s21::BSTree<int, int> tree1 = {{1, 10}, {2, 20}};
//     s21::BSTree<int, int> tree2(std::move(tree1));
//     EXPECT_EQ(tree2.size(), 2);
//     EXPECT_TRUE(tree1.empty());
// }

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

// TEST(Tree_Modifiers, Size) {
//     s21::BSTree<int, int> tree = {{1, 10}, {2, 20}, {3, 30}, {4, 40}};
//     EXPECT_EQ(tree.size(), 4);
//     tree.clear();
//     EXPECT_EQ(tree.size(), 0);
// }

// TEST(Tree_Modifiers, Clear) {
//     s21::BSTree<int, int> tree = {{1, 10}, {2, 20}};
//     tree.clear();
//     EXPECT_TRUE(tree.empty());
//     EXPECT_EQ(tree.size(), 0);
// }

// TEST(Itearator, BeginEnd) {
//     s21::BSTree<int, int> tree = {{1, 10}, {2, 20}, {3, 30}};
//     auto it = tree.begin();
//     EXPECT_NE(it, tree.end());
// }

TEST(Tree_Modifiers, MaxSizeInt) {
    s21::BSTree<int, int> tree;
    EXPECT_EQ(tree.max_size(), std::numeric_limits<std::size_t>::max() / sizeof(std::pair<int, int>));
}

TEST(Tree_Modifiers, MaxSizeDouble) {
    s21::BSTree<int, double> tree;
    EXPECT_EQ(tree.max_size(), std::numeric_limits<std::size_t>::max() / sizeof(std::pair<int, double>));
}

TEST(Tree_Modifiers, MaxSizeChar) {
    s21::BSTree<int, char> tree;
    EXPECT_EQ(tree.max_size(), std::numeric_limits<std::size_t>::max() / sizeof(std::pair<int, char>));
}

TEST(Tree_Modifiers, MaxSizeString) {
    s21::BSTree<int, std::string> tree;
    EXPECT_EQ(tree.max_size(), std::numeric_limits<std::size_t>::max() / sizeof(std::pair<int, std::string>));
}
