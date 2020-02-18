//
//  main.cpp
//  ParenthesisBalance
//
//  Created by Kyla Wilson on 2/13/20.
//  Copyright © 2020 Kyla Wilson. All rights reserved.
//

#include <iostream>
using namespace std;


class Node{
    
    private:
        char data;
        Node* nextNodePtr;
        Node* prevNodePtr;
        
    public:
        Node(){}
        
        void setData(char d){
            data = d;
        }
        
        char getData(){
            return data;
        }
        
        void setNextNodePtr(Node* nodePtr){
                nextNodePtr = nodePtr;
        }
        
        Node* getNextNodePtr(){
            return nextNodePtr;
        }
        
        void setPrevNodePtr(Node* nodePtr){
                prevNodePtr = nodePtr;
        }
        
        Node* getPrevNodePtr(){
            return prevNodePtr;
        }
        
};

class Stack{

    private:
        Node* headPtr;
        Node* tailPtr;

    
    public:
        Stack(){
            headPtr = new Node();
            tailPtr = new Node();
            headPtr->setNextNodePtr(0);
            tailPtr->setPrevNodePtr(0);
        }
    
        Node* getHeadPtr(){
            return headPtr;
        }
        
        Node* getTailPtr(){
            return tailPtr;
        }
        
        bool isEmpty(){
            
            if (headPtr->getNextNodePtr() == 0)
                return true;
            
            return false;
        }
        
        
        void push(char data){
            
            Node* newNodePtr = new Node();
            newNodePtr->setData(data);
            newNodePtr->setNextNodePtr(0);
            
            Node* lastNodePtr = tailPtr->getPrevNodePtr();
            
            if (lastNodePtr == 0){
                
                headPtr->setNextNodePtr(newNodePtr);
                newNodePtr->setPrevNodePtr(0);
                
            }
            else{
                
                lastNodePtr->setNextNodePtr(newNodePtr);
                newNodePtr->setPrevNodePtr(lastNodePtr);
                
            }
            
            tailPtr->setPrevNodePtr(newNodePtr);
            
        }

        
        char pop(){
            
            Node* lastNodePtr = tailPtr->getPrevNodePtr();
            Node* prevNodePtr = 0;
            
            char poppedData = '$'; //empty stack
            
            if (lastNodePtr != 0){
                prevNodePtr = lastNodePtr->getPrevNodePtr();
                poppedData = lastNodePtr->getData();
            }
            else
                return poppedData;
            
            if (prevNodePtr != 0){
                prevNodePtr->setNextNodePtr(0);
                tailPtr->setPrevNodePtr(prevNodePtr);
            }
            else{
                headPtr->setNextNodePtr(0);
                tailPtr->setPrevNodePtr(0);
            }
            
            return poppedData;
        }
        
        
        char peek(){
            
            Node* lastNodePtr = tailPtr->getPrevNodePtr();
            
            if (lastNodePtr != 0)
                return lastNodePtr->getData();
            else
                return '$'; //  empty stack
        
            
        }
        
        
        
};

int main(){

    Stack stack;

    string expression;
    
    cout << "Enter an expression: ";
    cin >> expression;
    
    int index = 0;
    

    int maxDepthCount = 0;
    
    while (index < expression.size()){
        // instend when a close par is found subtract from dephtCounter
        // also have a max depth
        char symbol = expression[index];
        int depthCounter = 0;
        
        if (symbol == '{' ) { // Check if open symbol
            stack.push(symbol); // Push to stack
            index++; // Increment index
            // 0 - 1 - 2 - 4 - 5 - 6 - 7 - 8
            depthCounter++; // 1 - 2 - 3 - 2 - 3
            maxDepthCount = depthCounter; // 1 - 2 - 3 - 2 - 3
            continue; // Continue on
        } else if (symbol == '}' ){ // If symbol is closing
            char topSymbol = stack.pop(); // Pop the top symbol and store it
            
            if (topSymbol == '{' && symbol == '}') { // If top item is opening symbol and the current symbol is closing
                depthCounter--; // 2 - 1 - 2 - 1, 
                index++; // Go to next index
                continue; // Continue on
            } else {
                cout << "Expression not balanced!!"  << ", Max depth: " << maxDepthCount << endl;
                return maxDepthCount;
            }
        } else {
            cout << "Invalid symbol "<< symbol << " in the expression!!" << endl;
            return 0;
        }
            
            
    }
    
    std::cout << "Max depth count: " << maxDepthCount << std::endl;
    
    if (!stack.isEmpty()){
        cout << "Expression is not balanced!" << endl;
        return 0;
    }
    
    cout << expression << " is balanced!!" << endl;

    
return 0;
}
