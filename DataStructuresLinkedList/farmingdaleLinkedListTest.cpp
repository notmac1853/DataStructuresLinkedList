// (c) 2013-2020, David Gerstl, all rights reserved
// For the use of my C++ students to use as a base to implement
// various programs needed for their data structures class.

// Class farmingdale::linkedList: General string linked List implementation

// very minimal set of tests. 
#include <iostream>
#include <string>
#include <random>
#include "farmingdaleLinkedList.h"
#include "farmingdaleLinkedListTest.h"


// test methods return 0 on success. Otherwise return the line number 
// on which the error occurred (For ease in finding it. Note that the 
// preprocessor directive __LINE__ will give you this line.


#ifndef TEMPLATED_LINKEDLIST
void printTestMessages(std::ostream& theStream) {
	theStream << "This is the non-templated version of the linked list tests: Make sure you do the template conversion and pass both tests" << std::endl;
	theStream << "You can switch these by uncommenting the #define for TEMPLATED_LINKEDLIST at line "<< TEMPLATED_HEADER_LINE << " of " << TEMPLATED_HEADER_FILE <<  std::endl;

#ifndef SECOND_SET_OF_LINKED_LIST_METHODS
	theStream << "\n\nThis set of tests is only appropriate for Module 7. IF YOU ARE DOING MODULE 8, you must go to "
		<< TEMPLATED_HEADER_FILE <<
		" and remove the comment in front of the #define for SECOND_SET_OF_LINKED_LIST_METHODS on line "
		<< TEMPLATED_HEADER_SECOND_SET_OF_LINKED_LIST_METHODS << std::endl;
#else 
	theStream << "\n\nThis set of tests is appropriate for Module 8. IF YOU ARE DOING MODULE 7, you should go to "
		<< TEMPLATED_HEADER_FILE <<
		" and add a  comment in front of the #define for SECOND_SET_OF_LINKED_LIST_METHODS on line "
		<< TEMPLATED_HEADER_SECOND_SET_OF_LINKED_LIST_METHODS << std::endl;
#endif // ndef SECOND_SET_OF_LINKED_LIST_METHODS
}



// Compare a deque and LL with a set of simple operations. You can uncomment the std::cerr 
// statements to look at how test progresses if you can't find a bug
int shortSimpleTest() {
	// some of my setup for tracking memory usage. 
	// See https://docs.microsoft.com/en-us/visualstudio/debugger/finding-memory-leaks-using-the-crt-library?view=vs-2019
	_CrtMemState sB4, sMiddle, sEnd;
	// Set a memory Checkpoint
	_CrtMemCheckpoint(&sB4);
	// Note that this code is put into its own scope so the dtor gets called BEFORE the end of the method
	// so we can test if the dtor is leaking memory
	{

		farmingdale::linkedList testLL;
		if (!testLL.isEmpty()) {
			std::cerr << "Failure line " << __LINE__ << std::endl;
			return __LINE__;
		}
		if (farmingdale::statusCode::FAILURE == testLL.insertAtHead("0")) {
			std::cerr << "Failure line " << __LINE__ << std::endl;
			return __LINE__;
		}
		// LL is now:  (head) 0 (tail)
		if (testLL.isEmpty()) {
			std::cerr << "Failure line " << __LINE__ << std::endl;
			return __LINE__;
		}
		if (farmingdale::statusCode::FAILURE == testLL.insertAtTail("1")) {
			std::cerr << "Failure line " << __LINE__ << std::endl;
			return __LINE__;
		}
		// LL is now:  (head) 0 1 (tail)
		std::string testString;
		if (farmingdale::statusCode::FAILURE == testLL.getHead(testString) || "0" != testString) {
			std::cerr << "Failure line " << __LINE__ << std::endl;
			return __LINE__;
		}
		if (farmingdale::statusCode::FAILURE == testLL.getTail(testString) || "1" != testString) {
			std::cerr << "Failure line " << __LINE__ << std::endl;
			return __LINE__;
		}
		if (farmingdale::statusCode::FAILURE == testLL.insertAtTail("2")) {
			std::cerr << "Failure line " << __LINE__ << std::endl;
			return __LINE__;
		}
		_CrtMemState b4Insert, b4Delete, afterDelete;
		_CrtMemCheckpoint(&b4Insert);
		// LL is now:  (head) 0 1 2 (tail)
		if (farmingdale::statusCode::FAILURE == testLL.insertAtHead("-1")) {
			std::cerr << "Failure line " << __LINE__ << std::endl;
			return __LINE__;
		}
		_CrtMemCheckpoint(&b4Delete);
		// Check that we grew from insert
		if ((b4Delete.lCounts[_NORMAL_BLOCK] - b4Insert.lCounts[_NORMAL_BLOCK]) < 1) {
			std::cerr << "It doesn't seem like you allocated any memory for insertAtHead()" << std::endl;
			return __LINE__;
		}
		// LL is now:  (head) -1 0 1 2 (tail)
		if (farmingdale::statusCode::FAILURE == testLL.removeAtHead(testString) || "-1" != testString) {
			std::cerr << "Failure line " << __LINE__ << std::endl;
			return __LINE__;
		}
		_CrtMemCheckpoint(&afterDelete);
		
		// Check that we're net zero 
		if ((afterDelete.lCounts[_NORMAL_BLOCK] - b4Insert.lCounts[_NORMAL_BLOCK]) > 0 ) {
			std::cerr << "It seems like removeAtHead() is leaking memory" << std::endl;
			return __LINE__;
		}

		// LL is now:  (head) 0 1 2 (tail)
		if (farmingdale::statusCode::FAILURE == testLL.getHead(testString) || "0" != testString) {
			std::cerr << "Failure line " << __LINE__ << std::endl;
			return __LINE__;
		}
		if (farmingdale::statusCode::FAILURE == testLL.getTail(testString) || "2" != testString) {
			std::cerr << "Failure line " << __LINE__ << std::endl;
			return __LINE__;
		}
		farmingdale::linkedList otherTestLL;
		if (farmingdale::statusCode::FAILURE == otherTestLL.insertAtHead("1")) {
			std::cerr << "Failure line " << __LINE__ << std::endl;
			return __LINE__;
		}
		// otherLL is now (head) 1 (tail)
		if (testLL == otherTestLL) {
			std::cerr << "Failure line " << __LINE__ << std::endl;
			return __LINE__;
		}
		if (farmingdale::statusCode::FAILURE == otherTestLL.insertAtHead("0")) {
			std::cerr << "Failure line " << __LINE__ << std::endl;
			return __LINE__;
		}
		// otherLL is now (head) 0 1 (tail)
		if (farmingdale::statusCode::FAILURE == otherTestLL.insertAtTail("2")) {
			std::cerr << "Failure line " << __LINE__ << std::endl;
			return __LINE__;
		}
#ifdef SECOND_SET_OF_LINKED_LIST_METHODS
		if (0 != otherTestLL.findAtPosition(4)) {
			// findAtPosition should return 0 if the index
			// is greater than the size of the list
			std::cerr << "Failure line " << __LINE__ << std::endl;
			return __LINE__;
		}
#endif // SECOND_SET_OF_LINKED_LIST_METHODS
		// otherLL is now (head) 0 1 2 (tail)
		if (testLL != otherTestLL) {
			std::cerr << "Failure line " << __LINE__ << std::endl;
			return __LINE__;
		}
		// Set a memory Checkpoint
		_CrtMemCheckpoint(&sMiddle);
		// Just for fun--not a great test
		std::cout << "The content of testLL (which should be: 0 1 2) is " << testLL << std::endl;
	}
	// Set a memory Checkpoint
	_CrtMemCheckpoint(&sEnd);

	// Now validate that you successfully cleaned up the memory in your destructor
	if ((sMiddle.lCounts[_NORMAL_BLOCK] - sB4.lCounts[_NORMAL_BLOCK]) < 1) {
		std::cerr << "It doesn't seem like you allocated any memory" << std::endl;
		return __LINE__;
	}
	if ((sEnd.lCounts[_NORMAL_BLOCK] - sB4.lCounts[_NORMAL_BLOCK]) != 0) {
		std::cerr << "It seems you are leaking memory in your destructor" << std::endl;
		return __LINE__;
	}



	return 0;
}


