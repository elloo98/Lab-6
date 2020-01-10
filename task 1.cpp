#include <iostream>
using namespace std;
class node {	
private:
	node* prev;
	node* next;
	int data;
public:
	void setPrev(node* nprev) {
		prev = nprev;
	}
	node* getPrev() {
		return prev;
	}
	void setNext(node* newnext) {
		if (newnext!=nullptr)
			next = newnext;
	}
	node* getNext() {
		return next;
	}
	void setData(int ndata) {
		data = ndata;
	}
	int getData() {
		return data;
	}
	node(node* nprev, node* nnext, int ndata) {
		prev = nprev;
		next = nnext;
		data = ndata;

	}
	node() {
		prev = nullptr;
		next = nullptr;
		data = 0;

	}
};

class DoublyLinkedList {
public:
	node* head = new node;
	node* tail = new node;



	bool add(node* data, int pos) {
		node* temp;
		node* next;
		node* prev;
		int count = 0;
		temp = new node;
		next = new node;
		prev = new node;
		prev = head;
		next = head;
		next = next->getNext();
		temp->setData(data->getData());
		if (head->getNext() == nullptr && tail->getPrev() == nullptr) {
			head->setNext(temp);
			tail->setPrev(temp);
			temp->setNext(tail);
			temp->setPrev(head);
			return true;
		}
		else {
			while (count < pos) {
				if (next != tail) {
					next = next->getNext();
					prev = prev->getNext();
					count++;
				}
				else {
					return false;
				}
			}
			temp->setNext(next);
			temp->setPrev(prev);
			next->setPrev(temp);
			prev->setNext(temp);
			return true;
		}
		return false;
	}


	bool remove(int pos) {
		node* temp = new node;
		node* next = new node;
		node* prev = new node;
		int count = 0;
		prev = head;
		temp = prev->getNext();
		next = temp->getNext();
		while (count < pos && next->getNext()!=nullptr) {
			prev = prev->getNext();
			temp = temp->getNext();
			next = next->getNext();
			count++;
		}
		prev->setNext(next);
		next->setPrev(prev);
		delete temp;
		return true;
	}


	bool replace(node* data, int pos) {
		node* temp = new node;
		temp=head->getNext();
		int count = 0;
		while (count < pos) {
			temp = temp->getNext();
			count++;
			if (temp == tail)
				return false;
		}
		temp->setData(data->getData());
		return true;
	}


	int search(node* data) {
		node* temp = head->getNext();
		int count=0;
		while (temp->getData() != data->getData()) {
			temp = temp->getNext();
			count++;
		}
		return count;
	}


	node* nodeAt(int pos) {
		node* temp = head->getNext();
		int count = 0;
		while (count != pos) {
			temp = temp->getNext();
			count++;
		}
		return temp;
	}


	void dispForward() {
		node* current = head;
		current = current->getNext();
		while (current != tail) { 
			cout << current->getData() << " "; 
			current = current->getNext(); }
		cout << endl;
		
	}


	void dispBackward() {
		node* temp = tail->getPrev();
		while (temp != head) {
			cout << temp->getData() << " ";
			temp = temp->getPrev();
		}
		cout << endl;
	}


	int size() {
		int count = 0;
		node* current = head;
		current = current->getNext();
		while (current != tail) {
			count++;
			current = current->getNext();
		}
		return count;
	}
};

/*int main() {
	bool test=true;
	DoublyLinkedList list;
	node* test1 = new node;
	node* test2 = new node;
	node* test3 = new node;
	node* test4 = new node;
	test1->setData(5);
	test2->setData(1231);
	test3->setData(71);
	cout << "Adding 5 to beginning of list and displaying\n";
	list.add(test1, 0);
	list.dispForward();
	cout << "Adding 1231 to end of list and displaying\n";
	list.add(test2, 1);
	list.dispForward();
	cout << "Adding 71 to start of list and displaying list backwards, so 71 should be last\n";
	list.add(test3, 0);
	list.dispBackward();
	cout << "Removing 5\n";
	list.remove(1);
	list.dispForward();
	cout << "Replace 71 with 5\n";
	list.replace(test1, 0);
	list.dispForward();
	cout << "Adding three entries and printing size, should be 5\n";
	list.add(test1, 2);
	list.add(test1, 1);
	list.add(test3, 3);
	list.dispForward();
	cout << list.size() << "\nTesting where 71 is, should be 3\n" << list.search(test3) << "\nFinally we find out what data is at pos 1, should be 5\n";
	test4 = list.nodeAt(1);
	cout << test4->getData() << "\n";
	system("pause");
	return 0;

}*/