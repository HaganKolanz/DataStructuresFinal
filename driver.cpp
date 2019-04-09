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
                cout<<title<<endl;
                PQ.enqueue(title, upvote, Time, url);
                cout<<"fuck"<<endl;
                counter = 0;
            }
        }
    }
}
int main(){
    PriorityQueue PQ;//open queue
    cout<<"here"<<endl;
    addFile(PQ);
    ofstream file;
    cout<<"here1"<<endl;
    file.open("memes.html");
    if(file.is_open()){
        cout<<"here2"<<endl;
        file << "<!DOCTYPE html>\n <html>\n <body>\n";
        cout<<"here3"<<endl;
        while(!PQ.isEmpty()){
            cout<<"here4"<<endl;
            meme p = PQ.peek();
            cout<<p.Title<<endl;
            file << "<h2>" << p.Title << "</h2>\n";
            cout<<p.Title<<endl;
            file << "<img src=\"" << p.URL << "\" alt=\"MEME\">\n";
            cout<<p.URL<<endl;
            PQ.dequeue();
            cout<<"here5"<<endl;
        }
        file << "</body>\n </html>";
    }
    else{
        cout << "could not open file" << endl;
    }

}