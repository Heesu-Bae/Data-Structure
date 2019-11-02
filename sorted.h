#pragma once
#include <string>
// File ItemType.h must be provided by the user of this class. 
//  ItemType.h must contain the following definitions: 
//  MAX_ITEMS:     the maximum number of items on the list 
//  ItemType:      the definition of the objects on the list 
//  RelationType:  {LESS, GREATER, EQUAL}
//  Member function ComparedTo(ItemType item) which returns 
//       LESS, if self "comes before" item 
//       GREATER, if self "comes after" item 
//       EQUAL, if self and item are the same 

#define MAX_ITEMS 10000

template <class ItemType>
class SortedType 
{
public:
  SortedType();
  bool IsFull() const;
  // Function:  Determines whether list is full.
  // Pre:  List has been initialized.
  // Post: Function value = (list is full)

  int LengthIs() const;
  // Function: Determines the number of elements in list.
  // Pre:  List has been initialized.
  // Post: Function value = number of elements in list

  void RetrieveItem(string& item, bool& found);
  // Function: Retrieves list element whose key matches item's key (if
  //           present).
  // Pre:  List has been initialized.
  //       Key member of item is initialized.
  // Post: If there is an element someItem whose key matches
  //       item's key, then found = true and item is a copy of
  //       someItem; otherwise found = false and item is unchanged.
  //       List is unchanged.

  void InsertItem(ItemType item);
  // Function: Adds item to list.
  // Pre:  List has been initialized.
  //       List is not full.
  //       item is not in list.
  //       List is sorted.
  // Post: item is in list.
  //       List is sorted

  void DeleteItem(ItemType item);
  // Function: Deletes the element whose key matches item's key.
  // Pre:  List has been initialized.
  //       Key member of item is initialized.
  //       One and only one element in list has a key matching item's key.
  // Post: No element in list has a key matching item's key.
  //       List is sorted.

  void ResetList();
  // Function: Initializes current position for an iteration through the list.
  // Pre:  List has been initialized.
  // Post: Current position is prior to list.

  void GetNextItem(ItemType& item);
  // Function: Gets the next element in list.
  // Pre:  List has been initialized and has not been changed since last call.
  //       Current position is defined.
  //       Element at current position is not last in list.
  //	     
  // Post: Current position is updated to next position.
  //       item is a copy of element at current position.

  int getLen() const { return length; }

  void Print() const;

private:
  int length;
  ItemType info[MAX_ITEMS];
  int currentPos;
};

template <class ItemType>
SortedType<ItemType>::SortedType()
{
	length = 0;
}

template <class ItemType>
bool SortedType<ItemType>::IsFull() const
{
	return (length == MAX_ITEMS);
}

template <class ItemType>
int SortedType<ItemType>::LengthIs() const
{
	return length;
}

template <class ItemType>
void SortedType<ItemType>::RetrieveItem(string& item, bool& found)
{
	int midPoint;
	int first = 0;
	int last = length - 1;

	bool moreToSearch = first <= last;
	found = false;

	while (moreToSearch && !found)
	{
		midPoint = (first + last) / 2;

		if (item.compare(info[midPoint].getID()) < 0)
		{
			last = midPoint - 1;
			moreToSearch = first <= last;
		}
		else if (item.compare(info[midPoint].getID()) > 0)
		{
			first = midPoint + 1;
			moreToSearch = first <= last;
		}
		else
		{
			found = true;
			item = info[midPoint].getID();
		}
	}
}

template <class ItemType>
void SortedType<ItemType>::DeleteItem(ItemType item)
{
	/*
	int location = 0;

	while (item.ComparedTo(info[location]) != EQUAL)
		location++;
	for (int index = location + 1; index < length; index++)
		info[index - 1] = info[index];
	length--;
	*/
}

template <class ItemType>
void SortedType<ItemType>::InsertItem(ItemType item)
{
	bool moreToSearch;
	int location = 0;

	moreToSearch = (location < length);
	while (moreToSearch)
	{
		if (item < info[location])
			moreToSearch = false;
		else if (item > info[location])
		{
			location++;
			moreToSearch = (location < length);
		}
	}

	for (int index = length; index > location; index--)
		info[index] = info[index - 1];

	info[location] = item;
	length++;
}

template <class ItemType>
void SortedType<ItemType>::ResetList()
// Post: currentPos has been initialized.
{
	currentPos = -1;
}

template <class ItemType>
void SortedType<ItemType>::GetNextItem(ItemType& item)
// Post: item is current item.
//       Current position has been updated.
{
	currentPos++;
	item = info[currentPos];
}

template <class ItemType>
void SortedType<ItemType>::Print() const
{
	cout << setw(20) << setfill(' ') << "ID" << setw(20) << setfill(' ') << "PW" << setw(20) << setfill(' ') <<  "Stamp Num" << endl;
	for (int i = 0; i < length; i++)
	{
		info[i].Print();
	}
	cout << endl;
}