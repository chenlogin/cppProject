# C++ Project

## 编辑器：vs2022
## 目录结构

- src /：源代码文件夹，其中存放所有的.cpp文件和主程序文件。
- include /：头文件夹，其中存放所有的.h文件。
- lib /：库文件夹，可能包含需要的库文件。
- bin /：可执行文件文件夹，它通常用于存储从源代码编译出来的二进制文件。
- test /：测试文件夹，存放所有的测试代码和测试数据。
- doc /：文档文件夹，用于存储项目的文档，比如设计文档，用户手册等。
- Makefile或者CMakeLists.txt：这些文件用于描述如何构建项目。在C++项目中，通常使用make或者cmake工具来进行项目的构建。
- .gitignore：如果你使用git作为版本控制系统，那么你可能为了忽略掉编译过程中生成的临时文件，需要在项目根目录下创建.gitignore文件。