// compare the deque and ll with a variety of operations
// this has not been tested, so may have errors. Once ll is done, we can debug.
int randomCompareWithDequeTest() {
	// some of my setup for tracking memory usage. 
	// See https://docs.microsoft.com/en-us/visualstudio/debugger/finding-memory-leaks-using-the-crt-library?view=vs-2019
	_CrtMemState sB4, sAfter;
	const int large_number_of_iterations = 10000;
	std::deque<std::string> testDeque;
	std::string out1, out2; // for holding output
	farmingdale::linkedList myLL;
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<> dis(1, 9);
	std::uniform_int_distribution<> bigDis(INT_MIN, INT_MAX);
	int position;
	for (int iteration = 0; iteration < large_number_of_iterations; ++iteration) {
		int action = dis(gen);
		std::string num = std::to_string(bigDis(gen));
		switch (action) {
		case 1:
			// insertAtHead() is M7
			testDeque.push_front(num);
			if (farmingdale::statusCode::FAILURE == myLL.insertAtHead(num))  {
				// bad bad bad. They don't match
				std::cerr << "Failure line " << __LINE__ << " on iteration " << iteration << std::endl;
				return __LINE__;
			}
			break;
		case 2:
			// insertAtTail is M7
			testDeque.push_back(num);
			if (farmingdale::statusCode::FAILURE ==myLL.insertAtTail(num))  {
				// bad bad bad. They don't match
				std::cerr << "Failure line " << __LINE__ << " on iteration " << iteration << std::endl;
				return __LINE__;
			}
			break;
		case 3:
			// removeAtHead() is M7. We check for leaks here in simpleTest, but do it again here
			// first a guard
			if (testDeque.empty()) {
				if (!(myLL.isEmpty())) {
					// bad bad bad. They don't match
					std::cerr << "Failure line " << __LINE__ << " on iteration " << iteration << std::endl;
					return __LINE__;
				}
				// if we get here, we're done with this iteration
				continue;
			} // testDeque.empty()
			out1 = testDeque.front();
			testDeque.pop_front();
			// Set a memory Checkpoint
			_CrtMemCheckpoint(&sB4);
			if (farmingdale::statusCode::FAILURE == myLL.removeAtHead(out2)) {
				// It better not be empty
				std::cerr << "Failure line " << __LINE__ << " on iteration " << iteration << std::endl;
				return __LINE__;
			}
			if (out1 != out2) {
				std::cerr << "Failure line " << __LINE__ << " on iteration " << iteration << std::endl;
				return __LINE__;
			}
			// Set a memory Checkpoint
			_CrtMemCheckpoint(&sAfter);
			// Check that we reduced the memory footprint across the remove:
			if (!(sAfter.lCounts[_NORMAL_BLOCK] < sB4.lCounts[_NORMAL_BLOCK])) {
				std::cerr << "It seems you are leaking memory in removeAtTail()" << std::endl;
				return __LINE__;
			}
			break;
		case 4:
			// getTail is M7
			if (true == testDeque.empty()) {
				// both better be
				if (!myLL.isEmpty()) {
					std::cerr << "Failure line " << __LINE__ << " on iteration " << iteration << std::endl;
					return __LINE__;
				}
				// if we get here, we're done.
				continue;
			} // empty
			out1 = testDeque.back();
			if (farmingdale::statusCode::FAILURE == myLL.getTail(out2)) {
				std::cerr << "Failure line " << __LINE__ << " on iteration " << iteration << std::endl;
				return __LINE__;
			}
			if (out1 != out2) {
				std::cerr << "Failure line " << __LINE__ << " on iteration " << iteration << std::endl;
				return __LINE__;
			}
			break;
		case 5:
			// getHead is M7
			if (true == testDeque.empty()) {
				// both better be
				if (!myLL.isEmpty()) {
					std::cerr << "Failure line " << __LINE__ << " on iteration " << iteration << std::endl;
					return __LINE__;
				}
				// if we get here, we're done.
				continue;
			} // empty
			out1 = testDeque.front();
			if (farmingdale::statusCode::FAILURE == myLL.getHead(out2)) {
				std::cerr << "Failure line " << __LINE__ << " on iteration " << iteration << std::endl;
				return __LINE__;
			}
			if (out1 != out2) {
				std::cerr << "Failure line " << __LINE__ << " on iteration " << iteration << std::endl;
				return __LINE__;
			}
			break;
#ifdef SECOND_SET_OF_LINKED_LIST_METHODS
		case 6:
			// findAtPostion is M8
		{
			if (testDeque.size() < 3) {
				// there's no read middle if there's no middle
				continue;
			}
			// not necessary, but good overflow prevention practice
			int max = (testDeque.size() > INT_MAX) ? (INT_MAX) : (int(testDeque.size()) - 1);
			std::uniform_int_distribution<> posnDis(1, max);
			position = posnDis(gen);
			std::deque<std::string>::iterator readThisItem = testDeque.begin() + (position);
			farmingdale::llNode* nodeRead = myLL.findAtPosition(position);
			if (nodeRead->data != *readThisItem) {
				std::cerr << "Failure line " << __LINE__ << " on iteration " << iteration << std::endl;
				return __LINE__;
			}
		}
		break;
		case 7:
			// add at middle (after (n-1)th item)) is M8
			if (testDeque.size() > 3) {
				// there's no read middle if there's no middle
				// not necessary, but good overflow prevention practice
				int max = (testDeque.size() > INT_MAX) ? (INT_MAX) : (int(testDeque.size()) - 1);
				std::uniform_int_distribution<> posnDis(1, max); // never 0 by design
				position = posnDis(gen);
				// note that deque insert makes your item the new X, so inserts before. We insert after
				std::deque<std::string>::iterator insertAfter = testDeque.begin() + (position);
				farmingdale::llNode* nodeAfter = myLL.findAtPosition(position);
				++insertAfter;
				testDeque.insert(insertAfter, num);
				myLL.insertAfter(nodeAfter, num);
			}
			break;
		case 8:
			// findAtPosition and Remove are M8
		{
			if (testDeque.size() < 3) {
				// there's no remove middle if there's no middle
				continue;
			}
			// not necessary, but good overflow prevention practice
			int max = (testDeque.size() > INT_MAX) ? (INT_MAX) : (int(testDeque.size()) - 2);
			std::uniform_int_distribution<> posnDis(1, max);
			position = posnDis(gen);
			std::deque<std::string>::iterator removeThisItem = testDeque.begin() + (position);
			farmingdale::llNode* nodeRemove = myLL.findAtPosition(position);
			testDeque.erase(removeThisItem);
			myLL.remove(nodeRemove);
		}
		break;
		case 9:
			// removeAtTail is M8
			if (true == testDeque.empty()) {
				// both better be
				if (!myLL.isEmpty()) {
					std::cerr << "Failure line " << __LINE__ << " on iteration " << iteration << std::endl;
					return __LINE__;
				}
				continue;
			} // empty
			out1 = testDeque.back();
			testDeque.pop_back();
			// Set a memory Checkpoint
			_CrtMemCheckpoint(&sB4);
			if (farmingdale::statusCode::FAILURE == myLL.removeAtTail(out2)) {
				std::cerr << "Failure line " << __LINE__ << " on iteration " << iteration << std::endl;
				return __LINE__;
			}
			if (out1 != out2) {
				std::cerr << "Failure line " << __LINE__ << " on iteration " << iteration << std::endl;
				return __LINE__;
			}
			// Set a memory Checkpoint
			_CrtMemCheckpoint(&sAfter);
			// Check that we reduced the memory footprint across the remove:
			if (!(sAfter.lCounts[_NORMAL_BLOCK] < sB4.lCounts[_NORMAL_BLOCK])) {
				std::cerr << "It seems you are leaking memory in removeAtTail()" << std::endl;
				return __LINE__;
			}
			break;
#endif  // SECOND_SET_OF_LINKED_LIST_METHODS
		default:
			position = 0; // no need for a noop and no warning about unused variable...win-win.
			break;
		} // switch
	} // for i = 0...ITERATIONS
	// One last check for equality
	if (myLL != testDeque) {
		std::cerr << "Failure line " << __LINE__ << std::endl;
		return __LINE__;
	}
	return 0;
}


