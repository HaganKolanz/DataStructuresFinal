#include "heap.hpp"
#include <iostream>
using namespace std;

PriorityQueue::PriorityQueue(){
    currentQueueSize = 0;
}
PriorityQueue::~PriorityQueue(){
}

int left(int i){return ((2*i)+1);}//left child begin at 0
int right(int i){return ((2*i) + 2);}//right child begin at 0
int parent(int i) { return (i)/2;}//parent with index start at 0
void swap(meme *x, meme *y){
    meme temp = *x;
    *x = *y;
    *y = temp;
}

void PriorityQueue::repairDownward(int nodeIndex){
    int l = left(nodeIndex);
    int r = right(nodeIndex);//store the variables
    int biggest = nodeIndex;
    if(l < currentQueueSize && (priorityQueue[l])->UpVotes > (priorityQueue[nodeIndex])->UpVotes)
        biggest = l;//left one has bigger group size
    if(l < currentQueueSize && (priorityQueue[l])->UpVotes == (priorityQueue[nodeIndex])->UpVotes
    && (priorityQueue[l])->Time > (priorityQueue[nodeIndex])->Time)
        biggest = l;//size equal but the left has bigger time (more recent)
    if(r < currentQueueSize && (priorityQueue[r])->UpVotes > (priorityQueue[biggest])->UpVotes)
        biggest = r;//the right has more upvotes
    if(r < currentQueueSize && (priorityQueue[r])->UpVotes == (priorityQueue[biggest])->UpVotes 
    &&(priorityQueue[r])->Time > (priorityQueue[biggest])->Time)
        biggest = r;//size equal but the right has bigger time (more recent)
    if(biggest != nodeIndex){//things were swapped
        swap(&(*priorityQueue[nodeIndex]), &(*priorityQueue[biggest]));
        repairDownward(biggest);//recursive call
    }
}

void PriorityQueue::repairUpward(int nodeIndex){
    int sizeP = priorityQueue[parent(nodeIndex)]->UpVotes;
    int sizeI = priorityQueue[nodeIndex]->UpVotes;
    int CsizeP = priorityQueue[parent(nodeIndex)]->Time;
    int CsizeI = priorityQueue[nodeIndex]->Time;//store the variables we are going to compare
    bool stop = false;//to stop the loop while it's no longer needed
    while(nodeIndex != 0 && !stop){
        if(sizeP < sizeI){
            swap(&(*priorityQueue[nodeIndex]), &(*priorityQueue[parent(nodeIndex)]));
            nodeIndex = parent(nodeIndex);//if the group size is less swap it
        }
        else if(sizeP == sizeI){
            while(nodeIndex != 0 && !stop){
                if(CsizeP < CsizeI && sizeP == sizeI){
                    swap(&(*priorityQueue[nodeIndex]), &(*priorityQueue[parent(nodeIndex)]));
                    nodeIndex = parent(nodeIndex);//the size is the same but time needs swaping
                }
                else{
                    stop = true;//nothing else needs swaping
                }
                //update the variables
                sizeP = priorityQueue[parent(nodeIndex)]->UpVotes;
                sizeI = priorityQueue[nodeIndex]->UpVotes;
                CsizeP = priorityQueue[parent(nodeIndex)]->Time;
                CsizeI = priorityQueue[nodeIndex]->Time;
            }
        }
        else{
            stop = true;//nothing else needs swaping then
        }
        //update the variables
        sizeP = priorityQueue[parent(nodeIndex)]->UpVotes;
        sizeI = priorityQueue[nodeIndex]->UpVotes;
        CsizeP = priorityQueue[parent(nodeIndex)]->Time;
        CsizeI = priorityQueue[nodeIndex]->Time;
    }
}

void PriorityQueue::enqueue(std::string _Title, int _UpVotes, int _Time, std::string _URL){
   
    meme *n;
    currentQueueSize++;
    n->Time = _Time;
    n->Title = _Title;
    n->UpVotes = _UpVotes;
    n->URL = _URL;
    priorityQueue.push_back(n);//set the value 
    repairUpward(currentQueueSize-1);//re order from the one you inserted
}

void PriorityQueue::dequeue(){
    if(currentQueueSize == 0){
        cout << "Heap empty, cannot dequeue" << endl;//make sure its not empty
    }
    else{
        if(currentQueueSize == 1){
            currentQueueSize--;//if there is only one in there then just decrease the size
            priorityQueue.pop_back();
        }
        else{
            priorityQueue[0] = priorityQueue[currentQueueSize - 1];//put the last one first
            priorityQueue.pop_back();
            currentQueueSize--;//decrease the size
            repairDownward(0);//re order the array
        }
    
    }
}

meme *PriorityQueue::peek(){
    if(currentQueueSize == 0){
        cout << "Heap empty, nothing to peek" << endl;
        
    }
        return priorityQueue[0];//the one on top
}

bool PriorityQueue::isEmpty(){
    if(currentQueueSize == 0){
        return true;//if empty
    }
    else{
        return false;
    }
}