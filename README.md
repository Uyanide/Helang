## Helang 中的函数

Helang 中的函数是一种特殊的函数，它们的第一个参数固定为一个 `u8` 数组，第二个参数固定为该数组的大小，后续参数可变。例如：

```c
int myFunction(u8 flags[], size_t size, ...);
```

“但是这和普通的可变参数函数有什么不同呢？” 你或许会问。

—— Helang 函数的特殊之处在于它们的前两个参数并非通过传统的方式传递，而是使用位掩码。例如：

```c
myFunction(1 | 2 | 6);
```

在函数内部，`flags` 数组会被解析为：

```c
flags[0] = 1;
flags[1] = 2;
flags[2] = 6;
size = 3;
```

“为什么要这样设计呢？” 你或许会问。

—— Why not？

## 声明和定义自己的 Helang 函数

> [!NOTE]
>
> 完整的示例可以在[main.c](main.c)、[power.h](power.h) 和 [power.c](power.c) 中找到。

1. 首先你需要自己的头文件和实现文件，例如 `myfunc.h` 和 `myfunc.c`。：

   ```c
   // file: myfunc.h

   #ifndef HELANG_MYFUNC_H
   #define HELANG_MYFUNC_H

   #include "helang.h"

   #endif  // HELANG_MYFUNC_H
   ```

   ```c
   // file: myfunc.c

   #include "myfunc.h"
   ```

2. 在头文件中，你需要使用 `HE_DECLARE` 宏来声明你的函数接口。例如：

   ```c
   // file: myfunc.h

   // ...
   HE_DECLARE(myFunction_impl);
   // ...
   ```

   此处的 `myFunction_impl` 是你的函数实现的标识，可以根据需要更改，但必须与实际调用时使用的名称 `myFunction` 不同，且在下文中保持一致。

3. 接着你需要定义一个宏来简化函数调用。例如：

   ```c
   // file: myfunc.h

   // ...
   #define myFunction(flags, ...) HE_INVOKE(myFunction_impl, HE_FLAGS(flags), __VA_ARGS__)
   // ...
   ```

   此处的 `myFunction` 是你希望在代码中调用的函数名称。

4. 在实现文件中，你需要使用 `HE_IMPLEMENT` 宏来实现你的函数。例如：

   ```c
   // file: myfunc.c

   // ...
   HE_IMPLEMENT(myFunction_impl) {
       // 你的函数实现
       return 0;
   }
   ```

   在实现中，你可以将 `flags` 视为一个 `u8` 数组，`size` 视为该数组的大小，后续参数通过 `va_list* args` 访问。返回值应为 `int`, 例如：

   ```c
   // file: myfunc.c

   // ...
   HE_IMPLEMENT(myFunction_impl) {
       for (size_t i = 0; i < size; ++i) {
           printf("Flag %zu: %d\n", i, flags[i]);
       }
       int value = va_arg(*args, int);
       printf("Value: %d\n", value);
       return 0;
   }
   ```

5. 现在你可以在代码中调用你的 Helang 函数了。例如：

   ```c
   myFunction(1 | 2 | 6, 42);
   ```

   这将输出：

   ```
   Flag 0: 1
   Flag 1: 2
   Flag 2: 6
   Value: 42
   ```

## 其他特性

- 在 Helang 中，万物皆可 `u8`，万物皆为 `u8`。我们的实现也将尊重这一教义。

  - 如果你的 `u8` 属于简单类型，具体来说，（展开后）属于以下中的任意一种：

    - `char`
    - `unsigned char`
    - `short`
    - `unsigned short`
    - `int`
    - `unsigned int`
    - `long`
    - `unsigned long`
    - `long long`
    - `unsigned long long`
    - `float`
    - `double`

    那么你可以直接在 `u8.h` 文件中写入该类型。例如，如果你希望 `u8` 具有 32 位宽度：

    ```c
    // file: u8.h

    uint32_t // 你不需要包含 <stdint.h> 即可使用其中的类型
    ```

    是的，尽管你的 LSP 可能对此颇有微词，但你真的只需要将希望的类型写入 `u8.h` 文件中即可，并且可以随心所欲地添加注释和空行。

  - 如果你的 `u8` 属于复杂类型，例如结构体或联合体，那么你需要在 `u8_complex.h` 文件中定义一个宏来通知 Helang 使用复杂类型，并定义该类型。例如：

    ```c
    // file: u8_complex.h

    #define U8_COMPLEX_TYPE

    typedef struct {
        int field1;
        float field2;
    } u8;
    ```

    并同时提供一个静态变量 `HE_NULL` 一个函数 `strtou8`。前者用于表示 `u8` 类型的“空值”，后者用于将字符串转换为 `u8` 类型。例如：

    ```c
    // file: u8_complex.h

    static const u8 HE_NULL = {};

    u8 strtou8(const char*, char**); // 仅声明
    ```

    然后在随便什么源文件里实现 `strtou8` 即可：

    ```c
    // file: main.c

    u8 strtou8(const char* str, char** end) {
       u8 result;
       // 你的转换逻辑
       return result;
    }
    ```

    `strtou8` 的行为应与 C 标准库中的类似函数一致，例如 `strtol` 和 `strtod`。
