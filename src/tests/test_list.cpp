#include "s21_tests.h"

TEST(Constructor, Default_list) {
  s21::list<std::string> str;
  s21::list<char> c;
  s21::list<bool> b;

  EXPECT_TRUE(str.empty());

  EXPECT_TRUE(c.empty());

  EXPECT_TRUE(b.empty());
}

TEST(Constructor, Parameterized_constructor_list) {
  s21::list<int> i(9);
  s21::list<s21::vector<int>> v(2);
  s21::list<double> d(6);

  EXPECT_FALSE(i.empty());
  EXPECT_EQ(i.size(), 9);

  EXPECT_FALSE(v.empty());
  EXPECT_EQ(v.size(), 2);

  EXPECT_FALSE(d.empty());
  EXPECT_EQ(d.size(), 6);
}

TEST(Constructor, Initializer_constructor_list) {
  s21::list<int> i{45435, 32435, -4234234, 676737, 65436};
  s21::list<double> d{4536.323, -535325.235, 90.9};
  s21::list<s21::vector<int>> v{1, 2, 3};

  EXPECT_EQ(i.size(), 5);

  EXPECT_FALSE(d.empty());
  EXPECT_EQ(d.size(), 3);

  EXPECT_FALSE(v.empty());
  EXPECT_EQ(v.size(), 3);
}

TEST(Constructor, Copy_constructor_list) {

  s21::list<int> list = {1, 2, 3};
  s21::list<int> copy(list);

  EXPECT_EQ(list.back(), copy.back());
  EXPECT_EQ(list.front(), copy.front());
}

TEST(Constructor, Mov_constructor_list) {

  s21::list<int> list = {-34234234, 0, 234345, 4234234};
  s21::list<int> mov(std::move(list));

  EXPECT_TRUE(list.empty());
  EXPECT_FALSE(mov.empty());
  EXPECT_EQ(mov.size(), 4);

  s21::list<bool> list2 = {true, false, false, true, false};
  s21::list<bool> mov2(std::move(list2));

  EXPECT_TRUE(list2.empty());
  EXPECT_FALSE(mov2.empty());
  EXPECT_EQ(mov2.size(), 5);

  s21::list<s21::vector<int>> list3{33, 3434, 42343, 45345, 3434, 0};
  s21::list<s21::vector<int>> mov3(std::move(list3));

  EXPECT_TRUE(list3.empty());
  EXPECT_FALSE(mov3.empty());
  EXPECT_EQ(mov3.size(), 6);
}

TEST(Operator, Assignment_operator_list) {

  s21::list<std::string> list = {"fdsggfdgvfg", "ggewfewrewrf", "rtregfedfgeg",
                                 "", "43949324"};
  s21::list<std::string> mov;
  mov = std::move(list);

  EXPECT_TRUE(list.empty());
  EXPECT_FALSE(mov.empty());
  EXPECT_EQ(mov.size(), 5);

  s21::list<double> list2 = {43234324.5454, -24234.34324, 0.0, 1221406.1};
  s21::list<double> mov2;
  mov2 = std::move(list2);

  EXPECT_TRUE(list2.empty());
  EXPECT_FALSE(mov2.empty());
  EXPECT_EQ(mov2.size(), 4);
}

TEST(List_Element_access, front) {
  s21::list<std::string> str{"fgweq", "41424", "212121"};
  s21::list<int> i{-3, -2, 12, 98734, 84324};
  s21::list<bool> b{true, false};

  EXPECT_EQ(str.front(), "fgweq");
  EXPECT_EQ(i.front(), -3);
  EXPECT_EQ(b.front(), true);
}

TEST(List_Element_access, back) {
  s21::list<std::string> str{"fgweq", "41424", "2)"};
  s21::list<int> i{-3, -2, 12, 98734, 84324};
  s21::list<bool> b{true, false};

  EXPECT_EQ(str.back(), "2)");
  EXPECT_EQ(i.back(), 84324);
  EXPECT_EQ(b.back(), false);
}

