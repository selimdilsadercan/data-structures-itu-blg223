#include <iostream>
#include <string>
#include <sstream>
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

class Tree {
    private:
        Node* root;

        Node* recursive_construct(string preorder, string inorder) {
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
        
            if(l_preorder != "") { top->setLeft(recursive_construct(l_preorder, l_inorder)); }
            if(r_preorder != "") { top->setRight(recursive_construct(r_preorder, r_inorder)); }
            return top;
        }

        string preorderTraversal(Node* top) {
            stringstream ss;
            ss << top->getData(); 
            if(top->getLeft()) { ss << this->preorderTraversal(top->getLeft()); }
            if(top->getRight()) { ss << this->preorderTraversal(top->getRight()); }
            return ss.str();
        }

        string inorderTraversal(Node* top) {
            stringstream ss;
            if(top->getLeft()) { ss << this->inorderTraversal(top->getLeft()); }
            ss << top->getData(); 
            if(top->getRight()) { ss << this->inorderTraversal(top->getRight()); }
            return ss.str();
        }

        string postorderTraversal(Node* top) {
            stringstream ss;
            if(top->getLeft()) { ss << this->postorderTraversal(top->getLeft()); }
            if(top->getRight()) { ss << this->postorderTraversal(top->getRight()); }
            ss << top->getData(); 
            return ss.str();
        }

    public:
        Tree(string preorder, string inorder) {
            this->root = recursive_construct(preorder, inorder);
        };
     
        void printPreorder() {
            cout << preorderTraversal(this->root) << endl;
        }

        void printInorder() {
            cout << inorderTraversal(this->root) << endl;
        }

        void printPostorder() {
            cout << postorderTraversal(this->root) << endl;
        }
};


int main () {
    Tree* tree = new Tree("1245367", "4251637");
    tree->printPreorder();
    tree->printInorder();
    tree->printPostorder();
    
    return 0;
}