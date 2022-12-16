#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct StatWord {
    string   word;
    unsigned repeatCnt;
    bool operator<(const StatWord& e) {
        return repeatCnt < e.repeatCnt;
    }
};

class Collectable {
public:
    virtual vector<StatWord> collect() const = 0;
};

// TODO  TrieCollectable

// TODO  TreeCollectable

// prueba del collectable para analizar la ley de Zipf
void Zipf(const Collectable& c) {
    vector<StatWord> words = c.collect();
    sort(words.rbegin(), words.rend());

    cout << "Stats for words: " << endl;
    for (const auto& x : words)
        cout << x.word << " : " << x.repeatCnt << endl;
}

int main()
{
    ifstream in("palabras");

    TrieCollectable trieColl;
    TreeCollectable treeColl;

    string s;
    while (in >> s) {
        trieColl.insertKey(s.c_str());
        treeColl.addWord(s);
    }

    cout << "con TrieCollectable: " << endl;
    Zipf(trieColl);

    cout << "con TreeCollectable: " << endl;
    Zipf(treeColl);

    return 0;

}


