#pragma once

#include <string>
#include <ostream>
#include <iostream>
using std::string;

class Buffer {
private:
    int currentLineNum = 0;
    /* int LineNum = 0; */
    // TODO: add a List here for storing the input lines
    struct List {
        struct List *front;
        struct List *back;
        string line;
        /* void operator=(List *tmp) {
            front = tmp->front;
            back = tmp->back;
            line = tmp->line;
        } */
        
    };
    List *head;
    List *tail;

public:
    int LineNum = 0;
    int Bytes = 0;
    Buffer();
    ~Buffer();

    void writeToFile(const string &filename) const;

    void moveToLine(int idx) ;

    void showLines(int from, int to);

    void deleteLines(int from, int to);
    void insertLine(const string &text);
    void appendLine(const string &text);

    List *getLine(int idx) const{// must have "const" here, or you can have a try
        int i = 1;
        List *tmp = nullptr;
        tmp = head->back;
        while (i != idx) {
           tmp = tmp->back;
           i++;
        }
        return tmp;
    }

    friend std::ostream &operator<<(std::ostream &os, List *tmp) {
        os << tmp->line;
        return os;
    }
};
