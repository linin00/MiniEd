#include <iostream>
#include <sstream>
#include "Editor.h"

using namespace std;
Editor::Editor()
{
    buffer = new Buffer();
}
Editor::~Editor()
{
    // TODO: Implement destructor
    delete buffer;
}
class out_of_r {
public:
    string what() {
        return "Line number out of range";
    };
    out_of_r() { }
};

class r_error {
public:
    string what() {
        if (type == 0)
            return "Number range error";
        if (type == 1)
            return "Delete range error";
    }
    r_error(int T): type(T) {}
private:
    int type;
};
void Editor::run()
{
    string cmd;
    while (true)
    {
        cout << "cmd> ";
        cout.flush();
        getline(cin, cmd);
        if (cmd == "Q")
            break;
        try {
            dispatchCmd(cmd);
        } catch (const char *e) {
            /* cout << "test" ; */
            cout << "? " << e << endl;
        } catch (out_of_r &oor) {
            cout << "? " << oor.what() << endl;
        } catch (r_error &re) {
            cout << "? " << re.what() << endl;
        }
    }
}
void Editor::cmdAppend()
{
    cout << "It's input mode now. Quit with a line with a single dot(.)" << endl;
    // TODO: finish cmdAppend.
    while (true)
    {
        string text;
        getline(cin, text);
        /* cout << 123; */
        if (text == ".")
            break;
        buffer->appendLine(text);
    }
}

void Editor::cmdInsert()
{
    cout << "It's input mode now. Quit with a line with a single dot(.)" << endl;
    bool firstLine = true;
    while (true)
    {
        string text;
        getline(cin, text);
        if (text == ".")
            break;
        if (firstLine) {
            buffer->insertLine(text);
            firstLine = false;
        }  else {
            buffer->appendLine(text);
        }
    } /* cout << buffer->LineNum; */
}

void Editor::cmdDelete(int start, int end)
{
    buffer->deleteLines(start, end);
}

void Editor::cmdNull(int line)
{
    buffer->moveToLine(line);
}

void Editor::cmdNumber(int start, int end)
{
    buffer->showLines(start, end);
}

void Editor::cmdWrite(const string &filename)
{
    buffer->writeToFile(filename);
}

void Editor::dispatchCmd(const string &cmd)
{
    if (cmd == "a") {
        cmdAppend();
        return;
    }
    if (cmd == "i") {
        cmdInsert();
        return;
    }
    if (cmd[0] == 'w' && cmd[1] == ' ') {
        // TODO: call cmdWrite with proper arguments
        string filename = cmd.substr(2);
        /* cout << filename; */
        cmdWrite(filename);
        return;
    }
    // TODO: handle special case "1,$n".
    int start, end;
    char comma, comma2, type = ' ';
    stringstream ss(cmd);
    ss >> start;
    if (ss.eof()) {
        if (start < 1 || start > buffer->LineNum)
            throw out_of_r();
        cmdNull(start);
        return;
    }
    ss >> comma >> end >> type;
    if (ss.good()) {/* cout<<123; */
        if (type == 'n') {
            if (start < 1 || end >buffer->LineNum || end < start)
                throw r_error(0);
            cmdNumber(start, end);
            return;
        } else if (type == 'd') {
            if (start < 1 || end >buffer->LineNum || end < start)
                throw r_error(1);
            cmdDelete(start, end);
            return;
        }
    }
    stringstream ss2(cmd);
    ss2 >> start >> comma >> comma2 >>type;
    if (ss2.good()) {/* cout<<123; */
        if (type == 'n' && comma2 == '$') {
            if (start < 1)
                throw r_error(0);
            cmdNumber(start, buffer->LineNum);
            return;
        } else if (type == 'd' && comma2 == '$') {
            if (start < 1)
                throw r_error(0);
            cmdDelete(start, buffer->LineNum);
            return;
        }
    }
    
    throw "Bad/Unknown command";
}
