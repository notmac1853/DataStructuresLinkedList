// (c) 2013-2020 David Gerstl, all rights reserved
// For the use of my C++ students to use as a base to implement
// dynamic arrays, exceptions and operator overloading, and templates


// Class farmingdale::stack: General std::string stack implementation based on array. 
// We will add dynamic arrays (for unlimited size), templates (to allow multiple types) etc.

// note: This is not thread safe--there are no mutexes or locks on the indexes.

// like #pragma once but more portable
#ifndef H_FARMINGDALELINKEDLIST
#define H_FARMINGDALELINKEDLIST


// Note to students. It's OK to #include in a library header (inside the guards). 
// but DO NOT add a "using" directive inside a library header
#include <string>
#include <deque>
#include "farmingdaleStatus.h"

// See https://docs.microsoft.com/en-us/visualstudio/debugger/finding-memory-leaks-using-the-crt-library?view=vs-2019
// for some notes on what we're doing here.
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

// Two consts for student messages
const std::string TEMPLATED_HEADER_FILE = (std::string(__FILE__).substr(std::string(__FILE__).find_last_of("\\/") + 1));
const int TEMPLATED_HEADER_LINE = (__LINE__ + 3);
// Please set these before you start on the relevant project: 
// Uncomment this to test a templated version of the stack code.
//#define TEMPLATED_LINKEDLIST

// another consts for student messages
const int TEMPLATED_HEADER_SECOND_SET_OF_LINKED_LIST_METHODS = (__LINE__ + 2);
// Uncomment this to enable the tests for the methods in Module 8 (the second set of tests)
#define SECOND_SET_OF_LINKED_LIST_METHODS

#ifndef TEMPLATED_LINKEDLIST
// This code section is for the initial [non-templated] version of the code.
namespace farmingdale {
	// Note: namespaces are additive, so you can add new elements to this namespace in other files or later
	struct llNode;
	class linkedList;
}


// a node of my ll
struct farmingdale::llNode {
	std::string data;
	llNode* next;
};

// Each method has a notation next to it indicating the Module in which you will program it.
// M7 = we will implement in Module 7, M8 = implement in Module 8
class farmingdale::linkedList {
private:
	llNode* head; // first node
	llNode* tail; // last node
public:
	linkedList(); // M7 // default ctor

	// Rule of threes
	linkedList(const linkedList&); // M8 // copy ctor
	~linkedList(); // M7 // dtor
	// not a reference paramter because we use copy/swap
	const linkedList& operator=(linkedList); //M8 // assignment operator

	// accessors
	inline bool isEmpty() const {
		//We can check either if head is 0 or we can check if tail is 0
		return (0 == head);
	} // M7 // write inline
	statusCode getHead(std::string&) const; // M7
	statusCode getTail(std::string&) const; // M7
	bool operator==(const linkedList&) const; // M7 (I write in the videos) // base comparison operator
	bool operator==(const std::deque<std::string>&) const; //M7 (I write in the videos)
														   // print a linkedList to a stream (e.g., std::cout)
	void printToStream(std::ostream& outputStream) const; // M7 (I write in the videos)
	llNode* search(std::string) const; // M8
	inline bool contains(std::string findMe) const { // M8 // write inline using search
		//Step 1: Call the search method and see if it returns null
		llNode* containsNode = search(findMe);
		return (search(findMe));
	}
	llNode* findAtPosition(int) const; // M8 // 0 = first item, 1 == second ....

	// mutators
	statusCode insertAtHead(std::string); // M7
	statusCode removeAtHead(std::string&); // M7
	statusCode insertAtTail(std::string); // M7
	statusCode insertAfter(llNode*, std::string); // M8
	statusCode removeAtTail(std::string&); // M8
	statusCode remove(llNode*); // M8  
	inline statusCode remove(std::string removeMe) { // M8 // write inline
		//Step 1: First call search(string)
		llNode* removeNode = search(removeMe);
		//Step 2: If search succeeds, call remove (node *)
		if (0 == removeNode) {
			return farmingdale::statusCode::FAILURE;
		}
		return (remove(removeNode));
	}



};
// Write the following here as outside inline functions: (all M7)
// operator!= linkedList,linkedList
inline bool operator!=(const farmingdale::linkedList& lhs, const farmingdale::linkedList& rhs) {
	return (!(lhs == rhs));
}
// operator!= linkedList,std::deque
inline bool operator!=(const farmingdale::linkedList& lhs, const std::deque<std::string>& rhs) {
	return (!(lhs == rhs));
}
// operator!= std::deque,linkedList
inline bool operator!=(const std::deque<std::string>& lhs, const farmingdale::linkedList& rhs) {
	return (!(rhs == lhs));
}
// operator== std::deque,linkedList
inline bool operator==(const std::deque<std::string>& lhs, const farmingdale::linkedList& rhs) {
	return (rhs == lhs);
}

