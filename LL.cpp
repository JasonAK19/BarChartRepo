//
// Created by Jason on 4/23/2023.
//
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

//DO NOT ADD ANY CONSTANTS OR FUNCTIONS TO ANY CLASS

// Templated Node class
// Normal node except that each node can hold a pair <T,int>
// where the first value is templated and the second value is the frequency
// (or quantity) of the first
// For example, if T was a string then it would hold string,int
template <class T>
class Node {
public:
    Node( const T& data ); //Node Constructor - Assume each quan
    pair<T,int>& GetData(); //Node Data Getter
    void SetData( const pair<T,int>& ); //Node Data Setter
    Node<T>* GetNext(); //Node m_next getter
    void SetNext( Node<T>* next ); //Node m_next setter
private:
    pair <T,int> m_data; //Holds templated data
    Node<T>* m_next; //Pointer to next node
};

template <class T>
Node<T>::Node( const T& data ) {
    m_data = make_pair(data,1);
    m_next = nullptr;
}

template <class T>
pair<T,int>& Node<T>::GetData() {
    return m_data;
}

template <class T>
void Node<T>::SetData( const pair<T,int>& data ) {
    m_data = data;
}

template <class T>
Node<T>* Node<T>::GetNext() {
    return m_next;
}

template <class T>
void Node<T>::SetNext( Node<T>* next ) {
    m_next = next;
}

//Templated Linked List class
template <class T>
class LL {
public:
    // Name: LL() (Linked List) - Default Constructor
    // Desc: Used to build a new linked list
    // Preconditions: None
    // Postconditions: Creates a new linked list where m_head points to nullptr
    LL();
    // Name: ~LL() - Destructor
    // Desc: Used to destruct a LL
    // Preconditions: There is an existing LL with at least one node
    // Postconditions: A LL is deallocated (including dynamically allocated nodes)
    //                 to have no memory leaks!
    ~LL();
    // Name: LL (Copy Constructor)
    // Desc: Creates a copy of existing LL
    //       Requires a LL - REQUIRED to be implemented even if not used
    // Preconditions: Source LL exists
    // Postconditions: Copy of source LL
    LL(const LL&);
    // Name: operator= (Overloaded Assignment Operator)
    // Desc: Makes two LL of the same type have identical number of nodes and values
    // Preconditions: Requires two linked lists of the same templated type
    //                REQUIRED to be implemented even if not used
    // Postconditions: Two idenetical LL
    LL<T>& operator= (const LL&);
    // Name: Find
    // Desc: Iterates through LL and returns node if data found
    // Preconditions: LL Populated
    // Postconditions: Returns nullptr if not found OR Node pointer if found
    Node<T>* Find(const T& data);
    // Name: Insert
    // Desc: Either inserts a node to the linked list OR increments frequency of first
    //       Takes in data. If "first" (of pair) NOT in list, adds node
    //       If "first" (of pair) is already in list, increments quantity
    //       Inserts "first" in order with no duplicates
    // Preconditions: Requires a LL.
    // Postconditions: Node inserted in LL based on first value (or quantity incremented)
    void Insert(const T&);
    // Name: RemoveAt
    // Desc: Removes a node at a particular position based on data passed (matches first)
    // Preconditions: LL with at least one node.
    // Postconditions: Removes first node with passed value (in first)
    void RemoveAt(const T&);
    // Name: Display
    // Desc: Display all nodes in linked list
    // Preconditions: Outputs the LL
    // Postconditions: Displays the pair in each node of LL
    void Display();
    // Name: GetSize
    // Desc: Returns the size of the LL
    // Preconditions: Requires a LL
    // Postconditions: Returns m_size
    int GetSize();
    // Name: operator<< (Overloaded << operator)
    // Desc: Returns the ostream of the data in each node
    // Preconditions: Requires a LL
    // Postconditions: Returns an ostream with the data from each node on different line
    template <class U>
    friend ostream& operator<<(ostream& output, const LL<U>&);
    // Name: Overloaded [] operator
    // Desc: When passed an integer, returns the data at that location
    // Precondition: Existing LL
    // Postcondition: Returns pair from LL using []
    pair<T,int>& operator[] (int x);//Overloaded [] operator to pull data from LL
private:
    Node <T> *m_head; //Node pointer for the head
    int m_size; //Number of nodes in queue
};
//*****************************************************************
//Implement LL here


