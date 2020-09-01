#include <iostream>
#include <stdlib.h>
#include <time.h>
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



class BinarySearchTree{
    
    private:
        int numNodes;
        BTNode* arrayOfBTNodes;
        int rootNodeID;

        
    public:
    
        BinarySearchTree(int n){
            numNodes = n;
            arrayOfBTNodes = new BTNode[numNodes];
            
            for (int index = 0; index < numNodes; index++){
                
                arrayOfBTNodes[index].setNodeId(index);
                arrayOfBTNodes[index].setLeftChildPtr(0);
                arrayOfBTNodes[index].setRightChildPtr(0);
                arrayOfBTNodes[index].setLevelNum(-1);
                
            }
        }
    
    
        void setLeftLink(int upstreamNodeID, int downstreamNodeID){
            arrayOfBTNodes[upstreamNodeID].setLeftChildPtr(&arrayOfBTNodes[downstreamNodeID]);
        }
        
        void setRightLink(int upstreamNodeID, int downstreamNodeID){
            arrayOfBTNodes[upstreamNodeID].setRightChildPtr(&arrayOfBTNodes[downstreamNodeID]);
        }
    
    
        void constructBSTree(){
            
            int leftIndex = 0;
            int rightIndex = numNodes-1;
            int middleIndex = (leftIndex + rightIndex)/2;
            
            rootNodeID = middleIndex;
            
            ChainNodes(middleIndex, leftIndex, rightIndex);
            
        }
    
    
        void ChainNodes(int middleIndex, int leftIndex, int rightIndex){
            
            if (leftIndex < middleIndex){
                int rootIDLeftSubtree = (leftIndex + middleIndex-1)/2;
                setLeftLink(middleIndex, rootIDLeftSubtree);
                ChainNodes(rootIDLeftSubtree, leftIndex, middleIndex-1);
            }
            
            
            if (rightIndex > middleIndex){
                int rootIDRightSubtree = (rightIndex + middleIndex + 1)/2;
                setRightLink(middleIndex, rootIDRightSubtree);
                ChainNodes(rootIDRightSubtree, middleIndex+1, rightIndex);
            }
            
            
        }
    
        
                
        void assignLevelNumbers(){
            
            Queue queue;
            queue.enqueue(rootNodeID);
            arrayOfBTNodes[rootNodeID].setLevelNum(0);
            
            while (!queue.isEmpty()){
                
                int firstNodeInQueue = queue.dequeue();
                
                int leftChildID = arrayOfBTNodes[firstNodeInQueue].getLeftChildID();
                if (leftChildID != -1){
                    queue.enqueue(leftChildID);
                    arrayOfBTNodes[leftChildID].setLevelNum(arrayOfBTNodes[firstNodeInQueue].getLevelNum()+1);
                }
                
                int rightChildID = arrayOfBTNodes[firstNodeInQueue].getRightChildID();
                if (rightChildID != -1){
                    queue.enqueue(rightChildID);
                    arrayOfBTNodes[rightChildID].setLevelNum(arrayOfBTNodes[firstNodeInQueue].getLevelNum()+1);
                }
                
            }
            
                    
        }
    
    
        int getDepth(int nodeid){
            return arrayOfBTNodes[nodeid].getLevelNum();
        }

    
    
        bool isAPureInternalNode(int id){

            if (arrayOfBTNodes[id].getLeftChildPtr() != 0 && arrayOfBTNodes[id].getRightChildPtr() != 0)
                return true;
            
            return false;
            
        }
        
        
        bool isALeafNode(int id){
            
            if (arrayOfBTNodes[id].getLeftChildPtr() == 0 && arrayOfBTNodes[id].getRightChildPtr() == 0)
                return true;
            
            return false;
            
            
        }
    
    int GetNodeCountAtLevel(int level) {
        // This function loops through all nodes. Theta(n)
        // If the given level matches the current node level
        // increment nodecounter. If all the nodes are  loop
        // through and none of the nodes match the given level
        // return -1
        int nodeCount = 0, index = 0;
        
        while(index < numNodes) {
            int currentNodeLevel = getDepth(index);
            
            if(level == currentNodeLevel)
                nodeCount++;

            index++;
        }
        
        if(nodeCount == 0)
            return -1;
        
        return nodeCount;
    }
    
};

double FindAverageForSuccessfulSearch(BinarySearchTree& bsTree, const int numElements) {
    
    int index = 0;
    double resultForSuccessfulSearch = 0;
    
    while(index < numElements) {
        // This function gets all nodes at the given level
        int nodesAtLevel = bsTree.GetNodeCountAtLevel(index);
        
        // If this variable is -1, there are no more nodes.
        if(nodesAtLevel == -1) break;
        
        if(index % 2 == 0) { // Determines to add or multiply
            resultForSuccessfulSearch += (index * nodesAtLevel);
        } else {
            resultForSuccessfulSearch *= (index  * nodesAtLevel);
        }
        
        index++;
    }
    
    return resultForSuccessfulSearch / numElements;
}

double FindAverageForUnsuccessfulSearch(BinarySearchTree& bsTree, const int numElements) {
    double resultForUnsuccessfulSearch = 0;
    
    int leafNodesComparisonSum = 0, semiInternalNodesComparisonSum = 0;
    int leafNodeCount = 0, semiInternalNodeCount = 0;
    
    for(int id = 0; id < numElements; id++) { // Loop through all nodes
        if(bsTree.isALeafNode(id)) { // If is a leaf node
            int comparison = bsTree.getDepth(id) + 1;
            leafNodesComparisonSum += comparison;
            leafNodeCount++;
        } else if(!bsTree.isAPureInternalNode(id) && !bsTree.isALeafNode(id)) { // If semi-internal node
            int comparison = bsTree.getDepth(id) + 1;
            semiInternalNodesComparisonSum += comparison;
            semiInternalNodeCount++;
        }
    }
    
    int numerator = (2 * leafNodesComparisonSum) + (1 * semiInternalNodesComparisonSum);
    int denumerator = (2 * leafNodeCount) + (1 * semiInternalNodeCount);
    resultForUnsuccessfulSearch = numerator / denumerator;
    
    return resultForUnsuccessfulSearch;
}


int main(){
    
    for (int numElements = 100000; numElements <= 100000; numElements *= 10){
        
        BinarySearchTree bsTree(numElements);
        bsTree.constructBSTree();
        bsTree.assignLevelNumbers(); // Assigning level numbers

        // Add the necessary code here to determine and print
        // the average number of comparisons for a successful search and for an unsuccessful search
        
        
        // Successful search
        std::cout << "Number elements: " << numElements << std::endl << std::endl;
        std::cout << "Successful search: ";
        double successfulSearchAverage = FindAverageForSuccessfulSearch(bsTree, numElements);
        std::cout << successfulSearchAverage << std::endl;
  
        std::cout << "Unsuccessful search: ";
        double unsuccessfulSearchAverage = FindAverageForUnsuccessfulSearch(bsTree, numElements);
        std::cout << unsuccessfulSearchAverage << std::endl << std::endl;
        
        // Unsuccessful seach
        
        
        
    }// numElements loop

    
    system("pause");
    
    return 0;
}
