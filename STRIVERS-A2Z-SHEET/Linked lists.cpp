#include<iostream>
#include <bits/stdc++.h>
using namespace std;

//STARTING LINKED LISTS REVISION
//Singly Linked List
//Creating the node 
class Node{
    public:
    int data;
    Node* next;

    //Constructor
    Node(int data){
        this -> data = data;
        this -> next = nullptr;
    }
    //Constructor 2 - Any of these teo formats can be used to create the node object
    Node(int data, Node* next){
        this -> data = data;
        this -> next = next;
    }

};

////Converting an array to linked list 
Node* convertArr2LL(vector<int> arr){
    int length = arr.size();
    Node* head = new Node(arr[0]);
    Node* prev = head;

    for(int i = 1; i<length; i++){
        Node* temp = new Node(arr[i]);
        prev -> next = temp;
        prev = temp;
    }

    return head;
}

////printing an ll
void printLL(Node* &head){
    Node* temp = head;

    while(temp != nullptr){
        cout << temp -> data << " ";
        temp = temp -> next;
    }

    cout << endl;
}

////Searching in a ll
bool searchInLL(int data, Node* &head){
    Node* temp = head;

    while(temp != nullptr){
        if(temp -> data == data) return true;

        temp = temp -> next;
    }

    return false;
}

////length of ll
int lengthOfLL(Node* &head){
    if(head == nullptr) return 0;
    Node* temp = head;
    int count = 0;

    while(temp != nullptr){
        count++;
        temp = temp -> next;
    }

    return count;
}

////inserting element at head
Node* insertAtHead(int data, Node* head){
    Node* newNode = new Node(data);

    newNode -> next = head;
    head = newNode;

    return head;
}
////insert at last/ end

Node* inserAtEnd(int data, Node* head){
    
    Node* newNode = new Node(data);
    if(head == NULL){
        head = newNode;
        return head;
    }

    Node* temp = head;
    while(temp-> next != NULL){
        temp = temp -> next;
    }

    temp -> next = newNode;
    return head;
}


////Inserting element at a given position
Node* insertAtPos(int data, int pos, Node* &head){
    Node* newNode = new Node(data);
    if(head == nullptr){
        head = newNode;
        return head;
    }

    Node* temp = head;

    int length = lengthOfLL(head);
    if(pos > length){
        head = inserAtEnd(data, head);
        return head;
    }

    for(int i = 0; i<pos-2; i++){
        temp = temp -> next;
    }

    newNode -> next = temp -> next;
    temp -> next = newNode;

    return head;
}




////DELETING ELEMENTS/NODES FROM LL
////Deleting from the head position
Node* deleteFromHead(Node* &head){
    if(head == NULL||head) return head;
    if(head -> next == NULL){
        delete head;
        return NULL;
    }

    Node* temp = head;
    head = temp -> next;
    delete temp;
    return head;
}

////Deleting from the last position
Node* deleteFromEnd(Node* &head){
    if(head == NULL) return head;
    if(head -> next == NULL){
        delete head;
        return NULL;
    }

    Node* temp = head;
    while(temp -> next-> next != NULL){
        temp = temp -> next;
    }

    delete temp -> next;
    temp -> next = nullptr;

    return head;
}

////Deleting element at a given position
Node* deleteAtPos(int pos, Node* &head){
    if(head == NULL|| pos <= 0) return head;
    if(head -> next == NULL && pos == 1){
        delete head;
        return NULL;
    }
    
    Node* temp = head;
    Node* prev = head;
    
    int length = lengthOfLL(head);
    if(pos > length) return head;

    if(pos == 1){
        head = deleteFromHead(head);
        return head;
    } 
        
    for(int i = 0; i<pos-1; i++){
        prev = temp;
        temp = temp -> next;
    }

    prev -> next = temp -> next;
    delete temp;
    return head;
}

////Deleting a given value from the ll
Node* deleteFromLL(int val, Node* &head){
    if(head == NULL) return head;

    Node* temp = head;
    Node* prev = head;
    while(temp != NULL){
        if(temp -> data == val){
            if(temp == head){
                head = deleteFromHead(head);
                return head;
            }

            prev -> next = temp -> next;
            delete temp;
            return head;
        }

        prev = temp;
        temp = temp -> next;
    }

    return head;
}

int main(){
    //Linked list node object creationi and accessing it through a pointer
    Node* node1 = new Node(10);
    cout << endl << node1 -> data << endl;
    
    // creating ll from array
    vector<int> sample = {1,2,3,4,5,6};
    Node* headLL1 = convertArr2LL(sample);
    printLL(headLL1);
    int length = lengthOfLL(headLL1);
    cout << "length of given ll : " << length << endl;
    bool ans = searchInLL(6, headLL1);
    cout << "6 in ll : " << ans << endl;

    headLL1 = insertAtHead(20,headLL1);
    headLL1 = inserAtEnd(23, headLL1);
    headLL1 = insertAtPos(21,2, headLL1);

    printLL(headLL1);

    headLL1 = deleteAtPos(9, headLL1);
    headLL1 = deleteFromEnd(headLL1);
    headLL1 = deleteFromHead(headLL1);
    headLL1 = deleteFromLL(3,headLL1);

    printLL(headLL1);

    return 0;
}