#include <iostream>
#include <fstream>
#include <string>
#include <cstring> // for string tokenizer and c-style string processing
#include <algorithm> // max function

#include <stdlib.h>
#include <time.h>
#include <vector>

using namespace std;

// Extend the code here as needed
std::vector<int> orderedNodes;

class BTNode{
    
    private:
        int nodeid;
        int data;
        int levelNum;
        BTNode* leftChildPtr;
        BTNode* rightChildPtr;
    
    public:
    
        BTNode(){}
        
        void setNodeId(int id){
            nodeid = id;
        }
    
        int getNodeId(){
            return nodeid;
        }
    
        void setData(int d){
            data = d;
        }
    
        int getData(){
            return data;
        }
    
        void setLevelNum(int level){
            levelNum = level;
        }
        
        int getLevelNum(){
            return levelNum;
        }
        
        void setLeftChildPtr(BTNode* ptr){
            leftChildPtr = ptr;
        }
    
        void setRightChildPtr(BTNode* ptr){
            rightChildPtr = ptr;
        }
    
        BTNode* getLeftChildPtr(){
            return leftChildPtr;
        }
    
        BTNode* getRightChildPtr(){
            return rightChildPtr;
        }
    
        int getLeftChildID(){
            if (leftChildPtr == 0)
                return -1;
            
            return leftChildPtr->getNodeId();
        }
        
        int getRightChildID(){
            if (rightChildPtr == 0)
                return -1;
            
            return rightChildPtr->getNodeId();
        }
};


class BinaryTree{
    
    private:
        int numNodes;
        BTNode* arrayOfBTNodes;
        
    public:
    
        BinaryTree(int n){
            numNodes = n;
            arrayOfBTNodes = new BTNode[numNodes];
            
            for (int id = 0; id < numNodes; id++){
                arrayOfBTNodes[id].setNodeId(id);
                arrayOfBTNodes[id].setLevelNum(-1);
                arrayOfBTNodes[id].setLeftChildPtr(0);
                arrayOfBTNodes[id].setRightChildPtr(0);
            }
        }
        
        void setLeftLink(int upstreamNodeID, int downstreamNodeID){
            arrayOfBTNodes[upstreamNodeID].setLeftChildPtr(&arrayOfBTNodes[downstreamNodeID]);
        }
        
        void setRightLink(int upstreamNodeID, int downstreamNodeID){
            arrayOfBTNodes[upstreamNodeID].setRightChildPtr(&arrayOfBTNodes[downstreamNodeID]);
        }
        
        void printLeafNodes(){
            
            for (int id = 0; id < numNodes; id++){
                
                if (arrayOfBTNodes[id].getLeftChildPtr() == 0 && arrayOfBTNodes[id].getRightChildPtr() == 0)
                    cout << id << " ";
            }
            
            cout << endl;
        }
    
    
        bool isLeafNode(int nodeid){
            
            if (arrayOfBTNodes[nodeid].getLeftChildPtr() == 0 && arrayOfBTNodes[nodeid].getRightChildPtr() == 0)
                return true;
            
            return false;
        }
    

        void PrintNodeData(){
            for (int nodeid = 0; nodeid < numNodes; nodeid++)
                cout << nodeid << " " << arrayOfBTNodes[nodeid].getData() << endl;
            
        }
        
        

        void InOrderTraversal(int nodeid, int *dataArray){
            
            if (nodeid == -1)
                return;
            
            
            InOrderTraversal(arrayOfBTNodes[nodeid].getLeftChildID(), dataArray);
            
            // Extend the code for this function here as needed

            orderedNodes.push_back(nodeid);
        
            cout << nodeid << " ";
            InOrderTraversal(arrayOfBTNodes[nodeid].getRightChildID(), dataArray);
            
        }

        
        void PrintInOrderTraversal(int *dataArray){
            
            // Extend the code for this function here as needed
            InOrderTraversal(0, dataArray);
            cout << endl;
            
            for(int index = 0; index < numNodes; index++)
                arrayOfBTNodes[orderedNodes[index]].setData(dataArray[index]);
           
        }

    
        
    
};


    void SelectionSort(int *array, int arraySize){
    
        for (int iterationNum = 0; iterationNum < arraySize-1; iterationNum++){
            
            int minIndex = iterationNum;
        
            for (int j = iterationNum+1; j < arraySize; j++){
            
                if (array[j] < array[minIndex])
                    minIndex = j;
        
            }
        
            // swap array[minIndex] with array[iterationNum]
            int temp = array[minIndex];
            array[minIndex] = array[iterationNum];
            array[iterationNum] = temp;
        
        }
    
    }
    
    

int main(){
    
    string filename;
    cout << "Enter a file name: ";
    cin >> filename;
    
    int numNodes;
    cout << "Enter number of nodes: ";
    cin >> numNodes;

    
    BinaryTree binaryTree(numNodes);
    
    ifstream fileReader(filename);
    
    if (!fileReader){
        cout << "File cannot be opened!! ";
        return 0;
    }

    int numCharsPerLine = 10;
    
    char *line = new char[numCharsPerLine];
    // '10' is the maximum number of characters per line
    
    fileReader.getline(line, numCharsPerLine, '\n');
    // '\n' is the delimiting character to stop reading the line
        
    while (fileReader){
            
        char* cptr = strtok(line, ",: ");
        
        string upstreamNodeToken(cptr);
        int upstreamNodeID = stoi(upstreamNodeToken);
        
        cptr = strtok(NULL, ",: ");
        
        int childIndex = 0; // 0 for left child; 1 for right child
        
        while (cptr != 0){
            
            string downstreamNodeToken(cptr);
            int downstreamNodeID = stoi(downstreamNodeToken);
            
            if (childIndex == 0 && downstreamNodeID != -1)
                binaryTree.setLeftLink(upstreamNodeID, downstreamNodeID);
            
            if (childIndex == 1 && downstreamNodeID != -1)
                binaryTree.setRightLink(upstreamNodeID, downstreamNodeID);
            
            cptr = strtok(NULL, ",: ");
            childIndex++;
        }
        
        fileReader.getline(line, numCharsPerLine, '\n');
        
    }

    // Generating the data array
    int *dataArray = new int[numNodes];
            
    int maxValue;
    cout << "Enter the maximum value for an element: ";
    cin >> maxValue;
            
    srand(time(NULL));
            
    cout << "Data array generated: ";
            
    for (int index = 0; index < numNodes; index++){
        dataArray[index] = 1 + rand() % maxValue;
        cout << dataArray[index] << " ";
    }
            
    cout << endl;
    
    SelectionSort(dataArray, numNodes);
    
    cout << "Inorder traversal: " << endl;
    binaryTree.PrintInOrderTraversal(dataArray);
    
    cout << "Node(ID) Data " << endl;
    binaryTree.PrintNodeData();
    

    

    system("pause");
    
    return 0;
}
