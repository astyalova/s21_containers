#include "s21_tests.h"

TEST(Constructor, Default) {
  s21::vector<int> i;
  s21::vector<double> d;
  s21::vector<std::string> str;

  EXPECT_TRUE(i.empty());
  EXPECT_TRUE(d.empty());
  EXPECT_TRUE(str.empty());
}

TEST(Constructor, Parameterized_constructor) {
  s21::vector<int> i(9);
  s21::vector<double> d(6);
  s21::vector<std::string> str(3);

  EXPECT_FALSE(i.empty());
  EXPECT_EQ(i.size(), 9);
  EXPECT_EQ(i.capacity(), 9);

  EXPECT_FALSE(d.empty());
  EXPECT_EQ(d.size(), 6);
  EXPECT_EQ(d.capacity(), 6);

  EXPECT_FALSE(str.empty());
  EXPECT_EQ(str.size(), 3);
  EXPECT_EQ(str.capacity(), 3);
}

TEST(Constructor, Initializer_list_constructor) {
  s21::vector<int> i{1, 2, 3, 4, -5, 6};
  s21::vector<double> d{6.5, -7.8, 4.5};
  s21::vector<std::string> str{"st", "v", "hh", "lll"};

  EXPECT_EQ(i.size(), 6);
  EXPECT_EQ(i.capacity(), 6);

  EXPECT_FALSE(d.empty());
  EXPECT_EQ(d.size(), 3);
  EXPECT_EQ(d.capacity(), 3);

  EXPECT_FALSE(str.empty());
  EXPECT_EQ(str.capacity(), 4);
  EXPECT_EQ(str.size(), 4);
}

TEST(Constructor, Copy_constructor) {
  s21::vector<int> i{1, 2, 3, 4, -5, 6};
  s21::vector<int> copy_i(i);

  EXPECT_FALSE(i.empty());
  EXPECT_FALSE(copy_i.empty());
  EXPECT_EQ(copy_i.size(), 6);
  EXPECT_EQ(copy_i.capacity(), i.capacity());
  for (size_t j = 0; j < i.size(); ++j) {
    EXPECT_EQ(copy_i[j], i[j]);
  }

  s21::vector<std::string> str{"st", "v", "hh", "lll"};
  s21::vector<std::string> str_copy(str);

  EXPECT_FALSE(str.empty());
  EXPECT_FALSE(str_copy.empty());
  EXPECT_EQ(str_copy.size(), 4);
  EXPECT_EQ(str_copy.capacity(), str.capacity());
  for (size_t j = 0; j < str.size(); ++j) {
    EXPECT_EQ(str_copy[j], str[j]);
  }
}

TEST(Constructor, Move_constructor) {
  s21::vector<int> i{1, 2, 3, 4, -5, 6};
  s21::vector<int> copy_i(std::move(i));

  EXPECT_TRUE(i.empty());
  EXPECT_FALSE(copy_i.empty());
  EXPECT_EQ(copy_i.size(), 6);

  s21::vector<std::string> str{"st", "v", "hh", "lll"};
  s21::vector<std::string> str_copy(std::move(str));

  EXPECT_TRUE(str.empty());
  EXPECT_FALSE(str_copy.empty());
  EXPECT_EQ(str_copy.size(), 4);
}

TEST(Operator, Assignment_operator) {
  s21::vector<int> vec1{1, 2, 3, 4, -5, 6};
  s21::vector<int> vec2;
  vec2 = std::move(vec1);

  EXPECT_FALSE(vec2.empty());
  EXPECT_EQ(vec2.size(), 6);
  EXPECT_EQ(vec1.size(), 0);
  EXPECT_EQ(vec1.capacity(), 0);
}

TEST(Element_access, At) {
  s21::vector<int> vec1{1, 2, 3, 4, -5, 6};

  EXPECT_EQ(vec1.at(0), 1);
  EXPECT_EQ(vec1.at(1), 2);
  EXPECT_EQ(vec1.at(2), 3);
  EXPECT_EQ(vec1.at(3), 4);
  EXPECT_EQ(vec1.at(4), -5);
  EXPECT_EQ(vec1.at(5), 6);
  EXPECT_THROW(vec1.at(7), std::out_of_range);
}

TEST(Element_access, At_) {
  s21::vector<int> vec1{1, 2, 3, 4, -5, 6};

  EXPECT_EQ(vec1[0], 1);
  EXPECT_EQ(vec1[1], 2);
  EXPECT_EQ(vec1[2], 3);
  EXPECT_EQ(vec1[3], 4);
  EXPECT_EQ(vec1[4], -5);
  EXPECT_EQ(vec1[5], 6);
}

