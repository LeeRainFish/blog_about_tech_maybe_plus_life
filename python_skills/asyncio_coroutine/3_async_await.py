import asyncio

async def test(i):
    print("test_1_",i)
    await asyncio.sleep(3)
    print("test_2_",i)
    return "done"



async def main():

    tasks_list = [
        asyncio.create_task(test(1)),
        asyncio.create_task(test(2)),
    ]

    await asyncio.wait(tasks_list,timeout=None)


if __name__ == "__main__":

    asyncio.run(main());
    # 不允许下面这样使用
#    tasks_list = [
#        asyncio.create_task(test(1)),
#        asyncio.create_task(test(2)),
#    ]
#
#    asyncio.run(asyncio.wait(tasks_list,timeout=None));
