#include <iostream>

typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
} TreeNode;

TreeNode* treeInsert(TreeNode* t, int data) {
    TreeNode* newNode;
    newNode = (TreeNode*) malloc(sizeof(TreeNode));
    newNode->key = data;
    newNode->left = NULL;
    newNode->right = NULL;
    TreeNode* current = t;
    TreeNode* parent = t;
    if (t==NULL)
    {
        t = newNode;
    }
    else {
        while (current->key != data)
        {
            parent = current;
            if (current->key > data)
            {
                current = current->left;
                if (current==NULL)
                {
                    parent->left = newNode;
                    return t;
                }
            }
            else
            {
                current = current->right;
                if (current==NULL)
                {
                    parent->right = newNode;
                    return t;
                }
            }
        }
    }
    return t;
}

void printTree(TreeNode* root) {
    if (root == NULL)
    {
        std::cout << std::endl << "NULL11" << std::endl;
        return;
    }
    if (root)
    {
        std::cout << root->key;
    }
    if (root->left || root->right)
    {
        std::cout << "(";
        if (root->left)
        {
            printTree(root->left);
        }
        else
        {
            std::cout << "NULL";
        }
        std::cout << ",";
        if (root->right)
        {
            printTree(root->right);
        }
        else
        {
            std::cout << "NULL";
        }
        std::cout << ")";

    }
}

TreeNode* getSuccessor(TreeNode* node) {
    TreeNode* current = node->right;
    TreeNode* parent = node;
    TreeNode* s = node;

    while (current != NULL)
    {
        parent = s;
        s = current;
        current = current->left;
    }
    if (s != node->right)
    {
        parent->left = s->right;
        s->right = node->right;
    }
    return s;
}

bool deletetree(TreeNode* root, int key) {
    TreeNode* current = root;
    TreeNode* parent = root;
    bool isLeftChild = true;

    while (current->key != key)
    {
        parent = current;
        if (key < current->key)
        {
            current = current->left;
            isLeftChild = true;
        }
        else
        {
            current = current->right;
            isLeftChild = false;
        }
        if (current == NULL)
        {
            return false;
        }
    }
    if (current->left == NULL && current->right == NULL)
    {
        if (current == NULL)
        {
            root = NULL;
        }
        else if (isLeftChild)
        {
            parent->left = NULL;
        }
        else
        {
            parent->right = NULL;
        }
    }
    else if (current->right == NULL)
    {
        if (isLeftChild)
        {
            parent->left = current->left;
        }
        else
        {
            parent->right = current->left;
        }
    }
    else if (current->left == NULL)
    {
        if (isLeftChild)
        {
            parent->left = current->right;
        }
        else
        {
            parent->right = current->right;
        }
    }
    else
    {
        TreeNode* successor = getSuccessor(current);
        if (current == root)
        {
            root = successor;
        }
        else if (isLeftChild)
        {
            parent->left = successor;
        }
        else
        {
            parent->right = successor;
        }
        successor->left = current->left;
    }
    return true;
}

int checkl(TreeNode* root) {
    int l = 0;
    if(root) {
            while (root->left != NULL)
            {
                if (root->left->right != NULL)
                {
                    l++;
                }
                l++;
                root = root->left;
            }
        
    }
    return l;
}
int checkr(TreeNode* root) {
    int r = 0;
    if (root) {
        while (root->right != NULL)
        {
            if (root->right->left != NULL)
            {
                r++;
            }
            r++;
            root = root->right;
        }

    }
    return r;
}

void isBalanced(TreeNode* root) {
    if (root == NULL)
    {
        std::cout << "Tree is empty";
    }
    int l = checkl(root);
    int r = checkr(root);
    if (l == r || l+1 == r || r+1==l)
    {
        std::cout << "Tree is balanced";
    }
    else
    {
        std::cout << "Tree is not balanced";
    }
}

int balancedPercent(TreeNode* root) {
    if (root == NULL)
    {
        std::cout << "Tree is empty";
        return 0;
    }
    int l = checkl(root);
    int r = checkr(root);
    int a = l + r;
    int per;
    int x;
    if (l > r)
    {
        per = l - r;
    }
    else
    {
        per = r - l;
    }
    x = (per * 100) / a;
    return x;
}

bool BinSearch(TreeNode* root, int value) {
    if (root == 0)
    {
        return false;
    }
    if (root->key == value)
    {
        return true;
    }
    TreeNode* current = root;
    if (value < current->key)
    {
        current = current->left;
        BinSearch(current, value);
    }
    else
    {
        current = current->right;
        BinSearch(current, value);
    }
    if (current == NULL)
    {
        return false;
    }
}

int main()
{
    ///////exercise 1.1, 2

    TreeNode* tree=NULL;
    tree=treeInsert(tree, 15);

    treeInsert(tree, 8);
    treeInsert(tree, 19);
    treeInsert(tree, 5);
    treeInsert(tree, 21);
    treeInsert(tree, 7);
    treeInsert(tree, 14);
    treeInsert(tree, 23);
    treeInsert(tree, 32);

    printTree(tree);
    std::cout << std::endl;

    isBalanced(tree);
    std::cout << std::endl;

    if (BinSearch(tree, 32))
    {
        std::cout << "Find" << std::endl;
    }
    else
    {
        std::cout << "Can't find" << std::endl;
    }

    ///////////////////
    
    //////// exercise 1.2

    TreeNode* trees = NULL;
    trees = treeInsert(trees, rand() % 99);
    int percent=0;
    const int size = 10000;
    int arr[size];
    for (size_t j = 0; j < 50; j++)
    {
        for (size_t i = 0; i < size; i++)
        {
            arr[i] = rand() % 99;
            treeInsert(trees, arr[i]);
        }
        percent += balancedPercent(trees);
        for (size_t i = 0; i < size; i++)
        {
            deletetree(trees, arr[i]);
        }
    }
    percent = percent / 50;
    std::cout << "Not balanced: " << percent << "%";

    ////////////

    return 0;
}

