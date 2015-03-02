// Using Google's C++ Unit Testing Framework
// The tests are straight forward as below. For more details, please visit:
// 		https://code.google.com/p/googletest/wiki/Primer
//

#include "gtest/gtest.h"
#include "String.cpp"

TEST(StringConstructorTest, DefaultConstructor) {
	String s1;
	std::string s2;
    EXPECT_EQ(s2.size(), s1.size());
    EXPECT_STREQ(s2.data(), s1.data());
}

TEST(StringConstructorTest, ConstCharConstructor) {
	String s1("Test");
    EXPECT_STREQ("Test", s1.data());
    EXPECT_EQ(4, s1.size());
}

TEST(StringConstructorTest, CopyConstructor) {
	String s1("Test");
	String s2(s1);
	std::string s3("Test");
	std::string s4(s3);
    EXPECT_STREQ(s4.data(), s2.data());
    EXPECT_EQ(s4.size(), s2.size());
}

TEST(StringMemberTest, Size) {
	String s1("Test");
    EXPECT_EQ(4, s1.size());
}

TEST(StringMemberTest, CStr) {
	String s1("Test");
    EXPECT_STREQ("Test\0", s1.c_str());
}

TEST(StringOperationTest, PushBackSmall) {
	String s1("T");
	s1.push_back('1');
    EXPECT_STREQ("T1", s1.data());
}

TEST(StringOperationTest, PushBackLarge) {
	String s1("Test");
	s1.push_back('1');
    EXPECT_STREQ("Test1", s1.data());
}

TEST(StringOperationTest, Append) {
	String s1("TEST1234");
	String s2("5678");
	std::string s3("TEST1234");
	std::string s4("5678");
	s1.append(s2);
	s3.append(s4);
    EXPECT_STREQ(s3.data(), s1.data());
}

TEST(StringOperationTest, SwapSmall) {
	String s1("Te");
	String s2("12");
	std::string s3("Te");
	std::string s4("12");
	s1.swap(s2);
	s3.swap(s4);
    EXPECT_STREQ(s3.data(), s1.data());
}

TEST(StringOperationTest, SwapLarge) {
	String s1("Test");
	String s2("123");
	std::string s3("Test");
	std::string s4("123");
	s1.swap(s2);
	s3.swap(s4);
    EXPECT_STREQ(s3.data(), s1.data());
}

TEST(StringOperationTest, SwapSmallLarge) {
	String s1("Te");
	String s2("123");
	std::string s3("Te");
	std::string s4("123");
	s1.swap(s2);
	s3.swap(s4);
    EXPECT_STREQ(s3.data(), s1.data());
    EXPECT_STREQ(s4.data(), s2.data());
}

TEST(StringOperationTest, SwapLargeSmall) {
	String s1("123");
	String s2("Te");
	std::string s3("123");
	std::string s4("Te");
	s1.swap(s2);
	s3.swap(s4);
    EXPECT_STREQ(s3.data(), s1.data());
    EXPECT_STREQ(s4.data(), s2.data());

}

TEST(StringEraseTest, EraseSmall1) {
	String s1("Te");
	std::string s2("Te");
	s1.erase(1,1);
	s2.erase(1,1);
    EXPECT_STREQ(s2.data(), s1.data());
}

TEST(StringEraseTest, EraseSmall2) {
	String s1("Te");
	std::string s2("Te");
	s1.erase(0,1);
	s2.erase(0,1);
    EXPECT_STREQ(s2.data(), s1.data());
}

TEST(StringEraseTest, EraseLargeToLarge) {
	String s1("Test");
	std::string s2("Test");
	s1.erase(2,1);
	s2.erase(2,1);
    EXPECT_STREQ(s2.data(), s1.data());
}

TEST(StringEraseTest, EraseLargeToSmall) {
	String s1("Test");
	std::string s2("Test");
	s1.erase(2,3);
	s2.erase(2,3);
    EXPECT_STREQ(s2.data(), s1.data());
}

TEST(StringEraseTest, EraseOutOfBound) {
	String s1("Test");
	std::string s2("Test");
	s1.erase(0,5);
	s2.erase(0,5);
    EXPECT_STREQ(s2.data(), s1.data());
}

TEST(StringAssignTest, AssignSmallToSmall) {
	String s1("Te");
	String s2("st");
	std::string s3("Te");
	std::string s4("st");
	s1.assign(s2);
	s3.assign(s4);
    EXPECT_STREQ(s3.data(), s1.data());
}

