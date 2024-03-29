# MiniEd
Ed是一个非常古老的行文本编辑器，曾经被用于文本文件的创建、显示、更改和其他一些操作。

Ed有两种模式，刚运行时Ed处于命令模式（command mode）。此时输入到Ed的文本会被当做命令进行处理。通过一些特殊命令，Ed可以被切换到输入模式（input mode），在输入模式下输入的文本会被当做文件内容进行保存。

本次Lab的任务是使用C++通过面向对象的方法完成一个简化版的Ed编辑器MiniEd。在MiniEd中，仅需实现Ed命令的一个子集。

#### 命令与符号解释

在以下列出的Ed命令中，每个`?`为一个数字n，表示第n行。其值应该在第一行到最后一行之间（包含第一行和最后一行）。

每个`?,?`表示一个区间，其中`?`的含义同上。如`1,2`表示第一行到第二行；`5,11`表示第五行到第十一行；`6,6`表示第六行。应保证区间起点不大于终点。

每个命令为一行输入，以下为需要实现的命令说明。

> - `a`
>
> Appends text to the buffer after the current address line. If the current address is zero, the entered text is placed at the beginning of the buffer. Text is entered in input mode. The current address is set to the address of the last line entered or, if there were none, the current address is not changed.  
在当前地址行之后将文本追加到缓冲区。 如果当前地址为零，则将输入的文本放在缓冲区的开头。 在输入模式下输入文字。 当前地址设置为最后输入的行的地址，如果没有，则不更改当前地址。
>
> - `?,?d`
>
> Deletes the addressed lines from the buffer. The current address is set to the new address of the line after the last line deleted; if the lines deleted were originally at the end of the buffer, the current address is set to the address of the new last line; if no lines remain in the buffer, the current address is set to zero.  
从缓冲区中删除寻址的行。 在删除最后一行后，当前地址设置为该行的新地址； 如果删除的行原本在缓冲区的末尾，则当前地址设置为新的最后一行的地址； 如果缓冲区中没有剩余行，则将当前地址设置为零。
>
> - `i`
>
> Inserts text in the buffer before the current addressed line. If the current address is zero, the entered text is placed at the beginning of the buffer. Text is entered in input mode. The current address is set to the address of the last line entered or, if there were none, the current address is not changed. 
在当前寻址行之前的缓冲区中插入文本。 如果当前地址为零，则将输入的文本放在缓冲区的开头。 在输入模式下输入文字。 当前地址设置为最后输入的行的地址，如果没有，则不更改当前地址。 
>
> - `?,?n`
>
> Number command. Prints the addressed lines, preceding each line by its line number and a \<tab> (`'\t'`). The current address is set to the address of the last line printed. Specially, `1,$n` prints all lines in the buffer.
数字命令。 打印寻址的行，在每行之前加上其行号和<tab>(`'\t'`)。 当前地址设置为打印的最后一行的地址。 特别地，1，$ n打印缓冲区中的所有行。
>
> - `Q`
>
> Quits ed unconditionally. Unwritten changes are discarded.
无条件退出。 未写入的更改将被丢弃。  
>
> - `w file`
>
> Writes all lines to file and prints the number of bytes written to the file. Print an error if no filename is specified. The current address is unchanged.
将所有行写入文件，并打印写入文件的字节数。 如果未指定文件名，则打印错误。 当前地址不变。
>
> - `?`
>
> Null command. An address alone prints the addressed line. The current address is set to the address of the printed line.
空命令。 一个地址单独打印寻址的行。 当前地址设置为打印行的地址。
>
> 
>

对于无效指令或错误指令，请输出一个以问号开头的错误提示信息：
```bash
? Bad/Unknown command
```



#### 程序大体逻辑

MiniEd的部分代码已经给出，共五个文件：`Buffer.cc`、`Buffer.h`、`Editor.cc`、`Editor.h`和`ed.cc`。其中`Buffer.cc/h`、`Editor.cc/h`分别声明和实现了两个类。`ed.cc`中包含了`main`函数，并在其中建造并运行了一个`Editor`实例。在`Editor::run`中，程序会不断读入命令，对命令进行解析并调用相应的函数（`Editor::cmdXXX`）。`Buffer`类用于保存所有输入的文本，其中每行文本保存在一个`string`类型的字符串中，所有的行保存在一个链表中。`Buffer`类有各种用于操作和展示文本的函数，供`Editor`调用。

