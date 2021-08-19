

变量使用

```makefile
# 定义变量
# 变量名 = 值
CC = gcc
CFLAG = --std=c11 -lpthread

# 使用变量
# $(变量名)
main: main.c
	$(CC) $(CFLAG)-o main main.c

```

表达式
```makefile
# 伪目标命令

# =  verbatim assignment
# := simple expansion
# != shell output
# ?= conditional assignment
# += append to
# 
# $@ current target
# $< first prerequisite
# $^ all prerequisites
# $? prerequisites that have changed
# $| order-only prerequisites


```


伪目标
```makefile

# .PHONY是一个伪目标，可以有效防止在Makefile文件中定义的可执行命令的目标规则和工作目录下的实际文件出现名称冲突，并提高了执行Makefile的性能

.PHONY:all clean install

all: main1 main2

main1:main1.c
	gcc -o mian1 main1.c

main2:main2.c
	gcc -o mian2 main2.c

install:

clean:
	rm -f tmp

```
