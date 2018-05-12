# Lex

## Token Type 分类

* KEY_WORD(关键字)

```C

数据类型
["int", "float", "char", "double", "void"]

控制语句
["for", "if", "else", "while", "do"]

宏
["include"]

函数返回
["return"]
```

* IDENTIFIER(标识符)

```C
字母 or 数字 or 下划线
不以数字开头
```

* DIGIT_CONSTANT(数字常量)

```C
整数 or 点十浮点数
```

* OPERATOR(运算符)

```C
[ '=', '&', '<', '>', '++', '--', '+', '-', '*', '/', '>=', '<=', '!=' ]
```

* SEPARATOR(分隔符)

```C
['(', ')', '{', '}', '[', ']', ',', '\"', ';']
```

* STRING_CONSTANT(字符串常量)

```C
"STRING_CONSTANT"
```

## 识别流程

```C
start
```

```C
-> if '#' 识别 include 及其头文件

exp:

#include <stdio.h>

# TokenType::SHARP 分隔符
include TokenType::INCLUDE 关键字
< TokenType::LT 分隔符
stdio.h TokenType::IDENTIFIER 标识符
> TokenType::GT 分隔符

or
#include "source.h"

# TokenType::SHARP 分隔符
include TokenType::INCLUDE 关键字
" TokenType::DOUBLE_QUOTE 分隔符
stdio.h TokenType::IDENTIFIER 标识符
" TokenType::DOUBLE_QUOTE 分隔符
```

```C
-> if 字符 或 下划线 识别标识符
并判断是否为关键字

exp:

int TokenType::INT 关键字

value TokenType::IDENTIFIER 标识符
```

```C
-> if 数字 识别数字常量
```

```C
-> if 运算符 识别运算符
```

```C
-> if 分隔符 识别分隔符
若遇到 " 则识别字符串常量
```