#include <iostream>
#include <string>

#include "Array.hpp"
#include "colors.h"

template<typename T>
void printArray(const Array<T>& arr, const std::string& name)
{
	std::cout << name << " [size: " << arr.size() << "]: ";
	for (size_t i = 0; i < arr.size(); i++) {
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}

int main(void)
{
	std::cout << CYAN "=== CONSTRUCTOR TESTS ===" RESET << std::endl;
	{
		std::cout << BLUE "--- Test: Default constructor ---" RESET << std::endl;
		Array<int> defaultArray;
		std::cout << GREEN "Default array size: " << defaultArray.size() << RESET << std::endl;

		std::cout << BLUE "--- Test: Size constructor ---" RESET << std::endl;
		Array<int> sizedArray(10);
		std::cout << GREEN "Sized array (10) size: " << sizedArray.size() << RESET << std::endl;

		std::cout << YELLOW "Checking default initialization..." RESET << std::endl;
		bool allZero = true;
		for (unsigned int i = 0; i < sizedArray.size(); i++) {
			if (sizedArray[i] != 0) {
				allZero = false;
				std::cout << RED "Element " << i << " = " << sizedArray[i] << " (should be 0)" RESET << std::endl;
				break;
			}
		}
		std::cout << GREEN "All elements initialized to 0: " << (allZero ? "YES" : "NO") << RESET << std::endl;

		std::cout << BLUE "--- Test: Large array constructor ---" RESET << std::endl;
		Array<int> largeArray(1000);
		std::cout << GREEN "Large array size: " << largeArray.size() << RESET << std::endl;
	}
	std::cout << std::endl;

	std::cout << CYAN "=== ELEMENT ACCESS TESTS ===" RESET << std::endl;
	{
		std::cout << BLUE "--- Test: Basic element access and modification ---" RESET << std::endl;
		Array<int> arr(5);

		for (size_t i = 0; i < arr.size(); i++) {
			arr[i] = (i + 1) * 10;
		}

		printArray(arr, "Filled array");

		std::cout << BLUE "--- Test: Individual element access ---" RESET << std::endl;
		for (unsigned int i = 0; i < arr.size(); i++) {
			std::cout << GREEN "arr[" << i << "] = " << arr[i] << RESET << std::endl;
		}

		std::cout << BLUE "--- Test: Modify specific elements ---" RESET << std::endl;
		arr[0] = 999;
		arr[2] = 888;
		arr[4] = 777;
		printArray(arr, "Modified array");
	}
	std::cout << std::endl;

	std::cout << CYAN "=== COPY CONSTRUCTOR TESTS ===" RESET << std::endl;
	{
		std::cout << BLUE "--- Test: Copy constructor ---" RESET << std::endl;
		Array<int> original(4);

		for (unsigned int i = 0; i < original.size(); i++) {
			original[i] = i * i;
		}
		printArray(original, "Original");

		Array<int> copy(original);
		printArray(copy, "Copy");

		std::cout << YELLOW "Verifying deep copy (modifying original)..." RESET << std::endl;
		original[0] = 9999;
		original[1] = 8888;

		printArray(original, "Modified original");
		printArray(copy, "Copy (should be unchanged)");

		std::cout << GREEN "Copy independence: " <<
			((copy[0] != 9999 && copy[1] != 8888) ? "PASSED" : "FAILED") << RESET << std::endl;
	}
	std::cout << std::endl;

	std::cout << CYAN "=== ASSIGNMENT OPERATOR TESTS ===" RESET << std::endl;
	{
		std::cout << BLUE "--- Test: Assignment operator ---" RESET << std::endl;
		Array<int> source(3);
		Array<int> dest(5);

		source[0] = 100;
		source[1] = 200;
		source[2] = 300;

		for (unsigned int i = 0; i < dest.size(); i++) {
			dest[i] = i + 1;
		}

		printArray(source, "Source");
		printArray(dest, "Destination before");

		dest = source;
		printArray(dest, "Destination after assignment");

		std::cout << GREEN "Size after assignment: " << dest.size() << " (should be 3)" << RESET << std::endl;

		std::cout << YELLOW "Testing deep copy in assignment..." RESET << std::endl;
		source[0] = 9999;
		printArray(source, "Modified source");
		printArray(dest, "Destination (should be unchanged)");
		std::cout << GREEN "Assignment independence: " <<
			((dest[0] == 100 && dest[1] == 200) ? "PASSED" : "FAILED") << RESET << std::endl;
		std::cout << BLUE "--- Test: Self assignment ---" RESET << std::endl;
		Array<int> selfTest(3);
		selfTest[0] = 111;
		selfTest[1] = 222;
		selfTest[2] = 333;
	}
	std::cout << std::endl;

	std::cout << CYAN "=== DIFFERENT TYPES TESTS ===" RESET << std::endl;
	{
		std::cout << BLUE "--- Test: String arrays ---" RESET << std::endl;
		Array<std::string> strings(4);
		strings[0] = "Hello";
		strings[1] = "Template";
		strings[2] = "Array";
		strings[3] = "World";

		printArray(strings, "String array");

		std::cout << BLUE "--- Test: Float arrays ---" RESET << std::endl;
		Array<float> floats(3);
		floats[0] = 3.14f;
		floats[1] = 2.71f;
		floats[2] = 1.41f;

		printArray(floats, "Float array");

		std::cout << BLUE "--- Test: Character arrays ---" RESET << std::endl;
		Array<char> chars(5);
		chars[0] = 'H';
		chars[1] = 'e';
		chars[2] = 'l';
		chars[3] = 'l';
		chars[4] = 'o';

		printArray(chars, "Character array");

		std::cout << BLUE "--- Test: Boolean arrays ---" RESET << std::endl;
		Array<bool> bools(4);
		bools[0] = true;
		bools[1] = false;
		bools[2] = true;
		bools[3] = false;

		printArray(bools, "Boolean array");
	}
	std::cout << std::endl;

	std::cout << CYAN "=== EXCEPTION TESTS ===" RESET << std::endl;
	{
		std::cout << BLUE "--- Test: Out of bounds access ---" RESET << std::endl;
		Array<int> testArray(3);
		testArray[0] = 10;
		testArray[1] = 20;
		testArray[2] = 30;

		printArray(testArray, "Test array");

		std::cout << YELLOW "Testing valid access..." RESET << std::endl;
		try {
			std::cout << GREEN "testArray[0] = " << testArray[0] << RESET << std::endl;
			std::cout << GREEN "testArray[2] = " << testArray[2] << RESET << std::endl;
		} catch (const std::exception& e) {
			std::cout << RED "Unexpected exception: " << e.what() << RESET << std::endl;
		}

		std::cout << YELLOW "Testing out of bounds access (index 3)..." RESET << std::endl;
		try {
			std::cout << testArray[3] << std::endl;
			std::cout << RED "ERROR: Should have thrown exception!" RESET << std::endl;
		} catch (const std::exception& e) {
			std::cout << GREEN "Correctly caught exception: " << e.what() << RESET << std::endl;
		}

		std::cout << YELLOW "Testing negative index access..." RESET << std::endl;
		try {
			std::cout << testArray[-1] << std::endl;
			std::cout << RED "ERROR: Should have thrown exception!" RESET << std::endl;
		} catch (const std::exception& e) {
			std::cout << GREEN "Correctly caught exception: " << e.what() << RESET << std::endl;
		}

		std::cout << YELLOW "Testing very large index..." RESET << std::endl;
		try {
			std::cout << testArray[999999] << std::endl;
			std::cout << RED "ERROR: Should have thrown exception!" RESET << std::endl;
		} catch (const std::exception& e) {
			std::cout << GREEN "Correctly caught exception: " << e.what() << RESET << std::endl;
		}
	}
	std::cout << std::endl;

	std::cout << CYAN "=== CONST CORRECTNESS TESTS ===" RESET << std::endl;
	{
		std::cout << BLUE "--- Test: Const array access ---" RESET << std::endl;
		Array<int> mutableArray(3);
		mutableArray[0] = 100;
		mutableArray[1] = 200;
		mutableArray[2] = 300;

		const Array<int>& constArray = mutableArray;

		std::cout << GREEN "Const array access:" RESET << std::endl;
		for (unsigned int i = 0; i < constArray.size(); i++) {
			std::cout << "  constArray[" << i << "] = " << constArray[i] << std::endl;
		}

		std::cout << YELLOW "Const array size: " << constArray.size() << RESET << std::endl;
	}
	std::cout << std::endl;

	std::cout << CYAN "=== EDGE CASES TESTS ===" RESET << std::endl;
	{
		std::cout << BLUE "--- Test: Zero-size array ---" RESET << std::endl;
		Array<int> zeroArray(0);
		std::cout << GREEN "Zero array size: " << zeroArray.size() << RESET << std::endl;

		std::cout << YELLOW "Testing access to zero-size array..." RESET << std::endl;
		try {
			zeroArray[0] = 42;
			std::cout << RED "ERROR: Should have thrown exception!" RESET << std::endl;
		} catch (const std::exception& e) {
			std::cout << GREEN "Correctly caught exception: " << e.what() << RESET << std::endl;
		}

		std::cout << BLUE "--- Test: Copy of zero-size array ---" RESET << std::endl;
		Array<int> zeroCopy(zeroArray);
		std::cout << GREEN "Zero copy size: " << zeroCopy.size() << RESET << std::endl;

		std::cout << BLUE "--- Test: Assignment with different sizes ---" RESET << std::endl;
		Array<int> small(2);
		Array<int> large(10);

		small[0] = 111;
		small[1] = 222;

		for (unsigned int i = 0; i < large.size(); i++) {
			large[i] = i * 10;
		}

		std::cout << YELLOW "Before assignment:" RESET << std::endl;
		printArray(small, "Small");
		printArray(large, "Large");

		large = small;
		std::cout << YELLOW "After assignment (large = small):" RESET << std::endl;
		printArray(large, "Large (now same as small)");
		std::cout << GREEN "Size changed correctly: " << large.size() << RESET << std::endl;
	}
	std::cout << std::endl;

	std::cout << GREEN "=== ALL ARRAY TEMPLATE TESTS COMPLETED SUCCESSFULLY ===" RESET << std::endl;

	return 0;
}
