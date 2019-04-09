
#ifndef HEAP_HPP
#define HEAP_HPP

#include <string>
#include <cstring>
#include <vector>

// a struct to store information about a meme
struct meme{
    std::string Title;
    int UpVotes;
    int Time;
    std::string URL;
};


class PriorityQueue{

public:
    PriorityQueue();
    ~PriorityQueue();
    void enqueue (std::string _Title, int _UpVotes, int _Time, std::string _URL);
    void dequeue();
    meme peek();
    bool isEmpty();
    void arrDouble();

private:
    void repairUpward(int nodeIndex);
    void repairDownward(int nodeIndex);
    int currentQueueSize; //number of memes currently in the priority queue
    int maxSize;
    meme *priorityQueue;
};

#endif