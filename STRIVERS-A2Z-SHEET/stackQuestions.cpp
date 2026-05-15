#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int priority(string opr){
    if(opr == "+" || opr == "-") return 0;
    else if (opr == "*" || opr == "/") return 1;
    else if (opr == "^") return 2;

    return -1;
}

//1. Infix to postfix notation conversion
string infixToPostfix(string& s) {
    string postfix = "";
    stack<string> st;

    for(int i = 0; i<s.size(); i++){
        string curr;
        curr = s[i];
        //is it an operand 
        if((curr >= "A" && curr <= "Z") || (curr >= "a" && curr <="z") 
        || (curr >= "0" && curr <= "9")) postfix += curr;
        
        //else is it ( or ^
        else if(curr == "(" || curr == "^") st.push(curr);

        //or is it )
        else if(curr == ")"){
            while(!st.empty() && (st.top() != "(")){
                string top = st.top();
                st.pop();
                postfix += top;
            }

            st.pop();
        }

        // now it's just /, *, + or -
        else {
            if(!st.empty()){
                int priority_curr = priority(curr);
                int priority_top = priority(st.top());

                if(priority_curr < priority_top){
                    while(!st.empty() && (st.top() != "(")){
                        string top = st.top();
                        st.pop();
                        postfix += top;
                    }
                }
            }

            st.push(curr);
        }
    }

    while(!st.empty()){
        string top = st.top();
        st.pop();
        postfix += top; 
    }

    return postfix;
}


//2. Infix to prefix conversion
//steps : 1. reverse the infix notation
//2. convert that into postfix
//3. reverse the resulting postfix notation

string infixToPrefix(string s){
    //reverse the infix expression
    reverse(s.begin(), s.end());

    //flip the inverted braces
    for(int i = 0; i<s.size(); i++){
        if(s[i] == '(') s[i] = ')';
        else if(s[i] == ')') s[i] = '(';
    }

    //find the postfix expression
    string postfix = infixToPostfix(s);

    //reverse postfix expression
    reverse(postfix.begin(), postfix.end());

    return postfix;
}


//3. Postfix to infix 
string postfixToInfix(string s){
    stack<string> st;

    for(int i = 0; i<s.size(); i++){
        string curr;
        curr = s[i];
        //is it an operand 
        if((curr >= "A" && curr <= "Z") || (curr >= "a" && curr <="z") 
        || (curr >= "0" && curr <= "9")) st.push(curr);

        //if it is an operand 
        else{
            string top1 = st.top();
            st.pop();
            string top2 = st.top();
            st.pop();

            string toAdd ="(" + top2 + curr + top1 + ")";
            st.push(toAdd);
        }
        
    }

    return st.top();
}

//4. Prefix to infix
string prefixToInfix(string s){
    stack<string> st;

    for(int i = s.size()-1; i >= 0; i--){
        string curr;
        curr = s[i];
        //is it an operand 
        if((curr >= "A" && curr <= "Z") || (curr >= "a" && curr <="z") 
        || (curr >= "0" && curr <= "9")) st.push(curr);

        //if it is an operand 
        else{
            string top1 = st.top();
            st.pop();
            string top2 = st.top();
            st.pop();

            string toAdd ="(" + top1 + curr + top2 + ")";
            st.push(toAdd);
        }
    }

    return st.top();

}

//5. Postfix to prefix  
string postfixToPrefix(string s){
    stack<string> st;

    for(int i = 0; i<=s.size() - 1; i++){
        string curr;
        curr = s[i];
        //if it is an operand
        if((curr >= "A" && curr <= "Z") || (curr >= "a" && curr <="z") 
        || (curr >= "0" && curr <= "9")) st.push(curr);

        //if not => operator
        else{
            string top1 = st.top();
            st.pop();
            string top2 = st.top();
            st.pop();

            string toAdd = curr + top2 + top1 ;
            st.push(toAdd);
        }
    }

    return st.top();
}

//6. Prefix to postfix

