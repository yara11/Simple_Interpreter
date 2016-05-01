#ifndef STACK_H_
#define STACK_H_
#include <iostream>
using namespace std;

template<typename MyType>
struct Node{
	MyType data;
	Node* next;
	Node(MyType val){
        data = val;
        next = 0;
    }
};
//Node* n = newNode(val);
//Node<int>* n = new Node(val);

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
        Node<MyType>* newTop = new Node<MyType>(val);
        newTop->next = this->top;
        this->top = newTop;
    }

    MyType pop(){
        if(top == NULL)
            return 0; ///not good, but a case that won't happen anyway
        Node<MyType>* temp = this->top;
        MyType ret = temp->data;
        this->top = this->top->next;
        delete temp;
        return ret;
    }

    MyType peek(){
        if(top == NULL)
            return 0; ///not good, but a case that won't happen anyway
        return top->data;
    }

    bool isEmpty(){
        return top == NULL;
    }

private:
    Node<MyType>* top;

};

#endif