int copyCtorTest() {
	// copy Ctor is defined in M8, so does nothing in M7
#ifdef SECOND_SET_OF_LINKED_LIST_METHODS
	// insert 100k random items in, then test/compare.
	const int large_number_of_iterations = 100000;
	std::deque<std::string> testDeque;
	farmingdale::linkedList myLL;
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<> bigDis(INT_MIN, INT_MAX);
	for (int iteration = 0; iteration < large_number_of_iterations; ++iteration) {
		std::string numString = std::to_string(bigDis(gen));
		testDeque.push_back(numString);
		myLL.insertAtTail(numString);
	}
	if (testDeque != myLL) {
		std::cerr << "Failure line " << __LINE__ << std::endl;
		return __LINE__;
	}
	farmingdale::linkedList ll2(myLL);
	if (ll2 != myLL) {
		std::cerr << "Failure line " << __LINE__ << std::endl;
		return __LINE__;
	}
	farmingdale::linkedList ll3 = myLL;
	if (ll2 != myLL) {
		std::cerr << "Failure line " << __LINE__ << std::endl;
		return __LINE__;
	}
	// now remove and replace an item
	// This makes sure that the copies are deep copies, not shallow.
	std::string tempStr;
	if (farmingdale::statusCode::FAILURE == myLL.removeAtHead(tempStr)) {
		std::cerr << "Failure line " << __LINE__ << std::endl;
		return __LINE__;
	}
	if (farmingdale::statusCode::FAILURE == myLL.insertAtHead("Fish")) {
		std::cerr << "Failure line " << __LINE__ << std::endl;
		return __LINE__;
	}
	if (ll2 == myLL) {
		std::cerr << "Failure line " << __LINE__ << std::endl;
		return __LINE__;
	}
#endif
	return 0;
}

