#include <iostream>
#include <fstream>
#include <string>
#include <cstring> // for string tokenizer and c-style string processing
#include <algorithm> // max function
#include <stack>
using namespace std;

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



class Node{
    
    private:
        int data;
        Node* nextNodePtr;
        Node* prevNodePtr;
        
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
        
        void setPrevNodePtr(Node* nodePtr){
                prevNodePtr = nodePtr;
        }
        
        Node* getPrevNodePtr(){
            return prevNodePtr;
        }
        
};

class Queue{

    private:
        Node* headPtr;
        Node* tailPtr;

    
    public:
        Queue(){
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
        
        
        void enqueue(int data){
            
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

        
        int dequeue(){
            
            Node* firstNodePtr = headPtr->getNextNodePtr();
            Node* nextNodePtr = 0;
            
            int poppedData = -100000; //empty queue
            
            if (firstNodePtr != 0){
                nextNodePtr = firstNodePtr->getNextNodePtr();
                poppedData = firstNodePtr->getData();
            }
            else
                return poppedData;
            
            if (nextNodePtr != 0){
                nextNodePtr->setPrevNodePtr(0);
                headPtr->setNextNodePtr(nextNodePtr);
            }
            else{
                headPtr->setNextNodePtr(0);
                tailPtr->setPrevNodePtr(0);
            }

            return poppedData;
            
        }
        
        
        int peek(){
            
            Node* firstNodePtr = headPtr->getNextNodePtr();
            
            if (firstNodePtr != 0)
                return firstNodePtr->getData();
            else
                return -100000; //empty queue
                
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
        
        
        void push(int data){
            
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

        
        int pop(){
            
            Node* lastNodePtr = tailPtr->getPrevNodePtr();
            Node* prevNodePtr = 0;
            
            int poppedData = -100000; //empty stack
            
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
        
        
        int peek(){
            
            Node* lastNodePtr = tailPtr->getPrevNodePtr();
            
            if (lastNodePtr != 0)
                return lastNodePtr->getData();
            else
                return -100000; //  empty stack
        
            
        }
      
};



class BinaryTree{
    
    private:
        int numNodes;
        int rootNodeID;
        BTNode* arrayOfBTNodes;
        
    public:
    
        BinaryTree(int n){
            numNodes = n;
            arrayOfBTNodes = new BTNode[numNodes];
            rootNodeID = 0;
            
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
        
        void setNodeData(int nodeid, int data){
            arrayOfBTNodes[nodeid].setData(data);
        }

        int getNodeData(int nodeid){
            return arrayOfBTNodes[nodeid].getData();
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
    
        int getNodeHeight(int nodeid){
            
            if (nodeid == -1 || isLeafNode(nodeid) )
                return 0;
            
            int leftChildID = arrayOfBTNodes[nodeid].getLeftChildID(); // -1 if not exist
            int rightChildID = arrayOfBTNodes[nodeid].getRightChildID(); // -1 if not exist
    
            return max(getNodeHeight(leftChildID), getNodeHeight(rightChildID)) + 1;
                        
        }
    
    
        int getTreeHeight(){
            return getNodeHeight(0);
        }
    

    bool isEssentiallyComplete(){
        Queue queue;
        queue.enqueue(0);
        bool noChildStartZone = false;
        
        while(!queue.isEmpty()) {
            int firstNodeID = queue.dequeue();
            BTNode* firstNode = &arrayOfBTNodes[firstNodeID];
            
            if(noChildStartZone == false && firstNode->getLeftChildID() == -1)
                noChildStartZone = true;
            else if(noChildStartZone == true && firstNode->getLeftChildID() != -1)
                return false;
            
            if(firstNode->getLeftChildID() != -1)
                queue.enqueue(firstNode->getLeftChildID());
            
            if(noChildStartZone == false && firstNode->getRightChildID() == -1)
                noChildStartZone = true;
            else if(noChildStartZone == true && firstNode->getRightChildID() != -1)
                return false;
                
            if(firstNode->getRightChildID() != -1)
                queue.enqueue(firstNode->getRightChildID());
        }
        
        return true;
    }
    
    bool isMaxHeap(){

        if(!isEssentiallyComplete()) return false;
        BTNode* currentNode = &arrayOfBTNodes[0]; // Making the first node the current node

        std::stack<int> rightNodes; // Will store all nodes to right side


        while(currentNode) { // While there is a node in treex

            int currentNodeData = currentNode->getData(); // Store current node data
            int leftNodeData = currentNode->getLeftChildPtr() ? currentNode->getLeftChildPtr()->getData() : -1; // left node exists, get its data
            int rightNodeData = currentNode->getRightChildPtr() ? currentNode->getRightChildPtr()->getData() : -1; // left node exists, get its data

            

            if(rightNodeData != -1) // If there is a right node
                rightNodes.push(currentNode->getRightChildID());

            

            if(leftNodeData != -1) { // If left node is not null

                

                if(leftNodeData <= currentNodeData) { // If the child data is less than parent data

                    

                    currentNode = currentNode->getLeftChildPtr(); // Set the current node to left node

                    

                    if(!currentNode) // If there is no left node

                        if(!rightNodes.empty()){ // And the right node stack is not empty

                            currentNode = &arrayOfBTNodes[rightNodes.top()]; // Set the current node to the last right node that was entered into the stack.

                            rightNodes.pop();

                        }

                } else { // Left node data is greater than parent data

                    return false; // Is not a max heap.

                }

                

            } else { // If there is left node

                if(!rightNodes.empty()) {

                    currentNode = &arrayOfBTNodes[rightNodes.top()]; // Set the current node to the last right node that was entered into the stack.

                    rightNodes.pop();

                }  else {

                    currentNode = nullptr; // There is no more checking to do, hence it is a max heap.
                }
            }
        }
        return true;

    }

};



int main(){
    
    string treeEdgesFilename;
    cout << "Enter the file name for the edges of the tree: ";
    cin >> treeEdgesFilename;
    
    int numNodes;
    cout << "Enter number of nodes: ";
    cin >> numNodes;
    
    string treeDataFilename;
    cout << "Enter the file name for the data of the nodes: ";
    cin >> treeDataFilename;
    
    BinaryTree binaryTree(numNodes);
    
    ifstream treeEdgeFileReader(treeEdgesFilename);
    
    if (!treeEdgeFileReader){
        cout << "File cannot be opened!! ";
        return 0;
    }

    int numCharsPerLine = 10;
    
    char *line = new char[numCharsPerLine];
    // '10' is the maximum number of characters per line
    
    treeEdgeFileReader.getline(line, numCharsPerLine, '\n');
    // '\n' is the delimiting character to stop reading the line
        
    while (treeEdgeFileReader){
            
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
        
        treeEdgeFileReader.getline(line, numCharsPerLine, '\n');
        
    }

    
    
    ifstream treeDataFileReader(treeDataFilename);
    treeDataFileReader.getline(line, numCharsPerLine, '\n');
    // '\n' is the delimiting character to stop reading the line
        
    while (treeDataFileReader){
            
        char* cptr = strtok(line, " ");
        
        string nodeidToken(cptr);
        int nodeid = stoi(nodeidToken);
        
        cptr = strtok(NULL, " ");
        
        string dataToken(cptr);
        int data = stoi(dataToken);
        
        binaryTree.setNodeData(nodeid, data);
        
        treeDataFileReader.getline(line, numCharsPerLine, '\n');
        
    }
    
    
    if (binaryTree.isEssentiallyComplete()){
        if (binaryTree.isMaxHeap()){
            cout << "The binary tree is essentially complete and a Max heap!!" << endl;
        }
        else{
            cout << "The binary tree is essentially complete, but not a Max heap" << endl;
        }
    }
    else{
        cout << "The binary tree is not essentially complete; hence it is not a Max heap " << endl;
    }
    
    
    system("pause");
    
    return 0;
}

