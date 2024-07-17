#include "dbg.h"

#include <stdio.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <pthread.h>

/// 我们定义了带有100个元素的数组，
/// 每个数组元素是一个含有10000个int元素的数组
static int sArrays[100][10000];

/// 此整数原子对象用于指示当前线程所要操作的数组索引
static volatile atomic_int sAtomicArrayIndex = ATOMIC_VAR_INIT(0);

/// 此整数原子对象用于存放最终的求和结果
static volatile atomic_int sAtomicArraySum = ATOMIC_VAR_INIT(0);

/// 对共享数组进行求和操作
/// 如果当前数组还没计算完，返回true；否则返回false
static bool AtomicComputeArraySum(void)
{
    // 获取当前所要计算的数组个数
    const int nLoops = (int)(sizeof(sArrays[0]) / sizeof(sArrays[0][0]));

    // 获取数组sArrays总共有多少元素
    const int arrayLen = (int)(sizeof(sArrays) / sizeof(sArrays[0]));

    // 利用原子加法来获取当前所要操作数组的索引
    const int currArrayIndex = atomic_fetch_add(&sAtomicArrayIndex, 1);

    // 若当前索引已经达到了数组长度，则直接返回false，说明数组已经全部计算完成
    if(currArrayIndex >= arrayLen)
        return false;

    // 对当前指派到的数组元素进行求和
    int sum = 0;
    for(int index = 0; index < nLoops; index++)
        sum += sArrays[currArrayIndex][index];

    // 将结果进行累加
    atomic_fetch_add(&sAtomicArraySum, sum);

    return true;
}

/// 线程处理函数
static void* ThreadProc(void *args)
{
    // 在用户线程中计算
    while(AtomicComputeArraySum());

    return NULL;
}

int main(int argc, const char * argv[])
{
    // 获取数组每个元素的数组长度
    const int nElems = (int)(sizeof(sArrays[0]) / sizeof(sArrays[0][0]));

    // 获取数组sArrays总共有多少元素
    const int arrayLen = (int)(sizeof(sArrays) / sizeof(sArrays[0]));

    // 我们先对共享的二维数组进行初始化，
    // 为了方便验证结果，将它所有数组的所有元素初始化为1
    for(int i = 0; i < arrayLen; i++)
    {
        for(int j = 0; j < nElems; j++)
            sArrays[i][j] = 1;
    }

    pthread_t threadID;
    // 创建线程并调度执行
    if(pthread_create(&threadID, NULL, ThreadProc, NULL) != 0)
    {
        puts("Failed to create a thread!");
        return 0;
    }

    // 在主线程中计算
    while(AtomicComputeArraySum());

    // 等待线程执行完毕
    pthread_join(threadID, NULL);

    // 输出最终结果
    const int result = atomic_load(&sAtomicArraySum);
    printf("The final result is: %d\n", result);
}