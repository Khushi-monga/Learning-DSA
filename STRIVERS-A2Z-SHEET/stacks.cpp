#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// //Implementing a stack using an array

//  class Stack{
//     public:
//     int *arr = NULL;
//     int size;
//     int top;

//     Stack(int size){
//         this -> size = size;
//         this-> top = -1;
//         this -> arr = new int[size];
//     }

//     void push(int data){
//         //List is full (overflow)
//         if(top == size - 1){
//             cout << "Stack Overflow" << endl;
//             return;
//         }

//         arr[++top] = data;
//         return;
//     }

//     int pop(){
//         //Empty list condition
//         if(top == -1) {
//             cout << "Stack Underflow" << endl;
//             return INT_MIN;
//         }

//         int popped = arr[top--]; //store the element to be popped and move top 1 step back
//         return popped;
//     }

//     int peek(){
//         //empty list
//         if(top == -1){
//             cout << "Stack empty" << endl;
//             return INT_MIN;
//         }

//         return arr[top];
//     }

//     int count(){
//         return top + 1;
//     }

//     void print(){
//         for(int i = 0; i<= top; i++){
//             cout << arr[i] << " " ;
//         } cout << endl;
//     }
//  };

// Implementation of stack using LL

//creating Node class first 
class Node{
    public:
    int data;
    Node* next;

    Node(int data){
        this -> data = data;
        this -> next = NULL;
    }
};

//Converting an array to linked list 
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

// creating the stack
class Stack{
    public:
    int size;
    Node* top;

    Stack(){
        this -> top = NULL;
        this -> size = 0;
    }

    void push(Node* &temp){
        temp -> next = top;
        top = temp;
        size++;
    }

    Node* pop(){
        Node* temp = top;
        top = top -> next;
        temp -> next = NULL;
        size--;
        return temp;
    }

    int peek(){
        if(top == NULL){
            cout << "Stack Underflow";
            return INT_MIN;
        }

        return top -> data;
    }

    int count(){
        return size;
    }

    void print(){
        Node* temp = top;
        while(temp != NULL){
            cout << temp -> data << endl;
            temp = temp -> next;
        }
    }
    
};

void printLL(Node* &head){
    Node* temp = head;

    while(temp != nullptr){
        temp = temp -> next;
    }

    cout << endl;
}


 int main(){

    cout << endl;
    // //Array implementation 
    // Stack* st = new Stack(10);
    // st->push(20);
    // st->push(40);
    // st->push(60);
    // st->push(80);
    // st->print();
    // int pop = st->pop();
    // cout << "Popped once" << endl;
    // st->print();
    // cout << "Top : " << st->peek() << endl;
    // cout << "Total number of elements : " << st->count() << endl;

    //LLimplementation
    Stack* st = new Stack();
    vector<int> sample = {10,20,30,40,50,60,70};
    Node* head = convertArr2LL(sample);

    printLL(head);

    
    // Pushing the elements of the linked list one by one to the stack
    Node* temp = head;
    while(temp != NULL){
        Node* after = temp -> next;
        st->push(temp);
        temp = after;
    }

    //printing the stack
    st->print();
    

    return 0;
 }