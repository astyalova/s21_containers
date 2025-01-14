#include "s21_tests.h"

TEST(Constructor, Default_stack) {
    s21::stack<int> i;
    s21::stack<double> d;
    s21::stack<std::string> str;

    EXPECT_TRUE(i.empty());
    EXPECT_TRUE(d.empty());
    EXPECT_TRUE(str.empty());
}

TEST(Constructor, Initializer_list_constructor_stack) {
    s21::stack<int> i{1, 2, 3, 4, -5, 6};
    s21::stack<double> d{6.5, -7.8, 4.5};
    s21::stack<std::string> str{"st", "v", "hh", "lll"};

    EXPECT_FALSE(i.empty());
    EXPECT_EQ(i.size(), 6);

    EXPECT_FALSE(d.empty());
    EXPECT_EQ(d.size(), 3);

    EXPECT_FALSE(str.empty());
    EXPECT_EQ(str.size(), 4);
}

TEST(Constructor, Copy_constructor_stack) {
    s21::stack<int> i{1, 2, 3, 4, -5, 6};
    s21::stack<int> copy_i(i);

    EXPECT_EQ(copy_i.size(), 6);
    while (!copy_i.empty()) {
        EXPECT_EQ(copy_i.top(), i.top());
        copy_i.pop();
        i.pop();
    }
}

TEST(Constructor, Move_constructor_stack) {
    s21::stack<int> i{1, 2, 3, 4, -5, 6};
    s21::stack<int> moved_i(std::move(i));

    EXPECT_TRUE(i.empty());
    EXPECT_FALSE(moved_i.empty());
    EXPECT_EQ(moved_i.size(), 6);
}

TEST(Operator, Move_assignment_operator_stack) {
    s21::stack<int> steck1{1, 2, 3};
    s21::stack<int> steck2;

    steck2 = std::move(steck1);
    EXPECT_TRUE(steck1.empty());
    EXPECT_FALSE(steck2.empty());
    EXPECT_EQ(steck2.size(), 3);
}

TEST(Element_access, Top_stack) {
    s21::stack<int> steck{1, 2, 3, 4};
    EXPECT_EQ(steck.top(), 4);

    steck.pop();
    EXPECT_EQ(steck.top(), 3);
}

TEST(stack_Capacity, Empty_stack) {
    s21::stack<int> steck;
    EXPECT_TRUE(steck.empty());

    steck.push(1);
    EXPECT_FALSE(steck.empty());
}

TEST(stack_Capacity, Size_stack) {
    s21::stack<int> steck{1, 2, 3};
    EXPECT_EQ(steck.size(), 3);

    steck.pop();
    EXPECT_EQ(steck.size(), 2);
}

TEST(stack_Modifiers, Push_stack) {
    s21::stack<int> steck;
    steck.push(5);
    steck.push(10);

    EXPECT_EQ(steck.size(), 2);
}

TEST(stack_Modifiers, Pop_stack) {
    s21::stack<int> steck {2, 4, 6, 8};
    EXPECT_EQ(steck.top(), 8);
    EXPECT_EQ(steck.size(), 4);

    steck.pop();
    EXPECT_EQ(steck.top(), 6);
    EXPECT_EQ(steck.size(), 3);
}

TEST(stack_Modifiers, Swap_stack) {
    s21::stack<int> steck1{1, 2, 3};
    s21::stack<int> steck2{4, 5, 6, 7};

    steck1.swap(steck2);

    EXPECT_EQ(steck1.top(), 7);
    EXPECT_EQ(steck2.top(), 3);
    EXPECT_EQ(steck1.size(), 4);
    EXPECT_EQ(steck2.size(), 3);
}
