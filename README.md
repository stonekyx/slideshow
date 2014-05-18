##编译环境要求
* Linux
* g++
* automake
* autoconf
* libtool
* make
* SDL2 ~~（目前还没实现绘图，所以暂时没有也没关系）~~
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
目前只是读取`test.slide`文件，然后输出解析的结果，~~没有实际绘图~~同时会有一个黑色的窗口。真正的图形将会显示在这个窗口里。

##已知问题
如果使用awesome窗口管理器，可能无法显示黑色窗口，而是显示一个无响应的透明窗口。目前的运行方法是切换到twm，或者在Xephyr里运行twm。
