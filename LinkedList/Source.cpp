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

	for (int i = 0; i < 5; ++i)
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

	if (midpoint->val < start->val) {
		return nullptr;
	}
	if (midpoint->val == val) {
		return midpoint;
	}
	else if (midpoint->val < val) {
		return BinarySearch(midpoint, end, val);
	}
	else if (midpoint->val > val) {
		return BinarySearch(start, midpoint->prev, val);
	}


}


int main()
{
	LinkedListNode* linked = GenLinked();
	cout << "Printing Linked List: " << endl;
	PrintLinked(linked);

	//SearchLinked(linked, 0);
	//SearchLinked(linked, 1);
	//SearchLinked(linked, 9);
	//SearchLinked(linked, 10);

	cout << BinarySearch(linked, nullptr, "f")->val;


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