![](http://www.plantuml.com/plantuml/png/ZL5BIWGn4Dtd55bsDds0Tk7uKH1aG134PPnKsuNvX5J5lhx5J1o4Y7OsATxdvL7P4Tl2DNYbZfDIKx0O1tCXqvr3JcMQIZq1wu8UzF1KaI-DHjB3FXcbzLdeaBBbmt8Jd1Y4cLFvaEk7v13SLSuGcq2OwphF88njy3YEtrPjtwLC5_0G2GgV0_utt887Xkv5TuGVCG89ztV4leOtA5q4BMdT5l1Iy9SAgw3mdExHmuOAtdS18NsANoeqlwpmj7KPsd-z0XabXpXbjHEy1ly5)



#### 任务

**代码**：

1. 实现一个**链表**，并作为`Buffer`的成员，用于保存所有行。
2. 实现`Buffer::writeToFile`，将当前所有的文本保存到指定文件中，并打印所保存的字节数。
3. 实现`Buffer::showLines`，将相应的文本行以规定格式打印出来。
4. 实现`Buffer::insertLine`，将指定文本插入到当前行之前。
5. 实现`Editor::cmdAppend`，完成对`a`命令的处理。
6. 在`Editor::dispatchCmd`中，完成对`cmdWrite`的调用。
7. 在`Editor::dispatchCmd`中，完成对`1,$n`情况的判断，以及后续的处理。
8. 完成`Editor`的析构函数。
9. 添加对各种异常情况的处理。异常情况如指定了行号区间、指定了超出范围的行号等。

除ed.cc外，可以随意更改代码及添加文件，实现了要求的功能即可。



**回答问题**：

1. 请解释在`Editor::dispatchCmd`中下述代码的逻辑，尤其注意对stringstream的使用。

```c++
    int start, end;
    char comma, type = ' ';
    stringstream ss(cmd);
    ss >> start;
    if (ss.eof()) {
        cmdNull(start);
        return;
    }
    ss >> comma >> end >> type;
    if (ss.good()) {
        if (type == 'n') {
            cmdNumber(start, end);
            return;
        } else if (type == 'd') {
            cmdDelete(start, end);
            return;
        }
    }
```



#### 使用样例

```
cmd> a  
It's input mode now. Quit with a line with a single dot(.)
#include <iostream>

int main()
{
}
.
cmd> 1,$n
1       #include <iostream>
2
3       int main()
4       {
5       }
cmd> 3
int main()
cmd> i
It's input mode now. Quit with a line with a single dot(.)
using namespace std;

#includ
.
cmd> 1,$n
1       #include <iostream>
2
3       using namespace std;
4
5       #includ
6       int main()
7       {
8       }
cmd> 4,5d
cmd> 1,$n
1       #include <iostream>
2
3       using namespace std;
4       int main()
5       {
6       }
cmd> 1,3c
? Bad/Unknown command
cmd> 1,4n
1       #include <iostream>
2
3       using namespace std;
4       int main()
cmd> a
It's input mode now. Quit with a line with a single dot(.)
    cout << "Hello my editor" << endl;
    
    return 0;
.
cmd> 1,$n
1       #include <iostream>
2
3       using namespace std;
4       int main()
5       {
6           cout << "Hello my editor" << endl;
7           
8           return 0;
9       }
cmd> write
? Bad/Unknown command
cmd> 1,999n
? Number range error
cmd> 4,2d
? Delete range error
cmd> 2019
? Line number out of range
cmd> w hello.cc
cmd> Q
```

### 提交

提交时，请将

- 你完成的MiniEd源代码压缩成7z压缩包，并重命名为`lab2-XXX.7z`
- 你对上述问题的回答`lab2-XXX.pdf`。

上传到 canvas 中。

（其中XXX为学号，如`lab2-518037910001.7z`和`lab2-518037910001.pdf`）

如果需要更改，请在文件名后加版本号，最终以最高版本号为准。如第二次提交可用`lab2-518037910001-2.7z`。

其余要求同 lab1。
