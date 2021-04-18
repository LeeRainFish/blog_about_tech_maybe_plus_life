import asyncio
# below v3.5

@asyncio.coroutine
def test(i):
    print("test_1",i)
    r = yield asyncio.sleep(3)
    print("test_2",i)


if __name__ == "__main__":
    loop = asyncio.get_event_loop()

    tasks = [test(i) for i in range(3)]
    loop.run_util_complete(asyncio.wait(tasks))

    loop.close()