TEST(Element_access, Front) {
  s21::vector<int> vec1{1, 2, 3, 4, -5, 6};
  EXPECT_EQ(vec1.front(), 1);

  s21::vector<std::string> str{"st", "v", "hh", "lll"};
  EXPECT_EQ(str.front(), "st");

  s21::vector<int> vec2{};
  EXPECT_THROW(vec2.front(), std::out_of_range);
}

TEST(Element_access, Back) {
  s21::vector<int> vec1{1, 2, 3, 4, -5, 6};
  EXPECT_EQ(vec1.back(), 6);

  s21::vector<std::string> str{"st", "v", "hh", "lll"};
  EXPECT_EQ(str.back(), "lll");

  s21::vector<int> vec2{};
  EXPECT_THROW(vec2.back(), std::out_of_range);
}

TEST(Element_access, Data) {
  s21::vector<int> vec1{1, 2, 3, 4, -5, 6};
  int *value = vec1.data();

  EXPECT_EQ(value[0], 1);
}

TEST(Vector_Iterators, Begin) {
  s21::vector<int> vec1{1, 2, 3, 4, -5, 6};
  s21::vector<int>::iterator it = vec1.begin();

  EXPECT_EQ(*it, 1);
}

TEST(Vector_Iterators, End) {
  s21::vector<int> vec1{1, 2, 3, 4, -5, 6};

  EXPECT_EQ(vec1.end(), vec1.begin() + 6);
}

TEST(Vector_Capacity, Empty) {
  s21::vector<int> vec1;
  s21::vector<int> vec2(2);
  s21::vector<int> vec3{1, 2, 3, 4, -5, 6};
  s21::vector<int> vec4{0};

  EXPECT_TRUE(vec1.empty());
  EXPECT_FALSE(vec2.empty());
  EXPECT_FALSE(vec3.empty());
  EXPECT_FALSE(vec4.empty());
}

TEST(Vector_Capacity, Size) {
  s21::vector<int> vec1;
  s21::vector<int> vec2(2);
  s21::vector<int> vec3{1, 2, 3, 4, -5, 6};
  s21::vector<int> vec4{0};

  EXPECT_EQ(vec1.size(), 0);
  EXPECT_EQ(vec2.size(), 2);
  EXPECT_EQ(vec3.size(), 6);
  EXPECT_EQ(vec4.size(), 1);
}

TEST(Vector_Capacity, Max_Size) {
  s21::vector<int> vec;
  size_t expected_max_size = std::numeric_limits<size_t>::max() / sizeof(int);
  EXPECT_EQ(vec.max_size(), expected_max_size);

  s21::vector<double> vec_double;
  size_t expected_max_size_double =
      std::numeric_limits<size_t>::max() / sizeof(double);
  EXPECT_EQ(vec_double.max_size(), expected_max_size_double);

  s21::vector<char> vec_char;
  size_t expected_max_size_char =
      std::numeric_limits<size_t>::max() / sizeof(char);
  EXPECT_EQ(vec_char.max_size(), expected_max_size_char);

  s21::vector<std::string> vec_str;
  size_t expected_max_size_str =
      std::numeric_limits<size_t>::max() / sizeof(char);
  EXPECT_EQ(vec_char.max_size(), expected_max_size_str);
}

struct CustomType {
  int data[100];
};

TEST(Vector_Capacity, Max_Size_CustomType) {
  s21::vector<CustomType> vec;
  size_t max_size = std::numeric_limits<size_t>::max() / sizeof(CustomType);
  EXPECT_EQ(vec.max_size(), max_size);
}

TEST(Vector_Capacity, Reserve) {
  s21::vector<int> vec(3);
  vec.reserve(7);
  EXPECT_EQ(vec.capacity(), 7);

  s21::vector<int> vec2(6);
  EXPECT_THROW(vec2.reserve(vec2.max_size() + 1), std::length_error);
}

TEST(Vector_Capacity, Reserve_large) {
  s21::vector<int> vec(10);
  vec.reserve(100000);

  EXPECT_EQ(vec.capacity(), 100000);
  EXPECT_EQ(vec.size(), 10);
}

TEST(Vector_Capacity, Capacity) {
  s21::vector<int> vec;
  EXPECT_EQ(vec.capacity(), 0);

  s21::vector<int> vec2{1, 2, 3, 4, -5, 6};
  EXPECT_EQ(vec2.capacity(), 6);

  s21::vector<int> vec3(2);
  EXPECT_EQ(vec3.capacity(), 2);
}

TEST(Vector_Capacity, Shrink_to_fit) {
  s21::vector<int> vec{1, 2, 3, 4, -5, 6};

  EXPECT_EQ(vec.capacity(), 6);

  vec.reserve(12);
  EXPECT_EQ(vec.capacity(), 12);

  vec.shrink_to_fit();
  EXPECT_EQ(vec.capacity(), 6);
}

TEST(Vector_Capacity, Shrink_to_fit_large) {
  s21::vector<int> vec(100000);
  vec.reserve(200000);
  EXPECT_EQ(vec.capacity(), 200000);

  vec.shrink_to_fit();
  EXPECT_EQ(vec.capacity(), 100000);
}

