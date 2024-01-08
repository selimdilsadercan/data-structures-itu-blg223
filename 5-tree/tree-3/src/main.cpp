#include <iostream>
#include <string>
#include <sstream>
#include <list>
using namespace std;

class Node {
    private:
        int data;
        Node* left;
        Node* right;
    public:
        Node(int data) {
            this->data = data;
            this->left = NULL;
            this->right = NULL;
        }
        int getData() {
            return this->data;
        }
        Node* getLeft() {
            return this->left;
        }
        Node* getRight() {
            return this->right;
        }
        void setData(int data) {
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
        Node* root = NULL;

        string preorderRecursion(Node* top) {
            stringstream ss;
            ss << top->getData()  << " "; 
            if(top->getLeft()) { ss << this->preorderRecursion(top->getLeft()) << " "; }
            if(top->getRight()) { ss << this->preorderRecursion(top->getRight()) << " "; }
            return ss.str();
        }

        string inorderRecursion(Node* top) {
            stringstream ss;
            if(top->getLeft()) { ss << this->inorderRecursion(top->getLeft()) << " "; }
            ss << top->getData() << " "; 
            if(top->getRight()) { ss << this->inorderRecursion(top->getRight()) << " ";}
            return ss.str();
        }

        string postorderRecursion(Node* top) {
            stringstream ss;
            if(top->getLeft()) { ss << this->postorderRecursion(top->getLeft()); }
            if(top->getRight()) { ss << this->postorderRecursion(top->getRight()); }
            ss << top->getData(); 
            return ss.str();
        }

        Node* removeRecursion(Node* node, int data) {
            if (node == NULL) {
                return node;
            }

            if (data < node->getData()) {
                node->setLeft(removeRecursion(node->getLeft(), data));
                return node;
            }

            if (data > node->getData()) {
                node->setRight(removeRecursion(node->getRight(), data));
                return node;
            }

            if (node->getLeft() == NULL) {
                Node* temp = node->getRight();
                delete node;
                return temp;
            } 

            if (node->getRight() == NULL) {
                Node* temp = node->getLeft();
                delete node;
                return temp;
            }

            Node* temp = node->getRight();
            while (temp->getLeft() != NULL) {
                temp = temp->getLeft();
            }
            node->setData(temp->getData());
            node->setRight(removeRecursion(node->getRight(), temp->getData()));
            return node;
        }

    public:
        Tree(list<int> v) {
            for(auto data : v) {
               add(data);
            }
        };
     
        void printPreorder() {
            cout << preorderRecursion(this->root) << endl;
        }

        void printInorder() {
            cout << inorderRecursion(this->root) << endl;
        }

        void printPostorder() {
            cout << postorderRecursion(this->root) << endl;
        }

        void add(int data) {
            if (this->root == NULL) {
                this->root = new Node(data);
            }
            Node* current = this->root;
            while(true) {
                if (data == current->getData()){
                    break;
                }
                else if (data < current->getData()) {
                    if(current->getLeft()) { 
                        current = current->getLeft(); 
                    }
                    else {
                        current->setLeft(new Node(data)); 
                        break;
                    }
                }
                else if (data > current->getData()) {
                    if(current->getRight()) { 
                        current = current->getRight(); 
                    }
                    else {
                        current->setRight(new Node(data)); 
                        break;
                    }
                }
            } 
        }

        void remove(int data) {
            this->root = removeRecursion(this->root, data);
        }

        bool contains(int data) {
            Node* current = this->root;
            while(true) {
                if (data == current->getData()){
                    return true;
                }
                else if (data < current->getData()) {
                    if(current->getLeft()) { current = current->getLeft(); }
                    else { break; }
                }
                else if (data > current->getData()) {
                    if(current->getRight()) { current = current->getRight(); }
                    else { break; }
                } 
            }
            return false;
        };
};

int main () {
    list<int> v;
    v.assign({10,5,15,3,8,11,20,1,4,6,9,13});
    Tree* tree = new Tree(v);

    cout << tree->contains(7) << endl; 

    tree->add(7);

    tree->printPreorder();

    cout << tree->contains(7) << endl; 

    tree->remove(5);

    tree->printPreorder();
    tree->printInorder();

    return 0;
}