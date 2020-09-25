// Algo_Assignment_Q8.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include "List.h"
using namespace std;


bool CheckExisting(vector<string> strVertices, string name) {

	for (int i = 0; i < strVertices.size(); i++)
		if (strVertices[i] == name)
			return true;

	return false;

}

void ReadCSV(string name, vector<string>& strVertices) {

	ifstream read;
	string Name1, Name2;
	int counter = 0;

	bool Name1Exist = false, Name2Exist = false;

	read.open(name);

	if (read) {
		getline(read, Name1, ',');
		strVertices.insert(strVertices.begin() + counter, Name1);
		counter++;
		getline(read, Name2, '\n');
		strVertices.insert(strVertices.begin() + counter, Name2);

		while (read) {

			getline(read, Name1, ',');

			if (Name1 == "")
				break;

			Name1Exist = CheckExisting(strVertices, Name1);

			if (!Name1Exist) {
				strVertices.insert(strVertices.begin() + counter, Name1);
				counter++;
			}

			getline(read, Name2, '\n');

			Name2Exist = CheckExisting(strVertices, Name2);

			if (!Name2Exist) {
				strVertices.insert(strVertices.begin() + counter, Name2);
				counter++;
			}
			Name1 = Name2 = "";
		}

		read.close();
	}
	else {
		cout << "Error reading file: " <<name<< endl;
	}

}

int FindPerson(string name,List<string> Adj_list) {
	Node<string>* temp = Adj_list.Head;
	int counter = 0;

	for (int i = 0; temp != NULL; i++) {
		if (name == temp->data)
			return counter;

		counter++;
		temp = temp->down;
	}

	return -1;

}

void MakeEdges(string person, string freind, List<string>& Adj_list) {

	int index = FindPerson(person, Adj_list);

	if (index != -1) {

		if (Adj_list[index]->next == NULL) {
			Adj_list[index]->next = new Node<string>(freind);
		}
		else {
			Node<string>* temp = Adj_list[index]->next;

			while (temp->next != NULL)
				temp = temp->next;

			temp->next = new Node<string>(freind);
		}
	}

	int index1 = FindPerson(freind, Adj_list);

	if (index1 != -1) {

		if (Adj_list[index1]->next == NULL) {
			Adj_list[index1]->next = new Node<string>(person);
		}
		else {
			Node<string>* temp = Adj_list[index1]->next;

			while (temp->next != NULL)
				temp = temp->next;

			temp->next = new Node<string>(person);
		}
	}
}

void InsertFreinds(List<string>& Adj_List) {

	ifstream read;
	string person,freind;
	read.open("friends.csv");

	if (read) {
		while (read) {
			getline(read, person, ',');
			getline(read, freind, '\n');
			MakeEdges(person, freind, Adj_List);
		}
	}
	else {
		cout << "Error reading file freinds.csv." << endl;
	}
}

int MostNumberOfFreinds(List<string> Adj_list,string& mostfrnds) {
	int counter = 0,max= -1;

	Node<string>* Nodes = Adj_list.Head;
	Node<string>* freinds = Nodes->next;

	while (Nodes != NULL) {
		while (freinds != NULL) {
			counter++;
			freinds = freinds->next;
		}

		if (counter > max) {
			max = counter;
			mostfrnds = Nodes->data;
		}
		counter = 0;

		Nodes = Nodes->down;
		if (Nodes != NULL)
			freinds = Nodes->next;
	}

	return max;
}

int LeastNumberOfFreinds(List<string> Adj_list, string& Leastfrnds) {
	int counter = 0, min = 99999999;

	Node<string>* Nodes = Adj_list.Head;
	Node<string>* freinds = Nodes->next;

	while (Nodes != NULL) {
		while (freinds != NULL) {
			counter++;
			freinds = freinds->next;
		}

		if (counter < min) {
			min = counter;
			Leastfrnds = Nodes->data;
		}
		counter = 0;

		Nodes = Nodes->down;
		if (Nodes != NULL)
			freinds = Nodes->next;
	}

	return min;
}

string SpecificNumberOfFreinds(List<string> Adj_list,int Number) {
	int counter = 0;

	Node<string>* Nodes = Adj_list.Head;
	Node<string>* freinds = Nodes->next;

	while (Nodes != NULL) {
		while (freinds != NULL) {
			counter++;
			freinds = freinds->next;
		}

		if (counter == Number) {
			return  Nodes->data;
		}
		counter = 0;

		Nodes = Nodes->down;
		if (Nodes != NULL)
			freinds = Nodes->next;
	}

	return "";
}

void MutualFreinds(string name1, string name2, List<string> Adj_List) {

	int index1 = FindPerson(name1,Adj_List);
	int index2 = FindPerson(name2,Adj_List);
	bool AreFreinds = false;
	vector<string> Freinds;
	vector<string> MutualFreinds;

	if (index1 >= 0 && index2 >= 0) {
		
		Node<string>* temp = Adj_List[index1]->next;

		for (int i = 0; temp != NULL; i++) {
			if ( temp->data == name2)
				AreFreinds = true;

			Freinds.push_back(temp->data);
			temp = temp->next;
		}
		
		if ( AreFreinds == false){
			cout<<"The 2 given names are not freinds. :( "<<endl;
			return;
		}

		temp = Adj_List[index2]->next;

		for (int i = 0; temp != NULL; i++) {
			for (int j = 0; j < Freinds.size(); j++) {
				if (Freinds[j] == temp->data)
					MutualFreinds.push_back(temp->data);
			}
			temp = temp->next;
		}

		cout << "Mutual Freinds of: " << name1 << " , " << name2 << " are: " << endl<<endl;
		
		for (int i = 0; i < MutualFreinds.size(); i++)
			cout << MutualFreinds[i] << " ";

	}
	else {
		cout << "Person not found." << endl;
	}

}

