#include <iostream>
#include <bits/stdc++.h>
using namespace std;

//Implementing a stack using an array

 class Stack{
    public:
    int *arr = NULL;
    int size;
    int top;

    Stack(int size){
        this -> size = size;
        this-> top = -1;
        this -> arr = new int[size];
    }

    void push(int data){
        //List is full (overflow)
        if(top == size - 1){
            cout << "Stack Overflow" << endl;
            return;
        }

        arr[++top] = data;
        return;
    }

    int pop(){
        //Empty list condition
        if(top == -1) {
            cout << "Stack Underflow" << endl;
            return INT_MIN;
        }

        int popped = arr[top--]; //store the element to be popped and move top 1 step back
        return popped;
    }

    int peek(){
        //empty list
        if(top == -1){
            cout << "Stack empty" << endl;
            return INT_MIN;
        }

        return arr[top];
    }

    int count(){
        return top + 1;
    }

    void print(){
        for(int i = 0; i<= top; i++){
            cout << arr[i] << " " ;
        } cout << endl;
    }
 };


 int main(){

    cout << endl;
    Stack* st = new Stack(10);
    st->push(20);
    st->push(40);
    st->push(60);
    st->push(80);
    st->print();
    int pop = st->pop();
    cout << "Popped once" << endl;
    st->print();
    cout << "Top : " << st->peek() << endl;
    cout << "Total number of elements : " << st->count() << endl;

    return 0;
 }