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
    
    int index = 0, depth = 0, maxDepth = 0;
    
    while (index < expression.size()) {
        
        char symbol = expression[index];
        
        if (symbol == '{' ){
            stack.push(symbol);
            index++, depth++;
                    
            if(depth > maxDepth)
                maxDepth = depth;
            continue;
            
        } else if (symbol == '}' ){
            char topSymbol = stack.pop();
            
            if (topSymbol == '{' && symbol == '}') {
                index++, depth--;
                continue;
            } else {
                cout << "Expression not balanced!!" <<  "\n, Depth: " << maxDepth << endl;
                return 0;
                
            }
        } else{
            cout << "Invalid symbol "<< symbol << " in the expression!!" << endl;
            return 0;
        }
    }
    
    if (!stack.isEmpty()){
        cout << "Expression not balanced!!" <<  "\nDepth: " << maxDepth << endl;
        return 0;
    }

    cout << expression << " is balanced!!"  << "\nDepth: " << maxDepth << endl;

    
return 0;
}
