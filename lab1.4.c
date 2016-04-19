/* 定义将要通过任务参数传递的字符串。定义为const，且不是在栈空间上，以保证任务执行时也有效。*/
static const char *pcTextForTask1 = “Task 1 is running\r\n”;
static const char *pcTextForTask2 = “Task 2 is running\t\n”;

void vTaskFunction( void *);

int main( void )
{
    /* Create one of the two tasks. */
    xTaskCreate( vContinuousTaskFunction, /* 指向任务函数的指针. */
                 "Task 1",                /* 任务名. */
                 1000,                    /* 栈深度. */
                 (void *)pcTextForTask1,  /* 通过任务参数传入需要打印输出的文本. */
                 1,                       /* 此任务运行在优先级1上. */
                 NULL );                  /* 不会用到此任务的句柄. */
    
    /* 同样的方法创建另一个任务。至此，由相同的任务代码(vTaskFunction)创建了多个任务，仅仅是传入
    的参数不同。同一个任务创建了两个实例。*/
    xTaskCreate( vContinuousTaskFunction, "Task 2", 1000, (void *)pcTextForTask2, 1, NULL );
    
    xTaskCreate( vPeriodicTask, "Task 3", 1000, NULL, 2, NULL );

    /* Start the scheduler so our tasks start executing. */
    vTaskStartScheduler();
    
    /* If all is well then main() will never reach here as the scheduler will
    now be running the tasks. If main() does reach here then it is likely that
    there was insufficient heap memory available for the idle task to be created.
    CHAPTER 5 provides more information on memory management. */
    for( ;; );
}

void vContinuousTaskFunction( void *pvParameters ) 
{ 
    char *pcTaskName; 
    
    /* The string to print out is passed in via the parameter. Cast this to a 
    character pointer. */ 
    
    pcTaskName = ( char * ) pvParameters; 
    
    /* As per most tasks, this task is implemented in an infinite loop. */ 
    for( ;; ) 
    { 
        /* Print out the name of this task. */ 
        vPrintString( pcTaskName ); 
    } 
} 

void vPeriodicTask( void *pvParameters ) 
{   
    ( void ) pvParameters;
    portTickType xLastWakeTime; 
    
    /* 初始化xLastWakeTime,之后会在vTaskDelayUntil()中自动更新。*/ 
    xLastWakeTime = xTaskGetTickCount(); 
    
    /* As per most tasks, this task is implemented in an infinite loop. */ 
    for( ;; ) 
    { 
        /* Print out the name of this task. */ 
        vPrintString( "Periodic task is running\r\n" ); 
        
        /* The task should execute every 10 milliseconds exactly. */ 
        vTaskDelayUntil( &xLastWakeTime, ( 10 / portTICK_RATE_MS ) ); 
    } 
}