TEST(ListTest, Begin_End) {
  s21::list<int> list{1, 2, 3};

  int expected_values[] = {1, 2, 3};
  int index = 0;
  for (auto it = list.begin(); it != list.end(); ++it, ++index) {
    EXPECT_EQ(*it, expected_values[index]);
  }
}

TEST(List_Capacity, Max_Size) {
  s21::list<int> list;
  size_t expected_max_size = std::numeric_limits<size_t>::max() / sizeof(int);
  EXPECT_EQ(list.max_size(), expected_max_size);

  s21::list<double> list2;
  size_t expected_max_size_double =
      std::numeric_limits<size_t>::max() / sizeof(double);
  EXPECT_EQ(list2.max_size(), expected_max_size_double);

  s21::list<char> list3;
  size_t expected_max_size_char =
      std::numeric_limits<size_t>::max() / sizeof(char);
  EXPECT_EQ(list3.max_size(), expected_max_size_char);

  s21::list<std::string> list4;
  size_t expected_max_size_str =
      std::numeric_limits<size_t>::max() / sizeof(std::string);
  EXPECT_EQ(list4.max_size(), expected_max_size_str);
}

TEST(List_Modifiers, Clear) {
  s21::list<double> list{0.0, 2343, 212.43, 78.999};
  EXPECT_FALSE(list.empty());
  list.clear();
  EXPECT_EQ(list.size(), 0);
  EXPECT_TRUE(list.empty());

  s21::list<std::string> list2{"dvdsvvdsv", "wrfref"};
  EXPECT_FALSE(list2.empty());
  list2.clear();
  EXPECT_EQ(list.size(), 0);
  EXPECT_TRUE(list.empty());

  s21::list<bool> list3{false, true, true};
  EXPECT_FALSE(list3.empty());
  list3.clear();
  EXPECT_EQ(list3.size(), 0);
  EXPECT_TRUE(list3.empty());
}

TEST(List_Modifiers, Insert) {
  s21::list<int> list{1, 2, 3, 4, -5, 6};
  s21::list<int> list2 = {1, 2, 3, 4, -5, 6, 0};

  auto it = list.insert(list.end(), 0);
  EXPECT_EQ(*it, list2.back());

  auto it2 = list.insert(list.begin(), 0);
  int array_list_expect[] = {1, 0, 2, 2, 3, 4, -5, 6};

  EXPECT_EQ(*it2, array_list_expect[1]);

  s21::list<int> list3{1, 2, 3, 4, -5, 6};
  int array_list_exp[] = {1, 0, 2, 4, 2, 3, 4, -5, 6};
  auto it3 = list3.begin();
  std::advance(it3, 2);
  auto it4 = list3.insert(it3, 4);
  EXPECT_EQ(*it4, array_list_exp[3]);
}

TEST(List_Modifiers, Erase) {
  s21::list<int> list{1, 2, 3, 4, -5, 6};
  list.erase(list.begin());
  EXPECT_EQ(list.size(), 5);

  list.erase(list.begin());
  EXPECT_EQ(list.size(), 4);

  EXPECT_THROW(list.erase(list.end()), std::out_of_range);
}

TEST(List_Modifiers, Erase_Back) {
  s21::list<int> list = {1, 3, 5};
  auto it = list.begin();
  it++;
  it++;
  list.erase(it);

  EXPECT_EQ(list.size(), 2);
  EXPECT_EQ(list.back(), 3);
}

TEST(List_Modifiers, Push_back) {
  s21::list<double> list;

  list.push_back(1.1);
  EXPECT_EQ(list.back(), 1.1);
  EXPECT_EQ(list.size(), 1);
  list.push_back(2.2);
  EXPECT_EQ(list.back(), 2.2);
  EXPECT_EQ(list.size(), 2);
  list.push_back(3.3);
  EXPECT_EQ(list.back(), 3.3);
  EXPECT_EQ(list.size(), 3);

  s21::list<int> list2{4253445, -45435, 0};
  list2.push_back(435435);
  EXPECT_EQ(list2.back(), 435435);
  EXPECT_EQ(list2.size(), 4);
  list2.push_back(-567);
  EXPECT_EQ(list2.back(), -567);
  EXPECT_EQ(list2.size(), 5);
}