TEST(StringAssignTest, AssignLargeToLarge) {
	String s1("Test");
	String s2("123");
	std::string s3("Test");
	std::string s4("123");
	s1.assign(s2);
	s3.assign(s4);
    EXPECT_STREQ(s3.data(), s1.data());
}

TEST(StringAssignTest, AssignSmallToLarge) {
	String s1("Test");
	String s2("12");
	std::string s3("Test");
	std::string s4("12");
	s1.assign(s2);
	s3.assign(s4);
    EXPECT_STREQ(s3.data(), s1.data());
}

TEST(StringAssignTest, AssignLargeToSmall) {
	String s1("12");
	String s2("Test");
	std::string s3("12");
	std::string s4("Test");
	s1.assign(s2);
	s3.assign(s4);
    EXPECT_STREQ(s3.data(), s1.data());
}

TEST(StringOperatorTest, EqualOperator) {
	String s1("Test");
	String s2;
	std::string s3("Test");
	std::string s4;
	s2 = s1;
	s4 = s3;
    EXPECT_STREQ(s3.data(), s1.data());
}

TEST(StringOperatorTest, PlusEqualsOperator) {
	String s1("TEST1234");
	String s2("5678");
	std::string s3("TEST1234");
	std::string s4("5678");
	s1 += s2;
	s3 += s4;
    EXPECT_STREQ(s3.data(), s1.data());
}

TEST(StringResizeTest, Resize) {
	String s1("Test");
	std::string s2("Test");
	s1.resize(10);
	s2.resize(10);
    EXPECT_EQ(s2.size(), s1.size());
}

TEST(StringResizeTest, NegativeResize) {
	String s1("Test");
	try
	{
		s1.resize(-1);
	}
	catch (StringException& e)
	{
		std::cout << e.what() << std::endl;
	}
}

TEST(StringResizeTest, DataMatchAfterResize) {
	String s1("Test");
	std::string s2("Test");
	s1.resize(10);
	s2.resize(10);
    EXPECT_STREQ(s2.data(), s1.data());
}

TEST(StringReplaceTest, Replace5) {
	String s1("Test1234");
	String s2("5678");
	std::string s3("Test1234");
	std::string s4("5678");
	s1.replace(5, 5, s2);
	s3.replace(5, 5, s4);
    EXPECT_STREQ(s3.data(), s1.data());
}

TEST(StringReplaceTest, Replace2) {
	String s1("Test1234");
	String s2("5678");
	std::string s3("Test1234");
	std::string s4("5678");
	s1.replace(2, 2, s2);
	s3.replace(2, 2, s4);
    EXPECT_STREQ(s3.data(), s1.data());
}

TEST(StringReplaceTest, Replace0) {
	String s1("Test1234");
	String s2("5678");
	std::string s3("Test1234");
	std::string s4("5678");
	s1.replace(0, 0, s2);
	s3.replace(0, 0, s4);
    EXPECT_STREQ(s3.data(), s1.data());
}

TEST(StringReplaceTest, Replace10) {
	String s1("Test1234");
	String s2("5678");
	std::string s3("Test1234");
	std::string s4("5678");
	s1.replace(0, 10, s2);
	s3.replace(0, 10, s4);
    EXPECT_STREQ(s3.data(), s1.data());
}

TEST(StringInsertTest, InsertAt5) {
	String s1("Test1234");
	String s2("5678");
	std::string s3("Test1234");
	std::string s4("5678");
	s1.insert(5, s2);
	s3.insert(5, s4);
    EXPECT_STREQ(s3.data(), s1.data());
}

TEST(StringInsertTest, InsertAt2) {
	String s1("Test1234");
	String s2("5678");
	std::string s3("Test1234");
	std::string s4("5678");
	s1.insert(2, s2);
	s3.insert(2, s4);
    EXPECT_STREQ(s3.data(), s1.data());
}

TEST(StringInsertTest, InsertAt0) {
	String s1("Test1234");
	String s2("5678");
	std::string s3("Test1234");
	std::string s4("5678");
	s1.insert(0, s2);
	s3.insert(0, s4);
    EXPECT_STREQ(s3.data(), s1.data());
}

TEST(StringMemberFunction, ReserveSmallToLarge) {
	String s1("Te");
	s1.reserve(10);
    EXPECT_EQ(2, s1.size());
    EXPECT_EQ(10, s1.capacity());
}

