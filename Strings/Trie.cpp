/*
 * Descripcion: Un trie es una estructura de datos de arbol
 * multidireccional que se utiliza para almacenar cadenas en
 * un alfabeto. La coincidencia de patrones se puede
 * realizar de manera eficiente usando trie
 * Tiempo: O(n)
 */

struct TrieNode {
  unordered_map<char, TrieNode *> children;
  bool isEndOfWord;
  int numPrefix;

  TrieNode() : isEndOfWord(false), numPrefix(0) {}
};

class Trie {
 private:
  TrieNode *root;

 public:
  Trie() { root = new TrieNode(); }

  void insert(string word) {
    TrieNode *curr = root;
    for (char c : word) {
      if (curr->children.find(c) == curr->children.end()) {
        curr->children[c] = new TrieNode();
      }
      curr = curr->children[c];
      curr->numPrefix++;
    }
    curr->isEndOfWord = true;
  }

  bool search(string word) {
    TrieNode *curr = root;
    for (char c : word) {
      if (curr->children.find(c) == curr->children.end()) {
        return false;
      }
      curr = curr->children[c];
    }
    return curr->isEndOfWord;
  }

  bool startsWith(string prefix) {
    TrieNode *curr = root;
    for (char c : prefix) {
      if (curr->children.find(c) == curr->children.end()) {
        return false;
      }
      curr = curr->children[c];
    }
    return true;
  }

  int countPrefix(string prefix) {
    TrieNode *curr = root;
    for (char c : prefix) {
      if (curr->children.find(c) == curr->children.end()) {
        return 0;
      }
      curr = curr->children[c];
    }
    return curr->numPrefix;
  }
};
