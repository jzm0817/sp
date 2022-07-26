
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
$ x \& 0 = 0 \\ x | 1 = 1 \\ x \wedge 1 =  not(x) \\
x \wedge 0 = x$

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


## 整型常量

如果一个整型常量的第一个字符是数字0,那么该常量将被视为八进制数。现代编译器会检查数字在八进制下是否合法，非法的数字会报错。

```c
#include <stdio.h>

int main(){
    int a = 010;
    printf("%d\n", a);
}

```
![](pic/Screenshot%20from%202022-07-25%2014-13-26.png)


## 字符与字符串
单引号和双引号的含义不同。

单引号引起的一个字符实际上代表一个**整数**，整数值对应于该字符在编译器采用的字符集（如ASCII 字符）中的序列值。

双引号引起的字符串，代表的是一个指向无名数组起始字符的指针，该数组被双引号之间的字符及一个额外的二进制值为零的字符 '\0' 初始化。
两者混用，编译器的类型检查功能会检测到错误。


## 数组与指针

### const char **  and char **

```c
const char *
```
const 关键字修饰的是指针所指向的类型，也即 char 类型，而不是修饰指针本身，因此它不是一个有限定符的指针类型。

```c
char **
```
是指向 char 类型的指针的指针

```c
const char **
```
是指向 const char 类型的指针的指针

const char **  and char ** 均是没有限定符的指针类型，区别在于它们所指向的类型不同。

若赋值过程是合法的，则需满足：两个操作数都是指向有限定符或无限定符的相容类型的指针，左边指针必须具有右边指针所指向类型的全部限定符。


```c

char *cp = "hello";
const char *cpp = "world";
cpp = cp;    // legal
cp = cpp;    // illegal
```
![](pic/Screenshot%20from%202022-07-25%2015-04-26.png)


### 理解 C 语言声明的优先级规则

A 声明从它的名字开始读取，然后按照优先级顺序依次读取。

B 优先级从高到低依次是：

B1 声明中被括号扩起来的部分

B2 后缀操作符：

( ) 表示这是一个函数

[ ] 表示这是一个数组

B3 前缀操作符：

\* 表示指向 ... 的指针

C const volatile 关键字的**后面**紧跟类型说明符，那么它作用于类型说明，其他情况下，作用于它**左边紧邻**的指针星号。

```c
char * const *(*next)();
```
变量名 next，并被括号扩住，注意该括号内部，则为指向 ... 的指针。

再看括号外部，还有一个括号，则说明为函数，next 是一个函数指针，指向一个返回 ... 的函数。

最后看其余部分，const 后的 \* 表示得到指针所指地址的内容，且该指针为常量指针，const 前面的 char \* 表示为指向字符。

综上，next 是一个指针，它指向一个函数，该函数返回另一个指针，该指针指向一个类型为 char 的常量指针。


```c
char * (*c[10]) (int **p);
```
变量名为 c ，先看包含 c 的括号内，优先看后缀，表示数组，再看到有 \* 表示为指针，这一部分： c 是数组，其中的元素为指针。

再看 c 扩号外的部分，有括号，表示这是函数。

再看函数的返回类型为指向 char 类型的指针。

综上，c 是一个包含 10 个元素的数组，数组的元素为函数指针，其所指向的函数的返回值是一个指向 char 类型的指针，该函数以一个指向 char 类型指针的指针为唯一参数。


### 指针与数组

#### 定义与声明

C 语言中的对象（跟链接器有关的，如函数和变量）必须有且只有一个定义，但可以有多个 extern 声明。定义是一种特殊的声明，它创建了一个对象；声明简单地说明了在其他地方创建的对象的名字，它允许你使用这个名字。

定义：确定对象的类型并**分配内存**，用于创建新的对象。

声明：描述对象的类型，用于指代其他地方定义的对象。

extern 对象声明告诉编译器对象的类型和名字，对象内存分配则在别处进行。由于并未在声明中为数组分配内存，所以并不需要提供关于数组长度的信息。对于多维数组，需要提供除最左边一维之外的其他维度的信息。

#### 数组和指针的访问

```C
x = y；
```
x ： x 所代表的地址，称为左值，左值在编译时可知，表示存储结果的地方。

