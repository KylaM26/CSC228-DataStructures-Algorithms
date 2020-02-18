#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

// implementing the dynamic List ADT using Linked List

class Node{
    
    private:
        int data;
        Node* nextNodePtr;
        
    public:
        Node(){}
        
        void setData(int d){
            data = d;
        }
        
        int getData(){
            return data;
        }
        
        void setNextNodePtr(Node* nodePtr){
                nextNodePtr = nodePtr;
        }
        
        Node* getNextNodePtr(){
            return nextNodePtr;
        }
            
};

class List{

    private:
        Node *headPtr;
    
    public:
        List(){
            headPtr = new Node();
            headPtr->setNextNodePtr(0);
        }
    
        Node* getHeadPtr(){
            return headPtr;
        }
    
        bool isEmpty(){
            
            if (headPtr->getNextNodePtr() == 0)
                return true;
            
            return false;
        }
        
        
        void insert(int data){
            
            Node* currentNodePtr = headPtr->getNextNodePtr();
            Node* prevNodePtr = headPtr;
            
            while (currentNodePtr != 0){
                prevNodePtr = currentNodePtr;
                currentNodePtr = currentNodePtr->getNextNodePtr();
            }
            
            Node* newNodePtr = new Node();
            newNodePtr->setData(data);
            newNodePtr->setNextNodePtr(0);
            prevNodePtr->setNextNodePtr(newNodePtr);
            
        }
        
        void insertAtIndex(int insertIndex, int data){
            
            Node* currentNodePtr = headPtr->getNextNodePtr();
            Node* prevNodePtr = headPtr;
            
            int index = 0;
            
            while (currentNodePtr != 0){
                
                if (index == insertIndex)
                    break;
                
                prevNodePtr = currentNodePtr;
                currentNodePtr = currentNodePtr->getNextNodePtr();
                index++;
            }
            
            Node* newNodePtr = new Node();
            newNodePtr->setData(data);
            newNodePtr->setNextNodePtr(currentNodePtr);
            prevNodePtr->setNextNodePtr(newNodePtr);
            
        }
        
                

        void deleteALLElements(int data){
            if(isEmpty()) return;

            Node* current = headPtr->getNextNodePtr();
            int index = 0;

            while(current) {
                if(current->getData() == data) {
                    deleteElement(index);
                    index--;
                }

                current = current->getNextNodePtr();
                index++;
            }
            
        }


        
        void deleteElement(int deleteIndex){
            Node* currentNodePtr = headPtr->getNextNodePtr();
            Node* prevNodePtr = headPtr;
            Node* nextNodePtr = headPtr;
            int index = 0;
            
            while (currentNodePtr != 0){
            
                if (index == deleteIndex){
                    nextNodePtr = currentNodePtr->getNextNodePtr();
                    break;
                }
                
                prevNodePtr = currentNodePtr;
                currentNodePtr = currentNodePtr->getNextNodePtr();
                
                index++;
            }
            
            prevNodePtr->setNextNodePtr(nextNodePtr);
        
        }
        
        
        void IterativePrint(){
            
            Node* currentNodePtr = headPtr->getNextNodePtr();
            
            while (currentNodePtr != 0){
                cout << currentNodePtr->getData() << " ";
                currentNodePtr = currentNodePtr->getNextNodePtr();
            }
                
            cout << endl;
            
        }
        
        
};

int main(){

    srand(time(NULL));
    
    int listSize;
    cout << "Enter the number of elements in the list: ";
    cin >> listSize;
    
    int maxValue;
    cout << "Enter the maximum value for any element in the list: ";
    cin >> maxValue;
    
    List integerList; // Create an empty list
    
    for (int i = 0; i < listSize; i++){
        
        int value = 1 + rand()%maxValue;
        integerList.insertAtIndex(i, value);
    }
    
    cout << "Contents of the List (before deletion): ";
    integerList.IterativePrint();
    
    int deleteData;
    cout << "Enter the data to delete: ";
    cin >> deleteData;
    
    integerList.deleteALLElements(deleteData);
    
    
    cout << "Contents of the List (after deletion): ";
    integerList.IterativePrint();
    
    system("pause");
    
return 0;
}