#else // TEMPLATED_STACK
void printTestMessages(std::ostream& theStream) {
	theStream << "This is the templated version of the linked list tests: Make sure you do the template conversion and pass both tests" << std::endl;
	theStream << "You can switch these by uncommenting the #define for TEMPLATED_LINKEDLIST at line "<< TEMPLATED_HEADER_LINE << " of " << TEMPLATED_HEADER_FILE <<  std::endl;

#ifndef SECOND_SET_OF_LINKED_LIST_METHODS
	theStream << "\n\nThis set of tests is only appropriate for Module 7. IF YOU ARE DOING MODULE 8, you must go to "
		<< TEMPLATED_HEADER_FILE <<
		" and remove the comment in front of the #define for SECOND_SET_OF_LINKED_LIST_METHODS on line "
		<< TEMPLATED_HEADER_SECOND_SET_OF_LINKED_LIST_METHODS << std::endl;
#else
	theStream << "\n\nThis set of tests is appropriate for Module 8. IF YOU ARE DOING MODULE 7, you should go to "
		<< TEMPLATED_HEADER_FILE <<
		" and add a  comment in front of the #define for SECOND_SET_OF_LINKED_LIST_METHODS on line "
		<< TEMPLATED_HEADER_SECOND_SET_OF_LINKED_LIST_METHODS << std::endl;
#endif // ndef SECOND_SET_OF_LINKED_LIST_METHODS
}