TEST(List_Modifiers, Pop_Back) {
  s21::list<int> list = {1, 3, 5};
  list.pop_back();

  EXPECT_EQ(list.back(), 3);
  EXPECT_EQ(list.size(), 2);
}

TEST(List_Modifiers, Pop_Back_Alone) {
  s21::list<int> list = {1};
  list.pop_back();

  EXPECT_EQ(list.empty(), 1);
}

TEST(List_Modifiers, Push_front) {
  s21::list<double> list;

  list.push_front(1.1);
  EXPECT_EQ(list.front(), 1.1);
  EXPECT_EQ(list.size(), 1);
  list.push_front(2.2);
  EXPECT_EQ(list.front(), 2.2);
  EXPECT_EQ(list.size(), 2);
  list.push_front(3.3);
  EXPECT_EQ(list.front(), 3.3);
  EXPECT_EQ(list.size(), 3);

  s21::list<int> list2{4253445, -45435, 0};
  list2.push_front(435435);
  EXPECT_EQ(list2.front(), 435435);
  EXPECT_EQ(list2.size(), 4);
  list2.push_front(-567);
  EXPECT_EQ(list2.front(), -567);
  EXPECT_EQ(list2.size(), 5);
}

TEST(List_Modifiers, Pop_front) {
  s21::list<int> list = {1, 2, 3, 4, 5, 6};

  EXPECT_EQ(list.size(), 6);
  list.pop_front();
  EXPECT_EQ(list.front(), 2);
  EXPECT_EQ(list.size(), 5);
  list.pop_front();
  EXPECT_EQ(list.size(), 4);

  s21::list<double> list2{4253.434, -45435.3432};
  list2.pop_front();
  EXPECT_EQ(list2.back(), -45435.3432);
  EXPECT_EQ(list2.size(), 1);

  s21::list<double> list3{232432.1};
  list3.pop_front();
  EXPECT_TRUE(list3.empty());
}

TEST(List_Modifiers, Swap) {
  s21::list<int> list1{1, 2, 3};
  s21::list<int> list2{4, 5, 6, 7};
  list1.swap(list2);

  EXPECT_EQ(list1.size(), 4);
  EXPECT_EQ(list2.size(), 3);

  int expected_values[] = {4, 5, 6, 7};
  int index = 0;
  for (auto it = list1.begin(); it != list1.end(); ++it, ++index) {
    EXPECT_EQ(*it, expected_values[index]);
  }

  int expected_values2[] = {1, 2, 3};
  int index2 = 0;
  for (auto it = list2.begin(); it != list2.end(); ++it, ++index2) {
    EXPECT_EQ(*it, expected_values2[index2]);
  }
}

TEST(List_Modifiers, Merge) {
  s21::list<int> list1{1, 2, 2, 3, 4};
  s21::list<int> list2{9, 10, 4, 3};
  list1.merge(list2);

  int expected_values[] = {1, 2, 2, 3, 3, 4, 4, 9, 10};
  int index = 0;
  for (auto it = list1.begin(); it != list1.end(); ++it, ++index) {
    EXPECT_EQ(*it, expected_values[index]);
  }
}

TEST(List_Modifiers, Splice) {
  s21::list<int> list = {1, 2, 3, 4};
  s21::list<int> list2 = {5, 6, 7};
  auto pos = list.begin();
  pos++;
  pos++;
  list.splice(pos, list2);

  EXPECT_EQ(list.front(), 1);
  EXPECT_EQ(list.back(), 4);
  EXPECT_EQ(list.size(), 7);
  EXPECT_EQ(list.empty(), 0);
  EXPECT_EQ(list2.empty(), 1);
}

TEST(List_Modifiers, Splice_Empty) {
  s21::list<int> list = {1, 2, 4};
  s21::list<int> list2 = {5, 6, 7};
  auto pos = list.begin();

  list.splice(pos, list2);

  int expected_values[] = {5, 6, 7, 1, 2, 4};
  int index = 0;

  for (auto it = list.begin(); it != list.end(); ++it, ++index) {
    EXPECT_EQ(*it, expected_values[index]);
  }

  EXPECT_TRUE(list2.empty());
}

