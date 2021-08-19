

from _typeshed import StrPath


def tech_swap_var(a,b):
    a,b = b,a
    return a,b


def tech_string_format():
    # 1
    name = "Rose"
    s = "hi, I am " + name
    print(s)

    # 2 %替换
    name = "Rose"
    country = "china"
    age = 23

    s = "hi, I am %s. I'm from %s. and I'm %d" % (name,country,age)

    # 3 .format()
    s = "hi, I am{}. I'm from {}. and I'm {}".format(name,country,age)
    # 如果有重复的需要被替换的内容，可以在花括号里写入被替换参数的索引
    s = "hi, I am{0}. And I'm {0}".format(name,country,age)
    # { [index][ : [ [fill] align] [sign] [#] [width] [.precision] [type] ] }

    # 4 f-string python>=3.6
    s = f"hi, I am {name}. I'm from {country}. and I'm {age}"

def tech_yield_fibonacci(n):
    # ------------------
    # old
    # ------------------
    a = 0
    b = 1
    nums = []
    for _ in range(n):
        nums.append(a)
        a, b = b, a+b
    return nums

    # ------------------
    # new 不需要等待整个列表生成 yield 产出，生产
    # ------------------
    for _ in range(n):
        yield a
        a, b = b, a+b

for i in tech_yield_fibonacci(10):
    print(i)


def tech_list_comprehension():
    # 列表解析式

    arashi = ["ohno","sho","aiba","nino","jun"]
    # ------------------
    # old
    # ------------------
    for i in range(len(arashi)):
        arashi[i] = arashi[i].upper()

    # ------------------
    # new
    # ------------------
    arashi = [x.upper() for x in arashi ]
    # 筛选过滤 
    filter_arashi = [x for x in arashi if x.startswith("a")]


def tech_enumerate():
    arashi = ["ohno","sho","aiba","nino","jun"]
    for idx, el in enumerate(arashi):
        print(idx, el)


def tech_looping_backwards():
    # 反向遍历
    arashi = ["ohno","sho","aiba","nino","jun"]
    for idx, el in enumerate(reversed(arashi)):
        print(idx, el)


def tech_sorted():
    arashi = ["ohno","sho","aiba","nino","jun"]
    for idx, el in enumerate(sorted(arashi)):
        print(idx, el)


def tech_dict_merge():
    a = {"121":12,"121":12,"121":12,"121":12}
    b = {"121":12,"121":12,"121":12}

    c = {**a,**b}


def tech_sequence_unpcking():
    # 序列解包
    name = "Ohno Satoshi"

    # ------------------
    # old
    # ------------------
    str_list = name.split()
    first_name = str_list[0]
    last_name = str_list[1]

    # ------------------
    # new
    # ------------------
    first_name, last_name = name.split()


if __name__ == "__main__":

    tech_string_format()
