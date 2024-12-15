# Emulator

`Emulator`是一个基于`RISC-V`32位指令集的指令解释器，可以实现简单的`RISC-V`指令的执行

## 编译

### 使用命令行编译

在Linux下，使用下列命令来进行编译

```sh
gcc $(find . -name "*.c") -o Emulator -Iinclude/ -std=c17 -O2 -Wall -fdiagnostics-color=always
```

在Windows下，在powershell中执行下列命令

```pwsh
gcc (Get-ChildItem -Recurse -Path "src" -Filter "*.c" | Select-Object -ExpandProperty FullName) -o Emulator -Iinclude/ -std=c17 -O2 -Wall -fdiagnostics-color=always
```

### 使用CMake进行编译

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## 运行

编译得到的可执行文件按照以下方式执行

```sh
./Emulator.exe IMG
```

其中`IMG`请替换成要执行的riscv镜像路径，如果无镜像提供，则默认使用内部镜像，只会执行一句ebreak来结束运行