TEST(List_Modifiers, Reverse) {
  s21::list<int> list{1, 2, 3};
  list.reverse();

  int expected_values[] = {3, 2, 1};
  int index = 0;
  for (auto it = list.begin(); it != list.end(); ++it, ++index) {
    EXPECT_EQ(*it, expected_values[index]);
  }

  s21::list<std::string> list2{"fff"};
  list2.reverse();

  std::string expected_values2[] = {"fff"};
  int index2 = 0;
  for (auto it = list2.begin(); it != list2.end(); ++it, ++index2) {
    EXPECT_EQ(*it, expected_values2[index2]);
  }

  s21::list<double> list3{0.0, 0.1};
  list3.reverse();

  double expected_values3[] = {0.1, 0.0};
  int index3 = 0;
  for (auto it = list3.begin(); it != list3.end(); ++it, ++index3) {
    EXPECT_EQ(*it, expected_values3[index3]);
  }
}

TEST(List_Modifiers, Unique) {
  s21::list<int> list{1, 2, 2, 3, 3};
  list.unique();

  int expected_values[] = {1, 2, 3};
  int index = 0;
  for (auto it = list.begin(); it != list.end(); ++it, ++index) {
    EXPECT_EQ(*it, expected_values[index]);
  }
}

TEST(List_Modifiers, Sort) {
  s21::list<int> list{9, 10, 7, 6};
  list.sort();

  int expected_values[] = {6, 7, 9, 10};
  int index = 0;
  for (auto it = list.begin(); it != list.end(); ++it, ++index) {
    EXPECT_EQ(*it, expected_values[index]);
  }
}

TEST(List_Modifiers, InsertManyMiddle) {
  s21::list<int> list = {1, 2, 5, 6};
  auto it = list.begin();
  std::advance(it, 2);
  list.insert_many(it, 3, 4);
  int expected[] = {1, 2, 3, 4, 5, 6};
  int i = 0;
  for (auto it = list.begin(); it != list.end(); ++it, ++i) {
    EXPECT_EQ(*it, expected[i]);
  }
  EXPECT_EQ(list.size(), 6);
}

TEST(List_Modifiers, InsertManyFront) {
  s21::list<int> list = {3, 4, 5};
  list.insert_many_front(1, 2);
  int expected[] = {2, 1, 3, 4, 5};
  int i = 0;
  for (auto it = list.begin(); it != list.end(); ++it, ++i) {
    EXPECT_EQ(*it, expected[i]);
  }
  EXPECT_EQ(list.size(), 5);
}

TEST(List_Modifiers, InsertManyBack) {
  s21::list<int> list = {1, 2, 3};
  list.insert_many_back(4, 5);
  int expected[] = {1, 2, 3, 4, 5};
  int i = 0;
  for (auto it = list.begin(); it != list.end(); ++it, ++i) {
    EXPECT_EQ(*it, expected[i]);
  }
  EXPECT_EQ(list.size(), 5);
}

TEST(List_Modifiers, InsertManySingleElement) {
  s21::list<int> list = {1, 2, 4};
  auto it = list.begin();
  std::advance(it, 2);
  list.insert_many(it, 3);
  int expected[] = {1, 2, 3, 4};
  int i = 0;
  for (auto it = list.begin(); it != list.end(); ++it, ++i) {
    EXPECT_EQ(*it, expected[i]);
  }
  EXPECT_EQ(list.size(), 4);
}

TEST(List_Modifiers, InsertManyEmptyList) {
  s21::list<int> list;
  list.insert_many_back(1, 2, 3);
  int expected[] = {1, 2, 3};
  int i = 0;
  for (auto it = list.begin(); it != list.end(); ++it, ++i) {
    EXPECT_EQ(*it, expected[i]);
  }
  EXPECT_EQ(list.size(), 3);
}
