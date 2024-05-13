#include <iostream>

class TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;

    public:
        TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
        friend class BinaryTree;
};

class BinaryTree {
private:
    TreeNode* root;
    void insertRecursive(TreeNode*& node, int value);
    bool searchRecursive(TreeNode* node, int value);
    void inorderTraversalRecursive(TreeNode* node);

public:
    BinaryTree();
    void insert(int value);
    bool search(int value);
    void inorderTraversal();
};

BinaryTree::BinaryTree() : root(nullptr) {}

void BinaryTree::insertRecursive(TreeNode*& node, int value) {
    if (node == nullptr) {
        node = new TreeNode(value);
    } else if (value < node->value) {
        insertRecursive(node->left, value);
    } else if (value > node->value) {
        insertRecursive(node->right, value);
    }
}

bool BinaryTree::searchRecursive(TreeNode* node, int value) {
    if (node == nullptr) {
        return false;
    } else if (node->value == value) {
        return true;
    } else if (value < node->value) {
        return searchRecursive(node->left, value);
    } else {
        return searchRecursive(node->right, value);
    }
}

void BinaryTree::inorderTraversalRecursive(TreeNode* node) {
    if (node != nullptr) {
        inorderTraversalRecursive(node->left);
        std::cout << node->value << " ";
        inorderTraversalRecursive(node->right);
    }
}

void BinaryTree::insert(int value) {
    insertRecursive(root, value);
}

bool BinaryTree::search(int value) {
    return searchRecursive(root, value);
}

void BinaryTree::inorderTraversal() {
    inorderTraversalRecursive(root);
    std::cout << std::endl;
}

int main() {
    BinaryTree tree;
    tree.insert(6);
    tree.insert(3);
    tree.insert(10);
    tree.insert(2);
    tree.insert(4);
    tree.insert(12);
    tree.insert(8);
    tree.insert(9);
    tree.insert(11);

    tree.inorderTraversal(); // Output: 2 3 4 5 7
    std::cout << std::boolalpha << tree.search(4) << std::endl; // Output: true
    std::cout << std::boolalpha << tree.search(6) << std::endl; // Output: false

    return 0;
}
