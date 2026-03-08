#include <iostream>
#include <bits/stdc++.h>
using namespace std;

//Creating the node
class Node{

    public:
    int data;
    Node* next;
    Node* prev;

    Node(){
        data = 0;
        next = NULL;
        prev = NULL;
    }

    Node(int data){
        this -> data = data;
        next = NULL;
        prev = NULL;
    }

    Node(int data, Node* next){
        this -> data = data;
        this -> next = next;
        prev = NULL;
    }

    Node(int data, Node* next, Node* prev){
        this -> data = data;
        this -> next = next;
        this -> prev = prev;
    }

};

//Basic functionalities

Node* ConvertArr2DLL(vector<int> arr){
    Node* head = new Node(arr[0]);
    Node* temp = head;

    for(int i = 1; i<arr.size(); i++){
        Node* newNode = new Node(arr[i]);
        temp -> next = newNode;
        newNode -> prev = temp;
        temp = newNode;
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

// Questions start here
//Q1 delete all occurences of a key in the DLL
Node* delAll(int target, Node* &head){
    if(head == NULL || (head -> next == NULL && head -> data == target)) return NULL;
    if(head ->next == NULL) return head;

    Node* temp = head;
    Node* before = NULL;
    Node* toDel = NULL;

    while(temp != NULL){
        if(temp -> data == target){

            if(temp -> next == NULL && temp -> prev == NULL){
                free(temp);
                return NULL;
            }

            if(temp == head){
                head = head -> next;
                toDel= temp;
                temp = head;
                head -> prev = NULL;
                toDel -> next = NULL;
                free(toDel);
            }

            else if(temp -> next == NULL){
                before -> next = NULL;
                temp -> prev = NULL;
                temp = temp -> next;
                free(temp);
            }

            else{
                toDel = temp;
                temp = temp -> next;
                temp -> prev = before;
                before -> next = temp;
                free(toDel);
            }
        }
        else{
            before = temp;
            temp = temp -> next;
        }
    }

    return head;
}

//Q2
//Find Pairs with Given Sum in Doubly Linked List
//LINK : https://takeuforward.org/plus/dsa/problems/find-pairs-with-given-sum-in-doubly-linked-list?utm=codolio

vector<vector<int>> findPairsWithGivenSum(Node* head, int target) {
        vector<vector<int>> ans;
        if(head == NULL || head -> next == NULL) return ans;
        vector<int> pair;
        Node* slow = head;
        Node* fast = head -> next;
        int sum = 0;

        while(fast -> next != NULL){
            int slowVal = slow -> data;
            int fastVal = fast -> data;
            sum = slowVal + fastVal;
            
            if(sum == target){
                pair = {slowVal, fastVal};
                ans.push_back(pair);
                slow = slow -> next;
                break;
            }
            else if(sum < target){
                fast = fast -> next;
            }
            else {
                break;
            }
        }

        
        while(fast != slow){
            int slowVal = slow -> data;
            int fastVal = fast -> data;
            sum = slowVal + fastVal;

            if(sum == target){
                pair = {slowVal, fastVal};
                ans.push_back(pair);
                slow = slow -> next;
            }
            else if(sum < target) slow =slow -> next;
            else fast = fast -> prev;
        }

        return ans;
    }


int main(){
    cout << endl;

    vector<int> sample = {2,2,8,2,2};
    Node* head = ConvertArr2DLL(sample);

    //Q1
    // head = delAll(2, head);
    // printDll(head);

    //Q2
    vector<int> sample1 = {1, 2, 3, 4};
    Node* head1 = ConvertArr2DLL(sample1);
    vector<vector<int>> ans = findPairsWithGivenSum(head1, 10);
    cout << "size of ans : " << ans.size() << endl;
    for(int i = 0; i<ans.size(); i++){
        for(int j = 0; j<2; j++){
            cout << ans[i][j] << " ";
        } cout << endl;
    }

    return 0;
}