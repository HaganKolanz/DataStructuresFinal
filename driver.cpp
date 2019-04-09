#include <iostream>
#include <fstream>
#include "heap.hpp"
using namespace std;

void addFile(PriorityQueue &PQ){
    ifstream my_file;
    string part;
    string line;
    my_file.open("memes.txt");//open file
    if(!my_file.is_open()){
        cout << "Failed to open the file." << endl;//if can't open
    }
    else{
        int count = 0;
        string url;
        int upvote, Time;
        string title;
        int counter = 0;
        while(getline(my_file, line)){
            if(counter == 0){
                title = line;
                counter++;
            }
            else if(counter == 1){
                url = line;
                counter++;
            }
            else if(counter == 2){
                upvote = stoi(line);
                counter++;
            }
            else{
                Time = stoi(line);
                PQ.enqueue(title, upvote, Time, url);
                counter = 0;
            }
        }
    }
}
int main(){
    PriorityQueue PQ;//open queue
    addFile(PQ);
    ofstream file;
    file.open("memes.html");
    if(file.is_open()){
        file << "<!DOCTYPE html>\n <html>\n <body>\n";
        while(!PQ.isEmpty()){

            meme *p = PQ.peek();
            file << "<h2>" << p->Title << "</h2>\n";
            file << "<img src=\"" << p->URL << "\" alt=\"MEME\">\n";
            PQ.dequeue();
        }
        file << "</body>\n </html>"; 
    }
    else{
        cout << "could not open file" << endl;
    }

}