inline std::ostream& operator<<(std::ostream& theStream, const farmingdale::linkedList& theLinkedList) {
	theLinkedList.printToStream(theStream);
	return theStream;
}

#else 
// This is the TEMPLATED_STACK code, for the templated version of Stack
namespace farmingdale {
	// Note: namespaces are additive, so you can add new elements to this namespace in other files or later
	template <class CL> struct llNode;
	template <class CL> class linkedList;
}


// a node of my ll

template <class CL> struct farmingdale::llNode {
	CL data;
	llNode* next;
};

// Each method has a notation next to it indicating the Module in which you will program it.
// M7 = we will implement in Module 7, M8 = implement in Module 8
template <class CL> class farmingdale::linkedList {
private:
	llNode<CL>* head; // first node
	llNode<CL>* tail; // last node
public:
	linkedList(); // M7 // default ctor

	// Rule of threes
	linkedList(const linkedList&); // M8 // copy ctor
	~linkedList(); // M7 // dtor
	// not a reference paramter because we use copy/swap
	const linkedList& operator=(linkedList); //M8 // assignment operator

	// accessors
	inline bool isEmpty() const {
		//We can check either if head is 0 or we can check if tail is 0
		return (0 == head);
	} // M7 // write inline
	statusCode getHead(CL&) const; // M7
	statusCode getTail(CL&) const; // M7
	bool operator==(const linkedList&) const; // M7 (I write in the videos) // base comparison operator
	bool operator==(const std::deque<CL>&) const; //M7 (I write in the videos)
														   // print a linkedList to a stream (e.g., std::cout)
	void printToStream(std::ostream& outputStream) const; // M7 (I write in the videos)
	llNode<CL>* search(CL) const; // M8
	bool contains(CL findMe) const; // M8 // write inline using search
	llNode<CL>* findAtPosition(int) const; // M8 // 0 = first item, 1 == second ....

	// mutators
	statusCode insertAtHead(CL); // M7
	statusCode removeAtHead(CL&); // M7
	statusCode insertAtTail(CL); // M7
	statusCode insertAfter(llNode<CL>*, CL); // M8
	statusCode removeAtTail(CL&); // M8
	statusCode remove(llNode<CL>*); // M8  
	statusCode remove(CL removeMe); // M8 // write inline



};
// Write the following here as outside inline functions: (all M7)
// operator!= linkedList,linkedList
template <class CL> inline bool operator!=(const farmingdale::linkedList<CL>& lhs, const farmingdale::linkedList<CL>& rhs) {
	return (!(lhs == rhs));
}
// operator!= linkedList,std::deque
template <class CL> inline bool operator!=(const farmingdale::linkedList<CL>& lhs, const std::deque<std::string>& rhs) {
	return (!(lhs == rhs));
}
// operator!= std::deque,linkedList
template <class CL> inline bool operator!=(const std::deque<std::string>& lhs, const farmingdale::linkedList<CL>& rhs) {
	return (!(rhs == lhs));
}
// operator== std::deque,linkedList
template <class CL> inline bool operator==(const std::deque<std::string>& lhs, const farmingdale::linkedList<CL>& rhs) {
	return (rhs == lhs);
}

template <class CL> inline std::ostream& operator<<(std::ostream& theStream, const farmingdale::linkedList<CL>& theLinkedList) {
	theLinkedList.printToStream(theStream);
	return theStream;
}

// print a linkedList to a stream (e.g., std::cout)
template <class CL> void farmingdale::linkedList<CL>::printToStream(std::ostream& outputStream) const {
	//traverse and send the data of each node to outPutStream
	llNode<CL>* myIter = head;
	while (0 != myIter) {
		if (myIter != head) {
			outputStream << ";";
		}
		outputStream << myIter->data;
		myIter = myIter->next;
	}
}

//Default CTOR
template <class CL> farmingdale::linkedList<CL>::linkedList()
	:
	head(0),
	tail(0)
{}

template <class CL> farmingdale::statusCode farmingdale::linkedList<CL>::getHead(CL& returnedValue) const { // M7
	//Step 1: If the list is empty, return failure
	if (isEmpty() == true) {
		return farmingdale::statusCode::FAILURE;
	}
	//Step 2: Put the head's data value into returnedValue
	returnedValue = head->data;
	//Step 3: Return SUCCESS
	return farmingdale::SUCCESS;

}
template <class CL> farmingdale::statusCode farmingdale::linkedList<CL>::getTail(CL& returnedValue) const { // M7
	//Step 1: If the list is empty, return failure
	if (isEmpty() == true) {
		return farmingdale::statusCode::FAILURE;
	}
	//Step 2: Put the tail's data value into returnedValue
	returnedValue = tail->data;
	//Step 3: Return SUCCESS
	return farmingdale::statusCode::SUCCESS;
}

