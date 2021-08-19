import re


s = "fool123bar"
# re.search 扫描整个字符串并返回第一个成功的匹配
result = re.search("123",s)

print(type(result))
print(result)

print(result.span())
print(result.start())
print(result.end())

# re.match(pattern, string, flags=0)
# re.match 尝试从字符串的起始位置匹配一个模式，如果不是起始位置匹配成功的话，match()就返回none
res = re.match(r"(123)",s); 
# 不在起始位置匹配

print("res: ",res)

# re.match只匹配字符串的开始，如果字符串开始不符合正则表达式，则匹配失败，函数返回None；
# 而re.search匹配整个字符串，直到找到一个匹配


