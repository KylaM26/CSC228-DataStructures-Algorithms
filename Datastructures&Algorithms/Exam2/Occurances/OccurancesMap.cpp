#include <iostream>
#include <stdlib.h> //srand, rand
#include <time.h>//clock_t, clock, CLOCKS_PER_SEC
#include <map>
using namespace std;


// Complete tree

//0: 1, 2
//1: 3, 4
//2: 5, 6
//3: 7, 8
//4: 9, 10
//7: 11, 12
//8: 13, 14
//9: 15, 16
//10: 17, 18
//11: 19, 20


// implementing hash tables as an array of linked lists

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
        

            
        
        bool deleteElement(int deleteData){
            
            Node* currentNodePtr = headPtr->getNextNodePtr();
            Node* prevNodePtr = headPtr;
            Node* nextNodePtr = headPtr;
                        
            while (currentNodePtr != 0){
            
                if (currentNodePtr->getData() == deleteData){
                    nextNodePtr = currentNodePtr->getNextNodePtr();
                    prevNodePtr->setNextNodePtr(nextNodePtr);
                    return true;
                }
                
                prevNodePtr = currentNodePtr;
                currentNodePtr = currentNodePtr->getNextNodePtr();
                
            }
            
            return false;
        
        }
        
        int countList(){
            
            Node* currentNodePtr = headPtr->getNextNodePtr();
            int numElements = 0;
            
            while (currentNodePtr != 0){
                
                numElements++;
                currentNodePtr = currentNodePtr->getNextNodePtr();
                
            }
            
            return numElements;
        }

        
        void IterativePrint(){
            
            Node* currentNodePtr = headPtr->getNextNodePtr();
            
            while (currentNodePtr != 0){
                cout << currentNodePtr->getData() << " ";
                currentNodePtr = currentNodePtr->getNextNodePtr();
            }
                
            cout << endl;
            
        }
        
        
        bool containsElement(int searchData){
            
            Node* currentNodePtr = headPtr->getNextNodePtr();
            
            while (currentNodePtr != 0){
                
                if (currentNodePtr->getData() == searchData)
                    return true;
                
                currentNodePtr = currentNodePtr->getNextNodePtr();
            }
            
            return false;
            
        }
    
        
        
        
};


class Hashtable{
    
    private:
        List* listArray;
        int tableSize;
        
    public:
        Hashtable(int size){
            tableSize = size;
            listArray = new List[size];
        }
        
        int getTableSize(){
            return tableSize;
        }
        
        void insert(int data){
            
            int hashIndex = data % tableSize;
            listArray[hashIndex].insert(data);
            
        }
        
        void deleteElement(int data){
            
            int hashIndex = data % tableSize;
            while (listArray[hashIndex].deleteElement(data));
                
        }
        
        bool hasElement(int data){
            
            int hashIndex = data % tableSize;
            return listArray[hashIndex].containsElement(data);
            
        }
        
        void printHashTable(){
            
            for (int hashIndex = 0; hashIndex < tableSize; hashIndex++){
                cout << "Hash Index: " << hashIndex << " : " ;
                listArray[hashIndex].IterativePrint();
            }
            
        }
            
};

int main(){

    int numElements;
    cout << "Enter the number of elements you want to store in the hash table: ";
    cin >> numElements;
    
    int maxValue;
    cout << "Enter the maximum value for an element: ";
    cin >> maxValue;

    int hashTableSize;
    cout << "Enter the size of the hash table: ";
    cin >> hashTableSize;
    
    Hashtable hashTable(hashTableSize);
    std::map<int, int>occurrenceMap;
    srand(time(NULL));
        
    int array[numElements];
    
    cout << "Elements generated: ";
    for (int index = 0; index < numElements; index++){
        array[index] = rand() % maxValue;
        cout << array[index] << " ";
        hashTable.insert(array[index]);
     
        if(!occurrenceMap[array[index]]) {
            occurrenceMap[array[index]] = 1;
        } else {
            occurrenceMap[array[index]] = occurrenceMap[array[index]] + 1;
        }
    }
    
    cout << endl;
    
    
    std::cout << "Elements and their number of occurances" << std::endl;
    
    std::map<int, int>::iterator it = occurrenceMap.begin();
    while(it != occurrenceMap.end()) {
        std::cout<<it->first<<", "<<it->second<<std::endl;
        it++;
    }
return 0;
}