y ： y 所代表的是地址的中的内容，称为右值，在运行时可知，表示 xx 的内容。

C 语言引入了术语“可修改的左值”。表示左值允许出现在赋值语句的左边。数组名也用于确定对象在内存中的位置，也是左值，但它不能作为赋值的对象。数组名是个左值，但不是可修改的左值。

编译器为每个变量分配一个地址（左值），这个地址在编译时可知，而且该变量在运行时一直保存于这个地址。相反，存储于变量中的值（它的右值），只有在运行时才可知，如果要用到变量中存储的值，编译器就发出指令从指定地址读入变量的值并将它存于寄存器中。

##### 数组的访问

```c
char a[] = {1, 2, 3};

c = a[i];
```

编译器符号表具有一个地址 address

运行时1： 取 i 的值，将它与 address 相加

运行时2： 取地址 （address + i）中的内容

##### 指针的访问

```c
char *p; 

c = *p;
```
编译器符号表有一个符号 p， 地址为 address

运行时1： 取 address 中的内容 content

运行时2： 取地址 content 中的内容


##### 定义为指针，但以数组方式访问

```c
char *p = "abcdef";

c = p[i];
```
编译器符号表有一个符号 p， 地址为 address

运行时1： 取 address 中的内容 content

运行时2： 取 i 的值，将它与 content 相加

运行时3： 取地址 i + content 中的内容

p[i] 表示从 p 所指的地址开始，前进 i 步，移动间隔为一个指针所指类型占用的空间。


#### 数组与指针的其他区别
指针：

1.保存数据的地址

2.间接访问数据，首先取得指针的内容，把它作为地址，然后从这个地址中提取数据。如果指针有下标，就把指针的内容加上下标作为地址，从地址中提取数据
3.通常用于动态数据结构

4.相关的函数为 malloc(), free()

5.通常纸箱匿名数据

数组：

1.保存数据

2.直接访问数据，如有下标，只是简单地从其实地址加上下标的地址获取数据

3.通常用于存储固定数据且数据类型相同的元素

4.隐式分配和删除

5.自身即为数据名



### 数组与指针相同时
在实际应用中，数组和指针可以互换的情况要比不可互换的情形更为常见。

声明：

1.外部数组的声明

