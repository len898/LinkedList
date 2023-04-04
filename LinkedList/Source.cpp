#include <iostream>

typedef unsigned int int32;

using namespace std;

struct LinkedListNode
{
	string val;
	LinkedListNode* prev;
	LinkedListNode* next;

	LinkedListNode(string val, LinkedListNode* prev, LinkedListNode* next)
	{
		this->val = val;
		this->prev = prev;
		this->next = next;
	}
};


LinkedListNode* GenLinked()
{
	LinkedListNode* prev = nullptr;
	LinkedListNode* current = nullptr;
	LinkedListNode* first = nullptr;

	for (int i = 0; i < 10; ++i)
	{
		string current_val;
		cin >> current_val;
		current = new LinkedListNode(current_val, prev, nullptr);
		if (first == nullptr)
		{
			first = current;
		}

		if (prev != nullptr) prev->next = current;
		prev = current;
	}

	return first;
}

void PrintLinked(LinkedListNode* list)
{
	while (list != nullptr)
	{
		cout << list->val << endl;
		list = list->next;
	}
}

//returns nullptr if not found;
LinkedListNode* SearchLinked(LinkedListNode* start, string val)
{
	LinkedListNode* v = start;
	int i = 0;
	while (v != nullptr)
	{
		if (v->val == val)
		{
			cout << "Found value " << val << " at node " << i << endl;
			return v;
		}
		v = v->next;
		i++;
	}

	cout << "Could not find match... Returning nullptr." << endl;

	return nullptr;
}

LinkedListNode* FindMid(LinkedListNode* start, LinkedListNode* end) {
	LinkedListNode* slow = start;
	LinkedListNode* fast = start;
	while (fast != end && fast->next != end) {
		slow = slow->next;
		fast = fast->next->next;
	}
	return slow;
}

LinkedListNode* BinarySearch(LinkedListNode* start, LinkedListNode* end, string val) {
	LinkedListNode* endPt = end;
	LinkedListNode* midpoint = FindMid(start, end);

	if (midpoint->val == val) {
		return midpoint;
	}
	if (midpoint->val == start->val) {
		return nullptr;
	}
	else if (midpoint->val < val) {
		return BinarySearch(midpoint->next, end, val);
	}
	else if (midpoint->val > val) {
		return BinarySearch(start, midpoint->prev, val);
	}
}

LinkedListNode* swapNodes(LinkedListNode* node1, LinkedListNode* node2) {
	if (node1->next == node2) {
		LinkedListNode* tempBack = node1->prev;
		LinkedListNode* tempFront = node1->next;
		node1->prev = node2;
		node1->next = node2->next;
		if (node2->next != nullptr) {
			node2->next->prev = node1;
		}
		node2->prev = tempBack;
		if (tempBack != nullptr) {
			tempBack->next = node2;
		}
		node2->next = node1;
		return node2;
	}
	else {
		LinkedListNode* tempBack = node1->prev;
		LinkedListNode* tempFront = node1->next;
		node1->prev = node2->prev;
		if (node2->prev != nullptr) {
			node2->prev->next = node1;
		}
		node1->next = node2->next;
		if (node2->next != nullptr) {
			node2->next->prev = node1;
		}
		node2->prev = tempBack;
		if (tempBack != nullptr) {
			tempBack->next = node2;
		}
		node2->next = tempFront;
		if (tempFront != nullptr) {
			tempFront->prev = node2;
		}
		return node2;
	}
}

LinkedListNode* findMin(LinkedListNode* start) {
	LinkedListNode* minNode = start;
	LinkedListNode* traverser = start;
	while (traverser != nullptr) {
		if (traverser->val < minNode->val) {
			minNode = traverser;
		}
		traverser = traverser->next;
	}
	return minNode;
}

LinkedListNode* SelectionSort(LinkedListNode* head) {
	LinkedListNode* sortedHead = head;
	LinkedListNode* sortedTail = head;

	if (findMin(sortedTail)->val < sortedHead->val) {
		sortedHead = swapNodes(sortedTail, findMin(sortedTail));
	}

	sortedTail = sortedHead->next;

	while (sortedTail != nullptr) {
		PrintLinked(sortedTail);
		cout << endl;
		if (findMin(sortedTail)->val < sortedTail->val) {
			sortedTail = swapNodes(sortedTail, findMin(sortedTail));
		}
		sortedTail = sortedTail->next;
	}

	//cout << sortedHead->val << endl;
	return sortedHead;
}


int main()
{
	LinkedListNode* linked = GenLinked();
	cout << "Printing Linked List: " << endl;
	//PrintLinked(linked);

	//SearchLinked(linked, 0);
	//SearchLinked(linked, 1);
	//SearchLinked(linked, 9);
	//SearchLinked(linked, 10);

	/*if (BinarySearch(linked, nullptr, "f") != nullptr) {
		cout << "Value Found";
	}
	else {
		cout << "Null";
	}*/

	PrintLinked(SelectionSort(linked));
	//PrintLinked(linked);


	while (linked->next != nullptr)
	{
		if (linked->prev != nullptr)
		{
			delete linked->prev;
		}
		linked = linked->next;
	}

	delete linked;
}