void BFS(List<string> Adj_List) {

	queue<string> Queue;
	vector<string> Visited,InQueue;
	int index = 0;

	cout <<endl<< "Now implementing BFS. Please enter the Node you want to start from: " << endl;
	cin >> index;

	Queue.push(Adj_List[index]->data);
	InQueue.push_back(Queue.front());

	Node<string>* temp = Adj_List[index]->next;
	fstream write;
	
	write.open("BFS.txt",ios::out);
	int iteration = 1;

	if (write) {

		cout << "Writing into file: " << endl;
		write << "Iteration: ";
		write << iteration;
		write <<" "<< InQueue[0];
		write << '\n';

		bool visitedCheck = false,InQueueCheck = false;

		while (!Queue.empty()) {
			iteration++;
			Visited.push_back(Queue.front());
			Queue.pop();
			InQueue.erase(InQueue.begin());

			while (temp != NULL) {
				

				for (int i = 0; i < Visited.size(); i++) {
					if (temp->data == Visited[i]) {
						//cout << temp->data << " is repeating: " << endl;
						visitedCheck = true;
						break;
					}
				}
			
				for (int i = 0; i < InQueue.size(); i++) {
					if (temp->data == InQueue[i]) {
						//cout << temp->data << " is Already in Queue: " << endl;
						InQueueCheck = true;
						break;
					}
				}

				if (visitedCheck == false && InQueueCheck == false) {
					Queue.push(temp->data);
					InQueue.push_back(temp->data);
				}

				temp = temp->next;
				visitedCheck = false;
				InQueueCheck = false;
			}

			write << "Iteration: ";
			write << iteration;

			for (int i = 0; i < InQueue.size(); i++)
				write <<" "<< InQueue[i] << " ";

			write << '\n';

			if (!Queue.empty())
				index = FindPerson(Queue.front(), Adj_List);
			
			temp = Adj_List[index]->next;

		}
	}
	else {
		cout << "File could not be created. :( " << endl;
	}

	cout <<endl<< "BFS TREE: " << endl;
	write << '\n' <<"BFS TREE: " << '\n';
	for (int i = 0; i < Visited.size(); i++){
		write << Visited[i] << " ";
		cout << Visited[i] << " "; 
	}

	cout << endl <<endl;
}

void DFS(List<string> Adj_List) {

	stack<string> Stack;
	vector<string> Visited;
	vector<string> InStack;


	int index = 0;

	cout << endl<< "Now implementing DFS. Please enter the Node you want to start from: " << endl;
	cin >> index;

	Stack.push(Adj_List[index]->data);
	Visited.push_back(Stack.top());
	InStack.push_back(Stack.top());

	Node<string>* temp = Adj_List[index]->next;

	int personIndex = 0,counter=1;
	bool visited = false;
	while (!Stack.empty()) {

		while (temp != NULL) {

			for (int i = 0; i < Visited.size(); i++)
				if (Visited[i] == temp->data) {
					visited = true;
					break;
				}

			if (visited == false) {
			}

			Stack.push(temp->data);
			InStack.push_back(temp->data);
			Visited.push_back(temp->data);

			temp = temp->next;
		}

		personIndex = FindPerson(InStack[counter], Adj_List);
		temp = Adj_List[personIndex]->next;
		counter++;

		
	}
}

int main()
{
	vector<string> UniqueVertices;
	
	ReadCSV("friends.csv", UniqueVertices);

	List<string> Adj_list;
	
	for (int i = 0; i < UniqueVertices.size(); i++)
		Adj_list.InsertNode(UniqueVertices[i]);

	InsertFreinds(Adj_list);

	cout << "Adjacency List: \n" << endl;
	Adj_list.Display();

	string MostFrnds;
	int Snumber = 0;
	
	cout <<endl<< "The Most number of freinds are: " << MostNumberOfFreinds(Adj_list,MostFrnds) <<" of: "<<MostFrnds<< endl;
	cout <<endl<< "The Least number of freinds are: " << LeastNumberOfFreinds(Adj_list, MostFrnds) << " of: " << MostFrnds << endl;

	cout << endl<< "Please enter specific number of freinds to be found: " << endl;
	cin >> Snumber;

	cout << "Specific number of freinds : " <<Snumber<<" are of: "<<SpecificNumberOfFreinds(Adj_list, Snumber)<< endl;

	string Mn1, Mn2;
	cout << "Enter peopele you want to check mutual freinds of: " << endl;
	cin >> Mn1;
	cin.ignore();
	cout << "And: " << endl;
	cin >> Mn2;
	MutualFreinds(Mn1,Mn2, Adj_list);

	BFS(Adj_list);
	DFS(Adj_list);

}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
