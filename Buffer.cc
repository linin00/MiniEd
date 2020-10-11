#include <fstream>
#include <iostream>
#include "Buffer.h"

//TODO: your code here
//implement the functions in ListBuffer

Buffer::Buffer() {
    /* std::cout << 1234; */
    head = new List();
    tail = new List();
    head->back = tail;
    tail->front = head;
}

Buffer::~Buffer() {
    delete head;
    delete tail;
}

void Buffer::writeToFile(const string &filename) const {
    std::ofstream File;
    File.open(filename);
    List *tmp;
    tmp = new List;
    tmp = head->back;
    /* std::cout << tmp->line; */
    for (int i = 0; i < LineNum; i++) {
        File << tmp->line <<'\n';
        tmp = tmp->back;
    }
    File.close();
    std::cout << ":" << Bytes + LineNum << " byte(s) written\n";
}

void Buffer::showLines(int from, int to) {
    for (int i = from; i <= to; i++) {
        std::cout << i << '\t';
        moveToLine(i);
    }
}

void Buffer::deleteLines(int from, int to){
    int i = 1;
    List *tmp;
    tmp = new List;
    tmp = head->back;
    while (i != from) {
        tmp = tmp->back;
        i++;
    }
    for (i; i <= to; i++) {
        List *del = tmp; 
        tmp = del->back;
        del->front->back = tmp ;
        tmp->front = del->front;
        Bytes -= del->line.size();
        delete del;
    }
    LineNum -= (to - from + 1); 
    currentLineNum = from;
    if( LineNum == 0) 
        currentLineNum = 0;
}

void Buffer::insertLine(const string &text){
    int i = 1;
    List *tmp;
    tmp = new List;
    tmp = head->back;//?????????????
    while ( i != currentLineNum) {
        if (currentLineNum == 0) {
            currentLineNum = 1;
            break;
        }
        tmp = tmp->back;
        i++;
    }
    List *New;
    New = new List;
    New->line = text;

    New->front = tmp->front;
    New->front->back = New;
    New->back = tmp;
    tmp->front = New;
    LineNum++;
    Bytes += text.size();
}

void Buffer::appendLine(const string &text){
    int i = 0;
    List *tmp;
    tmp = new List;
    tmp = head;//?????????????
    /* std::cout << currentLineNum << " ";  */
    while ( i != currentLineNum ) {
        tmp = tmp->back;
        i++;
    }
    List *New2;
    New2 = new List;
    New2->line = text;
    /* std::cout << 1234; */

    New2->front = tmp;/* std::cout << 1234; */
    New2->back = tmp->back;/* std::cout << 1234; */
    New2->back->front = New2;/* std::cout << 1234; */
    tmp->back = New2;/* std::cout << 1234; */
    currentLineNum++;
    LineNum++;
    /* std::cout << sizeof(text); */
    Bytes += text.size();
}

void Buffer::moveToLine(int idx)  {
    std::cout << getLine(idx) << '\n';
    currentLineNum = idx;
}
