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


int main(){
    cout << endl;

    string infix = "a+b*(c^d-e)^(f+g*h)-i";
    string postfix = infixToPostfix(infix);
    cout << "Postfix string : " << postfix << endl;
    string new_infix = postfixToInfix(postfix);
    cout << "Infix expression returned back : " << new_infix << endl;

    string prefix = infixToPrefix(infix);
    cout << "prefix expression : " << prefix << endl;
    
    new_infix = prefixToInfix(prefix);
    cout << "Infix expression returned back : " << new_infix << endl;

    string new_prefix = postfixToPrefix(postfix);
    cout << "prefix expression from postfix : " << prefix << endl;

    string new_postfix = prefixToPostfix(prefix);
    cout << "Postfix string using prefix: " << postfix << endl;

    postfix = prefixToPostfix(new_prefix);
    cout << "Postfix string using new prefix: " << postfix << endl;

    return 0;
}