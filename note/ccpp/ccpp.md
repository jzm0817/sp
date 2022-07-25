
## std::endl  and  '\n'

> cppreference.com

fea:Inserts a newline character into the output sequence os and flushes it as if by calling os.put(os.widen('\n')) followed by os.flush().

notes:
This manipulator may be used to produce a line of output immediately, e.g. when displaying output from a long-running process, logging activity of multiple threads or logging activity of a program that may crash unexpectedly. An explicit flush of std::cout is also necessary before a call to std::system, if the spawned process performs any screen I/O. In most other usual interactive I/O scenarios, std::endl is redundant when used with std::cout because any input from std::cin, output to std::cerr, or program termination forces a call to std::cout.flush(). Use of std::endl in place of '\n', encouraged by some sources, may significantly degrade output performance.

In many implementations, standard output is line-buffered, and writing '\n' causes a flush anyway, unless std::ios::sync_with_stdio(false) was executed. In those situations, unnecessary endl only degrades the performance of file output, not standard output.

## .cc and .cpp

> https://stackoverflow.com/questions/18590135/what-is-the-difference-between-cc-and-cpp-file-suffix

Historically, the suffix for a C++ source file was .C. This caused a few problems the first time C++ was ported to a system where case wasn't significant in the filename.

Different users adopted different solutions: .cc, .cpp, .cxx and possibly others. Today, outside of the Unix world, it's mostly .cpp. Unix seems to use .cc more often.

For headers, the situation is even more confusing: for whatever reasons, the earliest C++ authors decided not to distinguish between headers for C and for C++, and used .h.

This doesn't cause any problems if there is no C in the project, but when you start having to deal with both, it's usually a good idea to distinguish between the headers which can be used in C (.h) and those which cannot (.hh or .hpp).

In addition, in C++, a lot of users (including myself) prefer keeping the template sources and the inline functions in a separate file. Which, while strictly speaking a header file, tends to get yet another set of conventions (.inl, .tcc and probably a lot of others).

In the case of headers it makes absolutely no difference to the compiler.

In the case of source files different endings will cause the compiler to assume a different language. But this can normally be overridden, and I used .cc with VC++ long before VC++ recognized it as C++.


## Input/Output Stream Library
> https://cplusplus.com/reference/

Input/Output Stream Library
Provides functionality to use an abstraction called streams specially designed to perform input and output operations on sequences of character, like files or strings.
This functionality is provided through several related classes, as shown in the following relationship map, with the corresponding header file names on top:

![](pic/Screenshot%20from%202022-07-04%2017-04-30.png)


## 零长度数组

> 嵌入式 C 语言自我修养 P286

ANSI C 标准规定：定义数组时，数组的长度要在编译时确定。 C99 标准支持变长数组，即编译时可以不知道数组的长度，在运行时指定数组的大小。

文中提及 GNU 的编译器支持零长数组，但使用其他编译器会报错

```c
// test code  t.c

#include <stdio.h>

int main(int argc, char** argv){
    int a[0];                   // zero length array
    size_t a_size = sizeof(a);
    // printf("%d\n", a_size);  // clang : warning  
    printf("%ld\n", a_size);    
    return 0;
}
```

<font color='red'> sizeof 不是函数 </font>

```shell
// gcc compiler
gcc -o build t.c

```

```shell
// clang compiler
clang t.c
```

clang warning :

![](pic/Screenshot%20from%202022-07-11%2010-42-46.png)


零长数组常常作为结构体的一个成员，构成一个变长结构体。零长数组不占用(结构体的)存储空间，但可以通过结构体的零长数组取访问内存。

<font color='red'> 书中 p288 的零长度数组类型为 int， gcc 编译时给出警告 </font>
![](pic/Screenshot%20from%202022-07-11%2014-38-48.png)

主要原因在 strcpy 函数的数据类型。

![](pic/Screenshot%20from%202022-07-11%2014-39-46.png)


``` C
// test code : zero length array 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct buff
{
    int len;
    char a[0];    // zero length array 
};


int main(int argc, char ** argv){

    struct buff * buf;
    printf("%d\n", sizeof(buf));
    printf("%d\n", sizeof(char));
    printf("%d\n", sizeof(int));
    buf = (struct buff *)malloc(sizeof(struct buff) + 20);
    buf -> len = 20;
    strcpy(buf -> a, "hello world!\n");
    puts(buf -> a);

    free(buf);
    return 0;
}
```

clang & gcc 均可通过编译，运行结果如下

![](pic/Screenshot%20from%202022-07-11%2014-49-07.png)

更为详细的内容可以参考：
> https://gcc.gnu.org/onlinedocs/gcc/Zero-Length.html#:~:text=A%20zero-length%20array%20can%20be%20useful%20as%20the,enclosing%20type%20as%20a%20result%20of%20tail%20padding.

以下截取其中部分内容：

Declaring zero-length arrays is allowed in GNU C as an extension. A zero-length array can be useful as the last element of a structure that is really a header for a variable-length object.

