#include <iostream>
#include <fstream>
#include <string>
#include <cstring> // for string tokenizer and c-style string processing
#include <algorithm> // max function

#include <ctime>
#include <ratio>
#include <chrono>

using namespace std;


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



class BTNode{
    
    private:
        int nodeid;

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
    
    

        
        
        
        void recursivePreOrderTraversal(){
            
            preOrderTraversal(0);
            //cout << endl;
            
        }
        
        
        void preOrderTraversal(int nodeid){
            
            if (nodeid == -1)
                return;
            
            preOrderTraversal(arrayOfBTNodes[nodeid].getLeftChildID());
            preOrderTraversal(arrayOfBTNodes[nodeid].getRightChildID());
            
        }
    
    
    
    void IterativePreOrderTraversalUsingStack(){
        
        // Implement here the code for the iterative procedure to
        // do preorder traversal of the binary tree using a Stack...
        
        
        
        
        if(numNodes < 1) return;
        
        Stack nodeStack = Stack();
        BTNode* currentNode = &arrayOfBTNodes[0];
        // Loop through will current node
        // if node has a right side push it to the stack
        // Once last left node is reached
        // make current node the pop node
        // Repeat process
        
        while(currentNode) { // While there is a node in array of nodes.
            if(currentNode->getRightChildPtr()) { // Check if the node has a right child.
                nodeStack.push(currentNode->getRightChildPtr()->getNodeId()); // if so, add it to the stack
            }
            
           // std::cout << currentNode->getNodeId() << std::endl; // print current node id
            currentNode = currentNode->getLeftChildPtr(); // Set current node equal to its left child
             
            if(currentNode == nullptr) { // If the new current node is null
                if(!nodeStack.isEmpty()) // and if the node stack is not empty
                    currentNode = &arrayOfBTNodes[nodeStack.pop()]; // Pop the last right node that was pushed unto the stack.
            }
        }
    }
};



int main(){
    
    string treeEdgesFilename;
    cout << "Enter the file name for the edges of the tree: ";
    cin >> treeEdgesFilename;
    
    int numNodes;
    cout << "Enter number of nodes: ";
    cin >> numNodes;
    
    
    BinaryTree binaryTree(numNodes);
    
    ifstream treeEdgeFileReader(treeEdgesFilename);
    
    if (!treeEdgeFileReader){
        cout << "File cannot be opened!! ";
        return 0;
    }

    int numCharsPerLine = 25;
    
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

    
    
    using namespace std::chrono;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    
    binaryTree.recursivePreOrderTraversal();
    
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double, std::micro> processingTime_micro = t2 - t1;
    
    cout << "Processing time (microseconds, recursive): " << processingTime_micro.count() << endl;

    
    t1 = high_resolution_clock::now();
    binaryTree.IterativePreOrderTraversalUsingStack();
    t2 = high_resolution_clock::now();
    processingTime_micro = t2 - t1;
    
    cout << "Processing time (microseconds, iterative): " << processingTime_micro.count() << endl;

    
    return 0;
}
