#include <iostream>
#include <string>
using namespace std;

class Node {
    private:
        char data;
        Node* left;
        Node* right;
    public:
        Node(char data) {
            this->data = data;
            this->left = NULL;
            this->right = NULL;
        }
        char getData() {
            return this->data;
        }
        Node* getLeft() {
            return this->left;
        }
        Node* getRight() {
            return this->right;
        }
        void setData(char data) {
            this->data = data;
        }
        void setLeft(Node* left) {
            this->left = left;
        }
        void setRight(Node* right) {
            this->right = right;
        }
};

void printTree(Node* root)  {
    cout << "root: " << root->getData() << endl;
    cout << "root.left: " << root->getLeft()->getData() << endl;
    cout << "root.right: " << root->getRight()->getData() << endl;
    cout << "root.left.left: " << root->getLeft()->getLeft()->getData() << endl;
    cout << "root.right.left: " << root->getRight()->getLeft()->getData() << endl;
    cout << "root.right.right: " << root->getRight()->getRight()->getData() << endl;
}

Node* tree(string preorder, string inorder) {
    int length = inorder.length();
    Node* top = new Node(preorder[0]);

    if(length == 1) {
        return top;
    }

    int sayi = 0;
    for(int i = 0; i < length; i++) {
        sayi++;
        if(top->getData() == inorder[i]) { break; }
    }
    
    string l_preorder = preorder.substr(1, sayi-1);
    string l_inorder = inorder.substr(0, sayi-1);
    string r_preorder = preorder.substr(sayi, length-1);
    string r_inorder = inorder.substr(sayi, length-1);
 
    if(l_preorder != "") { top->setLeft(tree(l_preorder, l_inorder)); }
    if(r_preorder != "") { top->setRight(tree(r_preorder, r_inorder)); }
    return top;
}

int main () {
    string preorder = "ABDCEF"; 
    string inorder = "DBAECF";

    Node* root = tree(preorder, inorder);
    printTree(root);
    
    return 0;
}