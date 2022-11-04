#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct StatWords {
    struct StatRecord{
        string word;
        unsigned int repCnt;
    };
    vector<StatRecord> records;

    void addWord(const string &word){
        bool flag = false;
        for(auto &record : records){
            if(record.word == word){    //Si encuentro incremento y rompo
                record.repCnt++;
                flag = true;
                break;
            }
        }
        if(!flag){ records.push_back({word, 1});}   //Si no encuentro lo agrego con rep = 1
        return;
    }
    void print(){
        for(auto &record : records){ cout << "word: " << record.word << " rep: " << record.repCnt << endl; }

        return;
    }

};


int main() {
    StatWords stats;
    string w;

    while (cin >> w)
        stats.addWord(w);

    stats.print();
    return 0; 
}