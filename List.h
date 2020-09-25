#pragma once
#include <iostream>
using namespace std;
template<class T>
class Node {
public:
	T data;
	Node* next, * down;

	Node() : data(0), next(NULL), down(NULL) {}
	Node(T data) : data(data), next(NULL), down(NULL) {}
};

template<class T>
class List {

public:

	Node<T>* Head, * last;

	List() {
		Head = NULL;
		last = NULL;
	}

	List(T data) {
		Node<T>* temp = new Node<T>(data);

		Head = temp;
		last = temp;

	}

	void InsertNode(T data) {

		Node<T>* temp = new Node<T>(data);

		if (Head == NULL) {
			Head = temp;
			last = Head;
		}
		else {

			last->down = temp;
			temp->down = NULL;
			last = temp;

		}
	}

	bool isEmpty() {
		if (Head == NULL) {
			return true;
		}

		return false;

	}

	Node<T>* operator [](int index) {
		Node<T>* temp = Head;

		for (int i = 0; i < index; i++)
			temp = temp->down;

		return temp;
	}

	void Display() {

		if (Head == NULL) {
			cout << "List is empty." << endl;
		}
		else {
			Node<T>* tempList = Head;
			Node<T>* tempFreinds = tempList->next;

			while (tempList != NULL) {

				cout << tempList->data << " --> ";

				while (tempFreinds != NULL) {
					cout << tempFreinds->data;
					if (tempFreinds->next != NULL)
						cout << " -> ";
					tempFreinds = tempFreinds->next;
				}

				cout << endl;
				tempList = tempList->down;
				if (tempList != NULL)
					tempFreinds = tempList->next;

			}

			cout << endl;
		}
	}

	void destroyEdges() {

		Node<T>* tempNode = Head;
		Node<T>* previous = NULL;

		while (tempNode != NULL) {

			Node<T>* tempEdges = tempNode->next;

			while (tempEdges != NULL) {
				previous = tempEdges;
				tempEdges = tempEdges->next;
				delete(previous);
			}

			tempNode = tempNode->down;
		}

	}

	void destroyVertices(Node<T> * temp) {

		if (temp != NULL) {
			destroyVertices(temp->down);
			delete(temp);
		}

		Head = NULL;
	}
};

