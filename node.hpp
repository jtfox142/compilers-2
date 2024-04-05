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
                childFour = new Node(val);
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
    };

};  // namespace node

#endif  // NODE_H