TEST(StringMemberFunction, ReserveLargeToLarge) {
	String s1("Test");
	s1.reserve(10);
    EXPECT_EQ(4, s1.size());
    EXPECT_EQ(10, s1.capacity());
}

TEST(StringAccessorFunction, At0Small) {
	String s1("Te");
	std::string s2("Te");
    EXPECT_EQ(s2.at(0), s1.at(0));
}

TEST(StringAccessorFunction, At1Small) {
	String s1("Te");
	std::string s2("Te");
    EXPECT_EQ(s2.at(1), s1.at(1));
}

TEST(StringAccessorFunction, At0Large) {
	String s1("Test");
	std::string s2("Test");
    EXPECT_EQ(s2.at(0), s1.at(0));
}

TEST(StringAccessorFunction, At1Large) {
	String s1("Test");
	std::string s2("Test");
    EXPECT_EQ(s2.at(1), s1.at(1));
}


TEST(StringAccessorFunction, At5OutOfBound) {
	try
	{
		String s1("Test");
		s1.at(6);
	}
	catch (StringException& e)
	{
		std::cout << e.what() << std::endl;
	}
}


TEST(StringOperatorTest, BracketOperatorSmall0) {
	String s1("Te");
	std::string s2("Te");
    EXPECT_EQ(s2[0], s1[0]);
}

TEST(StringOperatorTest, BracketOperatorSmall1) {
	String s1("Te");
	std::string s2("Te");
    EXPECT_EQ(s2[1], s1[1]);
}

TEST(StringOperatorTest, BracketOperatorLarge0) {
	String s1("Test");
	std::string s2("Test");
    EXPECT_EQ(s2[0], s1[0]);
}

TEST(StringOperatorTest, BracketOperatorLarge1) {
	String s1("Test");
	std::string s2("Test");
    EXPECT_EQ(s2[1], s1[1]);
}

TEST(StringOperatorTest, BracketOperator5OutOfBound) {
	try
	{
		String s1("Test");
	}
	catch (StringException& e)
	{
		std::cout << e.what() << std::endl;
	}
}

TEST(StringMemberFunction, Empty) {
	String s1;
	std::string s2;
    EXPECT_EQ(s2.empty(), s1.empty());
}

TEST(StringMemberFunction, EmptyBlank) {
	String s1("");
	std::string s2("");
    EXPECT_EQ(s2.empty(), s1.empty());
}

TEST(StringIterator, LargeBegin) {
	String s1("Test");
	std::string s2("Test");
	std::cout<< " s2.begin::s1.begin - "<<*(s2.begin()) << ":" <<*(s1.begin())
	<< std::endl;
    EXPECT_EQ(*(s2.begin()), *(s1.begin()));
}

TEST(StringIterator, LargeEnd) {
	String s1("Test");
	std::string s2("Test");
	std::cout<< " s2.end::s1.end - "<<*(s2.end()) << ":" <<*(s1.end())
	<< std::endl;
    EXPECT_EQ(*(s2.end()), *(s1.end()));
}

TEST(StringIterator, LargeBeginToEnd) {
	String s1("Test");
	std::string s2("Test");
	StringIterator itr1 = s1.begin();
	std::string::iterator itr2 = s2.begin();

	while((itr2 != s2.end()) && (itr1 != s1.end()))
	{
		EXPECT_EQ((*itr1), (*itr2));
		++itr1;
		++itr2;
	}
}

TEST(StringIterator, SmallBegin) {
	String s1("Te");
	std::string s2("Te");
	std::cout<< " s2.begin::s1.begin - "<<*(s2.begin()) << ":" <<*(s1.begin())
	<< std::endl;
    EXPECT_EQ(*(s2.begin()), *(s1.begin()));
}

TEST(StringIterator, SmallEnd) {
	String s1("Te");
	std::string s2("Te");
	std::cout<< " s2.end::s1.end - "<<*(s2.end()) << ":" <<*(s1.end())
	<< std::endl;
    EXPECT_EQ(*(s2.end()), *(s1.end()));
}

TEST(StringIterator, SmallBeginToEnd) {
	String s1("Te");
	std::string s2("Te");
	StringIterator itr1 = s1.begin();
	std::string::iterator itr2 = s2.begin();

	while((itr2 != s2.end()) && (itr1 != s1.end()))
	{
		EXPECT_EQ((*itr1), (*itr2));
		++itr1;
		++itr2;
	}
}



int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
