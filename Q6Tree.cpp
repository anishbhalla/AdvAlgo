#include <iostream>
using namespace std;

class TreeNode {
public:
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) {
        data = val;
        left = right = nullptr;
    }
};

class Tree {
public:
    TreeNode* root;

    Tree() {
        root = nullptr;
    }

    void insert(int val) {
        if (root == nullptr) {
            root = new TreeNode(val);
        } else {
            insertHelper(root, val);
        }
    }

    void insertHelper(TreeNode* node, int val) {
        if (val < node->data) {
            if (node->left == nullptr) {
                node->left = new TreeNode(val);
            } else {
                insertHelper(node->left, val);
            }
        } else {
            if (node->right == nullptr) {
                node->right = new TreeNode(val);
            } else {
                insertHelper(node->right, val);
            }
        }
    }

    bool search(int val) {
        return searchHelper(root, val);
    }

    bool searchHelper(TreeNode* node, int val) {
        if (node == nullptr) {
            return false;
        }
        if (node->data == val) {
            return true;
        }
        if (val < node->data) {
            return searchHelper(node->left, val);
        } else {
            return searchHelper(node->right, val);
        }
    }

    void inorderTraversal(TreeNode* node) {
        if (node != nullptr) {
            inorderTraversal(node->left);
            cout << node->data << " ";
            inorderTraversal(node->right);
        }
    }

    void printTree() {
        inorderTraversal(root);
        cout << endl;
    }
};

int main() {
    Tree t;
    int choice, val;

    do {
        cout << "\nMenu:\n";
        cout << "1. Insert\n";
        cout << "2. Search\n";
        cout << "3. Display Tree (In-order Traversal)\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> val;
                t.insert(val);
                break;

            case 2:
                cout << "Enter value to search: ";
                cin >> val;
                if (t.search(val)) {
                    cout << "Value " << val << " found in the tree.\n";
                } else {
                    cout << "Value " << val << " not found in the tree.\n";
                }
                break;

            case 3:
                cout << "Tree (In-order Traversal): ";
                t.printTree();
                break;

            case 4:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
