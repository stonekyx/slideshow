##编译环境要求
* Linux
* g++
* automake
* autoconf
* libtool
* make
* SDL（目前还没实现绘图，所以暂时没有也没关系）
* boost

在大多数发行版上应该都能在软件包管理器里找到，比如Ubuntu的apt-get。
理论上可以在Windows、MacOS上编译，但是需要进行一些调整。暂时只支持Linux。

##编译过程
在项目文件夹下执行：
```
mkdir m4
autoreconf -fi
./configure
make V=0
```
暂时不考虑安装的问题。

##运行
在项目文件夹下执行：
```
./main
```
目前只是读取`test.slide`文件，然后输出解析的结果，没有实际绘图。
