#include "trie.h"
#include <iostream>
using namespace std;


int main()
{
    Trie trie;
    vector<string> v{"abcd", "bcde", "bd", "cab", "cda", "abd"};
    for (auto& s : v) {
        trie.Insert(s);
    }
    trie.OpenAC();
    cout<<trie.Size()<<endl;
    for (auto& s : v) {
        cout<<s<<" "<<trie.Find(s)<<endl;
        cout<<s.substr(0, 2)<<" "<<trie.StartWith(s.substr(0, 2))<<endl;
    }
    string str("abcdsdefbdsdcabcdabdc");
    cout<<trie.Query(str)<<endl;
    trie.CloseAC();
    cout<<trie.Query(str)<<endl;

}