template <class CL> farmingdale::statusCode farmingdale::linkedList<CL>::insertAtHead(CL addMe) { // M7
	//Step 1: Allocate the memory for a new node. Return FAILURE if that fails
	llNode<CL>* temp;
	try {
		temp = new llNode<CL>;
	}
	catch (std::bad_alloc) {
		return farmingdale::statusCode::FAILURE;
	}
	//Step 2: Assign addMe to the data field of the new node
	temp->data = addMe;
	//Step 3: Always set the next field of the new node to whatever the head is right now
	temp->next = head;
	//Step 4: Make head point to our new node
	head = temp;
	//Step 5: If tail is null, then set tail to point to the new node
	if (0 == tail) {
		tail = temp;
	}
	//Step 6: Return SUCCESS
	return farmingdale::statusCode::SUCCESS;
}

template <class CL> farmingdale::statusCode farmingdale::linkedList<CL>::insertAtTail(CL addMe) {
	//Step 1: Allocate a new node, return FAILURE if we can't allocate
	llNode<CL>* temp;
	try {
		temp = new llNode<CL>;
	}
	catch (std::bad_alloc) {
		return farmingdale::statusCode::FAILURE;
	}
	//Step 2: Set the data field of the new node to addMe
	temp->data = addMe;
	//Step 3: Set the next field of the new node to 0
	temp->next = 0;
	//Step 4: If tail is not null, set the tail's next field to point to the new node.
	if (0 != tail) {
		tail->next = temp;
	}
	else if (0 == head) {
		//Step 6: If head is null, head should point to the new node
		head = temp;
	}
	//Step 5: Set tail to point to the new node
	tail = temp;

	//Step 7: Return SUCCESS
	return farmingdale::statusCode::SUCCESS;
}
template <class CL> farmingdale::statusCode farmingdale::linkedList<CL>::removeAtHead(CL& removedVal) {
	//Step 1: If the list is empty, then we fail
	if (isEmpty() == true) {
		return farmingdale::statusCode::FAILURE;
	}
	//Step 2: If the list is not empty, then put the data from head into removedVal
	removedVal = head->data;

	//Step 3: Make head into the current head's next
	llNode<CL>* current = head;
	head = head->next;
	//Step 4: If head is null, tail should be made null too
	if (0 == head) {
		tail = 0;
	}
	//Step 5: Delete the old head
	delete current;
	//Step 6: Return SUCCESS
	return farmingdale::statusCode::SUCCESS;

}

template <class CL> farmingdale::linkedList<CL>::~linkedList() {
	//Step 1: Traverse the linked list
	llNode<CL>* current = head;
	while (0 != current) {
		head = head->next;
		//Step 2: Delete each node in turn
		delete current;
		current = head;
	}
}

template <class CL> bool farmingdale::linkedList<CL>::operator==(const linkedList<CL>& rhs) const {
	farmingdale::llNode<CL>* current = head;
	farmingdale::llNode<CL>* rhsCurrent = rhs.head;
	//Step 1:  Do a parallel traversal
	while ((0 != current) && (0 != rhsCurrent)) {
		//Step 2: If, during the traversal, current's data and rhs' data are not the same, return false

		if (current->data != rhsCurrent->data) {
			return false;
		}
		current = current->next;
		rhsCurrent = rhsCurrent->next;


	}
	//Step 3: If both current and the rhsCurrent are null, then true
	if ((0 == rhsCurrent) && (0 == current)) {
		return true;
	}
	//Step 4: Return false
	return false;

}

//myLL myDeque
//if (myLL = myDeque)
//if (myDeque == myLL)			myDeque.operator==(myLL)

template <class CL> bool farmingdale::linkedList<CL>::operator==(const std::deque<CL>& rhs) const {
	//Step 1: Do a parallel traversal
	llNode<CL>* current = head;
	std::deque<std::string>::const_iterator rhsIterator = rhs.begin();
	while (0 != current && rhs.end() != rhsIterator) {
		//Step 2: If at any step, the data differs, return false
		if (current->data != *rhsIterator) {
			return false;
		}
		current = current->next;
		++rhsIterator;
	}
	//Step 3: If both are done, then return true
	if ((0 == current) && (rhs.end() == rhsIterator)) {
		return true;
	}
	//Step 4: return false
	return false;
}

template <class CL> farmingdale::linkedList<CL>::linkedList(const linkedList<CL>& copyMe) : head(0), tail(0) {
	llNode<CL>* otherLLNode = copyMe.head;
	while (0 != otherLLNode) {
		llNode* temp = new llNode;
		temp->data = otherLLNode->data;
		temp->next = 0;
		if (0 == head) {
			head = temp;
		}
		else {
			tail->next = temp;
		}
		tail = temp;
		otherLLNode = otherLLNode->next;
	}
}

#endif // TEMPLATED_LINKEDLIST


#endif // H_FARMINGDALELINKEDLIST