#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class treeNode {
    public:
    int data;
    treeNode* left;
    treeNode* right;

    treeNode(int val){
        data = val;
        left = NULL;
        right = NULL;
    }
};

//BFS TRAVERSAL

vector<vector<int>> BFS(treeNode* &root){
    if(root == NULL) return {};

    queue<treeNode*> q;
    vector<vector<int>> ans;
    q.push(root);

    while(!q.empty()){
        
        int n = q.size();
        vector<int> level;
        
        for(int i = 0; i<n; i++){
            treeNode* temp = q.front();
            q.pop();
            level.push_back(temp -> data);

            if(temp -> left != NULL) q.push(temp -> left);
            if(temp -> right != NULL) q.push(temp -> right);
        }

        ans.push_back(level);
    }

    return ans;
}

void printBfs(vector<vector<int>> &tree){
    for(int i = 0; i<tree.size(); i++){
        vector<int> curr = tree[i];

        for(int j = 0; j<curr.size(); j++){
            cout << curr[j] << " ";
        } cout << endl;
    }
}

//DFS traversals
//Preorder

void preorderTree(treeNode* &root){
    if(root == NULL) return;

    cout << root -> data << " " ;
    preorderTree(root -> left);
    preorderTree(root -> right);
}

//Inorder
void inorderTree(treeNode* &root){
    if(root == NULL) return;

    inorderTree(root -> left);
    cout << root -> data << " ";
    inorderTree(root -> right);
}

//postorder

void postorderTree(treeNode* &root){
    if(root == NULL) return;

    postorderTree(root -> left);
    postorderTree(root -> right);
    cout << root -> data << " ";
}

//DFS traversals but iteratively

//PREORDER

vector<int> preorder(treeNode* &root){
    if(root == NULL) return {};
    
    stack<treeNode*> st;
    vector<int> ans;
    st.push(root);
    
    while(!st.empty()){
        treeNode* temp = st.top();
        st.pop();
        ans.push_back(temp -> data);

        if(temp -> right != NULL) st.push(temp -> right);
        if(temp -> left != NULL) st.push(temp -> left);
    }

    return ans;
}

void printVector(vector<int> arr){
    for(int i = 0; i<arr.size(); i++){
        cout << arr[i] << " ";
    }cout << endl;
}

//Inorder

vector<int> inorder(treeNode* &root){
    if(root == NULL) return {};

    stack<treeNode*> st;
    vector<int> ans;
    treeNode* temp = root;

    while(true){
        if(temp != NULL){
            st.push(temp);
            temp = temp -> left;
        }

        else{

            if(st.empty()) break;

            temp = st.top();
            st.pop();
            ans.push_back(temp -> data);
            temp = temp -> right;
        }
    }

    return ans;
}

// Postorder
//using 2 stacks
// vector<int> postorder(treeNode* &root){
//     if(root == NULL) return {};

//     stack<treeNode*> st;
//     stack<treeNode*> st2;
//     vector<int> ans;
//     st.push(root);

//     while (!st.empty()){
//         treeNode* temp = st.top();
//         st.pop();
//         st2.push(temp);

//         if(temp -> left != NULL) st.push(temp -> left);
//         if(temp -> right != NULL) st.push(temp -> right);
//     }

//     while(!st2.empty()){
//         treeNode* temp = st2.top();
//         st2.pop();
//         ans.push_back(temp -> data);
//     }

//     return ans;
    
// }

//Postorder 
//Using single stack
vector<int> postorder(treeNode* &root){
    if(root == NULL) return {};
    stack<treeNode*> st;
    vector<int> ans;
    treeNode* curr = root;

    while(curr != NULL || !st.empty()){
        if(curr != NULL){
            st.push(curr);
            curr = curr -> left;
        }

        else{
            treeNode* temp = st.top()-> right;

            if(temp == NULL){
                temp = st.top();
                st.pop();
                ans.push_back(temp -> data);
                while((st.empty() == false) && (temp == st.top() -> right)){
                    temp = st.top();
                    st.pop();
                    ans.push_back(temp -> data);
                }
            }

            else curr = temp;
        }
    }

    return ans;
}



int main(){

    treeNode* root = new treeNode(1);
    root -> left = new treeNode(2);
    root -> right = new treeNode(3);
    root -> left -> left = new treeNode(4);
    root -> left -> right = new treeNode(5);
    root -> right -> left = new treeNode(6);
    root -> right -> right = new treeNode(7);

    vector<vector<int>> tree = BFS(root);
    printBfs(tree);
    
    cout << "Preorder traversal : " ;
    preorderTree(root);

    cout << endl << "Inorder traversal : " ;
    inorderTree(root);

    cout << endl << "Postorder traversal : " ;
    postorderTree(root);

    vector<int> preOrder = preorder(root);
    cout << endl << "Iterative preorder : " ;
    printVector(preOrder);

    vector<int> inOrder = inorder(root);
    cout << "Iterative inorder : " ;
    printVector(inOrder);

    vector<int> postOrder = postorder(root);
    cout << "Iterative postorder : " ;
    printVector(postOrder);

    return 0;
}