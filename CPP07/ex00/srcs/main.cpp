#include <iostream>
#include <string>

#include "colors.h"
#include "whatever.hpp"

int main(void)
{
	std::cout << YELLOW "=== BASIC SUBJECT TEST ===" RESET << std::endl;
	{
		int a = 2;
		int b = 3;

		::swap(a, b);
		std::cout << "a = " << a << ", b = " << b << std::endl;
		std::cout << "min(a, b) = " << ::min(a, b) << std::endl;
		std::cout << "max(a, b) = " << ::max(a, b) << std::endl;

		std::string c = "chaine1";
		std::string d = "chaine2";

		::swap(c, d);
		std::cout << "c = " << c << ", d = " << d << std::endl;
		std::cout << "min(c, d) = " << ::min(c, d) << std::endl;
		std::cout << "max(c, d) = " << ::max(c, d) << std::endl;
	}
	std::cout << std::endl;

	std::cout << CYAN "=== INTEGER TESTS ===" RESET << std::endl;
	{
		std::cout << BLUE "--- Test: Basic integer operations ---" RESET << std::endl;
		int x = 42;
		int y = 21;

		std::cout << GREEN "Before swap: x = " << x << ", y = " << y << RESET << std::endl;
		::swap(x, y);
		std::cout << GREEN "After swap: x = " << x << ", y = " << y << RESET << std::endl;

		std::cout << MAGENTA "min(" << x << ", " << y << ") = " << ::min(x, y) << RESET << std::endl;
		std::cout << MAGENTA "max(" << x << ", " << y << ") = " << ::max(x, y) << RESET << std::endl;

		std::cout << BLUE "--- Test: Equal values ---" RESET << std::endl;
		int equal1 = 100;
		int equal2 = 100;

		std::cout << YELLOW "min(" << equal1 << ", " << equal2 << ") = " << ::min(equal1, equal2) << RESET << std::endl;
		std::cout << YELLOW "max(" << equal1 << ", " << equal2 << ") = " << ::max(equal1, equal2) << RESET << std::endl;
		std::cout << YELLOW "Returns second parameter when equal" RESET << std::endl;
	}
	std::cout << std::endl;

	std::cout << CYAN "=== FLOAT TESTS ===" RESET << std::endl;
	{
		std::cout << BLUE "--- Test: Floating point operations ---" RESET << std::endl;
		float f1 = 3.14f;
		float f2 = 2.71f;

		std::cout << GREEN "Before swap: f1 = " << f1 << ", f2 = " << f2 << RESET << std::endl;
		::swap(f1, f2);
		std::cout << GREEN "After swap: f1 = " << f1 << ", f2 = " << f2 << RESET << std::endl;

		std::cout << MAGENTA "min(" << f1 << ", " << f2 << ") = " << ::min(f1, f2) << RESET << std::endl;
		std::cout << MAGENTA "max(" << f1 << ", " << f2 << ") = " << ::max(f1, f2) << RESET << std::endl;

		std::cout << BLUE "--- Test: Negative floats ---" RESET << std::endl;
		float neg1 = -5.5f;
		float neg2 = -10.2f;

		std::cout << YELLOW "min(" << neg1 << ", " << neg2 << ") = " << ::min(neg1, neg2) << RESET << std::endl;
		std::cout << YELLOW "max(" << neg1 << ", " << neg2 << ") = " << ::max(neg1, neg2) << RESET << std::endl;
	}
	std::cout << std::endl;

	std::cout << CYAN "=== STRING TESTS ===" RESET << std::endl;
	{
		std::cout << BLUE "--- Test: String operations ---" RESET << std::endl;
		std::string str1 = "hello";
		std::string str2 = "world";

		std::cout << GREEN "Before swap: str1 = \"" << str1 << "\", str2 = \"" << str2 << "\"" RESET << std::endl;
		::swap(str1, str2);
		std::cout << GREEN "After swap: str1 = \"" << str1 << "\", str2 = \"" << str2 << "\"" RESET << std::endl;

		std::cout << MAGENTA "min(\"" << str1 << "\", \"" << str2 << "\") = \"" << ::min(str1, str2) << "\"" RESET << std::endl;
		std::cout << MAGENTA "max(\"" << str1 << "\", \"" << str2 << "\") = \"" << ::max(str1, str2) << "\"" RESET << std::endl;

		std::cout << BLUE "--- Test: Alphabetical ordering ---" RESET << std::endl;
		std::string alpha = "apple";
		std::string beta = "zebra";

		std::cout << YELLOW "min(\"" << alpha << "\", \"" << beta << "\") = \"" << ::min(alpha, beta) << "\"" RESET << std::endl;
		std::cout << YELLOW "max(\"" << alpha << "\", \"" << beta << "\") = \"" << ::max(alpha, beta) << "\"" RESET << std::endl;

		std::cout << BLUE "--- Test: Different length strings ---" RESET << std::endl;
		std::string short_str = "hi";
		std::string long_str = "hello there";

		std::cout << YELLOW "min(\"" << short_str << "\", \"" << long_str << "\") = \"" << ::min(short_str, long_str) << "\"" RESET << std::endl;
		std::cout << YELLOW "max(\"" << short_str << "\", \"" << long_str << "\") = \"" << ::max(short_str, long_str) << "\"" RESET << std::endl;
	}
	std::cout << std::endl;

	std::cout << CYAN "=== CHARACTER TESTS ===" RESET << std::endl;
	{
		std::cout << BLUE "--- Test: Character operations ---" RESET << std::endl;
		char c1 = 'Z';
		char c2 = 'A';

		std::cout << GREEN "Before swap: c1 = '" << c1 << "', c2 = '" << c2 << "'" RESET << std::endl;
		::swap(c1, c2);
		std::cout << GREEN "After swap: c1 = '" << c1 << "', c2 = '" << c2 << "'" RESET << std::endl;

		std::cout << MAGENTA "min('" << c1 << "', '" << c2 << "') = '" << ::min(c1, c2) << "'" RESET << std::endl;
		std::cout << MAGENTA "max('" << c1 << "', '" << c2 << "') = '" << ::max(c1, c2) << "'" RESET << std::endl;
	}
	std::cout << std::endl;

	std::cout << CYAN "=== EDGE CASES TESTS ===" RESET << std::endl;
	{
		std::cout << BLUE "--- Test: Large numbers ---" RESET << std::endl;
		int big1 = 2147483647;
		int big2 = -2147483648;

		std::cout << YELLOW "min(" << big1 << ", " << big2 << ") = " << ::min(big1, big2) << RESET << std::endl;
		std::cout << YELLOW "max(" << big1 << ", " << big2 << ") = " << ::max(big1, big2) << RESET << std::endl;

		std::cout << BLUE "--- Test: Zero values ---" RESET << std::endl;
		int zero1 = 0;
		int zero2 = 0;

		std::cout << YELLOW "min(0, 0) = " << ::min(zero1, zero2) << RESET << std::endl;
		std::cout << YELLOW "max(0, 0) = " << ::max(zero1, zero2) << RESET << std::endl;

		std::cout << BLUE "--- Test: Empty strings ---" RESET << std::endl;
		std::string empty1 = "";
		std::string empty2 = "";
		std::string nonempty = "test";

		std::cout << YELLOW "min(\"\", \"\") = \"" << ::min(empty1, empty2) << "\"" RESET << std::endl;
		std::cout << YELLOW "min(\"\", \"test\") = \"" << ::min(empty1, nonempty) << "\"" RESET << std::endl;
		std::cout << YELLOW "max(\"\", \"test\") = \"" << ::max(empty1, nonempty) << "\"" RESET << std::endl;
	}
	std::cout << std::endl;

	std::cout << GREEN "=== ALL TEMPLATE FUNCTION TESTS COMPLETED SUCCESSFULLY ===" RESET << std::endl;

	return (0);
}