string prefixToPostfix(string s){
    stack<string> st;

    for(int i = s.size() - 1; i>=0; i--){
        string curr;
        curr = s[i];
        //if it is an operand
        if((curr >= "A" && curr <= "Z") || (curr >= "a" && curr <="z") 
        || (curr >= "0" && curr <= "9")) st.push(curr);

        //if not => operator
        else{
            string top1 = st.top();
            st.pop();
            string top2 = st.top();
            st.pop();

            string toAdd = top1 + top2 + curr ;
            st.push(toAdd);
        }
    }

    return st.top();
}

// 7. Check for balanced parenthesis 
// link : https://leetcode.com/problems/valid-parentheses/?utm=codolio

bool isValid(string s){
    unordered_map<string, string> braces = {
        {")" , "("},
        {"}" , "{"},
        {"]" , "["}
    };
    stack<string> openings;

    for(int i = 0; i<s.size(); i++){
        string curr;
        curr = s[i];
        //preserve the opening brackets
        if(curr == "(" || curr == "{" || curr == "[") openings.push(curr);
    

        //check the closing brackets for corresponding opening ones 
        else{
            if(openings.empty()) return false;

            string lastOp = openings.top();
            openings.pop();
            
            //they don't match
            if(lastOp!= braces[curr]) return false;
        }
    }

    if(!openings.empty()) return false;

    return true;
}

// // 8. Min stack
// class MinStack{
//     public:
//     stack<int> st;
//     int minNum = INT_MAX;

//     MinStack(){

//     }

//     void push(int val){
//         if(val < minNum){
//             int prevMin = minNum;
//             minNum = val;
//             val = 2*val - prevMin;
//         }

//         st.push(val);
//     }

//     void pop(){
//         int toPop = st.top();
//         st.pop();

//         int next = st.top();

//         if(next >toPop){
//             //then the popped value is the min val
//             //update minNum with the prevMin before the current one
//             minNum = 2*minNum - toPop;
//         }
//     }

//     int top(){
//         //if its the min value, we'll have to return the actual value 
//         int temp = st.top();
//         st.pop();
//         int next = st.top();
//         st.push(temp);

//         if(next > temp) return minNum;
//         else return temp;
//     }

//     int size(){
//         return st.size();
//     }

//     int min(){
//         return minNum;
//     }
// };

// 9. Next Greater Element 
// link : https://leetcode.com/problems/next-greater-element-i/description/?utm=codolio
vector<int> findNge(vector<int> nums1, vector<int> nums2){
    stack<int> st;
    unordered_map<int, int> trackNge; //arr val : nge val 
    vector<int> ans(nums1.size());

    for(int i = nums2.size()-1; i>=0; i--){
       while(!st.empty()){
        if(st.top() > nums2[i]){
            trackNge[nums2[i]] = st.top();
            break;
        }

        else st.pop();
       }

       if(st.empty()) trackNge[nums2[i]] = -1;
       st.push(nums2[i]);
    }

    for(int i = 0; i< nums1.size(); i++){
        ans[i] = trackNge[nums1[i]];
    }

    return ans;
}

//10. Next greater element II
//link : https://leetcode.com/problems/next-greater-element-ii/?utm=codolio
vector<int> circularNge(vector<int> nums){
    stack<int> st;
    vector<int> ans(nums.size());

    //first we'll find the nge for elements which have nge in the forward path(not circular)
    for(int i = nums.size() - 1; i>=0; i--){
        while(!st.empty()){
            if(st.top() > nums[i]){
                ans[i] = st.top();
                st.push(nums[i]);
                nums[i] = INT_MIN;
                break;
            }

            else{
                st.pop();
            }
        }

        if(st.empty()) st.push(nums[i]);
        
    }

    //now we have the monotonic stack in the increasing order
    //now we'll look for the nge for the leftover elements 

    for(int i = nums.size() - 1; i>=0; i--){
        if(nums[i] != INT_MIN){
            while(!st.empty()){
                if(st.top() > nums[i]){
                    ans[i] = st.top();
                    break;
                }

                else st.pop();
            }

            if(st.empty()) ans[i] = -1;
        }
    }
    

    return ans;
}