// Compare a deque and LL with a set of simple operations. You can uncomment the std::cerr 
// statements to look at how test progresses if you can't find a bug
int shortSimpleTest() {
	farmingdale::linkedList<int> testLL;
	if (!testLL.isEmpty()) {
		std::cerr << "Failure line " << __LINE__ << std::endl;
		return __LINE__;
	}
	if (farmingdale::statusCode::FAILURE == testLL.insertAtHead(0)) {
		std::cerr << "Failure line " << __LINE__ << std::endl;
		return __LINE__;
	}
	// LL is now:  (head) 0 (tail)
	if (testLL.isEmpty()) {
		std::cerr << "Failure line " << __LINE__ << std::endl;
		return __LINE__;
	}
	if (farmingdale::statusCode::FAILURE == testLL.insertAtTail(1)) {
		std::cerr << "Failure line " << __LINE__ << std::endl;
		return __LINE__;
	}
	// LL is now:  (head) 0 1 (tail)
	int testInt;
	if (farmingdale::statusCode::FAILURE == testLL.getHead(testInt) || 0 != testInt) {
		std::cerr << "Failure line " << __LINE__ << std::endl;
		return __LINE__;
	}
	if (farmingdale::statusCode::FAILURE == testLL.getTail(testInt) || 1 != testInt) {
		std::cerr << "Failure line " << __LINE__ << std::endl;
		return __LINE__;
	}
	if (farmingdale::statusCode::FAILURE == testLL.insertAtTail(2)) {
		std::cerr << "Failure line " << __LINE__ << std::endl;
		return __LINE__;
	}
	// LL is now:  (head) 0 1 2 (tail)
	if (farmingdale::statusCode::FAILURE == testLL.insertAtHead(-1)) {
		std::cerr << "Failure line " << __LINE__ << std::endl;
		return __LINE__;
	}
	// LL is now:  (head) -1 0 1 2 (tail)
	if (farmingdale::statusCode::FAILURE == testLL.removeAtHead(testInt) || -1 != testInt) {
		std::cerr << "Failure line " << __LINE__ << std::endl;
		return __LINE__;
	}
	// LL is now:  (head) 0 1 2 (tail)
	if (farmingdale::statusCode::FAILURE == testLL.getHead(testInt) || 0 != testInt) {
		std::cerr << "Failure line " << __LINE__ << std::endl;
		return __LINE__;
	}
	if (farmingdale::statusCode::FAILURE == testLL.getTail(testInt) || 2 != testInt) {
		std::cerr << "Failure line " << __LINE__ << std::endl;
		return __LINE__;
	}
	farmingdale::linkedList<int> otherTestLL;
	if (farmingdale::statusCode::FAILURE == otherTestLL.insertAtHead(1)) {
		std::cerr << "Failure line " << __LINE__ << std::endl;
		return __LINE__;
	}
	// otherLL is now (head) 1 (tail)
	if (testLL == otherTestLL) {
		std::cerr << "Failure line " << __LINE__ << std::endl;
		return __LINE__;
	}
	if (farmingdale::statusCode::FAILURE == otherTestLL.insertAtHead(0)) {
		std::cerr << "Failure line " << __LINE__ << std::endl;
		return __LINE__;
	}
	// otherLL is now (head) 0 1 (tail)
	if (farmingdale::statusCode::FAILURE == otherTestLL.insertAtTail(2)) {
		std::cerr << "Failure line " << __LINE__ << std::endl;
		return __LINE__;
	}
	// otherLL is now (head) 0 1 2 (tail)
	if (testLL != otherTestLL) {
		std::cerr << "Failure line " << __LINE__ << std::endl;
		return __LINE__;
	}
	// Just for fun--not a great test
	std::cout << "The content of testLL (which should be: 0 1 2) is " << testLL << std::endl;
	return 0;
}


