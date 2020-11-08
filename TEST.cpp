#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;

#define FORWARD 1
#define RIGHT 2
#define LEFT 3
#define DEGSET(x) ((x)+100)/10
void directionSet(float degree) {
    int degree_set = (int)degree;
    int result = DEGSET(degree_set);
    switch(result) {
        case 15:
            cout << RIGHT << endl;
            break;
        case 12:
            cout << FORWARD << endl;
            break;
        case 9:
            cout << LEFT << endl;
            break;
        default:
            cout << FORWARD << endl;
    }
}
typedef struct sNode {
    float* data;
    float* degree;
    sNode* next;
}Node;
typedef struct listStack {
    Node* peek;
    int size;
}Stack;
void createStack(Stack** stack) {
    (*stack) = (Stack*)malloc(sizeof(Stack));
    (*stack)->peek = NULL;
    (*stack)->size = 0;
}
Node* createNode(float* Degree,  float* Data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = (float*)malloc(sizeof(Data)+1);
    newNode->degree = (float*)malloc(sizeof(Degree)+1);
    newNode->next = NULL;
    newNode->data = Data;
    newNode->degree = Degree;
    return newNode;
}
void deleteNode(Node* removeNode) {
    free(removeNode->data);
    free(removeNode->degree);
    free(removeNode);}

void Push(Stack* stack, Node* addNode) {
    if(stack->size == 0) {
        cout << "...." << endl;
        stack->peek = addNode;
//    cout << "pushed : " << stack->peek->data <<endl;
  //  cout << "pushed : " << stack->peek->degree <<endl;
    } else {
        addNode->next = stack->peek;
        stack->peek = addNode;
    cout << "pushed  data : " << stack->peek->data <<endl;
    cout << "pushed  degree : " << stack->peek->degree <<endl;
    }
    stack->size++;
}
Node* Pop(Stack* stack) {
    Node* tempNode;

    if(stack->size == 0) {cout << "..no data.." << endl; tempNode = NULL;}
    else if(stack->size == 1) {
        tempNode = stack->peek;
        stack->peek = NULL;;
        stack->size--;
    }
    else {
        if(stack->peek->data < stack->peek->next->data) {
            cout << "\n NEXT:: " << endl;
            cout << "next->data :: " <<*(stack->peek->next->data) <<endl;
            cout << "\ndata :: " <<*(stack->peek->data) <<endl;


            tempNode = stack->peek->next;

            stack->peek->next = stack->peek;
            stack->peek = stack->peek->next;
            stack->size--;
        } else {

            cout << "\n PEEK:: " << endl;
            cout << "next->data :: " << *(stack->peek->next->data) <<endl;
            cout << "\ndata :: " << *(stack->peek->data) <<endl;
            

            tempNode = stack->peek;
            stack->peek = stack->peek->next;
            stack->size--;
        }
    }

    cout << *(tempNode->data) <<endl;
    return tempNode;
}
void deleteStack(Stack* stack) {
    int cnt = stack->size;
    int i;
    Node* tmpNode;

    for(i=0; i<cnt; i++) {
        tmpNode = Pop(stack);
        deleteNode(tmpNode);
    }
    free(stack);
}


int main(void) {

    int i;
    Stack* stack;
    createStack(&stack);

    float a=1.1;float b=45.2;
    float c=23.2;float d=3.33;
    float e=31.2;float f=33.33;
    Push(stack,createNode(&a, &b));
    Push(stack,createNode(&c, &d));
    Push(stack,createNode(&e, &f));

    Node* dataList = stack->peek;
    for(i=0; i<(stack->size); i++) {
        cout << "pushed  data : " << *(dataList->data) <<endl;
        cout << "pushed  degree: " << *(dataList->degree) <<endl;
        dataList = dataList->next;    
    }
 

    for(i=0; i<(stack->size); i++) {
        dataList = Pop(stack);    
        cout << "pushed  data : " << *(dataList->data) <<endl;
        cout << "pushed  degree: " << *(dataList->degree) <<endl;
        dataList = dataList->next;    
    }

    vector<Node*> vec_data;
    for(i=0; i<(stack->size); i++) {
        vec_data.push_back(dataList);
        dataList = dataList->next;    
    }
    sort(vec_data.begin(), vec_data.end(), greater<>());
    cout << *(vec_data[0]->degree) << endl;

    cout << " " << endl;
    directionSet(*(dataList->degree));
    /*    vector< vector<int> > vecTEST;
    vector<int> ve1;
    vector<int> ve2;

    ve1.push_back(1);
    ve1.push_back(23);
    ve1.push_back(5);
    ve2.push_back(4);
    ve2.push_back(5);
    ve2.push_back(522);
    ve2.push_back(11);

    vecTEST.push_back(ve1);
    vecTEST.push_back(ve2);

    cout << "vecTEST.size() : " << vecTEST.size() << endl;
    cout << "vecTEST[0].size : " << vecTEST[0].size() <<endl;
    cout << "vecTEST[1].size : " << vecTEST[1].size() <<endl;

    for(int i=0; i< vecTEST.size(); i++) {
        cout << "vecTEST["<<i<<"] : ";
        for(int j=0; j < vecTEST[i].size(); j++) {
            cout << vecTEST[i][j]<<" ";
        }
        cout << endl;
    }*/

    return 0;
}
