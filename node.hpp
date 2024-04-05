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

            void setChildOne(std::string val) {
                childOne = new Node(val);
                childNum++;
            }

            Node* getChildTwo() {
                return childTwo;
            }

            void setChildTwo(std::string val) {
                childTwo = new Node(val);
                childNum++;
            }

            Node* getChildThree() {
                return childThree;
            }

            void setChildThree(std::string val) {
                childThree = new Node(val);
                childNum++;
            }

            Node* getChildFour() {
                return childFour;
            }

            void setChildFour(std::string val) {
                childFive = new Node(val);
                childNum++;
            }

            Node* getChildFive() {
                return childFive;
            }

            void setChildFive(std::string val) {
                childFive = new Node(val);
                childNum++;
            }

            Node* getChildSix() {
                return childSix;
            }

            void setChildSix(std::string val) {
                childSix = new Node(val);
                childNum++;
            }

            Node* getChildSeven() {
                return childSeven;
            }

            void setChildSeven(std::string val) {
                childSeven = new Node(val);
                childNum++;
            }

            Node* getChildEight() {
                return childEight;
            }

            void setChildEight(std::string val) {
                childEight = new Node(val);
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