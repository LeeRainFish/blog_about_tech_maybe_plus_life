import gevent 


def test(n):
    for in range(n):
        print(gevent.getcurrent(),i)


def main():
    g1 = gevent(spawn(test,3))
    g2 = gevent(spawn(test,3))
    g3 = gevent(spawn(test,3))

    g1.join()
    g2.join()
    g3.join()



if __name__ == "__main__":
    main()

