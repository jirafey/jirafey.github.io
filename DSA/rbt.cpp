#include <iostream>
#include <vector>
using namespace std;

struct Node* root = nullptr;
struct Node {
    bool isRed;
    int value;
    struct Node* parent;
    struct Node* left;
    struct Node* right;

    // RED 0
    Node(): isRed(true), value(0), parent(nullptr), left(nullptr), right(nullptr) {}

    // RED NUM
    explicit Node(int _value): isRed(true), value(_value), parent(nullptr), left(nullptr), right(nullptr) {}
    explicit Node(bool _isRed, int _value): isRed(_isRed), value(_value), parent(nullptr), left(nullptr), right(nullptr) {}

    // ALL
    Node(bool _isRed, int _value, struct Node* _parent, struct Node* _left, struct Node* _right)
        : isRed(_isRed), value(_value), parent(_parent), left(_left), right(_right) {}
};

void recolor(Node* node0,Node* node1 = nullptr , Node* node2 = nullptr){
    if (node0){
        node0->isRed = not node0->isRed;
    }
    if (node1){
        node1->isRed = not node1->isRed;
    }
    if (node2){
        node2->isRed = not node2->isRed;
    }

}
void right_rotate(Node* target) {
    /*
    Parent           Parent
       |                |
       y      ==>       x      <-- Becomes new root of this subtree
      / \              / \
     x   C            A   y      <-- Becomes right child of x
    / \                  / \
   A   B                B   C    <-- B becomes left child of y
   */
    if (target == nullptr || target->left == nullptr) {
        cout << "target or target's left child is null";
        return;
    }
    struct Node* l_child = target->left;
    struct Node* lr_grandchild = l_child->right;
    struct Node* parent = target->parent;

    target->left = lr_grandchild; // link B
    if (lr_grandchild) {
        lr_grandchild->parent = target; // update parent for B
    }

    l_child->parent = parent;

    if (parent==nullptr) {
        root = l_child;
    }
    else if (parent->left==target) {
        parent->left = l_child;
    }
    else {
        parent->right = l_child;
    }

    // link right child
    l_child->right = target;
    // link parent
    target->parent = l_child;
}
void left_rotate(Node* target) {
    if (target == nullptr || target->right == nullptr) {
        cout << "target or target's right child is null";
        return;
    }
    struct Node* r_child = target->right;
    struct Node* rl_grandchild = r_child->left;
    struct Node* parent = target->parent;

    target->right = rl_grandchild; // link B
    if (rl_grandchild) {
        rl_grandchild->parent = target; // update parent for B
    }

    r_child->parent = parent;

    if (parent==nullptr) {
        root = r_child;
    }
    else if (parent->left==target) {
        parent->left = r_child;
    }
    else {
        parent->right = r_child;
    }

    // link right child
    r_child->left = target;
    // link parent
    target->parent = r_child;
}



void fixup(Node* node) {
    while (node != root && node->parent != nullptr && node->parent->isRed == true) {
        struct Node* parent = node->parent;
        if (parent->parent == nullptr) {
            parent->isRed = false;
            break;
        }
        struct Node* grandparent = parent->parent;
        struct Node* uncle = nullptr;
        bool parent_is_left;
        if (grandparent->left == parent) {
            uncle = grandparent->right;
            parent_is_left = true;
        }
        else {
            uncle = grandparent->left;
            parent_is_left = false;
        }
        int caseNum = 0;
        if (uncle != nullptr && uncle->isRed == true) {
            caseNum = 2;
        }
        else {
            if (parent_is_left) {
                if (parent->left == node) {
                    caseNum = 4; // LL
                } else {
                    caseNum = 3; // LR
                }
            }
            else {
                if (parent->right == node) {
                    caseNum = 4; // RR
                }
                else {
                    caseNum = 3; // RL
                }
            }

        }


        switch (caseNum) {
            case 2:
                recolor(grandparent, parent, uncle);
                node = grandparent;
                continue;
            case 3: // tringle ">" or ">"
                if (parent_is_left == true){
                    left_rotate(parent);
                    node = parent;
                }
                else {
                    right_rotate(parent);
                    node = parent;
                }
                continue;
            case 4: // line "/" or "\"
                if (parent_is_left == true){
                    right_rotate(grandparent);
                }
                else {
                    left_rotate(grandparent);
                }
                recolor(grandparent, parent);
                break;
        }
    } // end of while loop
    if (root != nullptr) {
        root->isRed = false;
    }
}



Node* add(int num) {
    struct Node* new_node = new Node(num);
    if (root==nullptr) {
        root = new_node;
    } else { // root exists
        struct Node* current = root;
        struct Node* trailing_parent = nullptr;
        while (current != nullptr) {
            trailing_parent = current;
            if (new_node->value < current->value) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        new_node->parent = trailing_parent;
        if (new_node->value < trailing_parent->value) {
            trailing_parent->left = new_node;
        } else {
            trailing_parent->right = new_node;
        }
    }
    fixup(new_node);
    return new_node;
}
void printInOrder(Node* node) {
    if (node == nullptr) {
        return;
    }

    printInOrder(node->left);

    cout << "Value: " << node->value;
    cout << ", Color: " << (node->isRed ? "RED" : "BLACK");
    cout << ", Parent: " << (node->parent ? to_string(node->parent->value) : "NULL");
    cout << ", Left Child: " << (node->left ? to_string(node->left->value) : "NULL");
    cout << ", Right Child: " << (node->right ? to_string(node->right->value) : "NULL");
    cout << endl;

    printInOrder(node->right);
}

void clearTree(Node* node) {
    if (node == nullptr) return;
    clearTree(node->left);
    clearTree(node->right);
    delete node;
}

// --- Main Function ---
int main(int argc, char* argv[]){
    vector<int> nums = {12, 5, 20, 8, 15, 25, 10, 7, 3, 18};

    cout << "--- Adding Nodes ---" << endl;
    for (int num_to_add : nums) {
        cout << "Adding " << num_to_add << "..." << endl;
        add(num_to_add);
    }

    cout << "\n--- Tree In-Order Traversal ---" << endl;
    if (root == nullptr) {
        cout << "Tree is empty." << endl;
    } else {
        printInOrder(root);
    }

    cout << "\n--- Cleaning Up Tree ---" << endl;
    clearTree(root);
    root = nullptr;
    cout << "Tree cleared." << endl;

    return 0;
}
