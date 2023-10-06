#include <iostream>
#include <vector>

using namespace std;

struct TrieNode {
  bool isLeaf;
  TrieNode* children[256];
};

TrieNode* getNewTrieNode() {
  TrieNode* node = new TrieNode();
  node->isLeaf = false;
  for (int i = 0; i < 26; i++) {
    node->children[i] = nullptr;
  }
  return node;
}

void insertWord(TrieNode* root, string word) {
  TrieNode* node = root;
  for (int i = 0; i < word.length(); i++) {
    int index = word[i] - 'A';
    if (node->children[index] == nullptr) {
      node->children[index] = getNewTrieNode();
    }
    node = node->children[index];
  }
  node->isLeaf = true;
}

bool searchWord(TrieNode* root, string pattern) {
  TrieNode* node = root;
  for (int i = 0; i < pattern.length(); i++) {
    int index = pattern[i] - 'A';
    if (node->children[index] == nullptr) {
      return false;
    }
    node = node->children[index];
  }
  return node->isLeaf;
}

vector<string> findAllWords(TrieNode* root, string pattern) {
  vector<string> words;
  TrieNode* node = root;
  for (int i = 0; i < pattern.length(); i++) {
    int index = pattern[i] - 'A';
    if (node->children[index] == nullptr) {
      break;
    }
    node = node->children[index];
  }

  if (node->isLeaf) {
    words.push_back(pattern);
  }

  for (int i = 0; i < 26; i++) {
    if (node->children[i] != nullptr) {
      vector<string> new_words = findAllWords(node->children[i], pattern + (char)(i + 1));
      words.insert(words.end(), new_words.begin(), new_words.end());
    }
  }

  return words;
}

int main() {
  TrieNode* root = getNewTrieNode();
  insertWord(root, "HelloWorld");
  insertWord(root, "GeeksForGeeks");
  insertWord(root, "CodeBlocks");
  insertWord(root, "PowerPoint");
  insertWord(root, "WikiPedia");

  string pattern = "HW";
  vector<string> words = findAllWords(root, pattern);
  for (string word : words) {
    cout << word << endl;
  }

  return 0;
}
