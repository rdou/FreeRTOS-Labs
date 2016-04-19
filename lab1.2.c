/* 定义将要通过任务参数传递的字符串。定义为const，且不是在栈空间上，以保证任务执行时也有效。*/
static const char *pcTextForTask1 = “Task 1 is running\r\n”;
static const char *pcTextForTask2 = “Task 2 is running\t\n”;

void vTaskFunction( void *);

int main( void )
{
    /* Create one of the two tasks. */
    xTaskCreate( vTaskFunction,          /* 指向任务函数的指针. */
                 "Task 1",               /* 任务名. */
                 1000,                   /* 栈深度. */
                 (void *)pcTextForTask1, /* 通过任务参数传入需要打印输出的文本. */
                 1,                      /* 此任务运行在优先级1上. */
                 NULL );                 /* 不会用到此任务的句柄. */
    
    /* 同样的方法创建另一个任务。至此，由相同的任务代码(vTaskFunction)创建了多个任务，仅仅是传入
    的参数不同。同一个任务创建了两个实例。*/
    xTaskCreate( vTaskFunction, "Task 2", 1000, (void *)pcTextForTask2, 1, NULL );
    
    /* Start the scheduler so our tasks start executing. */
    vTaskStartScheduler();
    
    /* If all is well then main() will never reach here as the scheduler will
    now be running the tasks. If main() does reach here then it is likely that
    there was insufficient heap memory available for the idle task to be created.
    CHAPTER 5 provides more information on memory management. */
    for( ;; );
}

void vTaskFunction( void *pvParameters )
{
    char *pcTaskName;
    volatile unsigned long ul;
    
    /* 需要打印输出的字符串从入口参数传入。强制转换为字符指针。*/
    pcTaskName = ( char * ) pvParameters;
    
    /* As per most tasks, this task is implemented in an infinite loop. */
    for( ;; )
    {
        /* Print out the name of this task. */
        vPrintString( pcTaskName );
        
        /* Delay for a period. */
        for( ul = 0; ul < mainDELAY_LOOP_COUNT; ul++ )
        {
        /* This loop is just a very crude delay implementation. There is
        nothing to do in here. Later exercises will replace this crude
        loop with a proper delay/sleep function. */
        }
    }
}
