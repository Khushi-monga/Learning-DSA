#include <iostream>
#include <bits/stdc++.h>
using namespace std;

//Implementing queue using arrays

// class Queue{
//     public:
//     int* arr = NULL;
//     int size;
//     int start;
//     int end;
//     int currSize;

//     Queue(int size){
//         this -> arr = new int[size];
//         this -> size = size;
//         start = -1;
//         end = -1;
//         currSize = 0;
//     }

//     void push(int data){
//         //Overflow condition
//         if(currSize == size){
//             cout << "Queue Overflow" << endl;
//             return;
//         }

//         //empty queue
//         if(currSize == 0){
//             start = end = 0;
//             arr[start] = data;
//             currSize++;
//             return;
//         }

//         end = (end + 1) % size; //peeche khaali hoga array toh waha shift 
//         arr[end] = data;
//         currSize++;
//         return;    
//     }

//     int pop(){
//         //empty list 
//         if(currSize == 0){
//             cout << "Queue Underflow" << endl;
//             return INT_MIN;
//         }

//         cout << "Start : " << start << endl;
//         cout << "At start : " << arr[start] << endl;
//         //single element
//         if(currSize == 1){
//             int popped = arr[start];
//             start = end = -1;
//             currSize--;
//             return popped;
//         }

//         int popped = arr[start];
//         start = (start+1) % size;
//         cout << "Updated start : " << start << endl;
//         currSize--;
//         return popped;
//     }

//     int peek(){
//         //empty list
//         if(currSize == 0){
//             cout << "Queue underflow" << endl;
//             return INT_MIN;
//         }

//         return arr[start];
//     }

//     int count(){
//         return currSize;
//     }

//     void print(){
//         int counter = 1;
//         int i = start;
//         while(counter <= currSize){
//             cout << arr[i] << " ";
//             i = (i + 1)% size;

//             counter++;
//         } cout << endl;

//     }
// };

// Implementing queues using linked lists
//creating the node class
class Node{
    public:
    int data;
    Node* next;

    Node(int data){
        this -> data = data;
        this -> next = NULL;
    }
};

//convert an array to a linked list
Node* convertArray2LL(vector<int> sample){
    Node* head = new Node(sample[0]);
    Node* temp = head;

    for(int i = 1; i<sample.size(); i++){
        Node* newNode = new Node(sample[i]);
        temp -> next = newNode;
        temp = newNode;
    }

    return head;
}

class Queue{
    public:
    Node* start;
    Node* end;
    int count;

    Queue(){
        start = NULL;
        end = NULL;
        count = 0;
    }

    Queue(int data){
        Node* temp = new Node(data);
        this -> start = temp;
        this -> end = temp;
        count = 1;
    }

    void push(int data){
        
        Node* temp = new Node(data);

        //if empty queue
        if(count == 0){
            start = temp;
            end = temp;
            count++;
            return;
        }

        //else
        end -> next = temp;
        end = temp;
        count++;
        return;
    }

    int pop(){
        //if empty queue
        if(count == 0){
            cout << "Queue Underflow" << endl;
            return INT_MIN;
        }

        int popped = start -> data;
        Node* temp = start;
        start = start -> next;
        temp -> next = NULL;
        delete temp;
        count--;
        return popped;
    }

    int peek(){
        //if empty queue
        if(count == 0){
            cout << "Empty queue" << endl;
            return INT_MIN;
        }

        return start -> data;
    }

    int size(){
        return count;
    }

    void print(){
        Node* temp = start;
        while(temp != NULL){
            cout << temp -> data << " ";
            temp = temp -> next;
        } cout << endl;
    }
};

int main(){

    // cout << endl;

    // Queue* q = new Queue(10);
    // q->print();

    // q->push(20);
    // q->push(30);
    // q->print();
    // q->pop();
    // q->print();

    // cout << "Peek : " << q->peek() << endl;
    // cout << "Size of queue : "<< q->size() << endl;

    // q->pop();
    // q->pop();
    // q->pop();

    //Using STL
    queue<int> q;
    q.push(5);
    q.push(8);
    q.push(29);
    q.pop();
    q.pop();
    q.pop();
    q.push(263);

    cout << q.front() << endl;

    return 0;
}