template <class T>
LL<T>::LL() {
    m_head = nullptr;
    m_size = 0;
}

template <class T>
LL<T>::~LL() {
    Node<T>* current = m_head;
    //iterates through linked list
    while ( current != nullptr ) {
        Node<T>* temp = current;
        current = current->GetNext();
        // deletes all nodes
        delete temp;
    }
    m_head = nullptr;
    m_size = 0;
}

template <class T>
LL<T>::LL( const LL<T>& source ) {
    m_head = nullptr;
    m_size = 0;
    Node<T>* current = source.m_head;
    while (current != nullptr) {
        for (int i = 0; i < current->GetData().second; i++) {
            //inserts the nodes from the original linked list into the new one
            Insert(current->GetData().first);
        }
        current = current->GetNext();
    }
}

template <class T>
LL<T>& LL<T>::operator=( const LL<T>& source ) {
    if ( this != &source ) {
        Node<T>* current = m_head;
        // deallocates all nodes
        while ( current != nullptr ) {
            Node<T>* temp = current;
            current = current->GetNext();
            delete temp;
        }
        // repopulates the nodes in LL
        m_head = nullptr;
        m_size = 0;
        current = source.m_head;
        while ( current != nullptr ) {
            Insert( current->GetData().first );
            current = current->GetNext();
        }
    }
    return *this;
}

template <class T>
Node<T>* LL<T>::Find( const T& data ) {
    Node<T>* current = m_head;
    while ( current != nullptr ) {
        if ( current->GetData().first == data ) {
            // Check if the current node's data matches the target data
            return current;
        }
        current = current->GetNext();
    }
    // Return nullptr if the target data is not found in the linked list
    return nullptr;
}

template <class T>
void LL<T>::Insert( const T& data ) {
    Node<T>* current = m_head;
    Node<T>* previous = nullptr;
    while ( current != nullptr and current->GetData().first < data ) {
        previous = current;
        current = current->GetNext();
    }
    if ( current == nullptr or current->GetData().first != data ) { // checks if the data is not already in the list
        Node<T>* newNode = new Node<T>(data);
        newNode->SetNext( current );
        if ( previous == nullptr ) {
            m_head = newNode;
        }
        else {
            previous->SetNext( newNode );
        }
        m_size++;
    }
    else {
        //increments the int the pair if the data is already in the linked list
        current->GetData().second++;
    }
}


template <class T>
void LL<T>::RemoveAt(const T& data) {
    Node<T> *current = m_head;
    Node<T> *previous = nullptr;

    // Loop until the end of the linked list or until a node with matching data is found
    while (current != nullptr and current->GetData().first != data) {
        previous = current;
        current = current->GetNext();
    }

    if (current != nullptr) {
        if (previous == nullptr) {
            m_head = current->GetNext(); // Update the head to the next node
        } else {
            previous->SetNext(current->GetNext()); // links the previous node to the next node
        }
        delete current;
    }
}

template <class T>
void LL<T>::Display() {
    Node<T>* current = m_head;
    while (current != nullptr) {
        pair<T, int> data = current->GetData();
        cout << "[" << data.first << "," << data.second << "] " << endl;
        current = current->GetNext();
    }
    if(current == nullptr){
        cout << "END" << endl;
    }
}

template<class T>
int LL<T>::GetSize() {
    return m_size;
}

template <class U>
ostream& operator<<(ostream& output, const LL<U>& list) {
    Node<U>* current = list.m_head;
    while (current != nullptr) {
        output << "(" << current->GetData().first << ", " << current->GetData().second << ")" << endl;
        current = current->GetNext();
    }
    if(current == nullptr){
        cout << "END" << endl; // Output "END" to indicate the end of the list
    }
    return output;
}

template <class T>
pair<T,int>& LL<T>::operator[] (int x) {
    static pair<T, int> defaultPair; //a static default pair that will get returned if index is less than 0

    if (x < 0) {
        return defaultPair;
    }


    Node<T>* current = m_head;
    int count = 0;
    while (current != nullptr) {
        if (count == x) {
            return current->GetData(); // Return the data of the current node as a reference
        }
        count++;
        current = current->GetNext();
    }

    return defaultPair; // Return the default pair if the index is out of range
}
