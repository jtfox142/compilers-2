#ifndef NODE_H
#define NODE_H

#include <string>

namespace node {

    class Node {
        //All these gets might be useless. If you return a pointer from a get, you typically want it to be immutable (const).
        //However, in order to assign it to the tempNode in tree.cpp, it cannot return a const because the types are incompatible
        public:
            inline Node(std::string val) {
                data = val;
                childNum = 1;
                childOne = NULL;
                childTwo = NULL;
                childThree = NULL;
                childFour = NULL;
                childFive = NULL;
                childSix = NULL;
                childSeven = NULL;
                childEight = NULL;
            }

            Node* getChildOne() {
                return childOne;
            }

            void setChildOne(Node* child) {
                childOne = child;
                childNum++;
            }

            Node* getChildTwo() {
                return childTwo;
            }

            void setChildTwo(Node* child) {
                childTwo = child;
                childNum++;
            }

            Node* getChildThree() {
                return childThree;
            }

            void setChildThree(Node* child) {
                childThree = child;
                childNum++;
            }

            Node* getChildFour() {
                return childFour;
            }

            void setChildFour(Node* child) {
                childFive = child;
                childNum++;
            }

            Node* getChildFive() {
                return childFive;
            }

            void setChildFive(Node* child) {
                childFive = child;
                childNum++;
            }

            Node* getChildSix() {
                return childSix;
            }

            void setChildSix(Node* child) {
                childSix = child;
                childNum++;
            }

            Node* getChildSeven() {
                return childSeven;
            }

            void setChildSeven(Node* child) {
                childSeven = child;
                childNum++;
            }

            Node* getChildEight() {
                return childEight;
            }

            void setChildEight(Node* child) {
                childEight = child;
                childNum++;
            }

            const std::string getData() {
                return data;
            }

            const int getChildNum() {
                return childNum;
            }

        private:
            std::string data;
            int childNum;
            Node* childOne;
            Node* childTwo;
            Node* childThree;
            Node* childFour;
            Node* childFive;
            Node* childSix;
            Node* childSeven;
            Node* childEight;

    };

};  // namespace node

#endif  // NODE_H