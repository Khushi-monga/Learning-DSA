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


//2. Reverse a linked list 
//LINK: https://leetcode.com/problems/reverse-linked-list/?utm=codolio

//Iterative approach

Node* reverseList(Node* &head){
    Node* temp = head;
    Node* before = nullptr;

    while(temp != NULL){
        Node* after = temp -> next; //store the next before changing next
        temp -> next = before; //point the next to the prev node
        before = temp; // move the prev node to temp 
        temp = after; // move temp forward using the stored next
    }

    return before;
}

//Recursive approach 

Node* revList(Node* &head){
    //base case
    if(head == NULL|| head -> next == NULL) return head;

    //breakdown the ll and go till the last element then come back reversing one by one
    Node* newHead = reverseList(head -> next);

    Node* front = head -> next;
    front -> next = head;
    head -> next = NULL;

    return newHead;
}


//3. Detect a loop in LL
//LINK : https://leetcode.com/problems/linked-list-cycle/description/?utm=codolio

//brute force - hashmaps
bool detectLoop(Node* &head){
    unordered_map<Node*, int> track;
    Node* temp = head;

    while(temp != NULL){
        if(track.find(temp) != track.end()) return true;
        track[temp] = 1;
        temp = temp -> next;
    }

    return false;
}


// tortoise and hare || Floyd's cycle detection
//[Proof is important (available in notes)]
bool isLoop(Node* &head){
    Node* slow = head;
    Node* fast = head;

    while(fast != NULL && fast -> next != NULL){
        
        slow = slow -> next;
        fast = fast -> next -> next;
        if(slow == fast) return true;
        
    }

    return false;
}

//4. Find the starting point of the loop 
//LINK: https://leetcode.com/problems/linked-list-cycle-ii/?utm=codolio

//brute force
Node* startOfLoop(Node* &head){
    Node* temp = head;
    unordered_map<Node*, int> track;

    while(temp != NULL){
        if(track.find(temp) != track.end()) return temp;

        track[temp] = 1;
        temp = temp -> next;
    }

    return NULL;
}

//Tortoise and hare
//Look at proof(available in notes)
Node* loopStartNode(Node* &head){
    Node* slow = head;
    Node* fast = head;

    while(fast != NULL && fast -> next != NULL){
        slow = slow -> next;
        fast = fast -> next -> next;
        if(slow == fast){
            //loop confirmed now detecting the start point 
            slow = head;
            while(slow != fast){
                slow = slow -> next;
                fast = fast -> next;
            }
            return slow;
        }
    }

    return NULL;
}


//5. Length of loop
//Brute force 
int lenOfLoop(Node* &head){
    Node* temp = head;
    unordered_map<Node*, int> track;
    int count = 1, ans = 0;

    while(temp != NULL){
        if(track.find(temp) != track.end()) {
            cout << "count : " << count<< endl;
            cout << "start point: " << track[temp] << endl;
            ans =  count - track[temp] ;
            return ans;
        }
        track[temp] = count++;
        cout << temp -> data << ": " << track[temp]<< endl; // was verifying count would be extra because we counted till temp became null
        temp = temp -> next;
    }

    return ans;
}

//tortoise and hare
int loopLength(Node* &head){
    Node* slow = head;
    Node* fast = head;
    int ans = 0;

    while(fast != NULL && fast -> next != NULL){
        slow = slow -> next;
        fast = fast -> next -> next;
        //detect the loop
        if(fast == slow){
            // now find length by moving fast forward with step 1 and reaching back slow
            fast = fast -> next;
            ans++;
            
            while(fast != slow){
                fast = fast -> next;
                ans++;
            }

            return ans;
        }
    }

    return ans;
}

//5/02/2026
//6. Checking whether an LL is palindrome or not
//LINK : https://leetcode.com/problems/palindrome-linked-list/?utm=codolio
bool isPalindrome(Node* &head){
    if(head -> next == NULL) return true;

    Node* slow = head;
    Node* fast = head;
    Node* before = NULL;
    Node* after = NULL;

    // Reverse the ll till mid
    while(fast != NULL && fast -> next != NULL){
        fast = fast -> next -> next;
        after = slow -> next;
        slow -> next = before;
        before = slow;
        slow = after;
    }

    if(fast!= NULL) slow = slow -> next;
    fast = before;

    while(fast != NULL && slow != NULL){
        if(fast -> data != slow -> data) return false;
        fast = fast -> next;
        slow = slow -> next;
    }

    //Restoring the half reversed list
    Node* temp = before;
    before = after;


    while(temp != NULL){
        after = temp -> next;
        temp -> next = before;
        before = temp;
        temp = after;
    }

    return true;
}


//7. Odd-Even linked list
//LINK : https://leetcode.com/problems/odd-even-linked-list/?utm=codolio

//8. delete nth node from end
//LINK : https://leetcode.com/problems/remove-nth-node-from-end-of-list/submissions/1938500907/?utm=codolio

//9. Delete middle node 
//LINK: https://leetcode.com/problems/remove-nth-node-from-end-of-list/submissions/1938500907/?utm=codolio

//10. Merge two sorted lists

//11. Sort list
//LINK : https://leetcode.com/problems/sort-list/submissions/1938752414/?utm=codolio


//12. Intersection between two linked lists
//LINK : https://leetcode.com/problems/intersection-of-two-linked-lists/submissions/1938781876/?utm=codolio





int main(){

    cout << endl; 
    vector<int> sample = {1,2,3,4,5,6,7,8,9,10};
    Node* Head = convertArr2LL(sample);

    // //testing Q1 
    // cout << lengthOfLL(Head) << endl;
    // Node* mid = midOfList(Head);
    // printLL(mid);

    // mid = middleOfList(Head);
    // printLL(mid);

    // //Testing Q2
    // Head = reverseList(Head);
    // printLL(Head);

    // Head = revList(Head);
    // printLL(Head);


    // //Testing Q3
    // bool ans = detectLoop(Head);
    // cout << "Loop in given LL : " << ans << endl;

    // ans = isLoop(Head);
    // cout << "Loop in given LL : " << ans << endl;

    //adding loop in list
    Node* temp = Head;
    Node* toPoint = NULL;
    int count = 1;
    while(temp -> next != NULL){
        temp = temp -> next;
        count++;
        if(count == 3) toPoint = temp;
    } 

    temp -> next = toPoint;

    // //testing again
    // ans = detectLoop(Head);
    // cout << "Loop in given LL : " << ans << endl;

    // ans = isLoop(Head);
    // cout << "Loop in given LL : " << ans << endl;

    // //Testing Q4
    // Node* startPt = startOfLoop(Head);
    // cout << "starting point of node : " << startPt -> data << endl;

    // startPt = loopStartNode(Head);
    // cout << "starting point of node : " << startPt -> data << endl;

    // //Testing Q5
    // int length = lenOfLoop(Head);
    // cout << "length of loop : " << length << endl;

    // length = loopLength(Head);
    // cout << "length of loop : " << length << endl;

    //Trying Q6
    vector<int> arr = {1,2,1};
    Node* head2 = convertArr2LL(arr);
    bool ans = isPalindrome(head2);
    cout << "Is the given LL palindrome : " << ans << endl;


    return 0;
}