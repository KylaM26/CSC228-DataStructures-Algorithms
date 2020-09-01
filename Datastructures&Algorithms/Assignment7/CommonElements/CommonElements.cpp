#include <iostream>
#include <stdlib.h> //srand, rand
#include <time.h>//clock_t, clock, CLOCKS_PER_SEC
#include <vector>
using namespace std;

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
    
    
    int read(int readIndex){
        
        Node* currentNodePtr = headPtr->getNextNodePtr();
        Node* prevNodePtr = headPtr;
        int index = 0;
        
        while (currentNodePtr != 0){
            
            if (index == readIndex)
                return currentNodePtr->getData();
            
            prevNodePtr = currentNodePtr;
            currentNodePtr = currentNodePtr->getNextNodePtr();
            
            index++;
            
        }
        
        return -1; // an invalid value indicating
        // index is out of range
        
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
        //while (listArray[hashIndex].deleteElement(data));
        listArray[hashIndex].deleteElement(data);
        
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
    
    
    void removeAllElements(){
        for (int hashIndex = 0; hashIndex < tableSize; hashIndex++)
            listArray[hashIndex].getHeadPtr()->setNextNodePtr(0);
        
    }
    
    
    
};

int main() {
    
    int numLists;
    cout << "Enter the number of lists: ";
    cin >> numLists;
    
    int numElements;
    cout << "Enter the number of elements per list: ";
    cin >> numElements;
    
    int maxValue;
    cout << "Enter the maximum value for an element: ";
    cin >> maxValue;
    
    int hashTableSize;
    cout << "Enter the size of the hash table: ";
    cin >> hashTableSize;
    
    cout << endl;
    
    Hashtable hashTable(hashTableSize);
    
    srand(time(NULL));
    
    List* listArray = new List[numLists];
    
    // Store all elements in a hashtable
    // Loop and store number as key, if key exist already print that element.
    
    for (int listArrayIndex = 0; listArrayIndex < numLists; listArrayIndex++){
        
        Hashtable commonElementTable(numElements);
        std::vector<int> repeatedElements;
        
        for (int index = 0; index < numElements; index++){
            int value = rand() % maxValue;
            listArray[listArrayIndex].insert(value);
            
            if(!commonElementTable.hasElement(value)) // If could not find element
                commonElementTable.insert(value); // Insert the element
            else // If value was already found in hashmap
                repeatedElements.push_back(value); // Store repeated value
        }
        
        std::cout << std::endl;
        
        cout << "Elements generated in List # " << (listArrayIndex) << endl;
        listArray[listArrayIndex].IterativePrint();
        
        // Printing common elements for each list to the console
        std::cout << "Common elements in list # " << listArrayIndex << std::endl;
        for(int i = 0; i < repeatedElements.size(); i++) {
            std::cout << repeatedElements.at(i) << " ";
        }
        
        std::cout << std::endl << std::endl;
    }
    
    List CommonElementsList;
    
    for (int index = 0; index < numElements; index++){
        int value = listArray[0].read(index);
        hashTable.insert(value);
        CommonElementsList.insert(value);
    }
    
    cout << "\nCommon elements in all the lists " << endl;
    CommonElementsList.IterativePrint();
    
    system("pause");
    
    return 0;
}