// compare the deque and ll with a variety of operations
// this has not been tested, so may have errors. Once ll is done, we can debug.
int randomCompareWithDequeTest() {
	const int large_number_of_iterations = 10000;
	std::deque<std::string> testDeque;
	std::string out1, out2; // for holding output
	farmingdale::linkedList<std::string> myLL;
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<> dis(1, 9);
	std::uniform_int_distribution<> bigDis(INT_MIN, INT_MAX);
	int position;
	for (int iteration = 0; iteration < large_number_of_iterations; ++iteration) {
		int action = dis(gen);
		std::string num = std::to_string(bigDis(gen));
		switch (action) {
		case 1:
			// insertAtHead() is M7
			testDeque.push_front(num);
			if (farmingdale::statusCode::FAILURE == myLL.insertAtHead(num))  {
				// bad bad bad. They don't match
				std::cerr << "Failure line " << __LINE__ << " on iteration " << iteration << std::endl;
				return __LINE__;
			}
			break;
		case 2:
			// insertAtTail is M7
			testDeque.push_back(num);
			if (farmingdale::statusCode::FAILURE ==myLL.insertAtTail(num))  {
				// bad bad bad. They don't match
				std::cerr << "Failure line " << __LINE__ << " on iteration " << iteration << std::endl;
				return __LINE__;
			}
			break;
		case 3:
			// removeAtHead() is M7
			// first a guard
			if (testDeque.empty()) {
				if (!(myLL.isEmpty())) {
					// bad bad bad. They don't match
					std::cerr << "Failure line " << __LINE__ << " on iteration " << iteration << std::endl;
					return __LINE__;
				}
				// if we get here, we're done with this iteration
				continue;
			} // testDeque.empty()
			out1 = testDeque.front();
			testDeque.pop_front();
			if (farmingdale::statusCode::FAILURE == myLL.removeAtHead(out2)) {
				// It better not be empty
				std::cerr << "Failure line " << __LINE__ << " on iteration " << iteration << std::endl;
				return __LINE__;
			}
			if (out1 != out2) {
				std::cerr << "Failure line " << __LINE__ << " on iteration " << iteration << std::endl;
				return __LINE__;
			}
			break;
		case 4:
			// getTail is M7
			if (true == testDeque.empty()) {
				// both better be
				if (!myLL.isEmpty()) {
					std::cerr << "Failure line " << __LINE__ << " on iteration " << iteration << std::endl;
					return __LINE__;
				}
				// if we get here, we're done.
				continue;
			} // empty
			out1 = testDeque.back();
			if (farmingdale::statusCode::FAILURE == myLL.getTail(out2)) {
				std::cerr << "Failure line " << __LINE__ << " on iteration " << iteration << std::endl;
				return __LINE__;
			}
			if (out1 != out2) {
				std::cerr << "Failure line " << __LINE__ << " on iteration " << iteration << std::endl;
				return __LINE__;
			}
			break;
		case 5:
			// getHead is M7
			if (true == testDeque.empty()) {
				// both better be
				if (!myLL.isEmpty()) {
					std::cerr << "Failure line " << __LINE__ << " on iteration " << iteration << std::endl;
					return __LINE__;
				}
				// if we get here, we're done.
				continue;
			} // empty
			out1 = testDeque.front();
			if (farmingdale::statusCode::FAILURE == myLL.getHead(out2)) {
				std::cerr << "Failure line " << __LINE__ << " on iteration " << iteration << std::endl;
				return __LINE__;
			}
			if (out1 != out2) {
				std::cerr << "Failure line " << __LINE__ << " on iteration " << iteration << std::endl;
				return __LINE__;
			}
			break;
#ifdef SECOND_SET_OF_LINKED_LIST_METHODS
		case 6:
			// findAtPostion is M8
		{
			if (testDeque.size() < 3) {
				// there's no read middle if there's no middle
				continue;
			}
			// not necessary, but good overflow prevention practice
			int max = (testDeque.size() > INT_MAX) ? (INT_MAX) : (int(testDeque.size()) - 1);
			std::uniform_int_distribution<> posnDis(1, max);
			position = posnDis(gen);
			std::deque<std::string>::iterator readThisItem = testDeque.begin() + (position);
			farmingdale::llNode<std::string>* nodeRead = myLL.findAtPostion(position);
			if (nodeRead->data != *readThisItem) {
				std::cerr << "Failure line " << __LINE__ << " on iteration " << iteration << std::endl;
				return __LINE__;
			}
		}
		break;
		case 7:
			// add at middle (after (n-1)th item)) is M8
			if (testDeque.size() > 3) {
				// there's no read middle if there's no middle
				// not necessary, but good overflow prevention practice
				int max = (testDeque.size() > INT_MAX) ? (INT_MAX) : (int(testDeque.size()) - 1);
				std::uniform_int_distribution<> posnDis(1, max); // never 0 by design
				position = posnDis(gen);
				// note that deque insert makes your item the new X, so inserts before. We insert after
				std::deque<std::string>::iterator insertAfter = testDeque.begin() + (position);
				farmingdale::llNode<std::string>* nodeAfter = myLL.findAtPostion(position);
				++insertAfter;
				testDeque.insert(insertAfter, num);
				myLL.insertAfter(nodeAfter, num);
			}
			break;
		case 8:
			// findAtPosition and Remove are M10
		{
			if (testDeque.size() < 3) {
				// there's no remove middle if there's no middle
				continue;
			}
			// not necessary, but good overflow prevention practice
			int max = (testDeque.size() > INT_MAX) ? (INT_MAX) : (int(testDeque.size()) - 2);
			std::uniform_int_distribution<> posnDis(1, max);
			position = posnDis(gen);
			std::deque<std::string>::iterator removeThisItem = testDeque.begin() + (position);
			farmingdale::llNode<std::string>* nodeRemove = myLL.findAtPostion(position);
			testDeque.erase(removeThisItem);
			myLL.remove(nodeRemove);
		}
		break;
		case 9:
			// removeAtTail is M8
			if (true == testDeque.empty()) {
				// both better be
				if (!myLL.isEmpty()) {
					std::cerr << "Failure line " << __LINE__ << " on iteration " << iteration << std::endl;
					return __LINE__;
				}
				continue;
			} // empty
			out1 = testDeque.back();
			testDeque.pop_back();
			if (farmingdale::statusCode::FAILURE == myLL.removeAtTail(out2)) {
				std::cerr << "Failure line " << __LINE__ << " on iteration " << iteration << std::endl;
				return __LINE__;
			}
			if (out1 != out2) {
				std::cerr << "Failure line " << __LINE__ << " on iteration " << iteration << std::endl;
				return __LINE__;
			}
			break;
#endif  // SECOND_SET_OF_LINKED_LIST_METHODS
		default:
			position = 0; // no need for a noop and no warning about unused variable...win-win.
			break;
		} // switch
	} // for i = 0...ITERATIONS
	  // One last check for equality
	if (myLL != testDeque) {
		std::cerr << "Failure line " << __LINE__ << std::endl;
		return __LINE__;
	}
	return 0;
}


