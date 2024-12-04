#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

class SuffixTree {
public:
    struct Node {
        map<char, Node*> children;
        int start, *end;
        int suffixLink;

        Node(int start, int* end) : start(start), end(end), suffixLink(-1) {}
    };

    string text;
    Node* root;
    vector<Node*> nodes;

    SuffixTree(const string& s) {
        text = s;
        text += '$'; 
        root = new Node(-1, new int(-1));
        nodes.push_back(root);
        buildTree();
    }

    void buildTree() {
        int n = text.size();
        int* end = new int(-1);
        int activeLength = 0;
        int activeEdge = 0;
        int remaining = 0;
        int lastNewNode = -1;
        for (int i = 0; i < n; i++) {
            *end = i;
            remaining++;
            lastNewNode = -1;

            while (remaining > 0) {
                if (activeLength == 0) {
                    activeEdge = i;
                }

                if (root->children.find(text[activeEdge]) == root->children.end()) {
                    root->children[text[activeEdge]] = new Node(i, end);
                    nodes.push_back(root->children[text[activeEdge]]);

                    if (lastNewNode != -1) {
                        nodes[lastNewNode]->suffixLink = root->children[text[activeEdge]]->start;
                        lastNewNode = -1;
                    }
                } else {
                    Node* current = root->children[text[activeEdge]];
                    int length = *current->end - current->start + 1;
                    if (activeLength >= length) {
                        activeEdge += length;
                        activeLength -= length;
                        continue;
                    }
                    if (text[current->start + activeLength] == text[i]) {
                        activeLength++;
                        if (lastNewNode != -1) {
                            nodes[lastNewNode]->suffixLink = current->start;
                            lastNewNode = -1;
                        }
                        break;
                    }
                    int* splitEnd = new int(current->start + activeLength - 1);
                    Node* split = new Node(current->start, splitEnd);
                    nodes.push_back(split);
                    current->start += activeLength;
                    split->children[text[current->start]] = current;
                    nodes.push_back(split->children[text[current->start]]);
                    root->children[text[activeEdge]] = split;

                    split->children[text[i]] = new Node(i, end);
                    nodes.push_back(split->children[text[i]]);
                    if (lastNewNode != -1) {
                        nodes[lastNewNode]->suffixLink = split->start;
                    }
                    lastNewNode = split->start;
                }
                remaining--;
                if (root->suffixLink == -1) {
                    activeEdge = i + 1;
                    activeLength = 0;
                } else {
                    activeEdge = nodes[root->suffixLink]->start;
                    activeLength = *end - nodes[root->suffixLink]->start;
                }
            }
        }
    }

    bool search(const string& substring) {
        int n = substring.size();
        Node* current = root;
        for (int i = 0; i < n; i++) {
            if (current->children.find(substring[i]) == current->children.end()) {
                return false;
            }
            current = current->children[substring[i]];
        }
        return true;
    }
};

int main() {
    string inputString;
    cout << "Enter a string to build the Suffix Tree: ";
    getline(cin, inputString);

    SuffixTree tree(inputString);

    string searchString;
    cout << "Enter a substring to search: ";
    getline(cin, searchString);

    if (tree.search(searchString)) {
        cout << "The substring \"" << searchString << "\" is found in the string!" << endl;
    } else {
        cout << "The substring \"" << searchString << "\" is NOT found in the string!" << endl;
    }

    return 0;
}
