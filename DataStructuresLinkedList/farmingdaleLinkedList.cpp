// (c) 2013-2020, David Gerstl, all rights reserved
// For the use of my C++ students to use as a base to implement
// various programs needed for their data structures class.

// Class farmingdale::linkedList: General string linked List implementation
#include <iostream> // for ostream::operator<<
#include <string>
#include <deque>
#include "farmingdaleLinkedList.h"


#ifndef TEMPLATED_LINKEDLIST
int studentTest() {
	return 0;
}

// print a linkedList to a stream (e.g., std::cout)
void farmingdale::linkedList::printToStream(std::ostream& outputStream) const {
	//traverse and send the data of each node to outPutStream
	llNode* myIter = head;
	while (0 != myIter) {
		if (myIter != head) {
			outputStream << ";";
		}
		outputStream << myIter->data;
		myIter = myIter->next;
	}
}

//Default CTOR
farmingdale::linkedList::linkedList() 
	:
	head(0),
	tail(0)
{}

farmingdale::statusCode farmingdale::linkedList::getHead(std::string& returnedValue) const { // M7
	//Step 1: If the list is empty, return failure
	if (isEmpty() == true) {
		return farmingdale::statusCode::FAILURE;
	}
	//Step 2: Put the head's data value into returnedValue
	returnedValue = head->data;
	//Step 3: Return SUCCESS
	return farmingdale::statusCode::SUCCESS;
	
}
farmingdale::statusCode farmingdale::linkedList::getTail(std::string& returnedValue) const { // M7
	//Step 1: If the list is empty, return failure
	if (isEmpty() == true) {
		return farmingdale::statusCode::FAILURE;
	}
	//Step 2: Put the tail's data value into returnedValue
	returnedValue = tail->data;
	//Step 3: Return SUCCESS
	return farmingdale::statusCode::SUCCESS;
}

farmingdale::statusCode farmingdale::linkedList::insertAtHead(std::string addMe) { // M7
	//Step 1: Allocate the memory for a new node. Return FAILURE if that fails
	llNode* temp;
	try {
		temp = new llNode;
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

farmingdale::statusCode farmingdale::linkedList::insertAtTail(std::string addMe) {
	//Step 1: Allocate a new node, return FAILURE if we can't allocate
	llNode* temp;
	try {
		temp = new llNode;
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
farmingdale::statusCode farmingdale::linkedList::removeAtHead(std::string& removedVal) {
	//Step 1: If the list is empty, then we fail
	if (isEmpty() == true) {
		return farmingdale::statusCode::FAILURE;
	}
	//Step 2: If the list is not empty, then put the data from head into removedVal
	removedVal = head->data;
	
	//Step 3: Make head into the current head's next
	llNode* current = head;
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

farmingdale::linkedList::~linkedList() {
	//Step 1: Traverse the linked list
	llNode* current = head;
	while (0 != current) {
		head = head->next;
		//Step 2: Delete each node in turn
		delete current;
		current = head;
	}
}

bool farmingdale::linkedList::operator==(const linkedList& rhs) const {
	farmingdale::llNode* current = head;
	farmingdale::llNode* rhsCurrent = rhs.head;
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

bool farmingdale::linkedList::operator==(const std::deque<std::string>& rhs) const {
	//Step 1: Do a parallel traversal
	llNode* current = head;
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

farmingdale::linkedList::linkedList(const linkedList& copyMe) : head(0), tail(0) {
	llNode* otherLLNode = copyMe.head;
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

/*farmingdale::linkedList::linkedList(const linkedList& copyMe) 
	:
	head(0), tail(0)
{
	llNode* otherNode = copyMe.head;
	//Step 1: Traverse copyMe, in each iteration
	while (0 != otherNode) {
		//Step 2: Create a new node.
		llNode* temp = new llNode;
		//Step 3: Copy the content of the node from the traversal
		temp->data = otherNode->data;
		//Step 4: Add new node to the end of us
		temp->next = 0;
		//if we exist, add to our tail
		if (0 != tail) {
			tail->next = temp;
		}
		if (0 == head) {
			head = temp;
		}
		tail = temp;
		otherNode = otherNode->next;
	}
}*/

farmingdale::statusCode farmingdale::linkedList::insertAfter(llNode* insertAfterMe, std::string stringToInsert) {
	//Step 1: Create a new node. Fail if we cannot create this node (set data)
	llNode* temp;
	try {
		temp = new llNode;
	}
	catch (std::bad_alloc) {
		return farmingdale::statusCode::FAILURE;
	}
	//Step 2: Stitch the new node in between insertAfterMe and its successor
		//take the next field of the new node, and put the successor there
		//make new node the successor of insertAfterMe
	//Step 3: If insertAfterMe was the tail, we are the new tail
	//Step 4: Return success

}

farmingdale::llNode* farmingdale::linkedList::search(std::string) const {
	//Step 1: Traverse the list but stop when we find it
	//Step 2: return current
}

farmingdale::statusCode farmingdale::linkedList::removeAtTail(std::string& returnedString) {
	//Step 1: If empty, return failure
	if (isEmpty()) {
		return farmingdale::statusCode::FAILURE;
	}
	//Step 2: Do a transversal with trailCurrent (TC) until current = tail
	llNode* current = head;
	llNode* trailCurrent = 0;
	while (0 != current && current != tail) {
		trailCurrent = current;
		current = current->next;
	}
	//Step 3a: If there was a single node, then set head and tail to null
	if (0 == trailCurrent) {
		head = 0;
		tail = 0;
	}
	else {
	//Step 3b: Otherwise, stitch out current from the ll. (Make tc's into 0)
		trailCurrent->next = 0;
	}
	tail = trailCurrent;
	//Step 4: Get the string from current
	returnedString = current->data;
	//Step 5: Delete current
	delete current;
	//Step 6: Return success
	return farmingdale::statusCode::SUCCESS;
}

farmingdale::statusCode farmingdale::linkedList::remove(llNode* removeMe) {
	//Step 1: Do a traversal with a trailCurrent. Stop when current == removeMe
	//Step 2: If a current is null, then removeMe is not in this LL--return failure
	//Step 3: if removeMe is head, then remove the head
	//Step 4: if current is an interior node (or tail), stitch out current 
	//trailCurrent's new successor will be current's current successor
	//Step 5: If tail was current, tail will become trailCurrent
	//Step 6: delete current
	//Step 7: return
}

farmingdale::llNode* farmingdale::linkedList::findAtPosition(int nth) const {
	//Step 1: Traverse the list. Stop when you've iterated nth times. Stop is current null
	//Step 2: Return current
}

#else // TEMPLATED_LINKEDLIST

int studentTest() {
	return 0;
}
#endif // TEMPLATED_LINKEDLIST