TEST(Vector_Modifiers, Clear) {
  s21::vector<int> vec{1, 2, 3, 4, -5, 6};
  EXPECT_FALSE(vec.empty());
  vec.clear();
  EXPECT_EQ(vec.capacity(), 0);
  EXPECT_EQ(vec.size(), 0);
  EXPECT_TRUE(vec.empty());
}

TEST(Vector_Modifiers, Insert) {
  s21::vector<int> vec{1, 2, 3, 4, -5, 6};
  vec.insert(vec.begin(), 8);

  EXPECT_EQ(vec[0], 8);
  EXPECT_EQ(vec[1], 1);
  EXPECT_EQ(vec[2], 2);
  EXPECT_EQ(vec[3], 3);
  EXPECT_EQ(vec[4], 4);
  EXPECT_EQ(vec[5], -5);
  EXPECT_EQ(vec[6], 6);
  EXPECT_EQ(vec.size(), 7);

  s21::vector<int> vec2{4, 2, 3, 4};
  vec2.insert(vec2.begin() + 2, 7);
  EXPECT_EQ(vec2[0], 4);
  EXPECT_EQ(vec2[1], 2);
  EXPECT_EQ(vec2[2], 7);
  EXPECT_EQ(vec2[3], 3);
  EXPECT_EQ(vec2[4], 4);
  EXPECT_EQ(vec2.size(), 5);
}

TEST(Vector_Modifiers, Erase) {
  s21::vector<int> vec{1, 2, 3, 4, -5, 6};
  vec.erase(vec.begin());

  EXPECT_EQ(vec[0], 2);
  EXPECT_EQ(vec.size(), 5);

  vec.erase(vec.begin() + 1);
  EXPECT_EQ(vec[1], 4);
  EXPECT_EQ(vec.size(), 4);
}

TEST(Vector_Modifiers, Push) {
  s21::vector<int> vec{1, 2, 3, 4, -5, 6};
  vec.push_back(6);

  EXPECT_EQ(vec[6], 6);
  EXPECT_EQ(vec.size(), 7);
}

TEST(Vector_Modifiers, Pop) {
  s21::vector<int> vec{1, 2, 3, 4, -5, 6};
  vec.pop_back();

  EXPECT_EQ(vec.size(), 5);
  EXPECT_THROW(vec.at(5), std::out_of_range);
}

TEST(Vector_Modifiers, Swap) {
  s21::vector<int> vec1{1, 2, 3};
  s21::vector<int> vec2{4, 5, 6, 7};
  vec1.swap(vec2);

  EXPECT_EQ(vec1[0], 4);
  EXPECT_EQ(vec1[1], 5);
  EXPECT_EQ(vec1[2], 6);
  EXPECT_EQ(vec1[3], 7);
  EXPECT_EQ(vec1.size(), 4);

  EXPECT_EQ(vec2[0], 1);
  EXPECT_EQ(vec2[1], 2);
  EXPECT_EQ(vec2[2], 3);
  EXPECT_EQ(vec2.size(), 3);
}

TEST(Vector_Modifiers, InsertMany) {
  s21::vector<int> vec{1, 2, 5};
  auto it = vec.begin() + 2;
  vec.insert_many(it, 3, 4);

  EXPECT_EQ(vec.size(), 5);
  int expected[] = {1, 2, 3, 4, 5};
  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(vec[i], expected[i]);
  }
}
TEST(Vector_Modifiers, InsertManyBegin) {
  s21::vector<int> vec{3, 4, 5};
  vec.insert_many(vec.begin(), 1, 2);

  EXPECT_EQ(vec.size(), 5);
  int expected[] = {1, 2, 3, 4, 5};
  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(vec[i], expected[i]);
  }
}
TEST(Vector_Modifiers, InsertManyEnd) {
  s21::vector<int> vec{1, 2, 3};
  vec.insert_many(vec.end(), 4, 5);

  EXPECT_EQ(vec.size(), 5);
  int expected[] = {1, 2, 3, 4, 5};
  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(vec[i], expected[i]);
  }
}
TEST(Vector_Modifiers, InsertManyBack) {
  s21::vector<int> vec{1, 2, 3};
  vec.insert_many_back(4, 5);

  EXPECT_EQ(vec.size(), 5);
  int expected[] = {1, 2, 3, 4, 5};
  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(vec[i], expected[i]);
  }
}
TEST(Vector_Modifiers, InsertManySingle) {
  s21::vector<int> vec{1, 2, 4};
  auto it = vec.begin() + 2;
  vec.insert_many(it, 3);

  EXPECT_EQ(vec.size(), 4);
  int expected[] = {1, 2, 3, 4};
  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(vec[i], expected[i]);
  }
}