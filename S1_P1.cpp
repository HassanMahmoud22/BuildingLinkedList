#include <iostream>
#include "S1_P1.h"
using namespace std;

template <class type>
list<type>::list()		//default constructor to initiate the variables
{
	first = NULL;
	last = NULL;
	dummy->link = NULL;
	dummy->previous = NULL;
	length = 0;
	count = 0;
}

template <class type>
list<type>::list(type value, int initial_size)
{							//paramterized constructor to initiate list with certian values and size

	while (count < initial_size)
	{
		newNode = new Node; //create newNode
		newNode->info = value;		//gives it the input value
		newNode->link = NULL;		//it's link is null
		newNode->previous = NULL;		//previous also null
		if (first == NULL)		//if first = null means that it's empty list
		{
			first = newNode;		//make the node is the first one
			last = newNode;			//also be the last one because it's the only node exist
			first->link = last;		//  make first link = last
			first->previous = NULL;	//and it's previous is null
			last->link = dummy;		// make last link be the dummy node
			dummy->link = NULL;		//dummy link = NULL because it's the after last node
			dummy->previous = last;	//dummy previous is the last node
		}
		else  //else the list isn't empty
		{
			last->link = newNode;	//last link will be the new node
			newNode->previous = last;	//new node previous will be the last node
			last = newNode;			//then the new node will be the last node
			last->link = dummy;		//and connect it with the dummy node
			dummy->previous = last;		//and connect dummy node with it
		}
		count++;		//then increment the number of elements
	}
}

template <class type>
list<type>::~list()	//destructor destroy the array
{
	destroyList();
}

template <class type>
int list<type>::size() //size function prints the number of elements in the list
{
	return count;
}

template <class type>
list<type>::listIterator::listIterator() // default constructor for the iterator
{
	current = NULL;
}

template <class type>
list<type>::listIterator::listIterator(Node* node)		// parametrized constructor make current refer to node
{
	current = node;
}

template <class type>
void list<type>::listIterator::operator++(int)	// ++ overloading make current move to next node
{
	current = current->link;
}

template <class type>
void list<type>::listIterator::operator--(int)
{
	current = current->previous;
}

template <class type>
bool list<type>::listIterator::operator==(const listIterator& itr)
{
	return (current == itr.current);
}

template <class type>
type& list<type>::listIterator::operator*()
{
	return current->info;
}

template <class type>
void list<type>::destroyList()	//function to destroy list
{
	Node* temp;			//create temp pointer of type Node
	while (first != NULL)	//if first != null means the list isn't empty
	{
		temp = first; //make the temp refer to the first node
		first = first->link;	//and make first be the next element
		delete temp;  //then delete the temp pointer
	}
	last = NULL;	//then last = null
	count = 0;		//and make count = zero that means there is no elements
}

template <class type>
void list<type>::copyList(const list<type>& another_list)
{
	Node* newNode; //pointer to create a node
	Node* current; //pointer to go in the list
	if (first != NULL) //if the list is not empty make it empty
		destroyList();
	if (another_list.first == NULL) //if another list is empty
	{
		first = NULL;	//make first,last null and count equal zero
		last = NULL;
		count = 0;
	}
	else
	{
		current = another_list.first; //current points to the list to be copied
		count = another_list.count; // makes count equals the list count
		Node* dum = new Node;		//this is the dummy node
		dum->link = NULL;		//dummy link is null
		dum->info = NULL;	//dummy info is null
		Node* first = new Node; //create the node
		first->info = current->info; //copy the info
		first->link = dum; //set the link  of the node to the dummy
		last = first; //make last refer to the first node
		dum->previous = last;	//make node refer to the last
		current = current->link; //make current point to the next

		while (current->info != NULL)
		{
			newNode = new Node; //create a node
			newNode->info = current->info; //copy the info
			newNode->link = dum; //set the link of newNode to NULL
			newNode->previous = last;
			last->link = newNode; //attach newNode after last
			last = newNode; //make last point to the actual last
			//node
			current = current->link; //make current point to the next node
		}
	}
}

template <class type>
list<type>& list<type>::operator=(list<type> another_list)
{
	if (this != &another_list) //if the list isnt same then copy it
	{
		copyList(another_list);
	}
	return *this;

}

template <class type>
bool list<type>::isEmpty()
{
	return (first == NULL);	//return true if first is null
}

template <class type>
void list<type>::print()
{
	Node* temp;  //create temp pointer
	temp = first;
	if (temp == NULL)	//if the list is empty print that it's empty
	{
		cout << "There is No any Node" << endl;
	}
	else
	{			//else print it untill find node->link is null
		while (temp->link != NULL)
		{
			cout << temp->info << " ";
			temp = temp->link;
		}
	}

}

template<class type>
void list<type>::insert(type value, listIterator position)
{
	if (first == NULL)	//if list is empty
	{
		newNode = new Node;		//then creates node
		newNode->info = value;
		first = newNode;		//make it the last and first
		last = newNode;
		first->link = last;
		first->previous = NULL;
		last->link = dummy;		//connect it to dummy
		dummy->link = NULL;
		dummy->previous = last;
	}
	else if (position == first && first != NULL)	//if position is first and there are more nodes
	{
		Node* current = new Node;		//create current node
		current->info = value;		//current info will be the value
		current->previous = NULL;	//thenn replace it with the first element
		current->link = first;
		first->previous = current;
		first = current;
	}
	else if (position == last)		//if position is last then replace it with the previous last node
	{
		Node* node = last->previous;
		Node* current = new Node;
		current->info = value;
		current->previous = node;
		node->link = current;
		current->link = last;
		last->previous = current;
	}
	else if (position == dummy)
	{							//if position is dummy then replace the new node with the last one
		Node* current = new Node;
		current->info = value;
		current->previous = last;
		current->link = dummy;
		last->link = current;
		dummy->previous = current;
		last = current;
	}
	else
	{		//else the node will be put in between the position node and it's previous
		Node* w = position.current;
		Node* node = w->previous;
		Node* current = new Node;
		current->info = value;
		current->link = w;  w->previous = current;
		current->previous = node;  node->link = current;
	}
	count++;
}
int main()
{
	list<int> v(3, 4);	//test intializing list with specific value and specific size
	list<int>::listIterator p;	//test iterator class
	v.insert(4, v.begin());		//test insert function
	p = v.end();		//test end() function
	p--;			//test -- overloading
	v.erase(p);			//test erase function
	p = v.begin();		//test begin() function
	p++;			//test ++ overloading
	cout << "the value of iterator is: " << *p << endl;		//test * overloading
	cout << "the size of list is: " << v.size() << endl;  //test size() function
	cout << "the list is: ";
	v.print();			//test print() function

	return 0;
}


