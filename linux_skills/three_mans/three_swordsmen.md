
## grep
用于查找比较多

    (1)find命令是根据文件的属性进行查找，如文件名，文件大小，所有者，所属组，是否为空，访问时间，修改时间等。 
    (2)grep是根据文件的内容进行查找，会对文件的每一行按照给定的模式(patter)进行匹配查找。 

## sed
文本编辑与替换,vim 的命令行模式部分兼容了sed的命令

全局替换关键字
```shell

$ %s/[old_word]/new_word/g

```

## awk
数据分析与生成报告

AWK 是一种处理文本文件的语言，是一个强大的文本分析工具。
之所以叫 AWK 是因为其取了三位创始人 Alfred Aho，Peter Weinberger, 和 Brian Kernighan 的 Family Name 的首字符。
    
    有内置变量
    内置算数函数
    内置字符串函数

$0 表示一整行
