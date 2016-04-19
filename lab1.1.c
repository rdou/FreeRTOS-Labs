int main( void )
{
    /* 创建第一个任务。需要说明的是一个实用的应用程序中应当检测函数xTaskCreate()的返回值，以确保任
    务创建成功。*/
    xTaskCreate( vTask1,   /* 指向任务函数的指针*/
                 "Task 1", /* 任务的文本名字，只会在调试中用到*/
                 1000,     /* 栈深度– 大多数小型微控制器会使用的值会比此值小得多*/
                 NULL,     /* 没有任务参数*/
                 1,        /* 此任务运行在优先级1上. */
                 NULL );   /* 不会用到任务句柄*/

    /* Create the other task in exactly the same way and at the same priority. */
    xTaskCreate( vTask2, "Task 2", 1000, NULL, 1, NULL );

    /* 启动调度器，任务开始执行*/
    vTaskStartScheduler();

    /* 如果一切正常，main()函数不应该会执行到这里。但如果执行到这里，很可能是内存堆空间不足导致空闲
    任务无法创建。第五章有讲述更多关于内存管理方面的信息*/
    for( ;; );
}

void vTask1( void *pvParameters )
{
    const char *pcTaskName = "Task 1 is running\r\n";
    volatile unsigned long ul;

    /* 和大多数任务一样，该任务处于一个死循环中。*/
    for( ;; )
    {
        /* Print out the name of this task. */
        vPrintString( pcTaskName );

        /* 延迟，以产生一个周期*/
        for( ul = 0; ul < mainDELAY_LOOP_COUNT; ul++ )
        {
        /* 这个空循环是最原始的延迟实现方式。在循环中不做任何事情。后面的示例程序将采用
        delay/sleep函数代替这个原始空循环。*/
        }
    }
}

void vTask2( void *pvParameters )
{
    const char *pcTaskName = "Task 2 is running\r\n";
    volatile unsigned long ul;

    /* 和大多数任务一样，该任务处于一个死循环中。*/
    for( ;; )
    {
        /* Print out the name of this task. */
        vPrintString( pcTaskName );

        /* 延迟，以产生一个周期*/
        for( ul = 0; ul < mainDELAY_LOOP_COUNT; ul++ )
        {
        /* 这个空循环是最原始的延迟实现方式。在循环中不做任何事情。后面的示例程序将采用
        delay/sleep函数代替这个原始空循环。*/
        }
    }
}
