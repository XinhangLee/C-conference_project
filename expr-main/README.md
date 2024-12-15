# ����
1. �������Linux�����У�������Ŀ��Ŀ¼��ִ������������б��룺
```shell
gcc ./src/expr.c ./test/test.c -Iinclude -std=c17 -o expr
```
����ִ�У�
```shell
gcc $(find . -name "*.c") -Iinclude -std=c17 -o expr
```
2. �������Windows�����У�������Ŀ��Ŀ¼��ִ������������б��룺
```shell
gcc .\src\expr.c .\test\test.c -std=c17 -o expr
```
3. ʹ��cmake����
```shell
mkdir build
cd build
cmake ..
cmake --build .
```
�����ʹ��clion�����Ը���ide����ʾ��ѡ��cmakeList.txt���й�����Ŀ��

# ����
����Linux��������������Ŀ��Ŀ¼��ִ�������������У�
```shell
./expr c e r # c��ʾ���� check_parentheses, e ��ʾ���� expr, r ��ʾ���м����������崫��Ĳ����������
```
����Windows��������������Ŀ��Ŀ¼��ִ�������������У�
```shell
.\expr.exe c e r # c��ʾ���� check_parentheses, e ��ʾ���� expr, r ��ʾ���м����������崫��Ĳ����������
```
����clion����ide���������ն˰��������������У�Ҳ������ide��ִ�г�������������д���ʵ�Ρ�
