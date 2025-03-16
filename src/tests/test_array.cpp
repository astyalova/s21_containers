#include "s21_tests.h"

TEST(Array_Constructor, Default) {
  s21::array<int, 5> arr;
  s21::array<int, 0> arr2;
  s21::array<double, 3> arr3;

  EXPECT_EQ(arr.size(), 5);
  EXPECT_TRUE(arr2.empty());
  EXPECT_EQ(arr3.size(), 3);
}

TEST(Array_Constructor, Parameterized_constructor) {
  s21::array<int, 5> arr{443, 342, 132, 0, 2};
  s21::array<std::string, 2> arr2{"ewrew", "wereewre"};
  s21::array<double, 3> arr3{0.0, 1.1, -2.2};

  EXPECT_EQ(arr.size(), 5);
  EXPECT_EQ(arr2.size(), 2);
  EXPECT_EQ(arr3.size(), 3);
}

TEST(Array_Constructor, Copy_constructor) {
  s21::array<int, 5> arr{443, 342, 132, 0, 2};
  s21::array<int, 5> copy(arr);

  EXPECT_EQ(arr.size(), 5);
  EXPECT_EQ(copy.size(), 5);

  for (size_t j = 0; j < arr.size(); ++j) {
    EXPECT_EQ(copy[j], arr[j]);
  }

  s21::array<bool, 2> arr2{true, false};
  s21::array<bool, 2> copy2(arr2);

  EXPECT_EQ(arr2.size(), 2);
  EXPECT_EQ(copy2.size(), 2);

  for (size_t j = 0; j < arr2.size(); ++j) {
    EXPECT_EQ(copy2[j], arr2[j]);
  }
}

TEST(Array_Constructor, Move_constructor) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  s21::array<int, 5> move(std::move(arr));

  EXPECT_TRUE(arr.empty());
  EXPECT_EQ(move.size(), 5);

  s21::array<std::string, 3> str{"23dsdd", "wewesz", "ddsc"};
  s21::array<std::string, 3> str_copy(std::move(str));

  EXPECT_TRUE(str.empty());
  EXPECT_EQ(str_copy.size(), 3);
}

TEST(Array_Operator, Assignment_operator) {
  s21::array<double, 4> arr1{432432.2, 2432432.32, 0.0, -23132.2};
  s21::array<double, 4> arr2;
  arr2 = std::move(arr1);

  EXPECT_FALSE(arr2.empty());
  EXPECT_EQ(arr2.size(), 4);

  s21::array<int, 5> arr3{432432, 2432432, 0, -23132, -4};
  s21::array<int, 5> arr4;
  arr4 = std::move(arr3);

  EXPECT_FALSE(arr4.empty());
  EXPECT_EQ(arr3.size(), 5);
}

TEST(Array_Operator, At) {
  s21::array<bool, 3> arr1{true, false, false};

  EXPECT_TRUE(arr1.at(0));
  EXPECT_FALSE(arr1.at(1));
  EXPECT_FALSE(arr1.at(2));
  EXPECT_THROW(arr1.at(10), std::out_of_range);

  s21::array<int, 4> arr2{1, 2, 3, 4};

  EXPECT_TRUE(arr1.at(0));
  EXPECT_FALSE(arr1.at(1));
  EXPECT_FALSE(arr1.at(2));
  EXPECT_THROW(arr2.at(7), std::out_of_range);
}

TEST(Array_element_access, Front) {
  s21::array<std::string, 3> str{"sdsds", "dfedfe", "dfdfd"};
  s21::array<char, 0> arr;

  EXPECT_EQ(str.front(), "sdsds");
  EXPECT_THROW(arr.front(), std::out_of_range);
}

TEST(Array_element_access, Back) {
  s21::array<double, 3> str{0.0, -1.1, -2.34};
  s21::array<int, 0> arr;

  EXPECT_EQ(str.back(), -2.34);
  EXPECT_THROW(arr.back(), std::out_of_range);
}

TEST(Array_Element_access, Data) {
  s21::array<int, 3> arr{4323434, 3244324, 5465};
  int *value = arr.data();

  EXPECT_EQ(value[0], 4323434);
}

TEST(Array_Iterators, Begin) {
  s21::array<int, 4> arr{32, 223, 3432};
  s21::array<int, 4>::iterator it = arr.begin();

  EXPECT_EQ(*it, 32);

  std::advance(it, 2);

  EXPECT_EQ(*it, 3432);
}

TEST(Array_Iterators, End) {
  s21::array<int, 10> arr{1, -2, 3, 4, -5, 6, 7, 8, 9, 10};

  EXPECT_EQ(arr.end(), arr.begin() + 10);
}

TEST(Array_Capacity, Max_Size) {
  s21::array<int, 0> arr;
  s21::array<double, 0> arr_double;
  s21::array<char, 0> arr_char;
  s21::array<std::string, 0> arr_str;

  EXPECT_EQ(arr.max_size(), 0);
  EXPECT_EQ(arr_double.max_size(), 0);
  EXPECT_EQ(arr_char.max_size(), 0);
  EXPECT_EQ(arr_str.max_size(), 0);
}

TEST(Array_Modifiers, Swap) {
  s21::array<int, 3> arr1{1, 2, 3};
  s21::array<int, 3> arr2{4, 5, 6};
  arr1.swap(arr2);

  EXPECT_EQ(arr1[0], 4);
  EXPECT_EQ(arr1[1], 5);
  EXPECT_EQ(arr1[2], 6);
  EXPECT_EQ(arr1.size(), 3);

  EXPECT_EQ(arr2[0], 1);
  EXPECT_EQ(arr2[1], 2);
  EXPECT_EQ(arr2[2], 3);
  EXPECT_EQ(arr2.size(), 3);
}

TEST(Array_Modifiers, Fill) {
  s21::array<double, 3> arr{22.2, 34324.4, 33432.9};

  arr.fill(0.0);

  for (size_t j = 0; j < arr.size(); ++j) {
    EXPECT_EQ(arr[j], 0.0);
  }
}
