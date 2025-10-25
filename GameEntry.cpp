#include <iostream>

using namespace std;

class GameEntry{
public:
    GameEntry(const string& n = "", int s= 0);
    string getName() const;
    int getScore() const;
private:
    int score;
    string name;
};
GameEntry::GameEntry(const string& n,int s) : name(n), score(s){}

string GameEntry::getName() const { return name;}
int GameEntry::getScore() const {return score;}


class Scores{
public:
    Scores(int maxEnt = 10);
    ~Scores();
    void add(const GameEntry& e);
    GameEntry remove(int i);
private:
    int maxEntries;
    int numEntries;
    GameEntry* entries;
};

Scores::Scores(int maxEnt){
    maxEntries = maxEnt;
    entries = new GameEntry[maxEntries];
    numEntries = 0;
}

Scores::~Scores(){
    delete[] entries;
}

void Scores::add(const GameEntry& e){
    int newScore = e.getScore();
    if(numEntries == maxEntries){
        if(newScore <= entries[maxEntries-1].getScore())
        {
            return;
        }
    }else numEntries++;
    
    int i =  numEntries - 2;
    
    while(i >= 0 && entries[i].getScore() < newScore){
        entries[i+1] =entries[i];
        i--;
    }
    entries[i] = e;

}

GameEntry Scores::remove(int i){
    if(i < 0 || i >= numEntries) {} // throw
    GameEntry e = entries[i];
    for(int k = i + 1; k < numEntries; k++){
        entries[k - 1] = entries[k];
    }
    numEntries--;
    
    return e;
}
    
    

int main(){
    
}
