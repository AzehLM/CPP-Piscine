#include <iostream>
#include <string>

#include "colors.h"
#include "iter.hpp"

template<typename T>
void print(T const& x)
{
	std::cout << x << " ";
}

template<typename T>
void increment(T& x)
{
	x++;
}

template<typename T>
void square(T& x)
{
	x = x * x;
}

void toUpper(char& c)
{
	if (c >= 'a' && c <= 'z')
		c = c - 'a' + 'A';
}

template<typename T>
void makeNegative(T& x)
{
	x = -x;
}

void doubleValue(int& x)
{
	x *= 2;
}

int main(void)
{
	std::cout << YELLOW "=== BASIC SUBJECT TEST ===" RESET << std::endl;
	{
		int tab[] = {0, 1, 2, 3, 4};
		::iter(tab, 5, print<int>);
		std::cout << std::endl;
	}
	std::cout << std::endl;

	std::cout << CYAN "=== INTEGER ARRAY TESTS ===" RESET << std::endl;
	{
		std::cout << BLUE "--- Test: Print integer array ---" RESET << std::endl;
		int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
		size_t size = sizeof(numbers) / sizeof(numbers[0]);

		std::cout << GREEN "Original array: ";
		::iter(numbers, size, print<int>);
		std::cout << RESET << std::endl;

		std::cout << BLUE "--- Test: Increment all values ---" RESET << std::endl;
		::iter(numbers, size, increment<int>);
		std::cout << GREEN "After increment: ";
		::iter(numbers, size, print<int>);
		std::cout << RESET << std::endl;

		std::cout << BLUE "--- Test: Square all values ---" RESET << std::endl;
		int squares[] = {1, 2, 3, 4, 5};
		size_t squares_size = sizeof(squares) / sizeof(squares[0]);

		std::cout << GREEN "Before squaring: ";
		::iter(squares, squares_size, print<int>);
		std::cout << RESET << std::endl;

		::iter(squares, squares_size, square<int>);
		std::cout << GREEN "After squaring: ";
		::iter(squares, squares_size, print<int>);
		std::cout << RESET << std::endl;

		std::cout << BLUE "--- Test: Double values ---" RESET << std::endl;
		int doubles[] = {10, 20, 30, 40, 50};
		size_t doubles_size = sizeof(doubles) / sizeof(doubles[0]);

		std::cout << GREEN "Before doubling: ";
		::iter(doubles, doubles_size, print<int>);
		std::cout << RESET << std::endl;

		::iter(doubles, doubles_size, doubleValue);
		std::cout << GREEN "After doubling: ";
		::iter(doubles, doubles_size, print<int>);
		std::cout << RESET << std::endl;
	}
	std::cout << std::endl;

	std::cout << CYAN "=== FLOAT ARRAY TESTS ===" RESET << std::endl;
	{
		std::cout << BLUE "--- Test: Float operations ---" RESET << std::endl;
		float floats[] = {1.1f, 2.2f, 3.3f, 4.4f, 5.5f};
		size_t floats_size = sizeof(floats) / sizeof(floats[0]);

		std::cout << GREEN "Original floats: ";
		::iter(floats, floats_size, print<float>);
		std::cout << RESET << std::endl;

		::iter(floats, floats_size, increment<float>);
		std::cout << GREEN "After increment: ";
		::iter(floats, floats_size, print<float>);
		std::cout << RESET << std::endl;

		std::cout << BLUE "--- Test: Make negative ---" RESET << std::endl;
		float positives[] = {10.5f, 20.7f, 30.1f};
		size_t pos_size = sizeof(positives) / sizeof(positives[0]);

		std::cout << GREEN "Before making negative: ";
		::iter(positives, pos_size, print<float>);
		std::cout << RESET << std::endl;

		::iter(positives, pos_size, makeNegative<float>);
		std::cout << GREEN "After making negative: ";
		::iter(positives, pos_size, print<float>);
		std::cout << RESET << std::endl;
	}
	std::cout << std::endl;

	std::cout << CYAN "=== CHARACTER ARRAY TESTS ===" RESET << std::endl;
	{
		std::cout << BLUE "--- Test: Character manipulation ---" RESET << std::endl;
		char chars[] = {'h', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};
		size_t chars_size = sizeof(chars) / sizeof(chars[0]);

		std::cout << GREEN "Original characters: ";
		::iter(chars, chars_size, print<char>);
		std::cout << RESET << std::endl;

		std::cout << BLUE "--- Test: Convert to uppercase ---" RESET << std::endl;
		::iter(chars, chars_size, toUpper);
		std::cout << GREEN "After uppercase conversion: ";
		::iter(chars, chars_size, print<char>);
		std::cout << RESET << std::endl;

		std::cout << BLUE "--- Test: Mixed case string ---" RESET << std::endl;
		char mixed[] = {'C', 'p', 'P', ' ', 'i', 'S', ' ', 'f', 'U', 'n'};
		size_t mixed_size = sizeof(mixed) / sizeof(mixed[0]);

		std::cout << GREEN "Before: ";
		::iter(mixed, mixed_size, print<char>);
		std::cout << RESET << std::endl;

		::iter(mixed, mixed_size, toUpper);
		std::cout << GREEN "After uppercase: ";
		::iter(mixed, mixed_size, print<char>);
		std::cout << RESET << std::endl;
	}
	std::cout << std::endl;

	std::cout << CYAN "=== STRING ARRAY TESTS ===" RESET << std::endl;
	{
		std::cout << BLUE "--- Test: String array operations ---" RESET << std::endl;
		std::string words[] = {"Hello", "World", "Template", "Function", "Test"};
		size_t words_size = sizeof(words) / sizeof(words[0]);

		std::cout << GREEN "Original words: ";
		::iter(words, words_size, print<std::string>);
		std::cout << RESET << std::endl;
	}
	std::cout << std::endl;

	std::cout << CYAN "=== EDGE CASES TESTS ===" RESET << std::endl;
	{
		std::cout << BLUE "--- Test: Empty array (size 0) ---" RESET << std::endl;
		int* empty_array = NULL;
		std::cout << YELLOW "Calling iter on empty array..." RESET << std::endl;
		::iter(empty_array, 0, print<int>);
		std::cout << GREEN "Empty array handled safely" RESET << std::endl;

		std::cout << BLUE "--- Test: Single element array ---" RESET << std::endl;
		int single[] = {42};
		std::cout << GREEN "Single element before: ";
		::iter(single, 1, print<int>);
		std::cout << RESET << std::endl;

		::iter(single, 1, increment<int>);
		std::cout << GREEN "Single element after increment: ";
		::iter(single, 1, print<int>);
		std::cout << RESET << std::endl;

		std::cout << BLUE "--- Test: Large array ---" RESET << std::endl;
		int large[1000];
		for (int i = 0; i < 1000; i++)
			large[i] = i;

		std::cout << YELLOW "Processing large array of 1000 elements..." RESET << std::endl;
		::iter(large, 1000, increment<int>);
		std::cout << GREEN "First 10 elements after increment: ";
		::iter(large, 10, print<int>);
		std::cout << RESET << std::endl;
		std::cout << GREEN "Last 10 elements: ";
		::iter(large + 990, 10, print<int>);
		std::cout << RESET << std::endl;
	}
	std::cout << std::endl;

	std::cout << CYAN "=== DIFFERENT DATA TYPES TESTS ===" RESET << std::endl;
	{
		std::cout << BLUE "--- Test: Boolean array ---" RESET << std::endl;
		bool bools[] = {true, false, true, false, true};
		size_t bools_size = sizeof(bools) / sizeof(bools[0]);

		std::cout << GREEN "Boolean array: ";
		::iter(bools, bools_size, print<bool>);
		std::cout << RESET << std::endl;

		std::cout << BLUE "--- Test: Double array ---" RESET << std::endl;
		double doubles[] = {3.14159, 2.71828, 1.41421, 1.73205};
		size_t doubles_size = sizeof(doubles) / sizeof(doubles[0]);

		std::cout << GREEN "Double array: ";
		::iter(doubles, doubles_size, print<double>);
		std::cout << RESET << std::endl;

		::iter(doubles, doubles_size, square<double>);
		std::cout << GREEN "After squaring: ";
		::iter(doubles, doubles_size, print<double>);
		std::cout << RESET << std::endl;
	}
	std::cout << std::endl;

	std::cout << CYAN "=== CONST ARRAY TESTS ===" RESET << std::endl;
	{
		std::cout << BLUE "--- Test: Const array with read-only function ---" RESET << std::endl;
		const int const_array[] = {100, 200, 300, 400, 500};
		size_t const_size = sizeof(const_array) / sizeof(const_array[0]);

		std::cout << GREEN "Const array: ";
		::iter(const_array, const_size, print<const int>);
		std::cout << RESET << std::endl;

		std::cout << YELLOW "Const arrays can only be used with read-only functions" RESET << std::endl;
	}
	std::cout << std::endl;

	std::cout << GREEN "=== ALL ITER TEMPLATE TESTS COMPLETED SUCCESSFULLY ===" RESET << std::endl;

	return (0);
}
