import re

pattern = re.compile(r'\d+')
pattern = re.compile(r'([a-z]+) ([a-z]+)', re.I)   # re.I 表示忽略大小写

m = pattern.match("one12twothree34four")
res1 = pattern.findall('runoob 123 google 456')


