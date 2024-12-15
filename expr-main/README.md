# 编译
1. 如果你在Linux环境中，请在项目根目录下执行以下命令进行编译：
```shell
gcc ./src/expr.c ./test/test.c -Iinclude -std=c17 -o expr
```
或者执行：
```shell
gcc $(find . -name "*.c") -Iinclude -std=c17 -o expr
```
2. 如果你在Windows环境中，请在项目根目录下执行以下命令进行编译：
```shell
gcc .\src\expr.c .\test\test.c -std=c17 -o expr
```
3. 使用cmake编译
```shell
mkdir build
cd build
cmake ..
cmake --build .
```
如果你使用clion，可以根据ide的提示，选择cmakeList.txt进行构建项目。

# 运行
对于Linux环境，可以在项目根目录下执行以下命令运行：
```shell
./expr c e r # c表示测试 check_parentheses, e 表示测试 expr, r 表示运行计算器，具体传入的参数由你决定
```
对于Windows环境，可以在项目根目录下执行以下命令运行：
```shell
.\expr.exe c e r # c表示测试 check_parentheses, e 表示测试 expr, r 表示运行计算器，具体传入的参数由你决定
```
对于clion此类ide，可以在终端按照上述方法运行，也可以在ide可执行程序的运行配置中传入实参。