//Next smaller element
vector<int> findNse(vector<int> nums){
    stack<int> st;
    vector<int> ans(nums.size());

    for(int i = nums.size()-1; i>=0; i--){
        while(!st.empty()){
            if(st.top() < nums[i]){
                ans[i] = st.top();
                break;
            }
            
            else st.pop();
        }

        if(st.empty()) ans[i] = -1;

        st.push(nums[i]);
    }

    return ans;
}

//12. Previous greater element 
vector<int> findPge(vector<int> nums){
    stack<int> st;
    vector<int> ans(nums.size());

    for(int i = 0; i<nums.size(); i++){
        while(!st.empty()){
            if(st.top() > nums[i]){
                ans[i] = st.top();
                break;
            }
            
            else st.pop();
        }

        if(st.empty()) ans[i] = -1;

        st.push(nums[i]);
    }

    return ans;
}


//13. Previous smaller element
vector<int> findPse(vector<int> nums){
    stack<int> st;
    vector<int> ans(nums.size());

    for(int i = 0; i<nums.size(); i++){
        while(!st.empty()){
            if(st.top() < nums[i]){
                ans[i] = st.top();
                break;
            }
            
            else st.pop();
        }

        if(st.empty()) ans[i] = -1;

        st.push(nums[i]);
    }

    return ans;
}


//14. Number of next greater elements
//12. Previous greater element 
vector<int> countNge(vector<int> nums){
    stack<int> st;
    vector<int> ans(nums.size());

    for(int i = nums.size() - 1; i>=0; i--){
        while(!st.empty()){
            if(st.top() > nums[i]){
                ans[i] = st.size();
                break;
            }
            
            else st.pop();
        }

        if(st.empty()) ans[i] = 0;

        st.push(nums[i]);
    }

    return ans;
}


void printVector(vector<int> arr){
    for(int i = 0; i<arr.size(); i++){
        cout << arr[i] << " ";
    }

    cout << endl;
}

int main(){
    cout << endl;

    // string infix = "a+b*(c^d-e)^(f+g*h)-i";
    // string postfix = infixToPostfix(infix);
    // cout << "Postfix string : " << postfix << endl;
    // string new_infix = postfixToInfix(postfix);
    // cout << "Infix expression returned back : " << new_infix << endl;

    // string prefix = infixToPrefix(infix);
    // cout << "prefix expression : " << prefix << endl;
    
    // new_infix = prefixToInfix(prefix);
    // cout << "Infix expression returned back : " << new_infix << endl;

    // string new_prefix = postfixToPrefix(postfix);
    // cout << "prefix expression from postfix : " << prefix << endl;

    // string new_postfix = prefixToPostfix(prefix);
    // cout << "Postfix string using prefix: " << postfix << endl;

    // postfix = prefixToPostfix(new_prefix);
    // cout << "Postfix string using new prefix: " << postfix << endl;

    // string test = "({({({({[[[[[]]]]]})})})})";
    // bool ans = isValid(test);
    // cout << "the given string is : " << endl;
    // if(ans) cout << "valid" << endl;
    // else cout << "invalid" << endl;

    //9. 
    vector<int> nums2 = {5,6,3,4,3,2,1,4};
    vector<int> nums1 = {1,8,9,2,5};
    // vector<int> ans = findNge(nums1, nums2);
    // for(int i = 0; i<ans.size(); i++){
    //     cout << ans[i] << " ";
    // } 
    // cout << endl;

    //10.
    // vector<int> ans = circularNge(nums2);
    // printVector(ans);

    //11. 
    // vector<int> ans = findNse(nums2);
    // vector<int> ans = findPge(nums2);
    // printVector(ans);

    // 12.
    // vector<int> ans = findPse(nums2);
    // printVector(ans);

    //13. 
    vector<int> ans = countNge(nums2);
    printVector(ans);


    return 0;
}