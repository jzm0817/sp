

##

### Big-Endian & Little-Endian

Big-Endian:内存低地址存放数据的高位

Little-Endian:内存高低址存放数据的高位

在 linux 中，对于可执行文件，可用
```shell
readelf -h file_name 
```
查看数据存放是大端还是小端

![](pic/Screenshot%20from%202022-07-04%2014-10-21.png)

据说，CPU决定是大端模式还是小端模式，但使用交叉编译器如 
```shell
aarch64_be-none-linux-gnu-g++
```
进行编译，得到的是大端模式的 elf 文件。


## Linux 查看 CPU 支持的指令集

```shell

cat /proc/cpuinfo
```