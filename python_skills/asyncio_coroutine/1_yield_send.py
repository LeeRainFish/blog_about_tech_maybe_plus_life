# yield send()
# 这个例子是生成器的形式 和 协程要做区分
def eater():
    print('Ready to eat.')
    while True:
        food = yield
        print('get the food: %s, and start to eat.' % food)

def consumer():
    r = ''
    while True:
        # 是暂停接收也是返回
        # n = yield r  ==  n = yield ; return r
        # go channel
        n = yield r
        if not n:
            return

        print("consum %s"%n)
        r = '200 OK'
        


def producter(c):

    c.send(None)
    # next(c)
    n = 0
    while n < 5:
        n = n + 1
        print("product %s"%n)
        r = c.send(n)
        print("producter consumer return %s"%r)

    c.close()



if __name__ == "__main__":
    c = consumer()
    producter(c)

