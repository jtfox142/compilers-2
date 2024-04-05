#include "tree.hpp"

#include <iostream>
#include <iomanip>

//root, left, middle, right
void tree::printPreorder(node::Node *root, int level) {
    if(root == NULL) return;

    std::cout << std::setw(level * 2) << root->getData().at(0) << ":" << root->getData() << std::endl;
    //file << std::setw(level * 2) << root->getData().at(0) << ":" << root->getData() << std::endl;

    printPreorder(root->getChildOne(), level+1);
    printPreorder(root->getChildTwo(), level+1);
    printPreorder(root->getChildThree(), level+1);
    printPreorder(root->getChildFour(), level+1);
    printPreorder(root->getChildFive(), level+1);
    printPreorder(root->getChildSix(), level+1);
    printPreorder(root->getChildSeven(), level+1);
    printPreorder(root->getChildEight(), level+1);
}

//Inefficient, but it works. Would love to optimize later
void tree::insert(node::Node* token, node::Node* root) {
    //std::cout << "Inserting " << word << " into the tree." << std::endl;
    
    //If the while loop is broken, then the tempNodeOne is at a NULL address. This is where the new node should go
    if(root->getChildNum() == 1) {
        root->setChildOne(token->getData());
        //std::cout << word << " has been inserted on the left." << std::endl;
    }
    else if(root->getChildNum() == 2) {
        root->setChildTwo(token->getData());
        //std::cout << word << " has been inserted in the middle." << std::endl;
    }
    else if(root->getChildNum() == 3) {
        root->setChildThree(token->getData());
        //std::cout << word << " has been inserted on the right." << std::endl;
    }
    else if(root->getChildNum() == 4) {
        root->setChildFour(token->getData());
        //std::cout << word << " has been inserted on the right." << std::endl;
    }
}