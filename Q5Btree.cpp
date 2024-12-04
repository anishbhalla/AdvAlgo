#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class BTreeNode {
public:
    vector<int> keys;
    vector<BTreeNode*> children;
    bool leaf;
    int t; 

    BTreeNode(int degree, bool isLeaf);

    void insertNonFull(int key);

    void splitChild(int i, BTreeNode* y);

    void remove(int key);

    
    void removeFromLeaf(int idx);

    void removeFromNonLeaf(int idx);

    int findKey(int key);

    void traverse();
};

class BTree {
public:
    BTreeNode* root;
    int t;  

    BTree(int degree) {
        root = nullptr;
        t = degree;
    }

    void insert(int key);
    void remove(int key);

    void traverse() {
        if (root != nullptr) root->traverse();
    }
};

BTreeNode::BTreeNode(int degree, bool isLeaf) {
    t = degree;
    leaf = isLeaf;
}

void BTreeNode::insertNonFull(int key) {
    int i = keys.size() - 1;

    if (leaf) {
        keys.push_back(0);
        while (i >= 0 && keys[i] > key) {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = key;
    } else {
        while (i >= 0 && keys[i] > key) i--;
        if (children[i + 1]->keys.size() == 2 * t - 1) {
            splitChild(i + 1, children[i + 1]);
            if (keys[i + 1] < key) i++;
        }
        children[i + 1]->insertNonFull(key);
    }
}

void BTreeNode::splitChild(int i, BTreeNode* y) {
    BTreeNode* z = new BTreeNode(y->t, y->leaf);
    z->keys.resize(t - 1);
    for (int j = 0; j < t - 1; j++) z->keys[j] = y->keys[j + t];
    if (!y->leaf) z->children.resize(t);
    for (int j = 0; j < t; j++) z->children[j] = y->children[j + t];
    y->keys.resize(t - 1);
    children.insert(children.begin() + i + 1, z);
    keys.insert(keys.begin() + i, y->keys[t - 1]);
}

void BTree::insert(int key) {
    if (root == nullptr) {
        root = new BTreeNode(t, true);
        root->keys.push_back(key);
    } else {
        if (root->keys.size() == 2 * t - 1) {
            BTreeNode* s = new BTreeNode(t, false);
            s->children.push_back(root);
            s->splitChild(0, root);
            int i = (s->keys[0] < key) ? 1 : 0;
            s->children[i]->insertNonFull(key);
            root = s;
        } else {
            root->insertNonFull(key);
        }
    }
}

void BTreeNode::remove(int key) {
    int idx = findKey(key);
    if (idx < keys.size() && keys[idx] == key) {
        if (leaf)
            removeFromLeaf(idx);
        else
            removeFromNonLeaf(idx);
    } else {
        if (leaf) {
            cout << "Key " << key << " is not in the tree\n";
            return;
        }
        bool lastChild = (idx == keys.size());
        if (children[idx]->keys.size() < t)
            children[idx]->keys.resize(t);
        if (lastChild && idx > keys.size())
            children[idx - 1]->remove(key);
        else
            children[idx]->remove(key);
    }
}

void BTreeNode::removeFromLeaf(int idx) {
    keys.erase(keys.begin() + idx);
}

void BTreeNode::removeFromNonLeaf(int idx) {
    int k = keys[idx];
    if (children[idx]->keys.size() >= t) {
        int pred = children[idx]->keys.back();
        keys[idx] = pred;
        children[idx]->remove(pred);
    } else if (children[idx + 1]->keys.size() >= t) {
        int succ = children[idx + 1]->keys.front();
        keys[idx] = succ;
        children[idx + 1]->remove(succ);
    } else {
        children[idx]->keys.push_back(k);
        keys.erase(keys.begin() + idx);
        children[idx]->remove(k);
    }
}

int BTreeNode::findKey(int key) {
    int idx = 0;
    while (idx < keys.size() && keys[idx] < key) ++idx;
    return idx;
}

void BTree::remove(int key) {
    if (!root) {
        cout << "Tree is empty\n";
        return;
    }
    root->remove(key);
    if (root->keys.empty()) {
        BTreeNode* tmp = root;
        root = (root->leaf) ? nullptr : root->children[0];
        delete tmp;
    }
}

void BTreeNode::traverse() {
    int i;
    for (i = 0; i < keys.size(); i++) {
        if (!leaf) children[i]->traverse();
        cout << keys[i] << " ";
    }
    if (!leaf) children[i]->traverse();
}

int main() {
    int degree;
    cout << "Enter the minimum degree of the B-Tree: ";
    cin >> degree;

    BTree t(degree);

    int choice, key;
    do {
        cout << "\n1. Insert\n2. Delete\n3. Display\n4. Exit\nChoose an option: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter key to insert: ";
                cin >> key;
                t.insert(key);
                break;
            case 2:
                cout << "Enter key to delete: ";
                cin >> key;
                t.remove(key);
                break;
            case 3:
                cout << "B-Tree contents: ";
                t.traverse();
                cout << endl;
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);

    return 0;
}