int copyCtorTest() {
	// copy Ctor is defined in M8, so does nothing in M7
#ifdef SECOND_SET_OF_LINKED_LIST_METHODS
	// insert 100k random items in, then test/compare.
	const int large_number_of_iterations = 100000;
	std::deque<std::string> testDeque;
	farmingdale::linkedList<std::string> myLL;
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<> bigDis(INT_MIN, INT_MAX);
	for (int iteration = 0; iteration < large_number_of_iterations; ++iteration) {
		std::string numString = std::to_string(bigDis(gen));
		testDeque.push_back(numString);
		myLL.insertAtTail(numString);
	}
	if (testDeque != myLL) {
		std::cerr << "Failure line " << __LINE__ << std::endl;
		return __LINE__;
	}
	farmingdale::linkedList<std::string> ll2(myLL);
	if (ll2 != myLL) {
		std::cerr << "Failure line " << __LINE__ << std::endl;
		return __LINE__;
	}
	farmingdale::linkedList<std::string> ll3 = myLL;
	if (ll2 != myLL) {
		std::cerr << "Failure line " << __LINE__ << std::endl;
		return __LINE__;
	}
	// now remove and replace an item
	// This makes sure that the copies are deep copies, not shallow.
	std::string tempStr;
	if (farmingdale::statusCode::FAILURE == myLL.removeAtHead(tempStr)) {
		std::cerr << "Failure line " << __LINE__ << std::endl;
		return __LINE__;
	}
	if (farmingdale::statusCode::FAILURE == myLL.insertAtHead("Fish")) {
		std::cerr << "Failure line " << __LINE__ << std::endl;
		return __LINE__;
	}
	if (ll2 == myLL) {
		std::cerr << "Failure line " << __LINE__ << std::endl;
		return __LINE__;
	}
#endif
	return 0;
}


#endif // TEMPLATED_STACK
