#ifndef STACK_H_
#define STACK_H_
#include <iostream>
using namespace std;

template<typename MyType>
struct Node{
	MyType data;
	Node* next;
	Node* newNode(MyType val){
        Node* n = new Node;
        n->data = val;
        n->next = 0;
        return n;
    }
};

template<typename MyType>
class Stack{
public:
    Stack(){
        initialize();
    }

    void initialize(){
        top = 0;
    }

    void push(MyType val){
        Node<MyType>* newTop = newNode(val);
        newTop->next = top;
        top = newTop;
    }

    MyType pop(){
        if(top == 0)
            exit(-1);
            ///return 0; ///not good, but a case that won't happen anyway
        Node<MyType>* temp = top;
        MyType ret = temp->data;
        top = temp->next;
        delete temp;
        return ret;
    }

    MyType peek(){
        if(top == 0)
            exit(-1);
            ///return 0; ///not good, but a case that won't happen anyway
        return top->data;
    }

    bool isEmpty(){
        return top == 0;
    }

private:
    Node<MyType>* top;

};

#endif
