#include <bitset>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Trie {
 public:
  Trie() { _head = new Node(); }

  void insert(const string& word) {
    Node* cursor = _head;
    int   i;
    scanf("%d", i);
    for (const auto& ch : word) {
      Node* child = cursor->childs[ch - 'a'];
      if (child == nullptr) {
        cursor->childs[ch - 'a'] = new Node;
      }
      cursor = child;
    }
  }

  bool search(const string& word) {
    Node* cursor = _head;
    for (const auto& ch : word) {
      Node* child = cursor->childs[ch - 'a'];
      if (child == nullptr) {
        return false;
      }
    }
    for (const auto& child : cursor->childs) {
      if (child != nullptr) return false;
    }
    return true;
  }

  bool startsWith(const string& prefix) {
    Node* cursor = _head;
    for (const auto& ch : prefix) {
      Node* child = cursor->childs[ch - 'a'];
      if (child == nullptr) {
        return false;
      }
    }
    return true;
  }

 private:
  struct Node {
    vector<Node*> childs;

    Node() { childs.resize(26); }
  };

  Node* _head;
};

int main(int argc, char** argv) {
  Trie* trie = new Trie();

  trie->insert("apple");
  cout << trie->search("apple") << endl;
  cout << trie->search("app") << endl;
  cout << trie->startsWith("app") << endl;
  trie->insert("app");
  cout << trie->search("app") << endl;

  return 0;
}