Although the size of a zero-length array is zero, an array member of this kind may increase the size of the enclosing type as a result of tail padding. The offset of a zero-length array member from the beginning of the enclosing structure is the same as the offset of an array with one or more elements of the same type. The alignment of a zero-length array is the same as the alignment of its elements.

Declaring zero-length arrays in other contexts, including as interior members of structure objects or as non-member objects, is discouraged. Accessing elements of zero-length arrays declared in such contexts is undefined and may be diagnosed.

## 没有成员的结构体

> https://gcc.gnu.org/onlinedocs/gcc/Empty-Structures.html#Empty-Structures


```C

#include <stdio.h>

int main(){
    struct empty {

    };

    printf("%d\n", sizeof(struct empty));

}

```
![](pic/Screenshot%20from%202022-07-11%2014-32-29.png)

``` cpp

#include <iostream>
#include <cstdio>

int main(){
    struct empty {

    };

    printf("%d\n", sizeof(struct empty));
    // std::cout << sizeof(struct empty) << '\n';
}
```
![](pic/Screenshot%20from%202022-07-11%2014-33-14.png)


C 中，没有成员的结构体长度为 0. C++ 中，没有成员的结构体是语言的一部分， g++ compiler 会将其视为含有一个 char 成员的结构体。


## 寄存器操作

### 位运算应用

#### 高低位互换

#### 判断一个数是否为 2 的整数次幂

``` c
int num;

if ((num) & (num - 1) == 0){
    print("%d is power of 2 \n", num);
else{
    print("%d is not power of 2 \n", num);
    }
}
```
<font color='orange'> 若一个数是 2 的整数次幂，则它只有某一位(二进制视角下)为 1，其他位全为 0.这种情况下，将其值减 1 后，1 对应位的低位全为 1，其他位全为 0，再与其本身进行异或运算后结果为 0. </font>


#### 一个数对另一个数做 2 次异或运算，等于其本身
$$ x \wedge a \wedge  a = x$$


设 $x$ 为布尔数
$$ x \& 0 = 0 \\ x | 1 = 1 \\ x \wedge 1 =  not(x) \\
x \wedge 0 = x$$

某位与 1 进行异或运算相当于对该位取反，与 0 进行异或运算保持不变。
某位与 0 进行同或运算相当于对该位取反，与 1 进行同或运算保持不变。


#### 利用异或运算交换两个变量的值

```c
void swap(int *a, int *b){
    *a = *a ^ *b;
    *b = *a ^ *b;   // b = a
    *a = *a ^ *b;   // a = b    notice:(*b = *a)
}
```

#### 清零和置位(掩码 + 位运算)

ex. 将 32 bit 数据 0xFFFF0000 低 4 位置位

```c
int num = 0xFFFF0000;
int num_mod0 = num | 0x0F; 
int num_mod1 = num | (0x1 | 0x1 << 1 | 0x1 << 2 | 0x1 << 3);  // 适合非连续位的清零

```

ex. 0xFFFFFFFF 部分位清零 (bit 4 ~ bit 7 清零)

``` c
int num = 0xFFFFFFFF;
int num_mod0 = num & 0xFFFFFF0F;
int num_mod1 = num & ~(0x000000F0);     // 要清除的位用 1 表示
int num_mod2 = num & ~(0x1 << 4 | 0x1 << 5 | 0x1 << 6 | 0x1 << 7);
```


### 位域

<font color='orange'> 存在一定的阅读障碍，从代码可读性和可维护性考虑，进行寄存器操作时建议使用掩码 + 位运算的操作。</font>
位域一般和结构体类型结合使用，结构体内各成员的存储是按比特位分配的。

```C
struct register_usb{
    unsigned short en:1;
    unsigned short ep:4;
    unsigned short mode:3;
};
```

位域可以和联合体结合使用，使用方法和联合体的使用是一致的。

匿名位域：
``` C
struct register_usb2{
    unsigned short en:1;
    unsigned short :4;
    unsigned short mode:3;
};
```

``` C
// test for bit sfield

#include <stdio.h>
#include <stdint.h>

int main(){
    struct bitfield{
        uint8_t en   : 1;
        // uint8_t clk;
        uint8_t ep   : 4;
        uint8_t mode : 3; 
      
    };
    
    struct normal
    {   
        uint8_t en;
        uint8_t ep;
        uint8_t mode;
    };
    
    printf("%d Byte is occupied\n", sizeof(struct normal));
    printf("%d Byte is occupied\n", sizeof(struct bitfield));

}

```

![](pic/Screenshot%20from%202022-07-11%2016-19-17.png)

若将 bitfield 修改为 

```C
    struct bitfield{
        uint8_t en   : 1;
        uint8_t clk;
        uint8_t ep   : 4;
        uint8_t mode : 3; 
      
    };
```
![](pic/Screenshot%20from%202022-07-11%2016-20-36.png)

> C 和指针 10.5 位段

![](pic/Screenshot%20from%202022-07-11%2016-24-26.png)
![](pic/Screenshot%20from%202022-07-11%2016-22-41.png)



