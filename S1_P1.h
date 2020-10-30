#include <iostream>
#ifndef Header_H
#define Header_H
using namespace std;
template<class type>
class list
{
private:
	int count;
	struct Node
	{
		type info;
		Node* link;
		Node* previous;
	};
	Node* dummy = new Node;
	Node* first;
	Node* last;
	Node* newNode;
	int length;
public:
	list();
	~list();
	list(type value, int initial_size);
	int size();
	void print();

	class listIterator
	{
	private:
		friend class list;
		Node* current;
	public:


		listIterator();
		listIterator(Node* u);
		void operator ++ (int);
		void operator -- (int);
		type& operator * ();
		bool operator == (const listIterator& itr);
	};
	void destroyList();
	void copyList(const list<type>& otherList);
	void insert(type value, listIterator position);
	list<type>& operator = (list<type> another_list);

	bool isEmpty();

	listIterator erase(listIterator position)
	{
		if (first == NULL)
		{		//if the list is empty then tell user that
			cout << "The list is empty" << endl;
		}
		else if (position == first && count == 1)	//if position is first and there is only element in the list
		{
			Node* current = position.current;
			Node* w = current->link;   //delete it and make list empty
			w->previous = NULL;
			delete current;
			position++;
			count = 0;
			first = NULL;
			last = NULL;
			return position;
		}
		else if (position == first && count > 1)
		{				//if position is first and there are more than one element in the list
			Node* current = position.current;
			Node* w = current->link;
			w->previous = NULL;
			first = w;
			delete current;
			position++;
			count--;
			return position;
		}
		else if (position == last && count > 1)
		{					//if position is last and there are many elements then remove element before last 
			Node* current = position.current;
			Node* u = current->previous;
			Node* w = u->previous;
			w->link = current;
			current->previous = w;
			delete u;
			position++;
			count--;
			return position;
		}
		//if position = dummy then delete the last element
		else if (position == dummy)
		{
			Node* current = position.current;
			Node* u = current->previous;
			Node* w = u->previous;
			w->link = current;
			current->previous = w;
			last = w;
			delete u;
			position++;
			count--;
			return position;
		}
		else
		{		//else delete the node in the position
			Node* current = position.current;
			Node* u = current->previous;
			u->link = current->link;

			delete current;
			position++;
			count--;
			return position;
		}

	}
	listIterator begin()
	{
		listIterator temp(first);
		return temp;
	}
	listIterator end()
	{
		return listIterator(last->link);

	}

};
#endif
