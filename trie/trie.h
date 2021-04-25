#include <vector>
#include <string>
#include <iostream>

using namespace std;

struct node
{
    char val_;
    vector<node*> children_;
    bool end_;
    node* fail_;

    node()
    : children_(26, NULL),
      end_(false),
      fail_(NULL)
    {}
    ~node() {
        for (int i = 0; i < children_.size(); ++i) {
            if (children_[i]) {
                delete children_[i];
            }
        }
        // cout<<"delete node: " << val_<<endl;
    }
};


class Trie {
public:
    Trie();
    ~Trie();

    bool Find(const string& ) const;
    bool StartWith(const string& ) const;
    int Query(const string& ) const;

    void Insert(const string& );

    void OpenAC() { ACautomaton_ = true; GetFail(); }
    void CloseAC() { ACautomaton_ = false; }

    size_t Size() { return size_; }

private:
    void GetFail();
    int NormalQuery(const string& s) const;

private:
    node* root_;
    bool ACautomaton_;
    size_t size_;
};
