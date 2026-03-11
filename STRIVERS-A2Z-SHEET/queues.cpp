#include <iostream>
#include <bits/stdc++.h>
using namespace std;

//Implementing queue using arrays

class Queue{
    public:
    int* arr = NULL;
    int size;
    int start;
    int end;
    int currSize;

    Queue(int size){
        this -> arr = new int[size];
        this -> size = size;
        start = -1;
        end = -1;
        currSize = 0;
    }

    void push(int data){
        //Overflow condition
        if(currSize == size){
            cout << "Queue Overflow" << endl;
            return;
        }

        //empty queue
        if(currSize == 0){
            start = end = 0;
            arr[start] = data;
            currSize++;
            return;
        }

        end = (end + 1) % size; //peeche khaali hoga array toh waha shift 
        arr[end] = data;
        currSize++;
        return;    
    }

    int pop(){
        //empty list 
        if(currSize == 0){
            cout << "Queue Underflow" << endl;
            return INT_MIN;
        }

        cout << "Start : " << start << endl;
        cout << "At start : " << arr[start] << endl;
        //single element
        if(currSize == 1){
            int popped = arr[start];
            start = end = -1;
            currSize--;
            return popped;
        }

        int popped = arr[start];
        start = (start+1) % size;
        cout << "Updated start : " << start << endl;
        currSize--;
        return popped;
    }

    int peek(){
        //empty list
        if(currSize == 0){
            cout << "Queue underflow" << endl;
            return INT_MIN;
        }

        return arr[start];
    }

    int count(){
        return currSize;
    }

    void print(){
        int counter = 1;
        int i = start;
        while(counter <= currSize){
            cout << arr[i] << " ";
            i = (i + 1)% size;

            counter++;
        } cout << endl;

    }
};

int main(){

    cout << endl;
    Queue* q = new Queue(10);
    q->pop();
    q->push(20);
    q->push(30);
    q->push(40);
    q->push(50);
    q->print();
    q->pop();
    cout << "Popped once : " ;
    q->print();
    cout << "Top : " << q->peek() << endl;
    cout << "No of elements :" << q->count() << endl;
    q->pop();
    cout << "Popped once : " ;
    q->print();

    return 0;
}