#include "trie.h"
#include <queue>

using namespace std;


Trie::Trie()
: root_(new node()),
  ACautomaton_(false),
  size_(0)
{}

Trie::~Trie()
{
    if (root_)
        delete root_;
}

void Trie::Insert(const string& s)
{
    if (!root_) {
        root_ = new node();
    }
    node* now = root_;
    for (char c: s) {
        int id = c - 'a';
        if (!now->children_[id]) {
            now->children_[id] = new node();
        }
        now = now->children_[id];
        now->val_ = c;
    }
    now->end_ = true;
    ++size_;
    // if (ACautomaton_) GetFail();
}

bool Trie::StartWith(const string& s) const
{
    if (!root_) {
        return false;
    }
    node* now = root_;
    for (char c : s) {
        int id = c - 'a';
        if (!now->children_[id]) {
            return false;
        } else {
            now = now->children_[id];
        }
    }
    return true;
}

bool Trie::Find(const string& s) const
{
    if (!root_) {
        return false;
    }
    node* now = root_;
    for (char c : s) {
        int id = c - 'a';
        if (!now->children_[id]) {
            return false;
        } else {
            now = now->children_[id];
        }
    }
    return now->end_;
}

int Trie::Query(const string& s) const
{
    if (!root_) {
        return 0;
    }
    if (!ACautomaton_) {
        return NormalQuery(s);
    }
    int res = 0;
    node* now = root_;
    for (char c : s) {
        if (now->end_) {
            ++res;
            now = root_;
        }
        int id = c - 'a';
        if (!now->children_[id]) {
            if (now != root_) {
                now = now->fail_;
            }
        } else {
            now = now->children_[id];
        }
    }
    return res;
}

int Trie::NormalQuery(const string& s) const {
    if (!root_) {
        return 0;
    }
    int res = 0;
    node* now = root_;
    int i = 0;
    int last = 0;
    while (i < s.size()) {
        if (now->end_) {
            ++res;
            now = root_;
            last = i;
        }
        int id = s[i] - 'a';
        if (!now->children_[id]) {
            now = root_;
            i = ++last;
        } else {
            now = now->children_[id];
            ++i;
        }
    }
    return res;
}

void Trie::GetFail()
{
    if (!root_) return;
    queue<node*> q;
    for (node* temp : root_->children_) {
        if (temp) {
            temp->fail_ = root_;
            q.push(temp);
        }
    }
    while(!q.empty()) {
        node* now = q.front();
        q.pop();
        for (int i = 0; i < now->children_.size(); ++i) {
            node* child = now->children_[i];
            if (child) {
                node* temp = now->fail_;
                while(temp) {
                    if (temp->children_[i]) {
                        child->fail_ = temp->children_[i];
                        break;
                    }
                    temp = temp->fail_;
                }
                if (!temp) {
                    child->fail_ = root_;
                } 
                q.push(child);
            }
        }
    }
}
