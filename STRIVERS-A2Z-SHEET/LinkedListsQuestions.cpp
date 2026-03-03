#include<iostream>
#include <bits/stdc++.h>
using namespace std;

//Basic setup before questions

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

//printing an ll
void printLL(Node* &head){
    Node* temp = head;

    while(temp != nullptr){
        cout << temp -> data << " ";
        temp = temp -> next;
    }

    cout << endl;
}

//Searching in a ll
bool searchInLL(int data, Node* &head){
    Node* temp = head;

    while(temp != nullptr){
        if(temp -> data == data) return true;

        temp = temp -> next;
    }

    return false;
}

//length of ll
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



//1. Middle of linked list 
//LINK : https://leetcode.com/problems/middle-of-the-linked-list/submissions/1936429568/?utm=codolio

//Brute Force Solution 

Node* midOfList(Node* &head){
    int length = lengthOfLL(head), mid = 1;

    if(length%2 == 0) mid = length/2 + 1;
    else mid = (length + 1)/2; //the second middle is to be returned

    Node* temp = head;

    //Running one less than the mid becuase temp = head already covered one step
    for(int i = 1; i<mid; i++){
        temp = temp -> next;
    }

    return temp;
}

//Optimal solution using Tortoise-Hare Algorithm

Node* middleOfList(Node* &head){
    Node* slow = head;
    Node* fast = head;

    // why && not ||?
    //Because if fast is not null, but it's next is null, then also we don't want the loop to move forward
    //we want the loop to stop if any of these occur and that means we want the resultant to be 0 if any one of them is zero and that's the case of AND  
    while(fast != NULL && fast -> next != NULL){
        fast = fast -> next -> next;
        slow= slow -> next;
    }

    return slow;
}


int main(){

    cout << endl; 

    //testing Q1 
    vector<int> sample = {1,2,3,4,5,6,7,8,9,10};
    Node* Head = convertArr2LL(sample);
    cout << lengthOfLL(Head) << endl;
    Node* mid = midOfList(Head);
    printLL(mid);

    mid = middleOfList(Head);
    printLL(mid);

    return 0;
}