2.数组的定义(定义是声明的一种特殊情况，它分配内存空间，并可能提供一个初始值

3.函数参数的声明

**所有作为函数参数的数组名总是可以通过编译器转换为指针**。在使用数组时，数组总是可以写成指针的形式。

数组在声明：

1.extern 不能该写成指针的形式

2.定义，不能改写成指针的形式

3.函数的参数，可以写成指针形式，也可写成数组形式(func(char a[ ]))

数组在表达式中使用

可以写成指针或数组形式

数组和指针在编译器处理时是不同的，在运行时的表示形式也是不一样的，并可能产生不同的代码。对编译器而言，一个数组就是一个地址，一个指针就是一个地址的地址。


什么时候数组和指针是相同的

规则1 表达式中的数组名(与声明不同)被编译器当作一个指向该数组第一个元素的指针

规则2 下标总是与指针的偏移量相同

规则3 在函数参数的声明中，数组名被编译器当作指向该数组第一个元素的指针

规则1： **表达式中的数组名就是指针**

对数组下标的引用总是可以写成一个指向数组起始地址的指针加上偏移量。
如声明
```c
int a[10], *p, i = 2;
```
可以通过以下三种方式进行访问：
```c
p = a;
p[i];   // i[p];

```

```c
p = a;
*(p + i);

```

```c
p = a + i;
*p;

```

对数组的引用如 a[i] 在编译时总是被编译器改写成 *(a + i) 的形式。C 语言标准要求编译器具备这个概念性的行为。[ ] 表示一个取下标操作符，作用过程取一个整数和一个指向 T 类型的指针，产生的结果是一个指向 T 类型的指针，一个在表达式中的数组名就成了指针。**在表达式中，数组和指针可以互换，因为在编译器的作用后都是指针的形式，并且可以进行取下标的操作，**甚至取下标操作符的操作数是可交换的。       

编译器自动把下标值的步长调整到数组元素的大小。对起始地址执行加法操作前，编译器会计算每次增加的步长。这就是为什么指针总是有类型限制，每个指针只能指向一种类型的原因。


规则2: **C 语言把数组下标作为指针的偏移量**

数组下标是定义在指针的基础之上的，不论是指针还是数组，在连续的内存地址上移动时，编译器必须计算每次前进的步长。处理一维数组时，指针不见得比数组更快，C 语言把数组下标改为指针偏移量的根本原因是指针和偏移量是底层硬件所使用的基本模型。

规则3： **作为函数参数的数组名等同于指针**

作为类型的数组的形参声明应调整为类型的指针。在函数形参定义这一特殊情况下，编译器必须把数组形式改写为指向数组第一个元素的指针的形式。编译器只向函数传递数组的地址，而不是整个数组的拷贝。


#### 为什么把数组形参当做指针

非数组形式的参数实参均以值传递调用（对实参做一份拷贝并传递给调用的函数，函数不能修改作为实参的实际变量的值，只能修改传递给它的那份拷贝）。类似地，函数的返回值不能是一个函数数组，只能是指向数组或函数的指针。
数据也可以传址调用，只要加上取地址符 &，这样传递给函数的是实参的地址。

形参可以声明为数组或指针的形式，但在函数内部，编译器始终把他当做一个指向数组第一个元素（元素长度未知）的指针。不论是何种形式，函数并不能自动地知道所指的数组共有多少个元素，所以必须要有个约定，如数组以 NUL 结尾或者另有一个附加的参数表示数组的范围。


```c
func(int * tunip) {}
func(int tunip[]) {}
func(int tunip[200]) {}

int my_int;
int *my_ptr;
int my_array[10];
```

可以合法地使用下列任何一个实参来调用上面任何一个原型的函数。

```c
func(&my_int);          // int 参数的传址调用
func(my_ptr);           // 传递指针
func(my_array);         // 传递数组
func(&my_array[i])      // 传递数组的一部分
```

在函数的内部，则无法容易地分辨这些不同的实参，也就无法得知调用该函数的目的。所有属于函数实参的数组在编译时被编译器改写为指针，在函数内部对数组参数的任何引用都将残生一个对指针的引用。


```c

#include <stdio.h>
#include <stdint.h>

void func1(char ca[]);
void func2(const char * pa);

const char * ga = "Hello_world!";

int main(){
    char ca[] = "Hello_world!";
    const char * pa = "Hello_world!";

    func1(ca);
    func2(pa);

    printf("&ga:%p\n", &ga);
    printf("&(ga[0]):%p\n", &(ga[0]));
    printf("&(ga[1]):%p\n", &(ga[1]));
    printf("*(&(ga[0])):%c\n", *(&(ga[0])));
    printf("*(&(ga[1])):%c\n", *(&(ga[1])));
    printf("sizeof(ga): %lu Byte\n", sizeof(pa));
    printf("sizeof(const char *): %lu Byte\n", sizeof(const char *));
    printf("sizeof(const int *): %lu Byte\n", sizeof(const int *));
    printf("sizeof(const char): %lu Byte\n", sizeof(const char));
    printf("sizeof(const int): %lu Byte\n", sizeof(const int));
    printf("sizeof(int): %lu Byte\n", sizeof(int));
    printf("sizeof(uint16_t): %lu Byte\n", sizeof(uint16_t));
}


void func1(char ca[]){
    printf("&ca:%p\n", &ca);
    printf("&(ca[0]):%p\n", &(ca[0]));
    printf("&(ca[1]):%p\n", &(ca[1]));
}

void func2(const char * pa){
    printf("&pa:%p\n", &pa);
    printf("&(pa[0]):%p\n", &(pa[0]));
    printf("&(pa[1]):%p\n", &(pa[1]));
    printf("pa+1:%p\n", pa + 1);
    printf("++pa:%p\n", ++pa);
}
```

![](pic/Screenshot%20from%202022-07-26%2008-36-33.png)

修改

```c
const char * ga = "Hello_world!";    // global

const char * pa = "Hello_world!!";   // local
```
![](pic/Screenshot%20from%202022-07-26%2008-38-46.png)


#### 数组片段
可以让指针指向数组的任何一个元素，这样传递给函数的就是从该元素之后的数组片段。


#### 指针和数组可交换总结
1 用 a[i] 这样的形式访问数组，总是会被编译器改写为 *(a+i) 这样的指针访问。

2 指针就是指针，决不能改写为数组。可以用下标的形式访问指针，一般都是作为函数的参数时，而且你知道实际传递给函数的是一个数组。

3 在特定的上下文中，也就是它作为**函数的参数(也只有这种情况)**，一个数组的声明可以看作是一个指针。作为函数参数的数组(就是在一个函数调用中)始终会被编译器修改为指向数组第一个元素的指针。

4 当把一个数组定义为函数的参数时，可以选择把它定义为数组，也可以定义为指针，不论何种方法，在函数内部实际上获得的是一个指针。

5 在其他所有情况下，定义和声明必须匹配。如果定义了一个数组，在其他文件对它进行声明时也必须把它声明为数组，指针也如此。


### 多维数组

C 语言的多维数组：数组的数组

注意不能把几个范围下标如 [i][j][k] 写成 [i, j, k]，写成后一种形式实际上是将逗号表达式的结果作为要访问的下标。

```c
char carrot [10][20];

// means
typedef char vegetable[20];   // vegetable means char [20]
vegetable carrot[10];

```
变量名：carrot，后缀[10] ，表示它是一个具有 10 个元素的数组，每个元素是长度为 20 的 char 类型的数组。

carrot 是一个具有 10 个元素的数组，每个元素是一个 vegetable，也是数组，因此多维数组可视为数组的数组。


访问单个字符 carrot[i][j],编译时解析为 \*(\*(carrot + i) + j) 的形式。

计算时需要调整 i 的长度为 i * j  代表真实的偏移量。


正常情况下，赋值发生在两个相同的类型之间，而在表达式中，数组被编译器视为指向数组第一个元素的指针，**可以把数组赋值给一个指针，但不能把数组赋值给另一个数组，**因为数组作为一个整体不能成为赋值的对象。

指针所指向数组的维度不同，则自增运算的区别会很大。


```c
#include <stdio.h>
#include <stdint.h>

#define X 2
#define Y 3
#define Z 5

int main(){

    typedef char my_type;
    my_type array_mul[X][Y][Z] = {0};

    printf("sizeof(my_type): %lu \n", sizeof(my_type));
    printf("sizeof(array_mul): %lu \n", sizeof(array_mul));

    my_type (*e)[Y][Z] = array_mul;
    my_type (*r)[Z] = array_mul[0];
    my_type *t = array_mul[0][0];

    printf("array_mul: %p \n", array_mul);
    printf("e    : %p \n", e);
    printf("e + 1: %p \n", e + 1);
    printf("r    : %p \n", r);
    printf("r + 1: %p \n", r + 1);
    printf("t    : %p \n", t);
    printf("t + 1: %p \n", t + 1);

}
```

e 是指针，指向一个二维数组，r 是一个指向一维数组的指针，t 是指向一个 my_type 类型的指针。因此对上述指针进行移动，每次移动的距离分别为

e: sizeof(my_type) * Y * Z

r: sizeof(my_type) * Z

t: sizeof(my_type)


result(my_type is char):

![](pic/Screenshot%20from%202022-07-26%2009-26-04.png)


result(my_type is unint16_t)

![](pic/Screenshot%20from%202022-07-26%2009-31-41.png)


C 语言的多维数组，**<font color='red'>最右边</font>** 的下标是最先变化的，这个约束也成为行主序(仅对二维数组称行/列主序，更高维的数组一般称最右的下标先变化)。

最低地址  <------------------------------> 最高地址
int a[2][3] a[0][0]  a[0][1]  ...  a[2][3]

C 语言的多维数组最大的用途就是存储多个字符串，最右下标先变化这一特点使得每个字符串中相邻的字符在内存中也相邻存储。


#### 最后
```c

#include <stdio.h>
#include <stdint.h>

char ga[] = "abcdefghijklmn";

void my_array_func(char ca[10]){
    printf("       &ca: %p \n", &ca);
    printf("sizeof(ca): %lu \n", sizeof(ca));
    printf("  (*(&ca)): %p \n", (*(&ca)));
    printf("  & ca[0]): %p \n", &(ca[0]));
    printf("  &(ca[1]): %p \n", &(ca[1]));
    printf("      ++ca: %p \n", ++ca);
    printf("\n");
}

void my_pointer_func(char * pa){
    printf("       &pa: %p \n", &pa);
    printf("sizeof(pa): %lu \n", sizeof(pa));
    printf("  (*(&pa)): %p \n", (*(&pa)));
    printf("  &(pa[0]): %p \n", &(pa[0]));
    printf("  &(pa[1]): %p \n", &(pa[1]));
    printf("      ++pa: %p \n", ++pa);   
    printf("\n");
}

int main(){
    printf("sizeof(ga): %lu \n", sizeof(ga));
    printf("       &ga: %p \n", &ga);
    printf("  (*(&ga)): %p \n", (*(&ga)));
    printf("  &(ga[0]): %p \n", &(ga[0]));
    printf("  &(ga[1]): %p \n", &(ga[1]));
    printf("\n");

    my_array_func(ga);
    my_pointer_func(ga);
}
```

![](pic/Screenshot%20from%202022-07-26%2010-04-06.png)

数组作为函数的参数时，会转换为指针类型。
![](pic/Screenshot%20from%202022-07-26%2010-05-10.png)

参数调用为传址调用，传入 ga 第一个元素的地址，该地址由一个指针保存(指针的值为 ga 第一个元素的地址)，显然该指针的地址和 ga 的第一个元素的地址不同。数组 ca 被转换为 char * 类型的指针，在 x86_64 机器上使用 sizeof 的结果是 8 。


#### 再论指针

##### 多维数组的内存布局
多维数组的单个元素的存储和引用实际上是以线性形式排列在内存中的。
```c
type p[i][j]
```
p 是包含 i 个元素的数组，每个元素都是长度为 j 的 type 类型的数组。

因此 p[i][j] 将被编译器解释为 \*(\*(p + i) + j)

计算时需要调整 i 的长度为 i * j 代表真实的偏移量。

##### 指针数组
```c
char *p[N];
```

p 是包含 N 个元素的数组，每个元素为指向 char 类型的指针。

当看到 squash[i][j] 这样的引用形式时，不知道 squash 的声明为以下的哪种

```
int squash[X][Y];    // 二维数组
int *squash[X];      // 含 X 个 int 类型指针的数组
int **squash;        // int 类型指针的指针
int (*squash)[Y];    // 指向长度为 Y int 类型的指针
```
这点类似于在函数内部无法分辨传递给函数的实参究竟是数组还是指针。这是因为作为左值的数组名被编译器解析为指针。

##### 数组的数组
```c
type a[X][Y];
```
**a 表示包含 X 个长度为 Y type 类型数组的数组**

取 a[i][j]

假设编译器的符号表中，a 的地址为 addr

运行1：取 i 的值，把它的长度调整为行的长度 Y，计算 res1 = i * Y + addr

运行2：取 j 的值，长度为一个元素的长度，此处为 type 类型的长度，计算 res2 = res1 + j * sizeof(type)

运行3：从地址 res2 中取出内容

##### 指针数组(数组，元素为指针)

```c
type *p[X]
```
**p 为包含 X 个指向 type 类型数据指针的数组**
取 p[i][j]

假设编译器的符号表中，p 的地址为 addr

运行1：取 i 的值，计算 res1 = addr + i * sizeof(type) * X

运行2：从 res1 中取出内容 addr2

运行3：取 j 的值，计算 res2 = j * sizeof(type)

运行4：从地址 res2 中取出内容


##### 数组和指针是如何被编译器修改的

|实参|所匹配的形参|
|---|----|
|type c[X][Y] (数组的数组)|type (*) [Y] (数组指针(行指针))|
|type *c[X] (指针数组)|type **c (指针的指针)||
|type (*c)[Y] (数组指针(行指针))|type (*c)[Y] (数组指针(行指针))|
|type **c (指针的指针)|type **c (指针的指针)|

指针**数组**和数组**指针**的关键在后。指针数组是数组，数组指针是指针。