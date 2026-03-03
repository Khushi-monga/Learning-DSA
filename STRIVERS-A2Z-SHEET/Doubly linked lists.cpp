#include<iostream>
#include <bits/stdc++.h>
using namespace std;

//Creating Node for doubly linked lists
class Node{
    public:

    int data;
    Node* next;
    Node* prev;

    Node(int data){
        this -> data = data;
        next = nullptr;
        prev = nullptr;
    }

    Node(int data, Node* next, Node* prev){
        this -> data = data;
        this -> next = next;
        this -> prev = prev;
    }
};

//Creating a linked list from an array
Node* convertArr2Dll(vector<int> &arr){
    Node* head = new Node(arr[0]);
    Node* before = nullptr;
    Node* temp = head;
    int length = arr.size();

    for(int i = 1; i<length; i++){
        temp -> next = new Node(arr[i]);
        temp -> prev = before;
        before = temp;
        temp = temp -> next;
    }

    return head;
}

void printDll(Node* &head){
    Node* temp = head;

    while(temp != NULL){
        cout << temp -> data << " ";
        temp = temp -> next;
    }
    cout << endl;
}

int lengthOfDll(Node* &head){
    int cnt = 0;
    Node* temp = head;

    while(temp != NULL){
        cnt++;
        temp = temp -> next;
    }

    return cnt;
}

Node* deleteHead(Node* &head){
    if(head == NULL || head -> next == NULL) return NULL;

    Node* temp = head;
    head = temp -> next;
    head -> prev = nullptr;
    delete temp;

    return head;   
}

Node* deleteTail(Node* &head){
    if(head == NULL|| head-> next == NULL) return NULL;
    if(head -> next == NULL){
        delete head;
        return NULL;
    }

    Node* before = nullptr;
    Node* temp = head;
    while(temp-> next != NULL){
        before = temp;
        temp = temp -> next;
    }

    before -> next = temp -> next;
    temp -> prev = NULL;
    delete temp;
    
    return head;
}

//contraint : 1<=pos<=n
Node* deleteAtPos(int pos, Node* &head){
    if(pos <= 0) return head;
    Node* temp = head;
    int count = 1;

    while(temp != NULL){
        count++;
        temp = temp -> next;

        if(count == pos) break;
    }

    Node* before = temp -> prev;
    Node* after = temp -> next;
    //if there's a single element
    if(before == NULL && after == NULL){
        delete temp;
        return NULL;
    }
    //if the pos is 1, i.e., head
    else if(before == NULL){
        return deleteHead(head);
    }
    //if the pos is n, i.e., tail
    else if(after == NULL){
        return deleteTail(head);
    }
    else{
        before -> next = temp -> next;
        after -> prev = temp -> prev;
        temp -> next = NULL;
        temp -> prev = NULL;
        delete temp;
    }

    return head;
}


Node* deleteVal(int val, Node* &head){
    if(head == NULL) return head;

    Node* temp = head;
    while(temp != NULL){
        if(temp -> data == val) break;
        temp = temp -> next;
    }

    Node* before = temp -> prev;
    Node* after = temp -> next;

    if(after == NULL){
        return deleteTail(head);
    }

    else{
        before -> next = temp -> next ;
        after -> prev = temp -> prev;
        temp -> next = nullptr;
        temp -> prev = nullptr;
        delete temp; 
    }

    return head;
}


//deleting a given node only 
//contraint : given node != head
void deleteNode(Node* temp){
    Node* before = temp -> prev;
    Node* after = temp -> next;

    if(after == NULL){
        before -> next = nullptr;
        temp -> prev = nullptr;
        delete temp;
    }

    before -> next = after;
    after -> prev = before;
    temp -> next = temp -> prev = nullptr;
    delete temp;
}

//INSERTION 
Node* insertAtHead(int val, Node* &head){
    Node* newNode = new Node(val);

    if(head == NULL) return newNode;

    newNode -> next = head;
    head -> prev = newNode;
    head = newNode;
    return head;
}

Node* insertLast(int val, Node* &head){
    Node* newNode = new Node(val);

    if(head == NULL) return newNode;
    Node* temp = head;

    while(temp -> next != NULL){
        temp = temp -> next;
    }

    temp -> next = newNode;
    newNode -> prev = temp;
    return head;
}

//constraint 0<pos<n+1
Node* insertAtPos(int val, int pos, Node* &head){
    Node* newNode = new Node(val);

    if(head == NULL) return newNode;
    
    Node* temp = head;
    int count = 1;

    while(temp -> next != NULL){
        if(count == pos) break;
        temp = temp -> next;
        count++;
    }

    Node* before = temp -> prev;

    if(before == NULL){
        return insertAtHead(val, head);
    }

    before -> next = newNode;
    temp -> prev = newNode;
    newNode -> prev = before;
    newNode -> next = temp;
    return head;

}

//similarly insert at node

//Reverse a dll
Node* reverseDLL(Node* &head){
    if(head == NULL || head -> next == NULL) return head;

    Node* temp = head;
    Node* before = NULL;

    while(temp != NULL){
        before = temp -> prev;
        temp -> prev = temp -> next;
        temp -> next = before;
        temp = temp -> prev;
    }

    head = before -> prev; 
    return head;
}



int main(){
    cout << endl;
    vector<int> sample = {1,2,3,4,5,6};
    Node* Head = convertArr2Dll(sample);
    printDll(Head);

    Head = deleteHead(Head);
    printDll(Head);

    Head = deleteTail(Head);
    printDll(Head);

    Head = deleteAtPos(2,Head);
    printDll(Head);

    Head = insertAtHead(1, Head);
    printDll(Head);

    Head = insertLast(6, Head);
    printDll(Head);

    Head = insertAtPos(3, 3, Head);
    printDll(Head);

    Head = reverseDLL(Head);
    printDll(Head);
    

    return 0;
}