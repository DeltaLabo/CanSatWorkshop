---
url: "https://docs.espressif.com/projects/esp-idf/en/v4.2.3/esp32/api-reference/system/freertos.html"
final_url: "https://docs.espressif.com/projects/esp-idf/en/v4.2.3/esp32/api-reference/system/freertos.html"
title: "FreeRTOSÂ¶"
extracted_at: "2026-06-12T06:30:53.947602+00:00"
parser: "trafilatura-markdown"
confidence: 0.860
content_type: "text/html"
http_status: 200
word_count: 33531
---

# FreeRTOS[Â¶](https://docs.espressif.com#freertos)

## Overview[Â¶](https://docs.espressif.com#overview)

This section contains documentation of FreeRTOS types, functions, and macros. It is automatically generated from FreeRTOS header files.

Note

ESP-IDF FreeRTOS is based on the Xtensa port of FreeRTOS v8.2.0, however some functions of FreeRTOS v9.0.0 have been backported. See the [Backported Features](https://docs.espressif.com/api-guides/freertos-smp.html#backported-features) for more information.

For more information about FreeRTOS features specific to ESP-IDF, see [ESP-IDF FreeRTOS SMP Changes](https://docs.espressif.com/api-guides/freertos-smp.html)
and [ESP-IDF FreeRTOS Additions](https://docs.espressif.com/freertos_additions.html).

## Task API[Â¶](https://docs.espressif.com#task-api)

### Header File[Â¶](https://docs.espressif.com#header-file)

### Functions[Â¶](https://docs.espressif.com#functions)

-
BaseType_t
`xTaskCreatePinnedToCore`

(TaskFunction_t*pvTaskCode*,*const*char **const**pcName*,*const*uint32_t*usStackDepth*, void **const**pvParameters*, UBaseType_t*uxPriority*,[TaskHandle_t](https://docs.espressif.com#_CPPv412TaskHandle_t)**const**pvCreatedTask*,*const*BaseType_t*xCoreID*)[Â¶](https://docs.espressif.com#_CPPv423xTaskCreatePinnedToCore14TaskFunction_tPCKcK8uint32_tPCv11UBaseType_tPC12TaskHandle_tK10BaseType_t) Create a new task with a specified affinity.

This function is similar to xTaskCreate, but allows setting task affinity in SMP system.

**Return**pdPASS if the task was successfully created and added to a ready list, otherwise an error code defined in the file projdefs.h

**Parameters**`pvTaskCode`

: Pointer to the task entry function. Tasks must be implemented to never return (i.e. continuous loop).`pcName`

: A descriptive name for the task. This is mainly used to facilitate debugging. Max length defined by configMAX_TASK_NAME_LEN - default is 16.`usStackDepth`

: The size of the task stack specified as the number of bytes. Note that this differs from vanilla FreeRTOS.`pvParameters`

: Pointer that will be used as the parameter for the task being created.`uxPriority`

: The priority at which the task should run. Systems that include MPU support can optionally create tasks in a privileged (system) mode by setting bit portPRIVILEGE_BIT of the priority parameter. For example, to create a privileged task at priority 2 the uxPriority parameter should be set to ( 2 | portPRIVILEGE_BIT ).`pvCreatedTask`

: Used to pass back a handle by which the created task can be referenced.`xCoreID`

: If the value is tskNO_AFFINITY, the created task is not pinned to any CPU, and the scheduler can run it on any core available. Values 0 or 1 indicate the index number of the CPU which the task should be pinned to. Specifying values larger than (portNUM_PROCESSORS - 1) will cause the function to fail.

-
*static*BaseType_t`xTaskCreate`

(TaskFunction_t*pvTaskCode*,*const*char **const**pcName*,*const*uint32_t*usStackDepth*, void **const**pvParameters*, UBaseType_t*uxPriority*,[TaskHandle_t](https://docs.espressif.com#_CPPv412TaskHandle_t)**const**pvCreatedTask*)[Â¶](https://docs.espressif.com#_CPPv411xTaskCreate14TaskFunction_tPCKcK8uint32_tPCv11UBaseType_tPC12TaskHandle_t) Create a new task and add it to the list of tasks that are ready to run.

Internally, within the FreeRTOS implementation, tasks use two blocks of memory. The first block is used to hold the taskâs data structures. The second block is used by the task as its stack. If a task is created using xTaskCreate() then both blocks of memory are automatically dynamically allocated inside the xTaskCreate() function. (see

[http://www.freertos.org/a00111.html](http://www.freertos.org/a00111.html)). If a task is created using xTaskCreateStatic() then the application writer must provide the required memory. xTaskCreateStatic() therefore allows a task to be created without using any dynamic memory allocation.See xTaskCreateStatic() for a version that does not use any dynamic memory allocation.

xTaskCreate() can only be used to create a task that has unrestricted access to the entire microcontroller memory map. Systems that include MPU support can alternatively create an MPU constrained task using xTaskCreateRestricted().

Example usage:

// Task to be created. void vTaskCode( void * pvParameters ) { for( ;; ) { // Task code goes here. } } // Function that creates a task. void vOtherFunction( void ) { static uint8_t ucParameterToPass; TaskHandle_t xHandle = NULL; // Create the task, storing the handle. Note that the passed parameter ucParameterToPass // must exist for the lifetime of the task, so in this case is declared static. If it was just an // an automatic stack variable it might no longer exist, or at least have been corrupted, by the time // the new task attempts to access it. xTaskCreate( vTaskCode, "NAME", STACK_SIZE, &ucParameterToPass, tskIDLE_PRIORITY, &xHandle ); configASSERT( xHandle ); // Use the handle to delete the task. if( xHandle != NULL ) { vTaskDelete( xHandle ); } }

**Return**pdPASS if the task was successfully created and added to a ready list, otherwise an error code defined in the file projdefs.h

**Note**If program uses thread local variables (ones specified with â__threadâ keyword) then storage for them will be allocated on the taskâs stack.

**Parameters**`pvTaskCode`

: Pointer to the task entry function. Tasks must be implemented to never return (i.e. continuous loop).`pcName`

: A descriptive name for the task. This is mainly used to facilitate debugging. Max length defined by configMAX_TASK_NAME_LEN - default is 16.`usStackDepth`

: The size of the task stack specified as the number of bytes. Note that this differs from vanilla FreeRTOS.`pvParameters`

: Pointer that will be used as the parameter for the task being created.`uxPriority`

: The priority at which the task should run. Systems that include MPU support can optionally create tasks in a privileged (system) mode by setting bit portPRIVILEGE_BIT of the priority parameter. For example, to create a privileged task at priority 2 the uxPriority parameter should be set to ( 2 | portPRIVILEGE_BIT ).`pvCreatedTask`

: Used to pass back a handle by which the created task can be referenced.

-
[TaskHandle_t](https://docs.espressif.com#_CPPv412TaskHandle_t)`xTaskCreateStaticPinnedToCore`

(TaskFunction_t*pvTaskCode*,*const*char **const**pcName*,*const*uint32_t*ulStackDepth*, void **const**pvParameters*, UBaseType_t*uxPriority*, StackType_t **const**pxStackBuffer*, StaticTask_t **const**pxTaskBuffer*,*const*BaseType_t*xCoreID*)[Â¶](https://docs.espressif.com#_CPPv429xTaskCreateStaticPinnedToCore14TaskFunction_tPCKcK8uint32_tPCv11UBaseType_tPC11StackType_tPC12StaticTask_tK10BaseType_t) Create a new task with a specified affinity.

This function is similar to xTaskCreateStatic, but allows specifying task affinity in an SMP system.

**Return**If neither pxStackBuffer or pxTaskBuffer are NULL, then the task will be created and a task handle will be returned by which the created task can be referenced. If either pxStackBuffer or pxTaskBuffer are NULL then the task will not be created and NULL is returned.

**Parameters**`pvTaskCode`

: Pointer to the task entry function. Tasks must be implemented to never return (i.e. continuous loop).`pcName`

: A descriptive name for the task. This is mainly used to facilitate debugging. The maximum length of the string is defined by configMAX_TASK_NAME_LEN in FreeRTOSConfig.h.`ulStackDepth`

: The size of the task stack specified as the number of bytes. Note that this differs from vanilla FreeRTOS.`pvParameters`

: Pointer that will be used as the parameter for the task being created.`uxPriority`

: The priority at which the task will run.`pxStackBuffer`

: Must point to a StackType_t array that has at least ulStackDepth indexes - the array will then be used as the taskâs stack, removing the need for the stack to be allocated dynamically.`pxTaskBuffer`

: Must point to a variable of type StaticTask_t, which will then be used to hold the taskâs data structures, removing the need for the memory to be allocated dynamically.`xCoreID`

: If the value is tskNO_AFFINITY, the created task is not pinned to any CPU, and the scheduler can run it on any core available. Values 0 or 1 indicate the index number of the CPU which the task should be pinned to. Specifying values larger than (portNUM_PROCESSORS - 1) will cause the function to fail.

-
*static*[TaskHandle_t](https://docs.espressif.com#_CPPv412TaskHandle_t)`xTaskCreateStatic`

(TaskFunction_t*pvTaskCode*,*const*char **const**pcName*,*const*uint32_t*ulStackDepth*, void **const**pvParameters*, UBaseType_t*uxPriority*, StackType_t **const**pxStackBuffer*, StaticTask_t **const**pxTaskBuffer*)[Â¶](https://docs.espressif.com#_CPPv417xTaskCreateStatic14TaskFunction_tPCKcK8uint32_tPCv11UBaseType_tPC11StackType_tPC12StaticTask_t) Create a new task and add it to the list of tasks that are ready to run.

Internally, within the FreeRTOS implementation, tasks use two blocks of memory. The first block is used to hold the taskâs data structures. The second block is used by the task as its stack. If a task is created using xTaskCreate() then both blocks of memory are automatically dynamically allocated inside the xTaskCreate() function. (see

[http://www.freertos.org/a00111.html](http://www.freertos.org/a00111.html)). If a task is created using xTaskCreateStatic() then the application writer must provide the required memory. xTaskCreateStatic() therefore allows a task to be created without using any dynamic memory allocation.Example usage:

// Dimensions the buffer that the task being created will use as its stack. // NOTE: This is the number of bytes the stack will hold, not the number of // words as found in vanilla FreeRTOS. #define STACK_SIZE 200 // Structure that will hold the TCB of the task being created. StaticTask_t xTaskBuffer; // Buffer that the task being created will use as its stack. Note this is // an array of StackType_t variables. The size of StackType_t is dependent on // the RTOS port. StackType_t xStack[ STACK_SIZE ]; // Function that implements the task being created. void vTaskCode( void * pvParameters ) { // The parameter value is expected to be 1 as 1 is passed in the // pvParameters value in the call to xTaskCreateStatic(). configASSERT( ( uint32_t ) pvParameters == 1UL ); for( ;; ) { // Task code goes here. } } // Function that creates a task. void vOtherFunction( void ) { TaskHandle_t xHandle = NULL; // Create the task without using any dynamic memory allocation. xHandle = xTaskCreateStatic( vTaskCode, // Function that implements the task. "NAME", // Text name for the task. STACK_SIZE, // Stack size in bytes, not words. ( void * ) 1, // Parameter passed into the task. tskIDLE_PRIORITY,// Priority at which the task is created. xStack, // Array to use as the task's stack. &xTaskBuffer ); // Variable to hold the task's data structure. // puxStackBuffer and pxTaskBuffer were not NULL, so the task will have // been created, and xHandle will be the task's handle. Use the handle // to suspend the task. vTaskSuspend( xHandle ); }

**Return**If neither pxStackBuffer or pxTaskBuffer are NULL, then the task will be created and a task handle will be returned by which the created task can be referenced. If either pxStackBuffer or pxTaskBuffer are NULL then the task will not be created and NULL is returned.

**Note**If program uses thread local variables (ones specified with â__threadâ keyword) then storage for them will be allocated on the taskâs stack.

**Parameters**`pvTaskCode`

: Pointer to the task entry function. Tasks must be implemented to never return (i.e. continuous loop).`pcName`

: A descriptive name for the task. This is mainly used to facilitate debugging. The maximum length of the string is defined by configMAX_TASK_NAME_LEN in FreeRTOSConfig.h.`ulStackDepth`

: The size of the task stack specified as the number of bytes. Note that this differs from vanilla FreeRTOS.`pvParameters`

: Pointer that will be used as the parameter for the task being created.`uxPriority`

: The priority at which the task will run.`pxStackBuffer`

: Must point to a StackType_t array that has at least ulStackDepth indexes - the array will then be used as the taskâs stack, removing the need for the stack to be allocated dynamically.`pxTaskBuffer`

: Must point to a variable of type StaticTask_t, which will then be used to hold the taskâs data structures, removing the need for the memory to be allocated dynamically.

-
void
`vTaskDelete`

([TaskHandle_t](https://docs.espressif.com#_CPPv412TaskHandle_t)*xTaskToDelete*)[Â¶](https://docs.espressif.com#_CPPv411vTaskDelete12TaskHandle_t) Remove a task from the RTOS real time kernelâs management.

The task being deleted will be removed from all ready, blocked, suspended and event lists.

INCLUDE_vTaskDelete must be defined as 1 for this function to be available. See the configuration section for more information.

See the demo application file death.c for sample code that utilises vTaskDelete ().

**Note**The idle task is responsible for freeing the kernel allocated memory from tasks that have been deleted. It is therefore important that the idle task is not starved of microcontroller processing time if your application makes any calls to vTaskDelete (). Memory allocated by the task code is not automatically freed, and should be freed before the task is deleted.

Example usage:

void vOtherFunction( void ) { TaskHandle_t xHandle; // Create the task, storing the handle. xTaskCreate( vTaskCode, "NAME", STACK_SIZE, NULL, tskIDLE_PRIORITY, &xHandle ); // Use the handle to delete the task. vTaskDelete( xHandle ); }

**Parameters**`xTaskToDelete`

: The handle of the task to be deleted. Passing NULL will cause the calling task to be deleted.

-
void
`vTaskDelay`

(*const*TickType_t*xTicksToDelay*)[Â¶](https://docs.espressif.com#_CPPv410vTaskDelayK10TickType_t) Delay a task for a given number of ticks.

The actual time that the task remains blocked depends on the tick rate. The constant portTICK_PERIOD_MS can be used to calculate real time from the tick rate - with the resolution of one tick period.

INCLUDE_vTaskDelay must be defined as 1 for this function to be available. See the configuration section for more information.

vTaskDelay() specifies a time at which the task wishes to unblock relative to the time at which vTaskDelay() is called. For example, specifying a block period of 100 ticks will cause the task to unblock 100 ticks after vTaskDelay() is called. vTaskDelay() does not therefore provide a good method of controlling the frequency of a periodic task as the path taken through the code, as well as other task and interrupt activity, will effect the frequency at which vTaskDelay() gets called and therefore the time at which the task next executes. See vTaskDelayUntil() for an alternative API function designed to facilitate fixed frequency execution. It does this by specifying an absolute time (rather than a relative time) at which the calling task should unblock.

Example usage:

void vTaskFunction( void * pvParameters ) { // Block for 500ms. const TickType_t xDelay = 500 / portTICK_PERIOD_MS; for( ;; ) { // Simply toggle the LED every 500ms, blocking between each toggle. vToggleLED(); vTaskDelay( xDelay ); } }

**Parameters**`xTicksToDelay`

: The amount of time, in tick periods, that the calling task should block.

-
void
`vTaskDelayUntil`

(TickType_t **const**pxPreviousWakeTime*,*const*TickType_t*xTimeIncrement*)[Â¶](https://docs.espressif.com#_CPPv415vTaskDelayUntilPC10TickType_tK10TickType_t) Delay a task until a specified time.

INCLUDE_vTaskDelayUntil must be defined as 1 for this function to be available. See the configuration section for more information.

This function can be used by periodic tasks to ensure a constant execution frequency.

This function differs from vTaskDelay () in one important aspect: vTaskDelay () will cause a task to block for the specified number of ticks from the time vTaskDelay () is called. It is therefore difficult to use vTaskDelay () by itself to generate a fixed execution frequency as the time between a task starting to execute and that task calling vTaskDelay () may not be fixed [the task may take a different path though the code between calls, or may get interrupted or preempted a different number of times each time it executes].

Whereas vTaskDelay () specifies a wake time relative to the time at which the function is called, vTaskDelayUntil () specifies the absolute (exact) time at which it wishes to unblock.

The constant portTICK_PERIOD_MS can be used to calculate real time from the tick rate - with the resolution of one tick period.

Example usage:

// Perform an action every 10 ticks. void vTaskFunction( void * pvParameters ) { TickType_t xLastWakeTime; const TickType_t xFrequency = 10; // Initialise the xLastWakeTime variable with the current time. xLastWakeTime = xTaskGetTickCount (); for( ;; ) { // Wait for the next cycle. vTaskDelayUntil( &xLastWakeTime, xFrequency ); // Perform action here. } }

**Parameters**`pxPreviousWakeTime`

: Pointer to a variable that holds the time at which the task was last unblocked. The variable must be initialised with the current time prior to its first use (see the example below). Following this the variable is automatically updated within vTaskDelayUntil ().`xTimeIncrement`

: The cycle time period. The task will be unblocked at time *pxPreviousWakeTime + xTimeIncrement. Calling vTaskDelayUntil with the same xTimeIncrement parameter value will cause the task to execute with a fixed interface period.

-
UBaseType_t
`uxTaskPriorityGet`

([TaskHandle_t](https://docs.espressif.com#_CPPv412TaskHandle_t)*xTask*)[Â¶](https://docs.espressif.com#_CPPv417uxTaskPriorityGet12TaskHandle_t) Obtain the priority of any task.

INCLUDE_uxTaskPriorityGet must be defined as 1 for this function to be available. See the configuration section for more information.

Example usage:

void vAFunction( void ) { TaskHandle_t xHandle; // Create a task, storing the handle. xTaskCreate( vTaskCode, "NAME", STACK_SIZE, NULL, tskIDLE_PRIORITY, &xHandle ); // ... // Use the handle to obtain the priority of the created task. // It was created with tskIDLE_PRIORITY, but may have changed // it itself. if( uxTaskPriorityGet( xHandle ) != tskIDLE_PRIORITY ) { // The task has changed it's priority. } // ... // Is our priority higher than the created task? if( uxTaskPriorityGet( xHandle ) < uxTaskPriorityGet( NULL ) ) { // Our priority (obtained using NULL handle) is higher. } }

**Return**The priority of xTask.

**Parameters**`xTask`

: Handle of the task to be queried. Passing a NULL handle results in the priority of the calling task being returned.

-
UBaseType_t
`uxTaskPriorityGetFromISR`

([TaskHandle_t](https://docs.espressif.com#_CPPv412TaskHandle_t)*xTask*)[Â¶](https://docs.espressif.com#_CPPv424uxTaskPriorityGetFromISR12TaskHandle_t) A version of uxTaskPriorityGet() that can be used from an ISR.

**Return**The priority of xTask.

**Parameters**`xTask`

: Handle of the task to be queried. Passing a NULL handle results in the priority of the calling task being returned.

-
[eTaskState](https://docs.espressif.com#_CPPv410eTaskState)`eTaskGetState`

([TaskHandle_t](https://docs.espressif.com#_CPPv412TaskHandle_t)*xTask*)[Â¶](https://docs.espressif.com#_CPPv413eTaskGetState12TaskHandle_t) Obtain the state of any task.

States are encoded by the eTaskState enumerated type.

INCLUDE_eTaskGetState must be defined as 1 for this function to be available. See the configuration section for more information.

**Return**The state of xTask at the time the function was called. Note the state of the task might change between the function being called, and the functions return value being tested by the calling task.

**Parameters**`xTask`

: Handle of the task to be queried.

-
void
`vTaskPrioritySet`

([TaskHandle_t](https://docs.espressif.com#_CPPv412TaskHandle_t)*xTask*, UBaseType_t*uxNewPriority*)[Â¶](https://docs.espressif.com#_CPPv416vTaskPrioritySet12TaskHandle_t11UBaseType_t) Set the priority of any task.

INCLUDE_vTaskPrioritySet must be defined as 1 for this function to be available. See the configuration section for more information.

A context switch will occur before the function returns if the priority being set is higher than the currently executing task.

Example usage:

void vAFunction( void ) { TaskHandle_t xHandle; // Create a task, storing the handle. xTaskCreate( vTaskCode, "NAME", STACK_SIZE, NULL, tskIDLE_PRIORITY, &xHandle ); // ... // Use the handle to raise the priority of the created task. vTaskPrioritySet( xHandle, tskIDLE_PRIORITY + 1 ); // ... // Use a NULL handle to raise our priority to the same value. vTaskPrioritySet( NULL, tskIDLE_PRIORITY + 1 ); }

**Parameters**`xTask`

: Handle to the task for which the priority is being set. Passing a NULL handle results in the priority of the calling task being set.`uxNewPriority`

: The priority to which the task will be set.

-
void
`vTaskSuspend`

([TaskHandle_t](https://docs.espressif.com#_CPPv412TaskHandle_t)*xTaskToSuspend*)[Â¶](https://docs.espressif.com#_CPPv412vTaskSuspend12TaskHandle_t) Suspend a task.

INCLUDE_vTaskSuspend must be defined as 1 for this function to be available. See the configuration section for more information.

When suspended, a task will never get any microcontroller processing time, no matter what its priority.

Calls to vTaskSuspend are not accumulative - i.e. calling vTaskSuspend () twice on the same task still only requires one call to vTaskResume () to ready the suspended task.

Example usage:

void vAFunction( void ) { TaskHandle_t xHandle; // Create a task, storing the handle. xTaskCreate( vTaskCode, "NAME", STACK_SIZE, NULL, tskIDLE_PRIORITY, &xHandle ); // ... // Use the handle to suspend the created task. vTaskSuspend( xHandle ); // ... // The created task will not run during this period, unless // another task calls vTaskResume( xHandle ). //... // Suspend ourselves. vTaskSuspend( NULL ); // We cannot get here unless another task calls vTaskResume // with our handle as the parameter. }

**Parameters**`xTaskToSuspend`

: Handle to the task being suspended. Passing a NULL handle will cause the calling task to be suspended.

-
void
`vTaskResume`

([TaskHandle_t](https://docs.espressif.com#_CPPv412TaskHandle_t)*xTaskToResume*)[Â¶](https://docs.espressif.com#_CPPv411vTaskResume12TaskHandle_t) Resumes a suspended task.

INCLUDE_vTaskSuspend must be defined as 1 for this function to be available. See the configuration section for more information.

A task that has been suspended by one or more calls to vTaskSuspend () will be made available for running again by a single call to vTaskResume ().

Example usage:

void vAFunction( void ) { TaskHandle_t xHandle; // Create a task, storing the handle. xTaskCreate( vTaskCode, "NAME", STACK_SIZE, NULL, tskIDLE_PRIORITY, &xHandle ); // ... // Use the handle to suspend the created task. vTaskSuspend( xHandle ); // ... // The created task will not run during this period, unless // another task calls vTaskResume( xHandle ). //... // Resume the suspended task ourselves. vTaskResume( xHandle ); // The created task will once again get microcontroller processing // time in accordance with its priority within the system. }

**Parameters**`xTaskToResume`

: Handle to the task being readied.

-
BaseType_t
`xTaskResumeFromISR`

([TaskHandle_t](https://docs.espressif.com#_CPPv412TaskHandle_t)*xTaskToResume*)[Â¶](https://docs.espressif.com#_CPPv418xTaskResumeFromISR12TaskHandle_t) An implementation of vTaskResume() that can be called from within an ISR.

INCLUDE_xTaskResumeFromISR must be defined as 1 for this function to be available. See the configuration section for more information.

A task that has been suspended by one or more calls to vTaskSuspend () will be made available for running again by a single call to xTaskResumeFromISR ().

xTaskResumeFromISR() should not be used to synchronise a task with an interrupt if there is a chance that the interrupt could arrive prior to the task being suspended - as this can lead to interrupts being missed. Use of a semaphore as a synchronisation mechanism would avoid this eventuality.

**Return**pdTRUE if resuming the task should result in a context switch, otherwise pdFALSE. This is used by the ISR to determine if a context switch may be required following the ISR.

**Parameters**`xTaskToResume`

: Handle to the task being readied.

-
void
`vTaskSuspendAll`

(void)[Â¶](https://docs.espressif.com#_CPPv415vTaskSuspendAllv) Suspends the scheduler without disabling interrupts.

Context switches will not occur while the scheduler is suspended.

After calling vTaskSuspendAll () the calling task will continue to execute without risk of being swapped out until a call to xTaskResumeAll () has been made.

API functions that have the potential to cause a context switch (for example, vTaskDelayUntil(), xQueueSend(), etc.) must not be called while the scheduler is suspended.

Example usage:

void vTask1( void * pvParameters ) { for( ;; ) { // Task code goes here. // ... // At some point the task wants to perform a long operation during // which it does not want to get swapped out. It cannot use // taskENTER_CRITICAL ()/taskEXIT_CRITICAL () as the length of the // operation may cause interrupts to be missed - including the // ticks. // Prevent the real time kernel swapping out the task. vTaskSuspendAll (); // Perform the operation here. There is no need to use critical // sections as we have all the microcontroller processing time. // During this time interrupts will still operate and the kernel // tick count will be maintained. // ... // The operation is complete. Restart the kernel. xTaskResumeAll (); } }

-
BaseType_t
`xTaskResumeAll`

(void)[Â¶](https://docs.espressif.com#_CPPv414xTaskResumeAllv) Resumes scheduler activity after it was suspended by a call to vTaskSuspendAll().

xTaskResumeAll() only resumes the scheduler. It does not unsuspend tasks that were previously suspended by a call to vTaskSuspend().

Example usage:

void vTask1( void * pvParameters ) { for( ;; ) { // Task code goes here. // ... // At some point the task wants to perform a long operation during // which it does not want to get swapped out. It cannot use // taskENTER_CRITICAL ()/taskEXIT_CRITICAL () as the length of the // operation may cause interrupts to be missed - including the // ticks. // Prevent the real time kernel swapping out the task. vTaskSuspendAll (); // Perform the operation here. There is no need to use critical // sections as we have all the microcontroller processing time. // During this time interrupts will still operate and the real // time kernel tick count will be maintained. // ... // The operation is complete. Restart the kernel. We want to force // a context switch - but there is no point if resuming the scheduler // caused a context switch already. if( !xTaskResumeAll () ) { taskYIELD (); } } }

**Return**If resuming the scheduler caused a context switch then pdTRUE is returned, otherwise pdFALSE is returned.

-
TickType_t
`xTaskGetTickCount`

(void)[Â¶](https://docs.espressif.com#_CPPv417xTaskGetTickCountv) Get tick count

**Return**The count of ticks since vTaskStartScheduler was called.

-
TickType_t
`xTaskGetTickCountFromISR`

(void)[Â¶](https://docs.espressif.com#_CPPv424xTaskGetTickCountFromISRv) Get tick count from ISR

This is a version of xTaskGetTickCount() that is safe to be called from an ISR - provided that TickType_t is the natural word size of the microcontroller being used or interrupt nesting is either not supported or not being used.

**Return**The count of ticks since vTaskStartScheduler was called.

-
UBaseType_t
`uxTaskGetNumberOfTasks`

(void)[Â¶](https://docs.espressif.com#_CPPv422uxTaskGetNumberOfTasksv) Get current number of tasks

**Return**The number of tasks that the real time kernel is currently managing. This includes all ready, blocked and suspended tasks. A task that has been deleted but not yet freed by the idle task will also be included in the count.

-
char *
`pcTaskGetTaskName`

([TaskHandle_t](https://docs.espressif.com#_CPPv412TaskHandle_t)*xTaskToQuery*)[Â¶](https://docs.espressif.com#_CPPv417pcTaskGetTaskName12TaskHandle_t) Get task name

**Return**The text (human readable) name of the task referenced by the handle xTaskToQuery. A task can query its own name by either passing in its own handle, or by setting xTaskToQuery to NULL. INCLUDE_pcTaskGetTaskName must be set to 1 in FreeRTOSConfig.h for pcTaskGetTaskName() to be available.

-
UBaseType_t
`uxTaskGetStackHighWaterMark`

([TaskHandle_t](https://docs.espressif.com#_CPPv412TaskHandle_t)*xTask*)[Â¶](https://docs.espressif.com#_CPPv427uxTaskGetStackHighWaterMark12TaskHandle_t) Returns the high water mark of the stack associated with xTask.

INCLUDE_uxTaskGetStackHighWaterMark must be set to 1 in FreeRTOSConfig.h for this function to be available.

High water mark is the minimum free stack space there has been (in bytes rather than words as found in vanilla FreeRTOS) since the task started. The smaller the returned number the closer the task has come to overflowing its stack.

**Return**The smallest amount of free stack space there has been (in bytes rather than words as found in vanilla FreeRTOS) since the task referenced by xTask was created.

**Parameters**`xTask`

: Handle of the task associated with the stack to be checked. Set xTask to NULL to check the stack of the calling task.

-
uint8_t *
`pxTaskGetStackStart`

([TaskHandle_t](https://docs.espressif.com#_CPPv412TaskHandle_t)*xTask*)[Â¶](https://docs.espressif.com#_CPPv419pxTaskGetStackStart12TaskHandle_t) Returns the start of the stack associated with xTask.

INCLUDE_pxTaskGetStackStart must be set to 1 in FreeRTOSConfig.h for this function to be available.

Returns the highest stack memory address on architectures where the stack grows down from high memory, and the lowest memory address on architectures where the stack grows up from low memory.

**Return**A pointer to the start of the stack.

**Parameters**`xTask`

: Handle of the task associated with the stack returned. Set xTask to NULL to return the stack of the calling task.

-
void
`vTaskSetApplicationTaskTag`

([TaskHandle_t](https://docs.espressif.com#_CPPv412TaskHandle_t)*xTask*,[TaskHookFunction_t](https://docs.espressif.com#_CPPv418TaskHookFunction_t)*pxHookFunction*)[Â¶](https://docs.espressif.com#_CPPv426vTaskSetApplicationTaskTag12TaskHandle_t18TaskHookFunction_t) Sets pxHookFunction to be the task hook function used by the task xTask.

**Parameters**`xTask`

: Handle of the task to set the hook function for Passing xTask as NULL has the effect of setting the calling tasks hook function.`pxHookFunction`

: Pointer to the hook function.

-
[TaskHookFunction_t](https://docs.espressif.com#_CPPv418TaskHookFunction_t)`xTaskGetApplicationTaskTag`

([TaskHandle_t](https://docs.espressif.com#_CPPv412TaskHandle_t)*xTask*)[Â¶](https://docs.espressif.com#_CPPv426xTaskGetApplicationTaskTag12TaskHandle_t) Get the hook function assigned to given task.

**Return**The pxHookFunction value assigned to the task xTask.

**Parameters**`xTask`

: Handle of the task to get the hook function for Passing xTask as NULL has the effect of getting the calling tasks hook function.

-
void
`vTaskSetThreadLocalStoragePointer`

([TaskHandle_t](https://docs.espressif.com#_CPPv412TaskHandle_t)*xTaskToSet*, BaseType_t*xIndex*, void **pvValue*)[Â¶](https://docs.espressif.com#_CPPv433vTaskSetThreadLocalStoragePointer12TaskHandle_t10BaseType_tPv) Set local storage pointer specific to the given task.

Each task contains an array of pointers that is dimensioned by the configNUM_THREAD_LOCAL_STORAGE_POINTERS setting in FreeRTOSConfig.h. The kernel does not use the pointers itself, so the application writer can use the pointers for any purpose they wish.

**Parameters**`xTaskToSet`

: Task to set thread local storage pointer for`xIndex`

: The index of the pointer to set, from 0 to configNUM_THREAD_LOCAL_STORAGE_POINTERS - 1.`pvValue`

: Pointer value to set.

-
void *
`pvTaskGetThreadLocalStoragePointer`

([TaskHandle_t](https://docs.espressif.com#_CPPv412TaskHandle_t)*xTaskToQuery*, BaseType_t*xIndex*)[Â¶](https://docs.espressif.com#_CPPv434pvTaskGetThreadLocalStoragePointer12TaskHandle_t10BaseType_t) Get local storage pointer specific to the given task.

Each task contains an array of pointers that is dimensioned by the configNUM_THREAD_LOCAL_STORAGE_POINTERS setting in FreeRTOSConfig.h. The kernel does not use the pointers itself, so the application writer can use the pointers for any purpose they wish.

**Return**Pointer value

**Parameters**`xTaskToQuery`

: Task to get thread local storage pointer for`xIndex`

: The index of the pointer to get, from 0 to configNUM_THREAD_LOCAL_STORAGE_POINTERS - 1.

-
void
`vTaskSetThreadLocalStoragePointerAndDelCallback`

([TaskHandle_t](https://docs.espressif.com#_CPPv412TaskHandle_t)*xTaskToSet*, BaseType_t*xIndex*, void **pvValue*,[TlsDeleteCallbackFunction_t](https://docs.espressif.com#_CPPv427TlsDeleteCallbackFunction_t)*pvDelCallback*)[Â¶](https://docs.espressif.com#_CPPv447vTaskSetThreadLocalStoragePointerAndDelCallback12TaskHandle_t10BaseType_tPv27TlsDeleteCallbackFunction_t) Set local storage pointer and deletion callback.

Each task contains an array of pointers that is dimensioned by the configNUM_THREAD_LOCAL_STORAGE_POINTERS setting in FreeRTOSConfig.h. The kernel does not use the pointers itself, so the application writer can use the pointers for any purpose they wish.

Local storage pointers set for a task can reference dynamically allocated resources. This function is similar to vTaskSetThreadLocalStoragePointer, but provides a way to release these resources when the task gets deleted. For each pointer, a callback function can be set. This function will be called when task is deleted, with the local storage pointer index and value as arguments.

**Parameters**`xTaskToSet`

: Task to set thread local storage pointer for`xIndex`

: The index of the pointer to set, from 0 to configNUM_THREAD_LOCAL_STORAGE_POINTERS - 1.`pvValue`

: Pointer value to set.`pvDelCallback`

: Function to call to dispose of the local storage pointer when the task is deleted.

-
BaseType_t
`xTaskCallApplicationTaskHook`

([TaskHandle_t](https://docs.espressif.com#_CPPv412TaskHandle_t)*xTask*, void **pvParameter*)[Â¶](https://docs.espressif.com#_CPPv428xTaskCallApplicationTaskHook12TaskHandle_tPv) Calls the hook function associated with xTask. Passing xTask as NULL has the effect of calling the Running tasks (the calling task) hook function.

**Parameters**`xTask`

: Handle of the task to call the hook for.`pvParameter`

: Parameter passed to the hook function for the task to interpret as it wants. The return value is the value returned by the task hook function registered by the user.

-
[TaskHandle_t](https://docs.espressif.com#_CPPv412TaskHandle_t)`xTaskGetIdleTaskHandle`

(void)[Â¶](https://docs.espressif.com#_CPPv422xTaskGetIdleTaskHandlev) Get the handle of idle task for the current CPU.

xTaskGetIdleTaskHandle() is only available if INCLUDE_xTaskGetIdleTaskHandle is set to 1 in FreeRTOSConfig.h.

**Return**The handle of the idle task. It is not valid to call xTaskGetIdleTaskHandle() before the scheduler has been started.

-
[TaskHandle_t](https://docs.espressif.com#_CPPv412TaskHandle_t)`xTaskGetIdleTaskHandleForCPU`

(UBaseType_t*cpuid*)[Â¶](https://docs.espressif.com#_CPPv428xTaskGetIdleTaskHandleForCPU11UBaseType_t) Get the handle of idle task for the given CPU.

xTaskGetIdleTaskHandleForCPU() is only available if INCLUDE_xTaskGetIdleTaskHandle is set to 1 in FreeRTOSConfig.h.

**Return**Idle task handle of a given cpu. It is not valid to call xTaskGetIdleTaskHandleForCPU() before the scheduler has been started.

**Parameters**`cpuid`

: The CPU to get the handle for

-
UBaseType_t
`uxTaskGetSystemState`

([TaskStatus_t](https://docs.espressif.com#_CPPv412TaskStatus_t)**const**pxTaskStatusArray*,*const*UBaseType_t*uxArraySize*, uint32_t **const**pulTotalRunTime*)[Â¶](https://docs.espressif.com#_CPPv420uxTaskGetSystemStatePC12TaskStatus_tK11UBaseType_tPC8uint32_t) Get the state of tasks in the system.

configUSE_TRACE_FACILITY must be defined as 1 in FreeRTOSConfig.h for uxTaskGetSystemState() to be available.

uxTaskGetSystemState() populates an TaskStatus_t structure for each task in the system. TaskStatus_t structures contain, among other things, members for the task handle, task name, task priority, task state, and total amount of run time consumed by the task. See the TaskStatus_t structure definition in this file for the full member list.

Example usage:

// This example demonstrates how a human readable table of run time stats // information is generated from raw data provided by uxTaskGetSystemState(). // The human readable table is written to pcWriteBuffer void vTaskGetRunTimeStats( char *pcWriteBuffer ) { TaskStatus_t *pxTaskStatusArray; volatile UBaseType_t uxArraySize, x; uint32_t ulTotalRunTime, ulStatsAsPercentage; // Make sure the write buffer does not contain a string. *pcWriteBuffer = 0x00; // Take a snapshot of the number of tasks in case it changes while this // function is executing. uxArraySize = uxTaskGetNumberOfTasks(); // Allocate a TaskStatus_t structure for each task. An array could be // allocated statically at compile time. pxTaskStatusArray = pvPortMalloc( uxArraySize * sizeof( TaskStatus_t ) ); if( pxTaskStatusArray != NULL ) { // Generate raw status information about each task. uxArraySize = uxTaskGetSystemState( pxTaskStatusArray, uxArraySize, &ulTotalRunTime ); // For percentage calculations. ulTotalRunTime /= 100UL; // Avoid divide by zero errors. if( ulTotalRunTime > 0 ) { // For each populated position in the pxTaskStatusArray array, // format the raw data as human readable ASCII data for( x = 0; x < uxArraySize; x++ ) { // What percentage of the total run time has the task used? // This will always be rounded down to the nearest integer. // ulTotalRunTimeDiv100 has already been divided by 100. ulStatsAsPercentage = pxTaskStatusArray[ x ].ulRunTimeCounter / ulTotalRunTime; if( ulStatsAsPercentage > 0UL ) { sprintf( pcWriteBuffer, "%s\t\t%lu\t\t%lu%%\r\n", pxTaskStatusArray[ x ].pcTaskName, pxTaskStatusArray[ x ].ulRunTimeCounter, ulStatsAsPercentage ); } else { // If the percentage is zero here then the task has // consumed less than 1% of the total run time. sprintf( pcWriteBuffer, "%s\t\t%lu\t\t<1%%\r\n", pxTaskStatusArray[ x ].pcTaskName, pxTaskStatusArray[ x ].ulRunTimeCounter ); } pcWriteBuffer += strlen( ( char * ) pcWriteBuffer ); } } // The array is no longer needed, free the memory it consumes. vPortFree( pxTaskStatusArray ); } }

**Note**This function is intended for debugging use only as its use results in the scheduler remaining suspended for an extended period.

**Return**The number of TaskStatus_t structures that were populated by uxTaskGetSystemState(). This should equal the number returned by the uxTaskGetNumberOfTasks() API function, but will be zero if the value passed in the uxArraySize parameter was too small.

**Parameters**`pxTaskStatusArray`

: A pointer to an array of TaskStatus_t structures. The array must contain at least one TaskStatus_t structure for each task that is under the control of the RTOS. The number of tasks under the control of the RTOS can be determined using the uxTaskGetNumberOfTasks() API function.`uxArraySize`

: The size of the array pointed to by the pxTaskStatusArray parameter. The size is specified as the number of indexes in the array, or the number of TaskStatus_t structures contained in the array, not by the number of bytes in the array.`pulTotalRunTime`

: If configGENERATE_RUN_TIME_STATS is set to 1 in FreeRTOSConfig.h then *pulTotalRunTime is set by uxTaskGetSystemState() to the total run time (as defined by the run time stats clock, see[http://www.freertos.org/rtos-run-time-stats.html](http://www.freertos.org/rtos-run-time-stats.html)) since the target booted. pulTotalRunTime can be set to NULL to omit the total run time information.

-
void
`vTaskList`

(char **pcWriteBuffer*)[Â¶](https://docs.espressif.com#_CPPv49vTaskListPc) List all the current tasks.

configUSE_TRACE_FACILITY and configUSE_STATS_FORMATTING_FUNCTIONS must both be defined as 1 for this function to be available. See the configuration section of the FreeRTOS.org website for more information.

Lists all the current tasks, along with their current state and stack usage high water mark.

**Note**This function will disable interrupts for its duration. It is not intended for normal application runtime use but as a debug aid.

Tasks are reported as blocked (âBâ), ready (âRâ), deleted (âDâ) or suspended (âSâ).

vTaskList() calls uxTaskGetSystemState(), then formats part of the uxTaskGetSystemState() output into a human readable table that displays task names, states and stack usage.

**Note**This function is provided for convenience only, and is used by many of the demo applications. Do not consider it to be part of the scheduler.

vTaskList() has a dependency on the sprintf() C library function that might bloat the code size, use a lot of stack, and provide different results on different platforms. An alternative, tiny, third party, and limited functionality implementation of sprintf() is provided in many of the FreeRTOS/Demo sub-directories in a file called printf-stdarg.c (note printf-stdarg.c does not provide a full snprintf() implementation!).

It is recommended that production systems call uxTaskGetSystemState() directly to get access to raw stats data, rather than indirectly through a call to vTaskList().

**Parameters**`pcWriteBuffer`

: A buffer into which the above mentioned details will be written, in ASCII form. This buffer is assumed to be large enough to contain the generated report. Approximately 40 bytes per task should be sufficient.

-
void
`vTaskGetRunTimeStats`

(char **pcWriteBuffer*)[Â¶](https://docs.espressif.com#_CPPv420vTaskGetRunTimeStatsPc) Get the state of running tasks as a string

configGENERATE_RUN_TIME_STATS and configUSE_STATS_FORMATTING_FUNCTIONS must both be defined as 1 for this function to be available. The application must also then provide definitions for portCONFIGURE_TIMER_FOR_RUN_TIME_STATS() and portGET_RUN_TIME_COUNTER_VALUE() to configure a peripheral timer/counter and return the timers current count value respectively. The counter should be at least 10 times the frequency of the tick count.

Setting configGENERATE_RUN_TIME_STATS to 1 will result in a total accumulated execution time being stored for each task. The resolution of the accumulated time value depends on the frequency of the timer configured by the portCONFIGURE_TIMER_FOR_RUN_TIME_STATS() macro. Calling vTaskGetRunTimeStats() writes the total execution time of each task into a buffer, both as an absolute count value and as a percentage of the total system execution time.

**Note**This function will disable interrupts for its duration. It is not intended for normal application runtime use but as a debug aid.

vTaskGetRunTimeStats() calls uxTaskGetSystemState(), then formats part of the uxTaskGetSystemState() output into a human readable table that displays the amount of time each task has spent in the Running state in both absolute and percentage terms.

**Note**This function is provided for convenience only, and is used by many of the demo applications. Do not consider it to be part of the scheduler.

vTaskGetRunTimeStats() has a dependency on the sprintf() C library function that might bloat the code size, use a lot of stack, and provide different results on different platforms. An alternative, tiny, third party, and limited functionality implementation of sprintf() is provided in many of the FreeRTOS/Demo sub-directories in a file called printf-stdarg.c (note printf-stdarg.c does not provide a full snprintf() implementation!).

It is recommended that production systems call uxTaskGetSystemState() directly to get access to raw stats data, rather than indirectly through a call to vTaskGetRunTimeStats().

**Parameters**`pcWriteBuffer`

: A buffer into which the execution times will be written, in ASCII form. This buffer is assumed to be large enough to contain the generated report. Approximately 40 bytes per task should be sufficient.

-
BaseType_t
`xTaskNotify`

([TaskHandle_t](https://docs.espressif.com#_CPPv412TaskHandle_t)*xTaskToNotify*, uint32_t*ulValue*,[eNotifyAction](https://docs.espressif.com#_CPPv413eNotifyAction)*eAction*)[Â¶](https://docs.espressif.com#_CPPv411xTaskNotify12TaskHandle_t8uint32_t13eNotifyAction) Send task notification.

configUSE_TASK_NOTIFICATIONS must be undefined or defined as 1 for this function to be available.

When configUSE_TASK_NOTIFICATIONS is set to one each task has its own private ânotification valueâ, which is a 32-bit unsigned integer (uint32_t).

Events can be sent to a task using an intermediary object. Examples of such objects are queues, semaphores, mutexes and event groups. Task notifications are a method of sending an event directly to a task without the need for such an intermediary object.

A notification sent to a task can optionally perform an action, such as update, overwrite or increment the taskâs notification value. In that way task notifications can be used to send data to a task, or be used as light weight and fast binary or counting semaphores.

A notification sent to a task will remain pending until it is cleared by the task calling xTaskNotifyWait() or ulTaskNotifyTake(). If the task was already in the Blocked state to wait for a notification when the notification arrives then the task will automatically be removed from the Blocked state (unblocked) and the notification cleared.

A task can use xTaskNotifyWait() to [optionally] block to wait for a notification to be pending, or ulTaskNotifyTake() to [optionally] block to wait for its notification value to have a non-zero value. The task does not consume any CPU time while it is in the Blocked state.

See

[http://www.FreeRTOS.org/RTOS-task-notifications.html](http://www.FreeRTOS.org/RTOS-task-notifications.html)for details.**Return**Dependent on the value of eAction. See the description of the eAction parameter.

**Parameters**`xTaskToNotify`

: The handle of the task being notified. The handle to a task can be returned from the xTaskCreate() API function used to create the task, and the handle of the currently running task can be obtained by calling xTaskGetCurrentTaskHandle().`ulValue`

: Data that can be sent with the notification. How the data is used depends on the value of the eAction parameter.`eAction`

: Specifies how the notification updates the taskâs notification value, if at all. Valid values for eAction are as follows:eSetBits: The taskâs notification value is bitwise ORed with ulValue. xTaskNofify() always returns pdPASS in this case.

eIncrement: The taskâs notification value is incremented. ulValue is not used and xTaskNotify() always returns pdPASS in this case.

eSetValueWithOverwrite: The taskâs notification value is set to the value of ulValue, even if the task being notified had not yet processed the previous notification (the task already had a notification pending). xTaskNotify() always returns pdPASS in this case.

eSetValueWithoutOverwrite: If the task being notified did not already have a notification pending then the taskâs notification value is set to ulValue and xTaskNotify() will return pdPASS. If the task being notified already had a notification pending then no action is performed and pdFAIL is returned.

eNoAction: The task receives a notification without its notification value being Â Â updated. ulValue is not used and xTaskNotify() always returns pdPASS in this case.

-
BaseType_t
`xTaskNotifyFromISR`

([TaskHandle_t](https://docs.espressif.com#_CPPv412TaskHandle_t)*xTaskToNotify*, uint32_t*ulValue*,[eNotifyAction](https://docs.espressif.com#_CPPv413eNotifyAction)*eAction*, BaseType_t **pxHigherPriorityTaskWoken*)[Â¶](https://docs.espressif.com#_CPPv418xTaskNotifyFromISR12TaskHandle_t8uint32_t13eNotifyActionP10BaseType_t) Send task notification from an ISR.

configUSE_TASK_NOTIFICATIONS must be undefined or defined as 1 for this function to be available.

When configUSE_TASK_NOTIFICATIONS is set to one each task has its own private ânotification valueâ, which is a 32-bit unsigned integer (uint32_t).

A version of xTaskNotify() that can be used from an interrupt service routine (ISR).

Events can be sent to a task using an intermediary object. Examples of such objects are queues, semaphores, mutexes and event groups. Task notifications are a method of sending an event directly to a task without the need for such an intermediary object.

A notification sent to a task can optionally perform an action, such as update, overwrite or increment the taskâs notification value. In that way task notifications can be used to send data to a task, or be used as light weight and fast binary or counting semaphores.

A notification sent to a task will remain pending until it is cleared by the task calling xTaskNotifyWait() or ulTaskNotifyTake(). If the task was already in the Blocked state to wait for a notification when the notification arrives then the task will automatically be removed from the Blocked state (unblocked) and the notification cleared.

A task can use xTaskNotifyWait() to [optionally] block to wait for a notification to be pending, or ulTaskNotifyTake() to [optionally] block to wait for its notification value to have a non-zero value. The task does not consume any CPU time while it is in the Blocked state.

See

[http://www.FreeRTOS.org/RTOS-task-notifications.html](http://www.FreeRTOS.org/RTOS-task-notifications.html)for details.**Return**Dependent on the value of eAction. See the description of the eAction parameter.

**Parameters**`xTaskToNotify`

: The handle of the task being notified. The handle to a task can be returned from the xTaskCreate() API function used to create the task, and the handle of the currently running task can be obtained by calling xTaskGetCurrentTaskHandle().`ulValue`

: Data that can be sent with the notification. How the data is used depends on the value of the eAction parameter.`eAction`

: Specifies how the notification updates the taskâs notification value, if at all. Valid values for eAction are as follows:eSetBits: The taskâs notification value is bitwise ORed with ulValue. xTaskNofify() always returns pdPASS in this case.

eIncrement: The taskâs notification value is incremented. ulValue is not used and xTaskNotify() always returns pdPASS in this case.

eSetValueWithOverwrite: The taskâs notification value is set to the value of ulValue, even if the task being notified had not yet processed the previous notification (the task already had a notification pending). xTaskNotify() always returns pdPASS in this case.

eSetValueWithoutOverwrite: If the task being notified did not already have a notification pending then the taskâs notification value is set to ulValue and xTaskNotify() will return pdPASS. If the task being notified already had a notification pending then no action is performed and pdFAIL is returned.

eNoAction: The task receives a notification without its notification value being updated. ulValue is not used and xTaskNotify() always returns pdPASS in this case.

`pxHigherPriorityTaskWoken`

: xTaskNotifyFromISR() will set *pxHigherPriorityTaskWoken to pdTRUE if sending the notification caused the task to which the notification was sent to leave the Blocked state, and the unblocked task has a priority higher than the currently running task. If xTaskNotifyFromISR() sets this value to pdTRUE then a context switch should be requested before the interrupt is exited. How a context switch is requested from an ISR is dependent on the port - see the documentation page for the port in use.

-
BaseType_t
`xTaskNotifyWait`

(uint32_t*ulBitsToClearOnEntry*, uint32_t*ulBitsToClearOnExit*, uint32_t **pulNotificationValue*, TickType_t*xTicksToWait*)[Â¶](https://docs.espressif.com#_CPPv415xTaskNotifyWait8uint32_t8uint32_tP8uint32_t10TickType_t) Wait for task notification

configUSE_TASK_NOTIFICATIONS must be undefined or defined as 1 for this function to be available.

When configUSE_TASK_NOTIFICATIONS is set to one each task has its own private ânotification valueâ, which is a 32-bit unsigned integer (uint32_t).

Events can be sent to a task using an intermediary object. Examples of such objects are queues, semaphores, mutexes and event groups. Task notifications are a method of sending an event directly to a task without the need for such an intermediary object.

A notification sent to a task can optionally perform an action, such as update, overwrite or increment the taskâs notification value. In that way task notifications can be used to send data to a task, or be used as light weight and fast binary or counting semaphores.

A notification sent to a task will remain pending until it is cleared by the task calling xTaskNotifyWait() or ulTaskNotifyTake(). If the task was already in the Blocked state to wait for a notification when the notification arrives then the task will automatically be removed from the Blocked state (unblocked) and the notification cleared.

A task can use xTaskNotifyWait() to [optionally] block to wait for a notification to be pending, or ulTaskNotifyTake() to [optionally] block to wait for its notification value to have a non-zero value. The task does not consume any CPU time while it is in the Blocked state.

See

[http://www.FreeRTOS.org/RTOS-task-notifications.html](http://www.FreeRTOS.org/RTOS-task-notifications.html)for details.**Return**If a notification was received (including notifications that were already pending when xTaskNotifyWait was called) then pdPASS is returned. Otherwise pdFAIL is returned.

**Parameters**`ulBitsToClearOnEntry`

: Bits that are set in ulBitsToClearOnEntry value will be cleared in the calling taskâs notification value before the task checks to see if any notifications are pending, and optionally blocks if no notifications are pending. Setting ulBitsToClearOnEntry to ULONG_MAX (if limits.h is included) or 0xffffffffUL (if limits.h is not included) will have the effect of resetting the taskâs notification value to 0. Setting ulBitsToClearOnEntry to 0 will leave the taskâs notification value unchanged.`ulBitsToClearOnExit`

: If a notification is pending or received before the calling task exits the xTaskNotifyWait() function then the taskâs notification value (see the xTaskNotify() API function) is passed out using the pulNotificationValue parameter. Then any bits that are set in ulBitsToClearOnExit will be cleared in the taskâs notification value (note *pulNotificationValue is set before any bits are cleared). Setting ulBitsToClearOnExit to ULONG_MAX (if limits.h is included) or 0xffffffffUL (if limits.h is not included) will have the effect of resetting the taskâs notification value to 0 before the function exits. Setting ulBitsToClearOnExit to 0 will leave the taskâs notification value unchanged when the function exits (in which case the value passed out in pulNotificationValue will match the taskâs notification value).`pulNotificationValue`

: Used to pass the taskâs notification value out of the function. Note the value passed out will not be effected by the clearing of any bits caused by ulBitsToClearOnExit being non-zero.`xTicksToWait`

: The maximum amount of time that the task should wait in the Blocked state for a notification to be received, should a notification not already be pending when xTaskNotifyWait() was called. The task will not consume any processing time while it is in the Blocked state. This is specified in kernel ticks, the macro pdMS_TO_TICSK( value_in_ms ) can be used to convert a time specified in milliseconds to a time specified in ticks.

-
void
`vTaskNotifyGiveFromISR`

([TaskHandle_t](https://docs.espressif.com#_CPPv412TaskHandle_t)*xTaskToNotify*, BaseType_t **pxHigherPriorityTaskWoken*)[Â¶](https://docs.espressif.com#_CPPv422vTaskNotifyGiveFromISR12TaskHandle_tP10BaseType_t) Simplified macro for sending task notification from ISR.

configUSE_TASK_NOTIFICATIONS must be undefined or defined as 1 for this macro to be available.

When configUSE_TASK_NOTIFICATIONS is set to one each task has its own private ânotification valueâ, which is a 32-bit unsigned integer (uint32_t).

A version of xTaskNotifyGive() that can be called from an interrupt service routine (ISR).

Events can be sent to a task using an intermediary object. Examples of such objects are queues, semaphores, mutexes and event groups. Task notifications are a method of sending an event directly to a task without the need for such an intermediary object.

A notification sent to a task can optionally perform an action, such as update, overwrite or increment the taskâs notification value. In that way task notifications can be used to send data to a task, or be used as light weight and fast binary or counting semaphores.

vTaskNotifyGiveFromISR() is intended for use when task notifications are used as light weight and faster binary or counting semaphore equivalents. Actual FreeRTOS semaphores are given from an ISR using the xSemaphoreGiveFromISR() API function, the equivalent action that instead uses a task notification is vTaskNotifyGiveFromISR().

When task notifications are being used as a binary or counting semaphore equivalent then the task being notified should wait for the notification using the ulTaskNotificationTake() API function rather than the xTaskNotifyWait() API function.

See

[http://www.FreeRTOS.org/RTOS-task-notifications.html](http://www.FreeRTOS.org/RTOS-task-notifications.html)for more details.**Parameters**`xTaskToNotify`

: The handle of the task being notified. The handle to a task can be returned from the xTaskCreate() API function used to create the task, and the handle of the currently running task can be obtained by calling xTaskGetCurrentTaskHandle().`pxHigherPriorityTaskWoken`

: vTaskNotifyGiveFromISR() will set *pxHigherPriorityTaskWoken to pdTRUE if sending the notification caused the task to which the notification was sent to leave the Blocked state, and the unblocked task has a priority higher than the currently running task. If vTaskNotifyGiveFromISR() sets this value to pdTRUE then a context switch should be requested before the interrupt is exited. How a context switch is requested from an ISR is dependent on the port - see the documentation page for the port in use.

-
uint32_t
`ulTaskNotifyTake`

(BaseType_t*xClearCountOnExit*, TickType_t*xTicksToWait*)[Â¶](https://docs.espressif.com#_CPPv416ulTaskNotifyTake10BaseType_t10TickType_t) Simplified macro for receiving task notification.

configUSE_TASK_NOTIFICATIONS must be undefined or defined as 1 for this function to be available.

When configUSE_TASK_NOTIFICATIONS is set to one each task has its own private ânotification valueâ, which is a 32-bit unsigned integer (uint32_t).

Events can be sent to a task using an intermediary object. Examples of such objects are queues, semaphores, mutexes and event groups. Task notifications are a method of sending an event directly to a task without the need for such an intermediary object.

A notification sent to a task can optionally perform an action, such as update, overwrite or increment the taskâs notification value. In that way task notifications can be used to send data to a task, or be used as light weight and fast binary or counting semaphores.

ulTaskNotifyTake() is intended for use when a task notification is used as a faster and lighter weight binary or counting semaphore alternative. Actual FreeRTOS semaphores are taken using the xSemaphoreTake() API function, the equivalent action that instead uses a task notification is ulTaskNotifyTake().

When a task is using its notification value as a binary or counting semaphore other tasks should send notifications to it using the xTaskNotifyGive() macro, or xTaskNotify() function with the eAction parameter set to eIncrement.

ulTaskNotifyTake() can either clear the taskâs notification value to zero on exit, in which case the notification value acts like a binary semaphore, or decrement the taskâs notification value on exit, in which case the notification value acts like a counting semaphore.

A task can use ulTaskNotifyTake() to [optionally] block to wait for a the taskâs notification value to be non-zero. The task does not consume any CPU time while it is in the Blocked state.

Where as xTaskNotifyWait() will return when a notification is pending, ulTaskNotifyTake() will return when the taskâs notification value is not zero.

See

[http://www.FreeRTOS.org/RTOS-task-notifications.html](http://www.FreeRTOS.org/RTOS-task-notifications.html)for details.**Return**The taskâs notification count before it is either cleared to zero or decremented (see the xClearCountOnExit parameter).

**Parameters**`xClearCountOnExit`

: if xClearCountOnExit is pdFALSE then the taskâs notification value is decremented when the function exits. In this way the notification value acts like a counting semaphore. If xClearCountOnExit is not pdFALSE then the taskâs notification value is cleared to zero when the function exits. In this way the notification value acts like a binary semaphore.`xTicksToWait`

: The maximum amount of time that the task should wait in the Blocked state for the taskâs notification value to be greater than zero, should the count not already be greater than zero when ulTaskNotifyTake() was called. The task will not consume any processing time while it is in the Blocked state. This is specified in kernel ticks, the macro pdMS_TO_TICSK( value_in_ms ) can be used to convert a time specified in milliseconds to a time specified in ticks.

### Structures[Â¶](https://docs.espressif.com#structures)

-
*struct*`xTASK_STATUS`

[Â¶](https://docs.espressif.com#_CPPv412xTASK_STATUS) Used with the uxTaskGetSystemState() function to return the state of each task in the system.

Public Members

-
[TaskHandle_t](https://docs.espressif.com#_CPPv412TaskHandle_t)`xHandle`

[Â¶](https://docs.espressif.com#_CPPv4N12xTASK_STATUS7xHandleE) The handle of the task to which the rest of the information in the structure relates.

-
*const*char *`pcTaskName`

[Â¶](https://docs.espressif.com#_CPPv4N12xTASK_STATUS10pcTaskNameE) A pointer to the taskâs name. This value will be invalid if the task was deleted since the structure was populated!

-
UBaseType_t
`xTaskNumber`

[Â¶](https://docs.espressif.com#_CPPv4N12xTASK_STATUS11xTaskNumberE) A number unique to the task.

-
[eTaskState](https://docs.espressif.com#_CPPv410eTaskState)`eCurrentState`

[Â¶](https://docs.espressif.com#_CPPv4N12xTASK_STATUS13eCurrentStateE) The state in which the task existed when the structure was populated.

-
UBaseType_t
`uxCurrentPriority`

[Â¶](https://docs.espressif.com#_CPPv4N12xTASK_STATUS17uxCurrentPriorityE) The priority at which the task was running (may be inherited) when the structure was populated.

-
UBaseType_t
`uxBasePriority`

[Â¶](https://docs.espressif.com#_CPPv4N12xTASK_STATUS14uxBasePriorityE) The priority to which the task will return if the taskâs current priority has been inherited to avoid unbounded priority inversion when obtaining a mutex. Only valid if configUSE_MUTEXES is defined as 1 in FreeRTOSConfig.h.

-
uint32_t
`ulRunTimeCounter`

[Â¶](https://docs.espressif.com#_CPPv4N12xTASK_STATUS16ulRunTimeCounterE) The total run time allocated to the task so far, as defined by the run time stats clock. See

[http://www.freertos.org/rtos-run-time-stats.html](http://www.freertos.org/rtos-run-time-stats.html). Only valid when configGENERATE_RUN_TIME_STATS is defined as 1 in FreeRTOSConfig.h.

-
StackType_t *
`pxStackBase`

[Â¶](https://docs.espressif.com#_CPPv4N12xTASK_STATUS11pxStackBaseE) Points to the lowest address of the taskâs stack area.

-
uint32_t
`usStackHighWaterMark`

[Â¶](https://docs.espressif.com#_CPPv4N12xTASK_STATUS20usStackHighWaterMarkE) The minimum amount of stack space that has remained for the task since the task was created. The closer this value is to zero the closer the task has come to overflowing its stack.

-
BaseType_t
`xCoreID`

[Â¶](https://docs.espressif.com#_CPPv4N12xTASK_STATUS7xCoreIDE) Core this task is pinned to (0, 1, or -1 for tskNO_AFFINITY). This field is present if CONFIG_FREERTOS_VTASKLIST_INCLUDE_COREID is set.

-

-
*struct*`xTASK_SNAPSHOT`

[Â¶](https://docs.espressif.com#_CPPv414xTASK_SNAPSHOT) Used with the uxTaskGetSnapshotAll() function to save memory snapshot of each task in the system. We need this struct because TCB_t is defined (hidden) in tasks.c.

Public Members

-
void *
`pxTCB`

[Â¶](https://docs.espressif.com#_CPPv4N14xTASK_SNAPSHOT5pxTCBE) Address of task control block.

-
StackType_t *
`pxTopOfStack`

[Â¶](https://docs.espressif.com#_CPPv4N14xTASK_SNAPSHOT12pxTopOfStackE) Points to the location of the last item placed on the tasks stack.

-
StackType_t *
`pxEndOfStack`

[Â¶](https://docs.espressif.com#_CPPv4N14xTASK_SNAPSHOT12pxEndOfStackE) Points to the end of the stack. pxTopOfStack < pxEndOfStack, stack grows hi2lo pxTopOfStack > pxEndOfStack, stack grows lo2hi

-
void *

### Macros[Â¶](https://docs.espressif.com#macros)

-
`tskKERNEL_VERSION_NUMBER`

[Â¶](https://docs.espressif.com#c.tskKERNEL_VERSION_NUMBER)

-
`tskKERNEL_VERSION_MAJOR`

[Â¶](https://docs.espressif.com#c.tskKERNEL_VERSION_MAJOR)

-
`tskKERNEL_VERSION_MINOR`

[Â¶](https://docs.espressif.com#c.tskKERNEL_VERSION_MINOR)

-
`tskKERNEL_VERSION_BUILD`

[Â¶](https://docs.espressif.com#c.tskKERNEL_VERSION_BUILD)

-
`tskNO_AFFINITY`

[Â¶](https://docs.espressif.com#c.tskNO_AFFINITY) Argument of xTaskCreatePinnedToCore indicating that task has no affinity.

-
`tskIDLE_PRIORITY`

[Â¶](https://docs.espressif.com#c.tskIDLE_PRIORITY) Defines the priority used by the idle task. This must not be modified.

-
`taskYIELD`

()[Â¶](https://docs.espressif.com#c.taskYIELD) task. h

Macro for forcing a context switch.

-
`taskENTER_CRITICAL`

(mux)[Â¶](https://docs.espressif.com#c.taskENTER_CRITICAL) task. h

Macro to mark the start of a critical code region. Preemptive context switches cannot occur when in a critical region.

**Note**This may alter the stack (depending on the portable implementation) so must be used with care!

-
`taskENTER_CRITICAL_ISR`

(mux)[Â¶](https://docs.espressif.com#c.taskENTER_CRITICAL_ISR)

-
`taskEXIT_CRITICAL`

(mux)[Â¶](https://docs.espressif.com#c.taskEXIT_CRITICAL) task. h

Macro to mark the end of a critical code region. Preemptive context switches cannot occur when in a critical region.

**Note**This may alter the stack (depending on the portable implementation) so must be used with care!

-
`taskEXIT_CRITICAL_ISR`

(mux)[Â¶](https://docs.espressif.com#c.taskEXIT_CRITICAL_ISR)

-
`taskDISABLE_INTERRUPTS`

()[Â¶](https://docs.espressif.com#c.taskDISABLE_INTERRUPTS) task. h

Macro to disable all maskable interrupts.

-
`taskENABLE_INTERRUPTS`

()[Â¶](https://docs.espressif.com#c.taskENABLE_INTERRUPTS) task. h

Macro to enable microcontroller interrupts.

-
`taskSCHEDULER_SUSPENDED`

[Â¶](https://docs.espressif.com#c.taskSCHEDULER_SUSPENDED)

-
`taskSCHEDULER_NOT_STARTED`

[Â¶](https://docs.espressif.com#c.taskSCHEDULER_NOT_STARTED)

-
`taskSCHEDULER_RUNNING`

[Â¶](https://docs.espressif.com#c.taskSCHEDULER_RUNNING)

-
`xTaskNotifyGive`

(xTaskToNotify)[Â¶](https://docs.espressif.com#c.xTaskNotifyGive) Simplified macro for sending task notification.

configUSE_TASK_NOTIFICATIONS must be undefined or defined as 1 for this macro to be available.

When configUSE_TASK_NOTIFICATIONS is set to one each task has its own private ânotification valueâ, which is a 32-bit unsigned integer (uint32_t).

Events can be sent to a task using an intermediary object. Examples of such objects are queues, semaphores, mutexes and event groups. Task notifications are a method of sending an event directly to a task without the need for such an intermediary object.

A notification sent to a task can optionally perform an action, such as update, overwrite or increment the taskâs notification value. In that way task notifications can be used to send data to a task, or be used as light weight and fast binary or counting semaphores.

xTaskNotifyGive() is a helper macro intended for use when task notifications are used as light weight and faster binary or counting semaphore equivalents. Actual FreeRTOS semaphores are given using the xSemaphoreGive() API function, the equivalent action that instead uses a task notification is xTaskNotifyGive().

When task notifications are being used as a binary or counting semaphore equivalent then the task being notified should wait for the notification using the ulTaskNotificationTake() API function rather than the xTaskNotifyWait() API function.

See

[http://www.FreeRTOS.org/RTOS-task-notifications.html](http://www.FreeRTOS.org/RTOS-task-notifications.html)for more details.**Return**xTaskNotifyGive() is a macro that calls xTaskNotify() with the eAction parameter set to eIncrement - so pdPASS is always returned.

**Parameters**`xTaskToNotify`

: The handle of the task being notified. The handle to a task can be returned from the xTaskCreate() API function used to create the task, and the handle of the currently running task can be obtained by calling xTaskGetCurrentTaskHandle().

### Type Definitions[Â¶](https://docs.espressif.com#type-definitions)

-
*typedef*void *`TaskHandle_t`

[Â¶](https://docs.espressif.com#_CPPv412TaskHandle_t) task. h

Type by which tasks are referenced. For example, a call to xTaskCreate returns (via a pointer parameter) an TaskHandle_t variable that can then be used as a parameter to vTaskDelete to delete the task.

-
*typedef*BaseType_t (*`TaskHookFunction_t`

)(void *)[Â¶](https://docs.espressif.com#_CPPv418TaskHookFunction_t) Defines the prototype to which the application task hook function must conform.

-
*typedef**struct*[xTASK_STATUS](https://docs.espressif.com#_CPPv412xTASK_STATUS)`TaskStatus_t`

[Â¶](https://docs.espressif.com#_CPPv412TaskStatus_t) Used with the uxTaskGetSystemState() function to return the state of each task in the system.

-
*typedef**struct*[xTASK_SNAPSHOT](https://docs.espressif.com#_CPPv414xTASK_SNAPSHOT)`TaskSnapshot_t`

[Â¶](https://docs.espressif.com#_CPPv414TaskSnapshot_t) Used with the uxTaskGetSnapshotAll() function to save memory snapshot of each task in the system. We need this struct because TCB_t is defined (hidden) in tasks.c.

-
*typedef*void (*`TlsDeleteCallbackFunction_t`

)(int, void *)[Â¶](https://docs.espressif.com#_CPPv427TlsDeleteCallbackFunction_t) Prototype of local storage pointer deletion callback.

### Enumerations[Â¶](https://docs.espressif.com#enumerations)

-
*enum*`eTaskState`

[Â¶](https://docs.espressif.com#_CPPv410eTaskState) Task states returned by eTaskGetState.

*Values:*-
`eRunning`

= 0[Â¶](https://docs.espressif.com#_CPPv48eRunning) A task is querying the state of itself, so must be running.

-
`eReady`

[Â¶](https://docs.espressif.com#_CPPv46eReady) The task being queried is in a read or pending ready list.

-
`eBlocked`

[Â¶](https://docs.espressif.com#_CPPv48eBlocked) The task being queried is in the Blocked state.

-
`eSuspended`

[Â¶](https://docs.espressif.com#_CPPv410eSuspended) The task being queried is in the Suspended state, or is in the Blocked state with an infinite time out.

-
`eDeleted`

[Â¶](https://docs.espressif.com#_CPPv48eDeleted) The task being queried has been deleted, but its TCB has not yet been freed.

-

-
*enum*`eNotifyAction`

[Â¶](https://docs.espressif.com#_CPPv413eNotifyAction) Actions that can be performed when vTaskNotify() is called.

*Values:*-
`eNoAction`

= 0[Â¶](https://docs.espressif.com#_CPPv49eNoAction) Notify the task without updating its notify value.

-
`eSetBits`

[Â¶](https://docs.espressif.com#_CPPv48eSetBits) Set bits in the taskâs notification value.

-
`eIncrement`

[Â¶](https://docs.espressif.com#_CPPv410eIncrement) Increment the taskâs notification value.

-
`eSetValueWithOverwrite`

[Â¶](https://docs.espressif.com#_CPPv422eSetValueWithOverwrite) Set the taskâs notification value to a specific value even if the previous value has not yet been read by the task.

-
`eSetValueWithoutOverwrite`

[Â¶](https://docs.espressif.com#_CPPv425eSetValueWithoutOverwrite) Set the taskâs notification value if the previous value has been read by the task.

-

-
*enum*`eSleepModeStatus`

[Â¶](https://docs.espressif.com#_CPPv416eSleepModeStatus) Possible return values for eTaskConfirmSleepModeStatus().

*Values:*-
`eAbortSleep`

= 0[Â¶](https://docs.espressif.com#_CPPv411eAbortSleep) A task has been made ready or a context switch pended since portSUPPORESS_TICKS_AND_SLEEP() was called - abort entering a sleep mode.

-
`eStandardSleep`

[Â¶](https://docs.espressif.com#_CPPv414eStandardSleep) Enter a sleep mode that will not last any longer than the expected idle time.

-
`eNoTasksWaitingTimeout`

[Â¶](https://docs.espressif.com#_CPPv422eNoTasksWaitingTimeout) No tasks are waiting for a timeout so it is safe to enter a sleep mode that can only be exited by an external interrupt.

-

## Queue API[Â¶](https://docs.espressif.com#queue-api)

### Header File[Â¶](https://docs.espressif.com#id1)

### Functions[Â¶](https://docs.espressif.com#id2)

-
BaseType_t
`xQueueGenericSendFromISR`

([QueueHandle_t](https://docs.espressif.com#_CPPv413QueueHandle_t)*xQueue*,*const*void **const**pvItemToQueue*, BaseType_t **const**pxHigherPriorityTaskWoken*,*const*BaseType_t*xCopyPosition*)[Â¶](https://docs.espressif.com#_CPPv424xQueueGenericSendFromISR13QueueHandle_tPCKvPC10BaseType_tK10BaseType_t) It is preferred that the macros xQueueSendFromISR(), xQueueSendToFrontFromISR() and xQueueSendToBackFromISR() be used in place of calling this function directly. xQueueGiveFromISR() is an equivalent for use by semaphores that donât actually copy any data.

Post an item on a queue. It is safe to use this function from within an interrupt service routine.

Items are queued by copy not reference so it is preferable to only queue small items, especially when called from an ISR. In most cases it would be preferable to store a pointer to the item being queued.

Example usage for buffered IO (where the ISR can obtain more than one value per call):

void vBufferISR( void ) { char cIn; BaseType_t xHigherPriorityTaskWokenByPost; // We have not woken a task at the start of the ISR. xHigherPriorityTaskWokenByPost = pdFALSE; // Loop until the buffer is empty. do { // Obtain a byte from the buffer. cIn = portINPUT_BYTE( RX_REGISTER_ADDRESS ); // Post each byte. xQueueGenericSendFromISR( xRxQueue, &cIn, &xHigherPriorityTaskWokenByPost, queueSEND_TO_BACK ); } while( portINPUT_BYTE( BUFFER_COUNT ) ); // Now the buffer is empty we can switch context if necessary. Note that the // name of the yield function required is port specific. if( xHigherPriorityTaskWokenByPost ) { taskYIELD_YIELD_FROM_ISR(); } }

**Return**pdTRUE if the data was successfully sent to the queue, otherwise errQUEUE_FULL.

**Parameters**`xQueue`

: The handle to the queue on which the item is to be posted.`pvItemToQueue`

: A pointer to the item that is to be placed on the queue. The size of the items the queue will hold was defined when the queue was created, so this many bytes will be copied from pvItemToQueue into the queue storage area.`[out] pxHigherPriorityTaskWoken`

: xQueueGenericSendFromISR() will set *pxHigherPriorityTaskWoken to pdTRUE if sending to the queue caused a task to unblock, and the unblocked task has a priority higher than the currently running task. If xQueueGenericSendFromISR() sets this value to pdTRUE then a context switch should be requested before the interrupt is exited.`xCopyPosition`

: Can take the value queueSEND_TO_BACK to place the item at the back of the queue, or queueSEND_TO_FRONT to place the item at the front of the queue (for high priority messages).

-
BaseType_t
`xQueueGiveFromISR`

([QueueHandle_t](https://docs.espressif.com#_CPPv413QueueHandle_t)*xQueue*, BaseType_t **const**pxHigherPriorityTaskWoken*)[Â¶](https://docs.espressif.com#_CPPv417xQueueGiveFromISR13QueueHandle_tPC10BaseType_t)

-
BaseType_t
`xQueueIsQueueEmptyFromISR`

(*const*[QueueHandle_t](https://docs.espressif.com#_CPPv413QueueHandle_t)*xQueue*)[Â¶](https://docs.espressif.com#_CPPv425xQueueIsQueueEmptyFromISRK13QueueHandle_t) Utilities to query queues that are safe to use from an ISR. These utilities should be used only from witin an ISR, or within a critical section.

-
BaseType_t
`xQueueIsQueueFullFromISR`

(*const*[QueueHandle_t](https://docs.espressif.com#_CPPv413QueueHandle_t)*xQueue*)[Â¶](https://docs.espressif.com#_CPPv424xQueueIsQueueFullFromISRK13QueueHandle_t)

-
UBaseType_t
`uxQueueMessagesWaitingFromISR`

(*const*[QueueHandle_t](https://docs.espressif.com#_CPPv413QueueHandle_t)*xQueue*)[Â¶](https://docs.espressif.com#_CPPv429uxQueueMessagesWaitingFromISRK13QueueHandle_t)

-
BaseType_t
`xQueueGenericSend`

([QueueHandle_t](https://docs.espressif.com#_CPPv413QueueHandle_t)*xQueue*,*const*void **const**pvItemToQueue*, TickType_t*xTicksToWait*,*const*BaseType_t*xCopyPosition*)[Â¶](https://docs.espressif.com#_CPPv417xQueueGenericSend13QueueHandle_tPCKv10TickType_tK10BaseType_t) It is preferred that the macros xQueueSend(), xQueueSendToFront() and xQueueSendToBack() are used in place of calling this function directly.

Post an item on a queue. The item is queued by copy, not by reference. This function must not be called from an interrupt service routine. See xQueueSendFromISR () for an alternative which may be used in an ISR.

Example usage:

struct AMessage { char ucMessageID; char ucData[ 20 ]; } xMessage; uint32_t ulVar = 10UL; void vATask( void *pvParameters ) { QueueHandle_t xQueue1, xQueue2; struct AMessage *pxMessage; // Create a queue capable of containing 10 uint32_t values. xQueue1 = xQueueCreate( 10, sizeof( uint32_t ) ); // Create a queue capable of containing 10 pointers to AMessage structures. // These should be passed by pointer as they contain a lot of data. xQueue2 = xQueueCreate( 10, sizeof( struct AMessage * ) ); // ... if( xQueue1 != 0 ) { // Send an uint32_t. Wait for 10 ticks for space to become // available if necessary. if( xQueueGenericSend( xQueue1, ( void * ) &ulVar, ( TickType_t ) 10, queueSEND_TO_BACK ) != pdPASS ) { // Failed to post the message, even after 10 ticks. } } if( xQueue2 != 0 ) { // Send a pointer to a struct AMessage object. Don't block if the // queue is already full. pxMessage = & xMessage; xQueueGenericSend( xQueue2, ( void * ) &pxMessage, ( TickType_t ) 0, queueSEND_TO_BACK ); } // ... Rest of task code. }

**Return**pdTRUE if the item was successfully posted, otherwise errQUEUE_FULL.

**Parameters**`xQueue`

: The handle to the queue on which the item is to be posted.`pvItemToQueue`

: A pointer to the item that is to be placed on the queue. The size of the items the queue will hold was defined when the queue was created, so this many bytes will be copied from pvItemToQueue into the queue storage area.`xTicksToWait`

: The maximum amount of time the task should block waiting for space to become available on the queue, should it already be full. The call will return immediately if this is set to 0 and the queue is full. The time is defined in tick periods so the constant portTICK_PERIOD_MS should be used to convert to real time if this is required.`xCopyPosition`

: Can take the value queueSEND_TO_BACK to place the item at the back of the queue, or queueSEND_TO_FRONT to place the item at the front of the queue (for high priority messages).

-
BaseType_t
`xQueuePeekFromISR`

([QueueHandle_t](https://docs.espressif.com#_CPPv413QueueHandle_t)*xQueue*, void **const**pvBuffer*)[Â¶](https://docs.espressif.com#_CPPv417xQueuePeekFromISR13QueueHandle_tPCv) A version of xQueuePeek() that can be called from an interrupt service routine (ISR).

Receive an item from a queue without removing the item from the queue. The item is received by copy so a buffer of adequate size must be provided. The number of bytes copied into the buffer was defined when the queue was created.

Successfully received items remain on the queue so will be returned again by the next call, or a call to xQueueReceive().

**Return**pdTRUE if an item was successfully received from the queue, otherwise pdFALSE.

**Parameters**`xQueue`

: The handle to the queue from which the item is to be received.`pvBuffer`

: Pointer to the buffer into which the received item will be copied.

-
BaseType_t
`xQueueGenericReceive`

([QueueHandle_t](https://docs.espressif.com#_CPPv413QueueHandle_t)*xQueue*, void **const**pvBuffer*, TickType_t*xTicksToWait*,*const*BaseType_t*xJustPeek*)[Â¶](https://docs.espressif.com#_CPPv420xQueueGenericReceive13QueueHandle_tPCv10TickType_tK10BaseType_t) It is preferred that the macro xQueueReceive() be used rather than calling this function directly.

Receive an item from a queue. The item is received by copy so a buffer of adequate size must be provided. The number of bytes copied into the buffer was defined when the queue was created.

This function must not be used in an interrupt service routine. See xQueueReceiveFromISR for an alternative that can.

Example usage:

struct AMessage { char ucMessageID; char ucData[ 20 ]; } xMessage; QueueHandle_t xQueue; // Task to create a queue and post a value. void vATask( void *pvParameters ) { struct AMessage *pxMessage; // Create a queue capable of containing 10 pointers to AMessage structures. // These should be passed by pointer as they contain a lot of data. xQueue = xQueueCreate( 10, sizeof( struct AMessage * ) ); if( xQueue == 0 ) { // Failed to create the queue. } // ... // Send a pointer to a struct AMessage object. Don't block if the // queue is already full. pxMessage = & xMessage; xQueueSend( xQueue, ( void * ) &pxMessage, ( TickType_t ) 0 ); // ... Rest of task code. } // Task to receive from the queue. void vADifferentTask( void *pvParameters ) { struct AMessage *pxRxedMessage; if( xQueue != 0 ) { // Receive a message on the created queue. Block for 10 ticks if a // message is not immediately available. if( xQueueGenericReceive( xQueue, &( pxRxedMessage ), ( TickType_t ) 10 ) ) { // pcRxedMessage now points to the struct AMessage variable posted // by vATask. } } // ... Rest of task code. }

**Return**pdTRUE if an item was successfully received from the queue, otherwise pdFALSE.

**Parameters**`xQueue`

: The handle to the queue from which the item is to be received.`pvBuffer`

: Pointer to the buffer into which the received item will be copied.`xTicksToWait`

: The maximum amount of time the task should block waiting for an item to receive should the queue be empty at the time of the call. The time is defined in tick periods so the constant portTICK_PERIOD_MS should be used to convert to real time if this is required. xQueueGenericReceive() will return immediately if the queue is empty and xTicksToWait is 0.`xJustPeek`

: When set to true, the item received from the queue is not actually removed from the queue - meaning a subsequent call to xQueueReceive() will return the same item. When set to false, the item being received from the queue is also removed from the queue.

-
UBaseType_t
`uxQueueMessagesWaiting`

(*const*[QueueHandle_t](https://docs.espressif.com#_CPPv413QueueHandle_t)*xQueue*)[Â¶](https://docs.espressif.com#_CPPv422uxQueueMessagesWaitingK13QueueHandle_t) Return the number of messages stored in a queue.

**Return**The number of messages available in the queue.

**Parameters**`xQueue`

: A handle to the queue being queried.

-
UBaseType_t
`uxQueueSpacesAvailable`

(*const*[QueueHandle_t](https://docs.espressif.com#_CPPv413QueueHandle_t)*xQueue*)[Â¶](https://docs.espressif.com#_CPPv422uxQueueSpacesAvailableK13QueueHandle_t) Return the number of free spaces available in a queue. This is equal to the number of items that can be sent to the queue before the queue becomes full if no items are removed.

**Return**The number of spaces available in the queue.

**Parameters**`xQueue`

: A handle to the queue being queried.

-
void
`vQueueDelete`

([QueueHandle_t](https://docs.espressif.com#_CPPv413QueueHandle_t)*xQueue*)[Â¶](https://docs.espressif.com#_CPPv412vQueueDelete13QueueHandle_t) Delete a queue - freeing all the memory allocated for storing of items placed on the queue.

**Parameters**`xQueue`

: A handle to the queue to be deleted.

-
BaseType_t
`xQueueReceiveFromISR`

([QueueHandle_t](https://docs.espressif.com#_CPPv413QueueHandle_t)*xQueue*, void **const**pvBuffer*, BaseType_t **const**pxHigherPriorityTaskWoken*)[Â¶](https://docs.espressif.com#_CPPv420xQueueReceiveFromISR13QueueHandle_tPCvPC10BaseType_t) Receive an item from a queue. It is safe to use this function from within an interrupt service routine.

Example usage:

QueueHandle_t xQueue; // Function to create a queue and post some values. void vAFunction( void *pvParameters ) { char cValueToPost; const TickType_t xTicksToWait = ( TickType_t )0xff; // Create a queue capable of containing 10 characters. xQueue = xQueueCreate( 10, sizeof( char ) ); if( xQueue == 0 ) { // Failed to create the queue. } // ... // Post some characters that will be used within an ISR. If the queue // is full then this task will block for xTicksToWait ticks. cValueToPost = 'a'; xQueueSend( xQueue, ( void * ) &cValueToPost, xTicksToWait ); cValueToPost = 'b'; xQueueSend( xQueue, ( void * ) &cValueToPost, xTicksToWait ); // ... keep posting characters ... this task may block when the queue // becomes full. cValueToPost = 'c'; xQueueSend( xQueue, ( void * ) &cValueToPost, xTicksToWait ); } // ISR that outputs all the characters received on the queue. void vISR_Routine( void ) { BaseType_t xTaskWokenByReceive = pdFALSE; char cRxedChar; while( xQueueReceiveFromISR( xQueue, ( void * ) &cRxedChar, &xTaskWokenByReceive) ) { // A character was received. Output the character now. vOutputCharacter( cRxedChar ); // If removing the character from the queue woke the task that was // posting onto the queue cTaskWokenByReceive will have been set to // pdTRUE. No matter how many times this loop iterates only one // task will be woken. } if( cTaskWokenByPost != ( char ) pdFALSE; { taskYIELD (); } }

**Return**pdTRUE if an item was successfully received from the queue, otherwise pdFALSE.

**Parameters**`xQueue`

: The handle to the queue from which the item is to be received.`pvBuffer`

: Pointer to the buffer into which the received item will be copied.`[out] pxHigherPriorityTaskWoken`

: A task may be blocked waiting for space to become available on the queue. If xQueueReceiveFromISR causes such a task to unblock *pxTaskWoken will get set to pdTRUE, otherwise *pxTaskWoken will remain unchanged.

-
void
`vQueueAddToRegistry`

([QueueHandle_t](https://docs.espressif.com#_CPPv413QueueHandle_t)*xQueue*,*const*char **pcName*)[Â¶](https://docs.espressif.com#_CPPv419vQueueAddToRegistry13QueueHandle_tPKc) The registry is provided as a means for kernel aware debuggers to locate queues, semaphores and mutexes. Call vQueueAddToRegistry() add a queue, semaphore or mutex handle to the registry if you want the handle to be available to a kernel aware debugger. If you are not using a kernel aware debugger then this function can be ignored.

configQUEUE_REGISTRY_SIZE defines the maximum number of handles the registry can hold. configQUEUE_REGISTRY_SIZE must be greater than 0 within FreeRTOSConfig.h for the registry to be available. Its value does not effect the number of queues, semaphores and mutexes that can be created - just the number that the registry can hold.

**Parameters**`xQueue`

: The handle of the queue being added to the registry. This is the handle returned by a call to xQueueCreate(). Semaphore and mutex handles can also be passed in here.`pcName`

: The name to be associated with the handle. This is the name that the kernel aware debugger will display. The queue registry only stores a pointer to the string - so the string must be persistent (global or preferably in ROM/Flash), not on the stack.

-
void
`vQueueUnregisterQueue`

([QueueHandle_t](https://docs.espressif.com#_CPPv413QueueHandle_t)*xQueue*)[Â¶](https://docs.espressif.com#_CPPv421vQueueUnregisterQueue13QueueHandle_t) The registry is provided as a means for kernel aware debuggers to locate queues, semaphores and mutexes. Call vQueueAddToRegistry() add a queue, semaphore or mutex handle to the registry if you want the handle to be available to a kernel aware debugger, and vQueueUnregisterQueue() to remove the queue, semaphore or mutex from the register. If you are not using a kernel aware debugger then this function can be ignored.

**Parameters**`xQueue`

: The handle of the queue being removed from the registry.

-
*const*char *`pcQueueGetName`

([QueueHandle_t](https://docs.espressif.com#_CPPv413QueueHandle_t)*xQueue*)[Â¶](https://docs.espressif.com#_CPPv414pcQueueGetName13QueueHandle_t) The queue registry is provided as a means for kernel aware debuggers to locate queues, semaphores and mutexes. Call pcQueueGetName() to look up and return the name of a queue in the queue registry from the queueâs handle.

**Note**This function has been back ported from FreeRTOS v9.0.0

**Return**If the queue is in the registry then a pointer to the name of the queue is returned. If the queue is not in the registry then NULL is returned.

**Parameters**`xQueue`

: The handle of the queue the name of which will be returned.

-
[QueueHandle_t](https://docs.espressif.com#_CPPv413QueueHandle_t)`xQueueGenericCreate`

(*const*UBaseType_t*uxQueueLength*,*const*UBaseType_t*uxItemSize*,*const*uint8_t*ucQueueType*)[Â¶](https://docs.espressif.com#_CPPv419xQueueGenericCreateK11UBaseType_tK11UBaseType_tK7uint8_t) Generic version of the function used to creaet a queue using dynamic memory allocation. This is called by other functions and macros that create other RTOS objects that use the queue structure as their base.

-
[QueueHandle_t](https://docs.espressif.com#_CPPv413QueueHandle_t)`xQueueGenericCreateStatic`

(*const*UBaseType_t*uxQueueLength*,*const*UBaseType_t*uxItemSize*, uint8_t **pucQueueStorage*, StaticQueue_t **pxStaticQueue*,*const*uint8_t*ucQueueType*)[Â¶](https://docs.espressif.com#_CPPv425xQueueGenericCreateStaticK11UBaseType_tK11UBaseType_tP7uint8_tP13StaticQueue_tK7uint8_t) Generic version of the function used to creaet a queue using dynamic memory allocation. This is called by other functions and macros that create other RTOS objects that use the queue structure as their base.

-
[QueueSetHandle_t](https://docs.espressif.com#_CPPv416QueueSetHandle_t)`xQueueCreateSet`

(*const*UBaseType_t*uxEventQueueLength*)[Â¶](https://docs.espressif.com#_CPPv415xQueueCreateSetK11UBaseType_t) Queue sets provide a mechanism to allow a task to block (pend) on a read operation from multiple queues or semaphores simultaneously.

See FreeRTOS/Source/Demo/Common/Minimal/QueueSet.c for an example using this function.

A queue set must be explicitly created using a call to xQueueCreateSet() before it can be used. Once created, standard FreeRTOS queues and semaphores can be added to the set using calls to xQueueAddToSet(). xQueueSelectFromSet() is then used to determine which, if any, of the queues or semaphores contained in the set is in a state where a queue read or semaphore take operation would be successful.

Note 1: See the documentation on

[http://wwwFreeRTOS.org/RTOS-queue-sets.html](http://wwwFreeRTOS.org/RTOS-queue-sets.html)for reasons why queue sets are very rarely needed in practice as there are simpler methods of blocking on multiple objects.Note 2: Blocking on a queue set that contains a mutex will not cause the mutex holder to inherit the priority of the blocked task.

Note 3: An additional 4 bytes of RAM is required for each space in a every queue added to a queue set. Therefore counting semaphores that have a high maximum count value should not be added to a queue set.

Note 4: A receive (in the case of a queue) or take (in the case of a semaphore) operation must not be performed on a member of a queue set unless a call to xQueueSelectFromSet() has first returned a handle to that set member.

**Return**If the queue set is created successfully then a handle to the created queue set is returned. Otherwise NULL is returned.

**Parameters**`uxEventQueueLength`

: Queue sets store events that occur on the queues and semaphores contained in the set. uxEventQueueLength specifies the maximum number of events that can be queued at once. To be absolutely certain that events are not lost uxEventQueueLength should be set to the total sum of the length of the queues added to the set, where binary semaphores and mutexes have a length of 1, and counting semaphores have a length set by their maximum count value. Examples:If a queue set is to hold a queue of length 5, another queue of length 12, and a binary semaphore, then uxEventQueueLength should be set to (5 + 12 + 1), or 18.

If a queue set is to hold three binary semaphores then uxEventQueueLength should be set to (1 + 1 + 1 ), or 3.

If a queue set is to hold a counting semaphore that has a maximum count of 5, and a counting semaphore that has a maximum count of 3, then uxEventQueueLength should be set to (5 + 3), or 8.

-
BaseType_t
`xQueueAddToSet`

([QueueSetMemberHandle_t](https://docs.espressif.com#_CPPv422QueueSetMemberHandle_t)*xQueueOrSemaphore*,[QueueSetHandle_t](https://docs.espressif.com#_CPPv416QueueSetHandle_t)*xQueueSet*)[Â¶](https://docs.espressif.com#_CPPv414xQueueAddToSet22QueueSetMemberHandle_t16QueueSetHandle_t) Adds a queue or semaphore to a queue set that was previously created by a call to xQueueCreateSet().

See FreeRTOS/Source/Demo/Common/Minimal/QueueSet.c for an example using this function.

Note 1: A receive (in the case of a queue) or take (in the case of a semaphore) operation must not be performed on a member of a queue set unless a call to xQueueSelectFromSet() has first returned a handle to that set member.

**Return**If the queue or semaphore was successfully added to the queue set then pdPASS is returned. If the queue could not be successfully added to the queue set because it is already a member of a different queue set then pdFAIL is returned.

**Parameters**`xQueueOrSemaphore`

: The handle of the queue or semaphore being added to the queue set (cast to an QueueSetMemberHandle_t type).`xQueueSet`

: The handle of the queue set to which the queue or semaphore is being added.

-
BaseType_t
`xQueueRemoveFromSet`

([QueueSetMemberHandle_t](https://docs.espressif.com#_CPPv422QueueSetMemberHandle_t)*xQueueOrSemaphore*,[QueueSetHandle_t](https://docs.espressif.com#_CPPv416QueueSetHandle_t)*xQueueSet*)[Â¶](https://docs.espressif.com#_CPPv419xQueueRemoveFromSet22QueueSetMemberHandle_t16QueueSetHandle_t) Removes a queue or semaphore from a queue set. A queue or semaphore can only be removed from a set if the queue or semaphore is empty.

See FreeRTOS/Source/Demo/Common/Minimal/QueueSet.c for an example using this function.

**Return**If the queue or semaphore was successfully removed from the queue set then pdPASS is returned. If the queue was not in the queue set, or the queue (or semaphore) was not empty, then pdFAIL is returned.

**Parameters**`xQueueOrSemaphore`

: The handle of the queue or semaphore being removed from the queue set (cast to an QueueSetMemberHandle_t type).`xQueueSet`

: The handle of the queue set in which the queue or semaphore is included.

-
[QueueSetMemberHandle_t](https://docs.espressif.com#_CPPv422QueueSetMemberHandle_t)`xQueueSelectFromSet`

([QueueSetHandle_t](https://docs.espressif.com#_CPPv416QueueSetHandle_t)*xQueueSet*,*const*TickType_t*xTicksToWait*)[Â¶](https://docs.espressif.com#_CPPv419xQueueSelectFromSet16QueueSetHandle_tK10TickType_t) xQueueSelectFromSet() selects from the members of a queue set a queue or semaphore that either contains data (in the case of a queue) or is available to take (in the case of a semaphore). xQueueSelectFromSet() effectively allows a task to block (pend) on a read operation on all the queues and semaphores in a queue set simultaneously.

See FreeRTOS/Source/Demo/Common/Minimal/QueueSet.c for an example using this function.

Note 1: See the documentation on

[http://wwwFreeRTOS.org/RTOS-queue-sets.html](http://wwwFreeRTOS.org/RTOS-queue-sets.html)for reasons why queue sets are very rarely needed in practice as there are simpler methods of blocking on multiple objects.Note 2: Blocking on a queue set that contains a mutex will not cause the mutex holder to inherit the priority of the blocked task.

Note 3: A receive (in the case of a queue) or take (in the case of a semaphore) operation must not be performed on a member of a queue set unless a call to xQueueSelectFromSet() has first returned a handle to that set member.

**Return**xQueueSelectFromSet() will return the handle of a queue (cast to a QueueSetMemberHandle_t type) contained in the queue set that contains data, or the handle of a semaphore (cast to a QueueSetMemberHandle_t type) contained in the queue set that is available, or NULL if no such queue or semaphore exists before before the specified block time expires.

**Parameters**`xQueueSet`

: The queue set on which the task will (potentially) block.`xTicksToWait`

: The maximum time, in ticks, that the calling task will remain in the Blocked state (with other tasks executing) to wait for a member of the queue set to be ready for a successful queue read or semaphore take operation.

-
[QueueSetMemberHandle_t](https://docs.espressif.com#_CPPv422QueueSetMemberHandle_t)`xQueueSelectFromSetFromISR`

([QueueSetHandle_t](https://docs.espressif.com#_CPPv416QueueSetHandle_t)*xQueueSet*)[Â¶](https://docs.espressif.com#_CPPv426xQueueSelectFromSetFromISR16QueueSetHandle_t) A version of xQueueSelectFromSet() that can be used from an ISR.

### Macros[Â¶](https://docs.espressif.com#id3)

-
`xQueueCreate`

(uxQueueLength, uxItemSize)[Â¶](https://docs.espressif.com#c.xQueueCreate) Creates a new queue instance. This allocates the storage required by the new queue and returns a handle for the queue.

Example usage:

struct AMessage { char ucMessageID; char ucData[ 20 ]; }; void vATask( void *pvParameters ) { QueueHandle_t xQueue1, xQueue2; // Create a queue capable of containing 10 uint32_t values. xQueue1 = xQueueCreate( 10, sizeof( uint32_t ) ); if( xQueue1 == 0 ) { // Queue was not created and must not be used. } // Create a queue capable of containing 10 pointers to AMessage structures. // These should be passed by pointer as they contain a lot of data. xQueue2 = xQueueCreate( 10, sizeof( struct AMessage * ) ); if( xQueue2 == 0 ) { // Queue was not created and must not be used. } // ... Rest of task code. }

**Return**If the queue is successfully create then a handle to the newly created queue is returned. If the queue cannot be created then 0 is returned.

**Parameters**`uxQueueLength`

: The maximum number of items that the queue can contain.`uxItemSize`

: The number of bytes each item in the queue will require. Items are queued by copy, not by reference, so this is the number of bytes that will be copied for each posted item. Each item on the queue must be the same size.

-
`xQueueCreateStatic`

(uxQueueLength, uxItemSize, pucQueueStorage, pxQueueBuffer)[Â¶](https://docs.espressif.com#c.xQueueCreateStatic) Creates a new queue instance, and returns a handle by which the new queue can be referenced.

Internally, within the FreeRTOS implementation, queues use two blocks of memory. The first block is used to hold the queueâs data structures. The second block is used to hold items placed into the queue. If a queue is created using xQueueCreate() then both blocks of memory are automatically dynamically allocated inside the xQueueCreate() function. (see

[http://www.freertos.org/a00111.html](http://www.freertos.org/a00111.html)). If a queue is created using xQueueCreateStatic() then the application writer must provide the memory that will get used by the queue. xQueueCreateStatic() therefore allows a queue to be created without using any dynamic memory allocation.[http://www.FreeRTOS.org/Embedded-RTOS-Queues.html](http://www.FreeRTOS.org/Embedded-RTOS-Queues.html)Example usage:

struct AMessage { char ucMessageID; char ucData[ 20 ]; }; #define QUEUE_LENGTH 10 #define ITEM_SIZE sizeof( uint32_t ) // xQueueBuffer will hold the queue structure. StaticQueue_t xQueueBuffer; // ucQueueStorage will hold the items posted to the queue. Must be at least // [(queue length) * ( queue item size)] bytes long. uint8_t ucQueueStorage[ QUEUE_LENGTH * ITEM_SIZE ]; void vATask( void *pvParameters ) { QueueHandle_t xQueue1; // Create a queue capable of containing 10 uint32_t values. xQueue1 = xQueueCreate( QUEUE_LENGTH, // The number of items the queue can hold. ITEM_SIZE // The size of each item in the queue &( ucQueueStorage[ 0 ] ), // The buffer that will hold the items in the queue. &xQueueBuffer ); // The buffer that will hold the queue structure. // The queue is guaranteed to be created successfully as no dynamic memory // allocation is used. Therefore xQueue1 is now a handle to a valid queue. // ... Rest of task code. }

**Return**If the queue is created then a handle to the created queue is returned. If pxQueueBuffer is NULL then NULL is returned.

**Parameters**`uxQueueLength`

: The maximum number of items that the queue can contain.`uxItemSize`

: The number of bytes each item in the queue will require. Items are queued by copy, not by reference, so this is the number of bytes that will be copied for each posted item. Each item on the queue must be the same size.`pucQueueStorage`

: If uxItemSize is not zero then pucQueueStorageBuffer must point to a uint8_t array that is at least large enough to hold the maximum number of items that can be in the queue at any one time - which is ( uxQueueLength * uxItemsSize ) bytes. If uxItemSize is zero then pucQueueStorageBuffer can be NULL.`pxQueueBuffer`

: Must point to a variable of type StaticQueue_t, which will be used to hold the queueâs data structure.

-
`xQueueSendToFront`

(xQueue, pvItemToQueue, xTicksToWait)[Â¶](https://docs.espressif.com#c.xQueueSendToFront) This is a macro that calls xQueueGenericSend().

Post an item to the front of a queue. The item is queued by copy, not by reference. This function must not be called from an interrupt service routine. See xQueueSendFromISR () for an alternative which may be used in an ISR.

Example usage:

struct AMessage { char ucMessageID; char ucData[ 20 ]; } xMessage; uint32_t ulVar = 10UL; void vATask( void *pvParameters ) { QueueHandle_t xQueue1, xQueue2; struct AMessage *pxMessage; // Create a queue capable of containing 10 uint32_t values. xQueue1 = xQueueCreate( 10, sizeof( uint32_t ) ); // Create a queue capable of containing 10 pointers to AMessage structures. // These should be passed by pointer as they contain a lot of data. xQueue2 = xQueueCreate( 10, sizeof( struct AMessage * ) ); // ... if( xQueue1 != 0 ) { // Send an uint32_t. Wait for 10 ticks for space to become // available if necessary. if( xQueueSendToFront( xQueue1, ( void * ) &ulVar, ( TickType_t ) 10 ) != pdPASS ) { // Failed to post the message, even after 10 ticks. } } if( xQueue2 != 0 ) { // Send a pointer to a struct AMessage object. Don't block if the // queue is already full. pxMessage = & xMessage; xQueueSendToFront( xQueue2, ( void * ) &pxMessage, ( TickType_t ) 0 ); } // ... Rest of task code. }

**Return**pdTRUE if the item was successfully posted, otherwise errQUEUE_FULL.

**Parameters**`xQueue`

: The handle to the queue on which the item is to be posted.`pvItemToQueue`

: A pointer to the item that is to be placed on the queue. The size of the items the queue will hold was defined when the queue was created, so this many bytes will be copied from pvItemToQueue into the queue storage area.`xTicksToWait`

: The maximum amount of time the task should block waiting for space to become available on the queue, should it already be full. The call will return immediately if this is set to 0 and the queue is full. The time is defined in tick periods so the constant portTICK_PERIOD_MS should be used to convert to real time if this is required.

-
`xQueueSendToBack`

(xQueue, pvItemToQueue, xTicksToWait)[Â¶](https://docs.espressif.com#c.xQueueSendToBack) This is a macro that calls xQueueGenericSend().

Post an item to the back of a queue. The item is queued by copy, not by reference. This function must not be called from an interrupt service routine. See xQueueSendFromISR () for an alternative which may be used in an ISR.

Example usage:

struct AMessage { char ucMessageID; char ucData[ 20 ]; } xMessage; uint32_t ulVar = 10UL; void vATask( void *pvParameters ) { QueueHandle_t xQueue1, xQueue2; struct AMessage *pxMessage; // Create a queue capable of containing 10 uint32_t values. xQueue1 = xQueueCreate( 10, sizeof( uint32_t ) ); // Create a queue capable of containing 10 pointers to AMessage structures. // These should be passed by pointer as they contain a lot of data. xQueue2 = xQueueCreate( 10, sizeof( struct AMessage * ) ); // ... if( xQueue1 != 0 ) { // Send an uint32_t. Wait for 10 ticks for space to become // available if necessary. if( xQueueSendToBack( xQueue1, ( void * ) &ulVar, ( TickType_t ) 10 ) != pdPASS ) { // Failed to post the message, even after 10 ticks. } } if( xQueue2 != 0 ) { // Send a pointer to a struct AMessage object. Don't block if the // queue is already full. pxMessage = & xMessage; xQueueSendToBack( xQueue2, ( void * ) &pxMessage, ( TickType_t ) 0 ); } // ... Rest of task code. }

**Return**pdTRUE if the item was successfully posted, otherwise errQUEUE_FULL.

**Parameters**`xQueue`

: The handle to the queue on which the item is to be posted.`pvItemToQueue`

: A pointer to the item that is to be placed on the queue. The size of the items the queue will hold was defined when the queue was created, so this many bytes will be copied from pvItemToQueue into the queue storage area.`xTicksToWait`

: The maximum amount of time the task should block waiting for space to become available on the queue, should it already be full. The call will return immediately if this is set to 0 and the queue is full. The time is defined in tick periods so the constant portTICK_PERIOD_MS should be used to convert to real time if this is required.

-
`xQueueSend`

(xQueue, pvItemToQueue, xTicksToWait)[Â¶](https://docs.espressif.com#c.xQueueSend) This is a macro that calls xQueueGenericSend(). It is included for backward compatibility with versions of FreeRTOS.org that did not include the xQueueSendToFront() and xQueueSendToBack() macros. It is equivalent to xQueueSendToBack().

Post an item on a queue. The item is queued by copy, not by reference. This function must not be called from an interrupt service routine. See xQueueSendFromISR () for an alternative which may be used in an ISR.

Example usage:

struct AMessage { char ucMessageID; char ucData[ 20 ]; } xMessage; uint32_t ulVar = 10UL; void vATask( void *pvParameters ) { QueueHandle_t xQueue1, xQueue2; struct AMessage *pxMessage; // Create a queue capable of containing 10 uint32_t values. xQueue1 = xQueueCreate( 10, sizeof( uint32_t ) ); // Create a queue capable of containing 10 pointers to AMessage structures. // These should be passed by pointer as they contain a lot of data. xQueue2 = xQueueCreate( 10, sizeof( struct AMessage * ) ); // ... if( xQueue1 != 0 ) { // Send an uint32_t. Wait for 10 ticks for space to become // available if necessary. if( xQueueSend( xQueue1, ( void * ) &ulVar, ( TickType_t ) 10 ) != pdPASS ) { // Failed to post the message, even after 10 ticks. } } if( xQueue2 != 0 ) { // Send a pointer to a struct AMessage object. Don't block if the // queue is already full. pxMessage = & xMessage; xQueueSend( xQueue2, ( void * ) &pxMessage, ( TickType_t ) 0 ); } // ... Rest of task code. }

**Return**pdTRUE if the item was successfully posted, otherwise errQUEUE_FULL.

**Parameters**`xQueue`

: The handle to the queue on which the item is to be posted.`pvItemToQueue`

: A pointer to the item that is to be placed on the queue. The size of the items the queue will hold was defined when the queue was created, so this many bytes will be copied from pvItemToQueue into the queue storage area.`xTicksToWait`

: The maximum amount of time the task should block waiting for space to become available on the queue, should it already be full. The call will return immediately if this is set to 0 and the queue is full. The time is defined in tick periods so the constant portTICK_PERIOD_MS should be used to convert to real time if this is required.

-
`xQueueOverwrite`

(xQueue, pvItemToQueue)[Â¶](https://docs.espressif.com#c.xQueueOverwrite) Only for use with queues that have a length of one - so the queue is either empty or full.

Post an item on a queue. If the queue is already full then overwrite the value held in the queue. The item is queued by copy, not by reference.

This function must not be called from an interrupt service routine. See xQueueOverwriteFromISR () for an alternative which may be used in an ISR.

Example usage:

void vFunction( void *pvParameters ) { QueueHandle_t xQueue; uint32_t ulVarToSend, ulValReceived; // Create a queue to hold one uint32_t value. It is strongly // recommended *not* to use xQueueOverwrite() on queues that can // contain more than one value, and doing so will trigger an assertion // if configASSERT() is defined. xQueue = xQueueCreate( 1, sizeof( uint32_t ) ); // Write the value 10 to the queue using xQueueOverwrite(). ulVarToSend = 10; xQueueOverwrite( xQueue, &ulVarToSend ); // Peeking the queue should now return 10, but leave the value 10 in // the queue. A block time of zero is used as it is known that the // queue holds a value. ulValReceived = 0; xQueuePeek( xQueue, &ulValReceived, 0 ); if( ulValReceived != 10 ) { // Error unless the item was removed by a different task. } // The queue is still full. Use xQueueOverwrite() to overwrite the // value held in the queue with 100. ulVarToSend = 100; xQueueOverwrite( xQueue, &ulVarToSend ); // This time read from the queue, leaving the queue empty once more. // A block time of 0 is used again. xQueueReceive( xQueue, &ulValReceived, 0 ); // The value read should be the last value written, even though the // queue was already full when the value was written. if( ulValReceived != 100 ) { // Error! } // ... }

**Return**xQueueOverwrite() is a macro that calls xQueueGenericSend(), and therefore has the same return values as xQueueSendToFront(). However, pdPASS is the only value that can be returned because xQueueOverwrite() will write to the queue even when the queue is already full.

**Parameters**`xQueue`

: The handle of the queue to which the data is being sent.`pvItemToQueue`

: A pointer to the item that is to be placed on the queue. The size of the items the queue will hold was defined when the queue was created, so this many bytes will be copied from pvItemToQueue into the queue storage area.

-
`xQueuePeek`

(xQueue, pvBuffer, xTicksToWait)[Â¶](https://docs.espressif.com#c.xQueuePeek) This is a macro that calls the xQueueGenericReceive() function.

Receive an item from a queue without removing the item from the queue. The item is received by copy so a buffer of adequate size must be provided. The number of bytes copied into the buffer was defined when the queue was created.

Successfully received items remain on the queue so will be returned again by the next call, or a call to xQueueReceive().

This macro must not be used in an interrupt service routine. See xQueuePeekFromISR() for an alternative that can be called from an interrupt service routine.

Example usage:

struct AMessage { char ucMessageID; char ucData[ 20 ]; } xMessage; QueueHandle_t xQueue; // Task to create a queue and post a value. void vATask( void *pvParameters ) { struct AMessage *pxMessage; // Create a queue capable of containing 10 pointers to AMessage structures. // These should be passed by pointer as they contain a lot of data. xQueue = xQueueCreate( 10, sizeof( struct AMessage * ) ); if( xQueue == 0 ) { // Failed to create the queue. } // ... // Send a pointer to a struct AMessage object. Don't block if the // queue is already full. pxMessage = & xMessage; xQueueSend( xQueue, ( void * ) &pxMessage, ( TickType_t ) 0 ); // ... Rest of task code. } // Task to peek the data from the queue. void vADifferentTask( void *pvParameters ) { struct AMessage *pxRxedMessage; if( xQueue != 0 ) { // Peek a message on the created queue. Block for 10 ticks if a // message is not immediately available. if( xQueuePeek( xQueue, &( pxRxedMessage ), ( TickType_t ) 10 ) ) { // pcRxedMessage now points to the struct AMessage variable posted // by vATask, but the item still remains on the queue. } } // ... Rest of task code. }

**Return**pdTRUE if an item was successfully received from the queue, otherwise pdFALSE.

**Parameters**`xQueue`

: The handle to the queue from which the item is to be received.`pvBuffer`

: Pointer to the buffer into which the received item will be copied.`xTicksToWait`

: The maximum amount of time the task should block waiting for an item to receive should the queue be empty at the time of the call. The time is defined in tick periods so the constant portTICK_PERIOD_MS should be used to convert to real time if this is required. xQueuePeek() will return immediately if xTicksToWait is 0 and the queue is empty.

-
`xQueueReceive`

(xQueue, pvBuffer, xTicksToWait)[Â¶](https://docs.espressif.com#c.xQueueReceive) queue. h

This is a macro that calls the xQueueGenericReceive() function.

Receive an item from a queue. The item is received by copy so a buffer of adequate size must be provided. The number of bytes copied into the buffer was defined when the queue was created.

Successfully received items are removed from the queue.

This function must not be used in an interrupt service routine. See xQueueReceiveFromISR for an alternative that can.

Example usage:

struct AMessage { char ucMessageID; char ucData[ 20 ]; } xMessage; QueueHandle_t xQueue; // Task to create a queue and post a value. void vATask( void *pvParameters ) { struct AMessage *pxMessage; // Create a queue capable of containing 10 pointers to AMessage structures. // These should be passed by pointer as they contain a lot of data. xQueue = xQueueCreate( 10, sizeof( struct AMessage * ) ); if( xQueue == 0 ) { // Failed to create the queue. } // ... // Send a pointer to a struct AMessage object. Don't block if the // queue is already full. pxMessage = & xMessage; xQueueSend( xQueue, ( void * ) &pxMessage, ( TickType_t ) 0 ); // ... Rest of task code. } // Task to receive from the queue. void vADifferentTask( void *pvParameters ) { struct AMessage *pxRxedMessage; if( xQueue != 0 ) { // Receive a message on the created queue. Block for 10 ticks if a // message is not immediately available. if( xQueueReceive( xQueue, &( pxRxedMessage ), ( TickType_t ) 10 ) ) { // pcRxedMessage now points to the struct AMessage variable posted // by vATask. } } // ... Rest of task code. }

**Return**pdTRUE if an item was successfully received from the queue, otherwise pdFALSE.

**Parameters**`xQueue`

: The handle to the queue from which the item is to be received.`pvBuffer`

: Pointer to the buffer into which the received item will be copied.`xTicksToWait`

: The maximum amount of time the task should block waiting for an item to receive should the queue be empty at the time of the call. xQueueReceive() will return immediately if xTicksToWait is zero and the queue is empty. The time is defined in tick periods so the constant portTICK_PERIOD_MS should be used to convert to real time if this is required.

-
`xQueueSendToFrontFromISR`

(xQueue, pvItemToQueue, pxHigherPriorityTaskWoken)[Â¶](https://docs.espressif.com#c.xQueueSendToFrontFromISR) This is a macro that calls xQueueGenericSendFromISR().

Post an item to the front of a queue. It is safe to use this macro from within an interrupt service routine.

Items are queued by copy not reference so it is preferable to only queue small items, especially when called from an ISR. In most cases it would be preferable to store a pointer to the item being queued.

Example usage for buffered IO (where the ISR can obtain more than one value per call):

void vBufferISR( void ) { char cIn; BaseType_t xHigherPrioritTaskWoken; // We have not woken a task at the start of the ISR. xHigherPriorityTaskWoken = pdFALSE; // Loop until the buffer is empty. do { // Obtain a byte from the buffer. cIn = portINPUT_BYTE( RX_REGISTER_ADDRESS ); // Post the byte. xQueueSendToFrontFromISR( xRxQueue, &cIn, &xHigherPriorityTaskWoken ); } while( portINPUT_BYTE( BUFFER_COUNT ) ); // Now the buffer is empty we can switch context if necessary. if( xHigherPriorityTaskWoken ) { portYIELD_FROM_ISR (); } }

**Return**pdTRUE if the data was successfully sent to the queue, otherwise errQUEUE_FULL.

**Parameters**`xQueue`

: The handle to the queue on which the item is to be posted.`pvItemToQueue`

: A pointer to the item that is to be placed on the queue. The size of the items the queue will hold was defined when the queue was created, so this many bytes will be copied from pvItemToQueue into the queue storage area.`[out] pxHigherPriorityTaskWoken`

: xQueueSendToFrontFromISR() will set *pxHigherPriorityTaskWoken to pdTRUE if sending to the queue caused a task to unblock, and the unblocked task has a priority higher than the currently running task. If xQueueSendToFromFromISR() sets this value to pdTRUE then a context switch should be requested before the interrupt is exited.

-
`xQueueSendToBackFromISR`

(xQueue, pvItemToQueue, pxHigherPriorityTaskWoken)[Â¶](https://docs.espressif.com#c.xQueueSendToBackFromISR) This is a macro that calls xQueueGenericSendFromISR().

Post an item to the back of a queue. It is safe to use this macro from within an interrupt service routine.

Items are queued by copy not reference so it is preferable to only queue small items, especially when called from an ISR. In most cases it would be preferable to store a pointer to the item being queued.

Example usage for buffered IO (where the ISR can obtain more than one value per call):

void vBufferISR( void ) { char cIn; BaseType_t xHigherPriorityTaskWoken; // We have not woken a task at the start of the ISR. xHigherPriorityTaskWoken = pdFALSE; // Loop until the buffer is empty. do { // Obtain a byte from the buffer. cIn = portINPUT_BYTE( RX_REGISTER_ADDRESS ); // Post the byte. xQueueSendToBackFromISR( xRxQueue, &cIn, &xHigherPriorityTaskWoken ); } while( portINPUT_BYTE( BUFFER_COUNT ) ); // Now the buffer is empty we can switch context if necessary. if( xHigherPriorityTaskWoken ) { portYIELD_FROM_ISR (); } }

**Return**pdTRUE if the data was successfully sent to the queue, otherwise errQUEUE_FULL.

**Parameters**`xQueue`

: The handle to the queue on which the item is to be posted.`pvItemToQueue`

: A pointer to the item that is to be placed on the queue. The size of the items the queue will hold was defined when the queue was created, so this many bytes will be copied from pvItemToQueue into the queue storage area.`[out] pxHigherPriorityTaskWoken`

: xQueueSendToBackFromISR() will set *pxHigherPriorityTaskWoken to pdTRUE if sending to the queue caused a task to unblock, and the unblocked task has a priority higher than the currently running task. If xQueueSendToBackFromISR() sets this value to pdTRUE then a context switch should be requested before the interrupt is exited.

-
`xQueueOverwriteFromISR`

(xQueue, pvItemToQueue, pxHigherPriorityTaskWoken)[Â¶](https://docs.espressif.com#c.xQueueOverwriteFromISR) A version of xQueueOverwrite() that can be used in an interrupt service routine (ISR).

Only for use with queues that can hold a single item - so the queue is either empty or full.

Post an item on a queue. If the queue is already full then overwrite the value held in the queue. The item is queued by copy, not by reference.

Example usage:

QueueHandle_t xQueue; void vFunction( void *pvParameters ) { // Create a queue to hold one uint32_t value. It is strongly // recommended *not* to use xQueueOverwriteFromISR() on queues that can // contain more than one value, and doing so will trigger an assertion // if configASSERT() is defined. xQueue = xQueueCreate( 1, sizeof( uint32_t ) ); } void vAnInterruptHandler( void ) { // xHigherPriorityTaskWoken must be set to pdFALSE before it is used. BaseType_t xHigherPriorityTaskWoken = pdFALSE; uint32_t ulVarToSend, ulValReceived; // Write the value 10 to the queue using xQueueOverwriteFromISR(). ulVarToSend = 10; xQueueOverwriteFromISR( xQueue, &ulVarToSend, &xHigherPriorityTaskWoken ); // The queue is full, but calling xQueueOverwriteFromISR() again will still // pass because the value held in the queue will be overwritten with the // new value. ulVarToSend = 100; xQueueOverwriteFromISR( xQueue, &ulVarToSend, &xHigherPriorityTaskWoken ); // Reading from the queue will now return 100. // ... if( xHigherPrioritytaskWoken == pdTRUE ) { // Writing to the queue caused a task to unblock and the unblocked task // has a priority higher than or equal to the priority of the currently // executing task (the task this interrupt interrupted). Perform a context // switch so this interrupt returns directly to the unblocked task. portYIELD_FROM_ISR(); // or portEND_SWITCHING_ISR() depending on the port. } }

**Return**xQueueOverwriteFromISR() is a macro that calls xQueueGenericSendFromISR(), and therefore has the same return values as xQueueSendToFrontFromISR(). However, pdPASS is the only value that can be returned because xQueueOverwriteFromISR() will write to the queue even when the queue is already full.

**Parameters**`xQueue`

: The handle to the queue on which the item is to be posted.`pvItemToQueue`

: A pointer to the item that is to be placed on the queue. The size of the items the queue will hold was defined when the queue was created, so this many bytes will be copied from pvItemToQueue into the queue storage area.`[out] pxHigherPriorityTaskWoken`

: xQueueOverwriteFromISR() will set *pxHigherPriorityTaskWoken to pdTRUE if sending to the queue caused a task to unblock, and the unblocked task has a priority higher than the currently running task. If xQueueOverwriteFromISR() sets this value to pdTRUE then a context switch should be requested before the interrupt is exited.

-
`xQueueSendFromISR`

(xQueue, pvItemToQueue, pxHigherPriorityTaskWoken)[Â¶](https://docs.espressif.com#c.xQueueSendFromISR) This is a macro that calls xQueueGenericSendFromISR(). It is included for backward compatibility with versions of FreeRTOS.org that did not include the xQueueSendToBackFromISR() and xQueueSendToFrontFromISR() macros.

Post an item to the back of a queue. It is safe to use this function from within an interrupt service routine.

Items are queued by copy not reference so it is preferable to only queue small items, especially when called from an ISR. In most cases it would be preferable to store a pointer to the item being queued.

Example usage for buffered IO (where the ISR can obtain more than one value per call):

void vBufferISR( void ) { char cIn; BaseType_t xHigherPriorityTaskWoken; // We have not woken a task at the start of the ISR. xHigherPriorityTaskWoken = pdFALSE; // Loop until the buffer is empty. do { // Obtain a byte from the buffer. cIn = portINPUT_BYTE( RX_REGISTER_ADDRESS ); // Post the byte. xQueueSendFromISR( xRxQueue, &cIn, &xHigherPriorityTaskWoken ); } while( portINPUT_BYTE( BUFFER_COUNT ) ); // Now the buffer is empty we can switch context if necessary. if( xHigherPriorityTaskWoken ) { // Actual macro used here is port specific. portYIELD_FROM_ISR (); } }

**Return**pdTRUE if the data was successfully sent to the queue, otherwise errQUEUE_FULL.

**Parameters**`xQueue`

: The handle to the queue on which the item is to be posted.`pvItemToQueue`

: A pointer to the item that is to be placed on the queue. The size of the items the queue will hold was defined when the queue was created, so this many bytes will be copied from pvItemToQueue into the queue storage area.`[out] pxHigherPriorityTaskWoken`

: xQueueSendFromISR() will set *pxHigherPriorityTaskWoken to pdTRUE if sending to the queue caused a task to unblock, and the unblocked task has a priority higher than the currently running task. If xQueueSendFromISR() sets this value to pdTRUE then a context switch should be requested before the interrupt is exited.

-
`xQueueReset`

(xQueue)[Â¶](https://docs.espressif.com#c.xQueueReset) Reset a queue back to its original empty state. pdPASS is returned if the queue is successfully reset. pdFAIL is returned if the queue could not be reset because there are tasks blocked on the queue waiting to either receive from the queue or send to the queue.

**Return**always returns pdPASS

**Parameters**`xQueue`

: The queue to reset

### Type Definitions[Â¶](https://docs.espressif.com#id4)

-
*typedef*void *`QueueHandle_t`

[Â¶](https://docs.espressif.com#_CPPv413QueueHandle_t) Type by which queues are referenced. For example, a call to xQueueCreate() returns an QueueHandle_t variable that can then be used as a parameter to xQueueSend(), xQueueReceive(), etc.

-
*typedef*void *`QueueSetHandle_t`

[Â¶](https://docs.espressif.com#_CPPv416QueueSetHandle_t) Type by which queue sets are referenced. For example, a call to xQueueCreateSet() returns an xQueueSet variable that can then be used as a parameter to xQueueSelectFromSet(), xQueueAddToSet(), etc.

-
*typedef*void *`QueueSetMemberHandle_t`

[Â¶](https://docs.espressif.com#_CPPv422QueueSetMemberHandle_t) Queue sets can contain both queues and semaphores, so the QueueSetMemberHandle_t is defined as a type to be used where a parameter or return value can be either an QueueHandle_t or an SemaphoreHandle_t.

## Semaphore API[Â¶](https://docs.espressif.com#semaphore-api)

### Header File[Â¶](https://docs.espressif.com#id5)

### Macros[Â¶](https://docs.espressif.com#id6)

-
`semBINARY_SEMAPHORE_QUEUE_LENGTH`

[Â¶](https://docs.espressif.com#c.semBINARY_SEMAPHORE_QUEUE_LENGTH)

-
`semSEMAPHORE_QUEUE_ITEM_LENGTH`

[Â¶](https://docs.espressif.com#c.semSEMAPHORE_QUEUE_ITEM_LENGTH)

-
`semGIVE_BLOCK_TIME`

[Â¶](https://docs.espressif.com#c.semGIVE_BLOCK_TIME)

-
`xSemaphoreCreateBinary`

()[Â¶](https://docs.espressif.com#c.xSemaphoreCreateBinary) Creates a new binary semaphore instance, and returns a handle by which the new semaphore can be referenced.

In many usage scenarios it is faster and more memory efficient to use a direct to task notification in place of a binary semaphore!

[http://www.freertos.org/RTOS-task-notifications.html](http://www.freertos.org/RTOS-task-notifications.html)Internally, within the FreeRTOS implementation, binary semaphores use a block of memory, in which the semaphore structure is stored. If a binary semaphore is created using xSemaphoreCreateBinary() then the required memory is automatically dynamically allocated inside the xSemaphoreCreateBinary() function. (see

[http://www.freertos.org/a00111.html](http://www.freertos.org/a00111.html)). If a binary semaphore is created using xSemaphoreCreateBinaryStatic() then the application writer must provide the memory. xSemaphoreCreateBinaryStatic() therefore allows a binary semaphore to be created without using any dynamic memory allocation.The old vSemaphoreCreateBinary() macro is now deprecated in favour of this xSemaphoreCreateBinary() function. Note that binary semaphores created using the vSemaphoreCreateBinary() macro are created in a state such that the first call to âtakeâ the semaphore would pass, whereas binary semaphores created using xSemaphoreCreateBinary() are created in a state such that the the semaphore must first be âgivenâ before it can be âtakenâ.

Function that creates a semaphore by using the existing queue mechanism. The queue length is 1 as this is a binary semaphore. The data size is 0 as nothing is actually stored - all that is important is whether the queue is empty or full (the binary semaphore is available or not).

This type of semaphore can be used for pure synchronisation between tasks or between an interrupt and a task. The semaphore need not be given back once obtained, so one task/interrupt can continuously âgiveâ the semaphore while another continuously âtakesâ the semaphore. For this reason this type of semaphore does not use a priority inheritance mechanism. For an alternative that does use priority inheritance see xSemaphoreCreateMutex().

Example usage:

SemaphoreHandle_t xSemaphore = NULL; void vATask( void * pvParameters ) { // Semaphore cannot be used before a call to vSemaphoreCreateBinary (). // This is a macro so pass the variable in directly. xSemaphore = xSemaphoreCreateBinary(); if( xSemaphore != NULL ) { // The semaphore was created successfully. // The semaphore can now be used. } }

**Return**Handle to the created semaphore.

-
`xSemaphoreCreateBinaryStatic`

(pxStaticSemaphore)[Â¶](https://docs.espressif.com#c.xSemaphoreCreateBinaryStatic) Creates a new binary semaphore instance, and returns a handle by which the new semaphore can be referenced.

NOTE: In many usage scenarios it is faster and more memory efficient to use a direct to task notification in place of a binary semaphore!

[http://www.freertos.org/RTOS-task-notifications.html](http://www.freertos.org/RTOS-task-notifications.html)Internally, within the FreeRTOS implementation, binary semaphores use a block of memory, in which the semaphore structure is stored. If a binary semaphore is created using xSemaphoreCreateBinary() then the required memory is automatically dynamically allocated inside the xSemaphoreCreateBinary() function. (see

[http://www.freertos.org/a00111.html](http://www.freertos.org/a00111.html)). If a binary semaphore is created using xSemaphoreCreateBinaryStatic() then the application writer must provide the memory. xSemaphoreCreateBinaryStatic() therefore allows a binary semaphore to be created without using any dynamic memory allocation.This type of semaphore can be used for pure synchronisation between tasks or between an interrupt and a task. The semaphore need not be given back once obtained, so one task/interrupt can continuously âgiveâ the semaphore while another continuously âtakesâ the semaphore. For this reason this type of semaphore does not use a priority inheritance mechanism. For an alternative that does use priority inheritance see xSemaphoreCreateMutex().

Example usage:

SemaphoreHandle_t xSemaphore = NULL; StaticSemaphore_t xSemaphoreBuffer; void vATask( void * pvParameters ) { // Semaphore cannot be used before a call to xSemaphoreCreateBinary() or // xSemaphoreCreateBinaryStatic(). // The semaphore's data structures will be placed in the xSemaphoreBuffer // variable, the address of which is passed into the function. The // function's parameter is not NULL, so the function will not attempt any // dynamic memory allocation, and therefore the function will not return // return NULL. xSemaphore = xSemaphoreCreateBinaryStatic( &xSemaphoreBuffer ); // Rest of task code goes here. }

**Return**If the semaphore is created then a handle to the created semaphore is returned. If pxSemaphoreBuffer is NULL then NULL is returned.

**Parameters**`pxStaticSemaphore`

: Must point to a variable of type StaticSemaphore_t, which will then be used to hold the semaphoreâs data structure, removing the need for the memory to be allocated dynamically.

-
`xSemaphoreTake`

(xSemaphore, xBlockTime)[Â¶](https://docs.espressif.com#c.xSemaphoreTake) *Macro*to obtain a semaphore. The semaphore must have previously been created with a call to vSemaphoreCreateBinary(), xSemaphoreCreateMutex() or xSemaphoreCreateCounting().Example usage:

SemaphoreHandle_t xSemaphore = NULL; // A task that creates a semaphore. void vATask( void * pvParameters ) { // Create the semaphore to guard a shared resource. vSemaphoreCreateBinary( xSemaphore ); } // A task that uses the semaphore. void vAnotherTask( void * pvParameters ) { // ... Do other things. if( xSemaphore != NULL ) { // See if we can obtain the semaphore. If the semaphore is not available // wait 10 ticks to see if it becomes free. if( xSemaphoreTake( xSemaphore, ( TickType_t ) 10 ) == pdTRUE ) { // We were able to obtain the semaphore and can now access the // shared resource. // ... // We have finished accessing the shared resource. Release the // semaphore. xSemaphoreGive( xSemaphore ); } else { // We could not obtain the semaphore and can therefore not access // the shared resource safely. } } }

**Return**pdTRUE if the semaphore was obtained. pdFALSE if xBlockTime expired without the semaphore becoming available.

**Parameters**`xSemaphore`

: A handle to the semaphore being taken - obtained when the semaphore was created.`xBlockTime`

: The time in ticks to wait for the semaphore to become available. The macro portTICK_PERIOD_MS can be used to convert this to a real time. A block time of zero can be used to poll the semaphore. A block time of portMAX_DELAY can be used to block indefinitely (provided INCLUDE_vTaskSuspend is set to 1 in FreeRTOSConfig.h).

-
`xSemaphoreTakeRecursive`

(xMutex, xBlockTime)[Â¶](https://docs.espressif.com#c.xSemaphoreTakeRecursive) *Macro*to recursively obtain, or âtakeâ, a mutex type semaphore. The mutex must have previously been created using a call to xSemaphoreCreateRecursiveMutex();configUSE_RECURSIVE_MUTEXES must be set to 1 in FreeRTOSConfig.h for this macro to be available.

This macro must not be used on mutexes created using xSemaphoreCreateMutex().

A mutex used recursively can be âtakenâ repeatedly by the owner. The mutex doesnât become available again until the owner has called xSemaphoreGiveRecursive() for each successful âtakeâ request. For example, if a task successfully âtakesâ the same mutex 5 times then the mutex will not be available to any other task until it has also âgivenâ the mutex back exactly five times.

Example usage:

SemaphoreHandle_t xMutex = NULL; // A task that creates a mutex. void vATask( void * pvParameters ) { // Create the mutex to guard a shared resource. xMutex = xSemaphoreCreateRecursiveMutex(); } // A task that uses the mutex. void vAnotherTask( void * pvParameters ) { // ... Do other things. if( xMutex != NULL ) { // See if we can obtain the mutex. If the mutex is not available // wait 10 ticks to see if it becomes free. if( xSemaphoreTakeRecursive( xSemaphore, ( TickType_t ) 10 ) == pdTRUE ) { // We were able to obtain the mutex and can now access the // shared resource. // ... // For some reason due to the nature of the code further calls to // xSemaphoreTakeRecursive() are made on the same mutex. In real // code these would not be just sequential calls as this would make // no sense. Instead the calls are likely to be buried inside // a more complex call structure. xSemaphoreTakeRecursive( xMutex, ( TickType_t ) 10 ); xSemaphoreTakeRecursive( xMutex, ( TickType_t ) 10 ); // The mutex has now been 'taken' three times, so will not be // available to another task until it has also been given back // three times. Again it is unlikely that real code would have // these calls sequentially, but instead buried in a more complex // call structure. This is just for illustrative purposes. xSemaphoreGiveRecursive( xMutex ); xSemaphoreGiveRecursive( xMutex ); xSemaphoreGiveRecursive( xMutex ); // Now the mutex can be taken by other tasks. } else { // We could not obtain the mutex and can therefore not access // the shared resource safely. } } }

**Return**pdTRUE if the semaphore was obtained. pdFALSE if xBlockTime expired without the semaphore becoming available.

**Parameters**`xMutex`

: A handle to the mutex being obtained. This is the handle returned by xSemaphoreCreateRecursiveMutex();`xBlockTime`

: The time in ticks to wait for the semaphore to become available. The macro portTICK_PERIOD_MS can be used to convert this to a real time. A block time of zero can be used to poll the semaphore. If the task already owns the semaphore then xSemaphoreTakeRecursive() will return immediately no matter what the value of xBlockTime.

-
`xSemaphoreGive`

(xSemaphore)[Â¶](https://docs.espressif.com#c.xSemaphoreGive) *Macro*to release a semaphore. The semaphore must have previously been created with a call to vSemaphoreCreateBinary(), xSemaphoreCreateMutex() or xSemaphoreCreateCounting(). and obtained using sSemaphoreTake().This macro must not be used from an ISR. See xSemaphoreGiveFromISR () for an alternative which can be used from an ISR.

This macro must also not be used on semaphores created using xSemaphoreCreateRecursiveMutex().

Example usage:

SemaphoreHandle_t xSemaphore = NULL; void vATask( void * pvParameters ) { // Create the semaphore to guard a shared resource. vSemaphoreCreateBinary( xSemaphore ); if( xSemaphore != NULL ) { if( xSemaphoreGive( xSemaphore ) != pdTRUE ) { // We would expect this call to fail because we cannot give // a semaphore without first "taking" it! } // Obtain the semaphore - don't block if the semaphore is not // immediately available. if( xSemaphoreTake( xSemaphore, ( TickType_t ) 0 ) ) { // We now have the semaphore and can access the shared resource. // ... // We have finished accessing the shared resource so can free the // semaphore. if( xSemaphoreGive( xSemaphore ) != pdTRUE ) { // We would not expect this call to fail because we must have // obtained the semaphore to get here. } } } }

**Return**pdTRUE if the semaphore was released. pdFALSE if an error occurred. Semaphores are implemented using queues. An error can occur if there is no space on the queue to post a message - indicating that the semaphore was not first obtained correctly.

**Parameters**`xSemaphore`

: A handle to the semaphore being released. This is the handle returned when the semaphore was created.

-
`xSemaphoreGiveRecursive`

(xMutex)[Â¶](https://docs.espressif.com#c.xSemaphoreGiveRecursive) *Macro*to recursively release, or âgiveâ, a mutex type semaphore. The mutex must have previously been created using a call to xSemaphoreCreateRecursiveMutex();configUSE_RECURSIVE_MUTEXES must be set to 1 in FreeRTOSConfig.h for this macro to be available.

This macro must not be used on mutexes created using xSemaphoreCreateMutex().

A mutex used recursively can be âtakenâ repeatedly by the owner. The mutex doesnât become available again until the owner has called xSemaphoreGiveRecursive() for each successful âtakeâ request. For example, if a task successfully âtakesâ the same mutex 5 times then the mutex will not be available to any other task until it has also âgivenâ the mutex back exactly five times.

Example usage:

SemaphoreHandle_t xMutex = NULL; // A task that creates a mutex. void vATask( void * pvParameters ) { // Create the mutex to guard a shared resource. xMutex = xSemaphoreCreateRecursiveMutex(); } // A task that uses the mutex. void vAnotherTask( void * pvParameters ) { // ... Do other things. if( xMutex != NULL ) { // See if we can obtain the mutex. If the mutex is not available // wait 10 ticks to see if it becomes free. if( xSemaphoreTakeRecursive( xMutex, ( TickType_t ) 10 ) == pdTRUE ) { // We were able to obtain the mutex and can now access the // shared resource. // ... // For some reason due to the nature of the code further calls to // xSemaphoreTakeRecursive() are made on the same mutex. In real // code these would not be just sequential calls as this would make // no sense. Instead the calls are likely to be buried inside // a more complex call structure. xSemaphoreTakeRecursive( xMutex, ( TickType_t ) 10 ); xSemaphoreTakeRecursive( xMutex, ( TickType_t ) 10 ); // The mutex has now been 'taken' three times, so will not be // available to another task until it has also been given back // three times. Again it is unlikely that real code would have // these calls sequentially, it would be more likely that the calls // to xSemaphoreGiveRecursive() would be called as a call stack // unwound. This is just for demonstrative purposes. xSemaphoreGiveRecursive( xMutex ); xSemaphoreGiveRecursive( xMutex ); xSemaphoreGiveRecursive( xMutex ); // Now the mutex can be taken by other tasks. } else { // We could not obtain the mutex and can therefore not access // the shared resource safely. } } }

**Return**pdTRUE if the semaphore was given.

**Parameters**`xMutex`

: A handle to the mutex being released, or âgivenâ. This is the handle returned by xSemaphoreCreateMutex();

-
`xSemaphoreGiveFromISR`

(xSemaphore, pxHigherPriorityTaskWoken)[Â¶](https://docs.espressif.com#c.xSemaphoreGiveFromISR) *Macro*to release a semaphore. The semaphore must have previously been created with a call to vSemaphoreCreateBinary() or xSemaphoreCreateCounting().Mutex type semaphores (those created using a call to xSemaphoreCreateMutex()) must not be used with this macro.

This macro can be used from an ISR.

Example usage:

\#define LONG_TIME 0xffff \#define TICKS_TO_WAIT 10 SemaphoreHandle_t xSemaphore = NULL; // Repetitive task. void vATask( void * pvParameters ) { for( ;; ) { // We want this task to run every 10 ticks of a timer. The semaphore // was created before this task was started. // Block waiting for the semaphore to become available. if( xSemaphoreTake( xSemaphore, LONG_TIME ) == pdTRUE ) { // It is time to execute. // ... // We have finished our task. Return to the top of the loop where // we will block on the semaphore until it is time to execute // again. Note when using the semaphore for synchronisation with an // ISR in this manner there is no need to 'give' the semaphore back. } } } // Timer ISR void vTimerISR( void * pvParameters ) { static uint8_t ucLocalTickCount = 0; static BaseType_t xHigherPriorityTaskWoken; // A timer tick has occurred. // ... Do other time functions. // Is it time for vATask () to run? xHigherPriorityTaskWoken = pdFALSE; ucLocalTickCount++; if( ucLocalTickCount >= TICKS_TO_WAIT ) { // Unblock the task by releasing the semaphore. xSemaphoreGiveFromISR( xSemaphore, &xHigherPriorityTaskWoken ); // Reset the count so we release the semaphore again in 10 ticks time. ucLocalTickCount = 0; } if( xHigherPriorityTaskWoken != pdFALSE ) { // We can force a context switch here. Context switching from an // ISR uses port specific syntax. Check the demo task for your port // to find the syntax required. } }

**Return**pdTRUE if the semaphore was successfully given, otherwise errQUEUE_FULL.

**Parameters**`xSemaphore`

: A handle to the semaphore being released. This is the handle returned when the semaphore was created.`[out] pxHigherPriorityTaskWoken`

: xSemaphoreGiveFromISR() will set *pxHigherPriorityTaskWoken to pdTRUE if giving the semaphore caused a task to unblock, and the unblocked task has a priority higher than the currently running task. If xSemaphoreGiveFromISR() sets this value to pdTRUE then a context switch should be requested before the interrupt is exited.

-
`xSemaphoreTakeFromISR`

(xSemaphore, pxHigherPriorityTaskWoken)[Â¶](https://docs.espressif.com#c.xSemaphoreTakeFromISR) *Macro*to take a semaphore from an ISR. The semaphore must have previously been created with a call to vSemaphoreCreateBinary() or xSemaphoreCreateCounting().Mutex type semaphores (those created using a call to xSemaphoreCreateMutex()) must not be used with this macro.

This macro can be used from an ISR, however taking a semaphore from an ISR is not a common operation. It is likely to only be useful when taking a counting semaphore when an interrupt is obtaining an object from a resource pool (when the semaphore count indicates the number of resources available).

**Return**pdTRUE if the semaphore was successfully taken, otherwise pdFALSE

**Parameters**`xSemaphore`

: A handle to the semaphore being taken. This is the handle returned when the semaphore was created.`[out] pxHigherPriorityTaskWoken`

: xSemaphoreTakeFromISR() will set *pxHigherPriorityTaskWoken to pdTRUE if taking the semaphore caused a task to unblock, and the unblocked task has a priority higher than the currently running task. If xSemaphoreTakeFromISR() sets this value to pdTRUE then a context switch should be requested before the interrupt is exited.

-
`xSemaphoreCreateMutex`

()[Â¶](https://docs.espressif.com#c.xSemaphoreCreateMutex) *Macro*that implements a mutex semaphore by using the existing queue mechanism.Internally, within the FreeRTOS implementation, mutex semaphores use a block of memory, in which the mutex structure is stored. If a mutex is created using xSemaphoreCreateMutex() then the required memory is automatically dynamically allocated inside the xSemaphoreCreateMutex() function. (see

[http://www.freertos.org/a00111.html](http://www.freertos.org/a00111.html)). If a mutex is created using xSemaphoreCreateMutexStatic() then the application writer must provided the memory. xSemaphoreCreateMutexStatic() therefore allows a mutex to be created without using any dynamic memory allocation.Mutexes created using this function can be accessed using the xSemaphoreTake() and xSemaphoreGive() macros. The xSemaphoreTakeRecursive() and xSemaphoreGiveRecursive() macros must not be used.

This type of semaphore uses a priority inheritance mechanism so a task âtakingâ a semaphore MUST ALWAYS âgiveâ the semaphore back once the semaphore it is no longer required.

Mutex type semaphores cannot be used from within interrupt service routines.

See vSemaphoreCreateBinary() for an alternative implementation that can be used for pure synchronisation (where one task or interrupt always âgivesâ the semaphore and another always âtakesâ the semaphore) and from within interrupt service routines.

Example usage:

SemaphoreHandle_t xSemaphore; void vATask( void * pvParameters ) { // Semaphore cannot be used before a call to xSemaphoreCreateMutex(). // This is a macro so pass the variable in directly. xSemaphore = xSemaphoreCreateMutex(); if( xSemaphore != NULL ) { // The semaphore was created successfully. // The semaphore can now be used. } }

**Return**If the mutex was successfully created then a handle to the created semaphore is returned. If there was not enough heap to allocate the mutex data structures then NULL is returned.

-
`xSemaphoreCreateMutexStatic`

(pxMutexBuffer)[Â¶](https://docs.espressif.com#c.xSemaphoreCreateMutexStatic) Creates a new mutex type semaphore instance, and returns a handle by which the new mutex can be referenced.

Internally, within the FreeRTOS implementation, mutex semaphores use a block of memory, in which the mutex structure is stored. If a mutex is created using xSemaphoreCreateMutex() then the required memory is automatically dynamically allocated inside the xSemaphoreCreateMutex() function. (see

[http://www.freertos.org/a00111.html](http://www.freertos.org/a00111.html)). If a mutex is created using xSemaphoreCreateMutexStatic() then the application writer must provided the memory. xSemaphoreCreateMutexStatic() therefore allows a mutex to be created without using any dynamic memory allocation.Mutexes created using this function can be accessed using the xSemaphoreTake() and xSemaphoreGive() macros. The xSemaphoreTakeRecursive() and xSemaphoreGiveRecursive() macros must not be used.

This type of semaphore uses a priority inheritance mechanism so a task âtakingâ a semaphore MUST ALWAYS âgiveâ the semaphore back once the semaphore it is no longer required.

Mutex type semaphores cannot be used from within interrupt service routines.

See xSemaphoreCreateBinary() for an alternative implementation that can be used for pure synchronisation (where one task or interrupt always âgivesâ the semaphore and another always âtakesâ the semaphore) and from within interrupt service routines.

Example usage:

SemaphoreHandle_t xSemaphore; StaticSemaphore_t xMutexBuffer; void vATask( void * pvParameters ) { // A mutex cannot be used before it has been created. xMutexBuffer is // into xSemaphoreCreateMutexStatic() so no dynamic memory allocation is // attempted. xSemaphore = xSemaphoreCreateMutexStatic( &xMutexBuffer ); // As no dynamic memory allocation was performed, xSemaphore cannot be NULL, // so there is no need to check it. }

**Return**If the mutex was successfully created then a handle to the created mutex is returned. If pxMutexBuffer was NULL then NULL is returned.

**Parameters**`pxMutexBuffer`

: Must point to a variable of type StaticSemaphore_t, which will be used to hold the mutexâs data structure, removing the need for the memory to be allocated dynamically.

-
`xSemaphoreCreateRecursiveMutex`

()[Â¶](https://docs.espressif.com#c.xSemaphoreCreateRecursiveMutex) Creates a new recursive mutex type semaphore instance, and returns a handle by which the new recursive mutex can be referenced.

Internally, within the FreeRTOS implementation, recursive mutexs use a block of memory, in which the mutex structure is stored. If a recursive mutex is created using xSemaphoreCreateRecursiveMutex() then the required memory is automatically dynamically allocated inside the xSemaphoreCreateRecursiveMutex() function. (see

[http://www.freertos.org/a00111.html](http://www.freertos.org/a00111.html)). If a recursive mutex is created using xSemaphoreCreateRecursiveMutexStatic() then the application writer must provide the memory that will get used by the mutex. xSemaphoreCreateRecursiveMutexStatic() therefore allows a recursive mutex to be created without using any dynamic memory allocation.Mutexes created using this macro can be accessed using the xSemaphoreTakeRecursive() and xSemaphoreGiveRecursive() macros. The xSemaphoreTake() and xSemaphoreGive() macros must not be used.

A mutex used recursively can be âtakenâ repeatedly by the owner. The mutex doesnât become available again until the owner has called xSemaphoreGiveRecursive() for each successful âtakeâ request. For example, if a task successfully âtakesâ the same mutex 5 times then the mutex will not be available to any other task until it has also âgivenâ the mutex back exactly five times.

This type of semaphore uses a priority inheritance mechanism so a task âtakingâ a semaphore MUST ALWAYS âgiveâ the semaphore back once the semaphore it is no longer required.

Mutex type semaphores cannot be used from within interrupt service routines.

See vSemaphoreCreateBinary() for an alternative implementation that can be used for pure synchronisation (where one task or interrupt always âgivesâ the semaphore and another always âtakesâ the semaphore) and from within interrupt service routines.

Example usage:

SemaphoreHandle_t xSemaphore; void vATask( void * pvParameters ) { // Semaphore cannot be used before a call to xSemaphoreCreateMutex(). // This is a macro so pass the variable in directly. xSemaphore = xSemaphoreCreateRecursiveMutex(); if( xSemaphore != NULL ) { // The semaphore was created successfully. // The semaphore can now be used. } }

**Return**xSemaphore Handle to the created mutex semaphore. Should be of type SemaphoreHandle_t.

-
`xSemaphoreCreateRecursiveMutexStatic`

(pxStaticSemaphore)[Â¶](https://docs.espressif.com#c.xSemaphoreCreateRecursiveMutexStatic) Creates a new recursive mutex type semaphore instance, and returns a handle by which the new recursive mutex can be referenced.

Internally, within the FreeRTOS implementation, recursive mutexs use a block of memory, in which the mutex structure is stored. If a recursive mutex is created using xSemaphoreCreateRecursiveMutex() then the required memory is automatically dynamically allocated inside the xSemaphoreCreateRecursiveMutex() function. (see

[http://www.freertos.org/a00111.html](http://www.freertos.org/a00111.html)). If a recursive mutex is created using xSemaphoreCreateRecursiveMutexStatic() then the application writer must provide the memory that will get used by the mutex. xSemaphoreCreateRecursiveMutexStatic() therefore allows a recursive mutex to be created without using any dynamic memory allocation.Mutexes created using this macro can be accessed using the xSemaphoreTakeRecursive() and xSemaphoreGiveRecursive() macros. The xSemaphoreTake() and xSemaphoreGive() macros must not be used.

A mutex used recursively can be âtakenâ repeatedly by the owner. The mutex doesnât become available again until the owner has called xSemaphoreGiveRecursive() for each successful âtakeâ request. For example, if a task successfully âtakesâ the same mutex 5 times then the mutex will not be available to any other task until it has also âgivenâ the mutex back exactly five times.

This type of semaphore uses a priority inheritance mechanism so a task âtakingâ a semaphore MUST ALWAYS âgiveâ the semaphore back once the semaphore it is no longer required.

Mutex type semaphores cannot be used from within interrupt service routines.

See xSemaphoreCreateBinary() for an alternative implementation that can be used for pure synchronisation (where one task or interrupt always âgivesâ the semaphore and another always âtakesâ the semaphore) and from within interrupt service routines.

Example usage:

SemaphoreHandle_t xSemaphore; StaticSemaphore_t xMutexBuffer; void vATask( void * pvParameters ) { // A recursive semaphore cannot be used before it is created. Here a // recursive mutex is created using xSemaphoreCreateRecursiveMutexStatic(). // The address of xMutexBuffer is passed into the function, and will hold // the mutexes data structures - so no dynamic memory allocation will be // attempted. xSemaphore = xSemaphoreCreateRecursiveMutexStatic( &xMutexBuffer ); // As no dynamic memory allocation was performed, xSemaphore cannot be NULL, // so there is no need to check it. }

**Return**If the recursive mutex was successfully created then a handle to the created recursive mutex is returned. If pxMutexBuffer was NULL then NULL is returned.

**Parameters**`pxStaticSemaphore`

: Must point to a variable of type StaticSemaphore_t, which will then be used to hold the recursive mutexâs data structure, removing the need for the memory to be allocated dynamically.

-
`xSemaphoreCreateCounting`

(uxMaxCount, uxInitialCount)[Â¶](https://docs.espressif.com#c.xSemaphoreCreateCounting) Creates a new counting semaphore instance, and returns a handle by which the new counting semaphore can be referenced.

In many usage scenarios it is faster and more memory efficient to use a direct to task notification in place of a counting semaphore!

[http://www.freertos.org/RTOS-task-notifications.html](http://www.freertos.org/RTOS-task-notifications.html)Internally, within the FreeRTOS implementation, counting semaphores use a block of memory, in which the counting semaphore structure is stored. If a counting semaphore is created using xSemaphoreCreateCounting() then the required memory is automatically dynamically allocated inside the xSemaphoreCreateCounting() function. (see

[http://www.freertos.org/a00111.html](http://www.freertos.org/a00111.html)). If a counting semaphore is created using xSemaphoreCreateCountingStatic() then the application writer can instead optionally provide the memory that will get used by the counting semaphore. xSemaphoreCreateCountingStatic() therefore allows a counting semaphore to be created without using any dynamic memory allocation.Counting semaphores are typically used for two things:

1) Counting events.

In this usage scenario an event handler will âgiveâ a semaphore each time an event occurs (incrementing the semaphore count value), and a handler task will âtakeâ a semaphore each time it processes an event (decrementing the semaphore count value). The count value is therefore the difference between the number of events that have occurred and the number that have been processed. In this case it is desirable for the initial count value to be zero.

2) Resource management.

In this usage scenario the count value indicates the number of resources available. To obtain control of a resource a task must first obtain a semaphore - decrementing the semaphore count value. When the count value reaches zero there are no free resources. When a task finishes with the resource it âgivesâ the semaphore back - incrementing the semaphore count value. In this case it is desirable for the initial count value to be equal to the maximum count value, indicating that all resources are free.

Example usage:

SemaphoreHandle_t xSemaphore; void vATask( void * pvParameters ) { SemaphoreHandle_t xSemaphore = NULL; // Semaphore cannot be used before a call to xSemaphoreCreateCounting(). // The max value to which the semaphore can count should be 10, and the // initial value assigned to the count should be 0. xSemaphore = xSemaphoreCreateCounting( 10, 0 ); if( xSemaphore != NULL ) { // The semaphore was created successfully. // The semaphore can now be used. } }

**Return**Handle to the created semaphore. Null if the semaphore could not be created.

**Parameters**`uxMaxCount`

: The maximum count value that can be reached. When the semaphore reaches this value it can no longer be âgivenâ.`uxInitialCount`

: The count value assigned to the semaphore when it is created.

-
`xSemaphoreCreateCountingStatic`

(uxMaxCount, uxInitialCount, pxSemaphoreBuffer)[Â¶](https://docs.espressif.com#c.xSemaphoreCreateCountingStatic) Creates a new counting semaphore instance, and returns a handle by which the new counting semaphore can be referenced.

In many usage scenarios it is faster and more memory efficient to use a direct to task notification in place of a counting semaphore!

[http://www.freertos.org/RTOS-task-notifications.html](http://www.freertos.org/RTOS-task-notifications.html)Internally, within the FreeRTOS implementation, counting semaphores use a block of memory, in which the counting semaphore structure is stored. If a counting semaphore is created using xSemaphoreCreateCounting() then the required memory is automatically dynamically allocated inside the xSemaphoreCreateCounting() function. (see

[http://www.freertos.org/a00111.html](http://www.freertos.org/a00111.html)). If a counting semaphore is created using xSemaphoreCreateCountingStatic() then the application writer must provide the memory. xSemaphoreCreateCountingStatic() therefore allows a counting semaphore to be created without using any dynamic memory allocation.Counting semaphores are typically used for two things:

1) Counting events.

In this usage scenario an event handler will âgiveâ a semaphore each time an event occurs (incrementing the semaphore count value), and a handler task will âtakeâ a semaphore each time it processes an event (decrementing the semaphore count value). The count value is therefore the difference between the number of events that have occurred and the number that have been processed. In this case it is desirable for the initial count value to be zero.

2) Resource management.

In this usage scenario the count value indicates the number of resources available. To obtain control of a resource a task must first obtain a semaphore - decrementing the semaphore count value. When the count value reaches zero there are no free resources. When a task finishes with the resource it âgivesâ the semaphore back - incrementing the semaphore count value. In this case it is desirable for the initial count value to be equal to the maximum count value, indicating that all resources are free.

Example usage:

SemaphoreHandle_t xSemaphore; StaticSemaphore_t xSemaphoreBuffer; void vATask( void * pvParameters ) { SemaphoreHandle_t xSemaphore = NULL; // Counting semaphore cannot be used before they have been created. Create // a counting semaphore using xSemaphoreCreateCountingStatic(). The max // value to which the semaphore can count is 10, and the initial value // assigned to the count will be 0. The address of xSemaphoreBuffer is // passed in and will be used to hold the semaphore structure, so no dynamic // memory allocation will be used. xSemaphore = xSemaphoreCreateCounting( 10, 0, &xSemaphoreBuffer ); // No memory allocation was attempted so xSemaphore cannot be NULL, so there // is no need to check its value. }

**Return**If the counting semaphore was successfully created then a handle to the created counting semaphore is returned. If pxSemaphoreBuffer was NULL then NULL is returned.

**Parameters**`uxMaxCount`

: The maximum count value that can be reached. When the semaphore reaches this value it can no longer be âgivenâ.`uxInitialCount`

: The count value assigned to the semaphore when it is created.`pxSemaphoreBuffer`

: Must point to a variable of type StaticSemaphore_t, which will then be used to hold the semaphoreâs data structure, removing the need for the memory to be allocated dynamically.

-
`vSemaphoreDelete`

(xSemaphore)[Â¶](https://docs.espressif.com#c.vSemaphoreDelete) Delete a semaphore. This function must be used with care. For example, do not delete a mutex type semaphore if the mutex is held by a task.

**Parameters**`xSemaphore`

: A handle to the semaphore to be deleted.

-
`xSemaphoreGetMutexHolder`

(xSemaphore)[Â¶](https://docs.espressif.com#c.xSemaphoreGetMutexHolder) If xMutex is indeed a mutex type semaphore, return the current mutex holder. If xMutex is not a mutex type semaphore, or the mutex is available (not held by a task), return NULL.

Note: This is a good way of determining if the calling task is the mutex holder, but not a good way of determining the identity of the mutex holder as the holder may change between the function exiting and the returned value being tested.

-
`uxSemaphoreGetCount`

(xSemaphore)[Â¶](https://docs.espressif.com#c.uxSemaphoreGetCount) If the semaphore is a counting semaphore then uxSemaphoreGetCount() returns its current count value. If the semaphore is a binary semaphore then uxSemaphoreGetCount() returns 1 if the semaphore is available, and 0 if the semaphore is not available.

### Type Definitions[Â¶](https://docs.espressif.com#id7)

-
*typedef*[QueueHandle_t](https://docs.espressif.com#_CPPv413QueueHandle_t)`SemaphoreHandle_t`

[Â¶](https://docs.espressif.com#_CPPv417SemaphoreHandle_t)

## Timer API[Â¶](https://docs.espressif.com#timer-api)

### Header File[Â¶](https://docs.espressif.com#id8)

### Functions[Â¶](https://docs.espressif.com#id9)

-
[TimerHandle_t](https://docs.espressif.com#_CPPv413TimerHandle_t)`xTimerCreate`

(*const*char **const**pcTimerName*,*const*TickType_t*xTimerPeriodInTicks*,*const*UBaseType_t*uxAutoReload*, void **const**pvTimerID*,[TimerCallbackFunction_t](https://docs.espressif.com#_CPPv423TimerCallbackFunction_t)*pxCallbackFunction*)[Â¶](https://docs.espressif.com#_CPPv412xTimerCreatePCKcK10TickType_tK11UBaseType_tPCv23TimerCallbackFunction_t) Creates a new software timer instance, and returns a handle by which the created software timer can be referenced.

Internally, within the FreeRTOS implementation, software timers use a block of memory, in which the timer data structure is stored. If a software timer is created using xTimerCreate() then the required memory is automatically dynamically allocated inside the xTimerCreate() function. (see

[http://www.freertos.org/a00111.html](http://www.freertos.org/a00111.html)). If a software timer is created using xTimerCreateStatic() then the application writer must provide the memory that will get used by the software timer. xTimerCreateStatic() therefore allows a software timer to be created without using any dynamic memory allocation.Timers are created in the dormant state. The xTimerStart(), xTimerReset(), xTimerStartFromISR(), xTimerResetFromISR(), xTimerChangePeriod() and xTimerChangePeriodFromISR() API functions can all be used to transition a timer into the active state.

Example usage:

#define NUM_TIMERS 5 // An array to hold handles to the created timers. TimerHandle_t xTimers[ NUM_TIMERS ]; // An array to hold a count of the number of times each timer expires. int32_t lExpireCounters[ NUM_TIMERS ] = { 0 }; // Define a callback function that will be used by multiple timer instances. // The callback function does nothing but count the number of times the // associated timer expires, and stop the timer once the timer has expired // 10 times. void vTimerCallback( TimerHandle_t pxTimer ) { int32_t lArrayIndex; const int32_t xMaxExpiryCountBeforeStopping = 10; // Optionally do something if the pxTimer parameter is NULL. configASSERT( pxTimer ); // Which timer expired? lArrayIndex = ( int32_t ) pvTimerGetTimerID( pxTimer ); // Increment the number of times that pxTimer has expired. lExpireCounters[ lArrayIndex ] += 1; // If the timer has expired 10 times then stop it from running. if( lExpireCounters[ lArrayIndex ] == xMaxExpiryCountBeforeStopping ) { // Do not use a block time if calling a timer API function from a // timer callback function, as doing so could cause a deadlock! xTimerStop( pxTimer, 0 ); } } void main( void ) { int32_t x; // Create then start some timers. Starting the timers before the scheduler // has been started means the timers will start running immediately that // the scheduler starts. for( x = 0; x < NUM_TIMERS; x++ ) { xTimers[ x ] = xTimerCreate( "Timer", // Just a text name, not used by the kernel. ( 100 * x ), // The timer period in ticks. pdTRUE, // The timers will auto-reload themselves when they expire. ( void * ) x, // Assign each timer a unique id equal to its array index. vTimerCallback // Each timer calls the same callback when it expires. ); if( xTimers[ x ] == NULL ) { // The timer was not created. } else { // Start the timer. No block time is specified, and even if one was // it would be ignored because the scheduler has not yet been // started. if( xTimerStart( xTimers[ x ], 0 ) != pdPASS ) { // The timer could not be set into the Active state. } } } // ... // Create tasks here. // ... // Starting the scheduler will start the timers running as they have already // been set into the active state. vTaskStartScheduler(); // Should not reach here. for( ;; ); }

**Return**If the timer is successfully created then a handle to the newly created timer is returned. If the timer cannot be created (because either there is insufficient FreeRTOS heap remaining to allocate the timer structures, or the timer period was set to 0) then NULL is returned.

**Parameters**`pcTimerName`

: A text name that is assigned to the timer. This is done purely to assist debugging. The kernel itself only ever references a timer by its handle, and never by its name.`xTimerPeriodInTicks`

: The timer period. The time is defined in tick periods so the constant portTICK_PERIOD_MS can be used to convert a time that has been specified in milliseconds. For example, if the timer must expire after 100 ticks, then xTimerPeriodInTicks should be set to 100. Alternatively, if the timer must expire after 500ms, then xPeriod can be set to ( 500 / portTICK_PERIOD_MS ) provided configTICK_RATE_HZ is less than or equal to 1000.`uxAutoReload`

: If uxAutoReload is set to pdTRUE then the timer will expire repeatedly with a frequency set by the xTimerPeriodInTicks parameter. If uxAutoReload is set to pdFALSE then the timer will be a one-shot timer and enter the dormant state after it expires.`pvTimerID`

: An identifier that is assigned to the timer being created. Typically this would be used in the timer callback function to identify which timer expired when the same callback function is assigned to more than one timer.`pxCallbackFunction`

: The function to call when the timer expires. Callback functions must have the prototype defined by TimerCallbackFunction_t, which is âvoid vCallbackFunction( TimerHandle_t xTimer );â.

-
[TimerHandle_t](https://docs.espressif.com#_CPPv413TimerHandle_t)`xTimerCreateStatic`

(*const*char **const**pcTimerName*,*const*TickType_t*xTimerPeriodInTicks*,*const*UBaseType_t*uxAutoReload*, void **const**pvTimerID*,[TimerCallbackFunction_t](https://docs.espressif.com#_CPPv423TimerCallbackFunction_t)*pxCallbackFunction*, StaticTimer_t **pxTimerBuffer*)[Â¶](https://docs.espressif.com#_CPPv418xTimerCreateStaticPCKcK10TickType_tK11UBaseType_tPCv23TimerCallbackFunction_tP13StaticTimer_t) Creates a new software timer instance, and returns a handle by which the created software timer can be referenced.

Internally, within the FreeRTOS implementation, software timers use a block of memory, in which the timer data structure is stored. If a software timer is created using xTimerCreate() then the required memory is automatically dynamically allocated inside the xTimerCreate() function. (see

[http://www.freertos.org/a00111.html](http://www.freertos.org/a00111.html)). If a software timer is created using xTimerCreateStatic() then the application writer must provide the memory that will get used by the software timer. xTimerCreateStatic() therefore allows a software timer to be created without using any dynamic memory allocation.Timers are created in the dormant state. The xTimerStart(), xTimerReset(), xTimerStartFromISR(), xTimerResetFromISR(), xTimerChangePeriod() and xTimerChangePeriodFromISR() API functions can all be used to transition a timer into the active state.

Example usage:

// The buffer used to hold the software timer's data structure. static StaticTimer_t xTimerBuffer; // A variable that will be incremented by the software timer's callback // function. UBaseType_t uxVariableToIncrement = 0; // A software timer callback function that increments a variable passed to // it when the software timer was created. After the 5th increment the // callback function stops the software timer. static void prvTimerCallback( TimerHandle_t xExpiredTimer ) { UBaseType_t *puxVariableToIncrement; BaseType_t xReturned; // Obtain the address of the variable to increment from the timer ID. puxVariableToIncrement = ( UBaseType_t * ) pvTimerGetTimerID( xExpiredTimer ); // Increment the variable to show the timer callback has executed. ( *puxVariableToIncrement )++; // If this callback has executed the required number of times, stop the // timer. if( *puxVariableToIncrement == 5 ) { // This is called from a timer callback so must not block. xTimerStop( xExpiredTimer, staticDONT_BLOCK ); } } void main( void ) { // Create the software time. xTimerCreateStatic() has an extra parameter // than the normal xTimerCreate() API function. The parameter is a pointer // to the StaticTimer_t structure that will hold the software timer // structure. If the parameter is passed as NULL then the structure will be // allocated dynamically, just as if xTimerCreate() had been called. xTimer = xTimerCreateStatic( "T1", // Text name for the task. Helps debugging only. Not used by FreeRTOS. xTimerPeriod, // The period of the timer in ticks. pdTRUE, // This is an auto-reload timer. ( void * ) &uxVariableToIncrement, // A variable incremented by the software timer's callback function prvTimerCallback, // The function to execute when the timer expires. &xTimerBuffer ); // The buffer that will hold the software timer structure. // The scheduler has not started yet so a block time is not used. xReturned = xTimerStart( xTimer, 0 ); // ... // Create tasks here. // ... // Starting the scheduler will start the timers running as they have already // been set into the active state. vTaskStartScheduler(); // Should not reach here. for( ;; ); }

**Return**If the timer is created then a handle to the created timer is returned. If pxTimerBuffer was NULL then NULL is returned.

**Parameters**`pcTimerName`

: A text name that is assigned to the timer. This is done purely to assist debugging. The kernel itself only ever references a timer by its handle, and never by its name.`xTimerPeriodInTicks`

: The timer period. The time is defined in tick periods so the constant portTICK_PERIOD_MS can be used to convert a time that has been specified in milliseconds. For example, if the timer must expire after 100 ticks, then xTimerPeriodInTicks should be set to 100. Alternatively, if the timer must expire after 500ms, then xPeriod can be set to ( 500 / portTICK_PERIOD_MS ) provided configTICK_RATE_HZ is less than or equal to 1000.`uxAutoReload`

: If uxAutoReload is set to pdTRUE then the timer will expire repeatedly with a frequency set by the xTimerPeriodInTicks parameter. If uxAutoReload is set to pdFALSE then the timer will be a one-shot timer and enter the dormant state after it expires.`pvTimerID`

: An identifier that is assigned to the timer being created. Typically this would be used in the timer callback function to identify which timer expired when the same callback function is assigned to more than one timer.`pxCallbackFunction`

: The function to call when the timer expires. Callback functions must have the prototype defined by TimerCallbackFunction_t, which is âvoid vCallbackFunction( TimerHandle_t xTimer );â.`pxTimerBuffer`

: Must point to a variable of type StaticTimer_t, which will be then be used to hold the software timerâs data structures, removing the need for the memory to be allocated dynamically.

-
void *
`pvTimerGetTimerID`

([TimerHandle_t](https://docs.espressif.com#_CPPv413TimerHandle_t)*xTimer*)[Â¶](https://docs.espressif.com#_CPPv417pvTimerGetTimerID13TimerHandle_t) Returns the ID assigned to the timer.

IDs are assigned to timers using the pvTimerID parameter of the call to xTimerCreated() that was used to create the timer.

If the same callback function is assigned to multiple timers then the timer ID can be used within the callback function to identify which timer actually expired.

Example usage:

**Return**The ID assigned to the timer being queried.

**Parameters**`xTimer`

: The timer being queried.

See the xTimerCreate() API function example usage scenario.

-
void
`vTimerSetTimerID`

([TimerHandle_t](https://docs.espressif.com#_CPPv413TimerHandle_t)*xTimer*, void **pvNewID*)[Â¶](https://docs.espressif.com#_CPPv416vTimerSetTimerID13TimerHandle_tPv) Sets the ID assigned to the timer.

IDs are assigned to timers using the pvTimerID parameter of the call to xTimerCreated() that was used to create the timer.

If the same callback function is assigned to multiple timers then the timer ID can be used as time specific (timer local) storage.

Example usage:

**Parameters**`xTimer`

: The timer being updated.`pvNewID`

: The ID to assign to the timer.

See the xTimerCreate() API function example usage scenario.

-
BaseType_t
`xTimerIsTimerActive`

([TimerHandle_t](https://docs.espressif.com#_CPPv413TimerHandle_t)*xTimer*)[Â¶](https://docs.espressif.com#_CPPv419xTimerIsTimerActive13TimerHandle_t) Queries a timer to see if it is active or dormant.

A timer will be dormant if:

1) It has been created but not started, or 2) It is an expired one-shot timer that has not been restarted.

Timers are created in the dormant state. The xTimerStart(), xTimerReset(), xTimerStartFromISR(), xTimerResetFromISR(), xTimerChangePeriod() and xTimerChangePeriodFromISR() API functions can all be used to transition a timer into the active state.

Example usage:

// This function assumes xTimer has already been created. void vAFunction( TimerHandle_t xTimer ) { if( xTimerIsTimerActive( xTimer ) != pdFALSE ) // or more simply and equivalently "if( xTimerIsTimerActive( xTimer ) )" { // xTimer is active, do something. } else { // xTimer is not active, do something else. } }

**Return**pdFALSE will be returned if the timer is dormant. A value other than pdFALSE will be returned if the timer is active.

**Parameters**`xTimer`

: The timer being queried.

-
[TaskHandle_t](https://docs.espressif.com#_CPPv412TaskHandle_t)`xTimerGetTimerDaemonTaskHandle`

(void)[Â¶](https://docs.espressif.com#_CPPv430xTimerGetTimerDaemonTaskHandlev) xTimerGetTimerDaemonTaskHandle() is only available if INCLUDE_xTimerGetTimerDaemonTaskHandle is set to 1 in FreeRTOSConfig.h.

Simply returns the handle of the timer service/daemon task. It it not valid to call xTimerGetTimerDaemonTaskHandle() before the scheduler has been started.

-
TickType_t
`xTimerGetPeriod`

([TimerHandle_t](https://docs.espressif.com#_CPPv413TimerHandle_t)*xTimer*)[Â¶](https://docs.espressif.com#_CPPv415xTimerGetPeriod13TimerHandle_t) Returns the period of a timer.

**Return**The period of the timer in ticks.

**Parameters**`xTimer`

: The handle of the timer being queried.

-
TickType_t
`xTimerGetExpiryTime`

([TimerHandle_t](https://docs.espressif.com#_CPPv413TimerHandle_t)*xTimer*)[Â¶](https://docs.espressif.com#_CPPv419xTimerGetExpiryTime13TimerHandle_t) Returns the time in ticks at which the timer will expire. If this is less than the current tick count then the expiry time has overflowed from the current time.

**Return**If the timer is running then the time in ticks at which the timer will next expire is returned. If the timer is not running then the return value is undefined.

**Parameters**`xTimer`

: The handle of the timer being queried.

-
BaseType_t
`xTimerPendFunctionCallFromISR`

([PendedFunction_t](https://docs.espressif.com#_CPPv416PendedFunction_t)*xFunctionToPend*, void **pvParameter1*, uint32_t*ulParameter2*, BaseType_t **pxHigherPriorityTaskWoken*)[Â¶](https://docs.espressif.com#_CPPv429xTimerPendFunctionCallFromISR16PendedFunction_tPv8uint32_tP10BaseType_t) Used from application interrupt service routines to defer the execution of a function to the RTOS daemon task (the timer service task, hence this function is implemented in timers.c and is prefixed with âTimerâ).

Ideally an interrupt service routine (ISR) is kept as short as possible, but sometimes an ISR either has a lot of processing to do, or needs to perform processing that is not deterministic. In these cases xTimerPendFunctionCallFromISR() can be used to defer processing of a function to the RTOS daemon task.

A mechanism is provided that allows the interrupt to return directly to the task that will subsequently execute the pended callback function. This allows the callback function to execute contiguously in time with the interrupt - just as if the callback had executed in the interrupt itself.

Example usage:

// The callback function that will execute in the context of the daemon task. // Note callback functions must all use this same prototype. void vProcessInterface( void *pvParameter1, uint32_t ulParameter2 ) { BaseType_t xInterfaceToService; // The interface that requires servicing is passed in the second // parameter. The first parameter is not used in this case. xInterfaceToService = ( BaseType_t ) ulParameter2; // ...Perform the processing here... } // An ISR that receives data packets from multiple interfaces void vAnISR( void ) { BaseType_t xInterfaceToService, xHigherPriorityTaskWoken; // Query the hardware to determine which interface needs processing. xInterfaceToService = prvCheckInterfaces(); // The actual processing is to be deferred to a task. Request the // vProcessInterface() callback function is executed, passing in the // number of the interface that needs processing. The interface to // service is passed in the second parameter. The first parameter is // not used in this case. xHigherPriorityTaskWoken = pdFALSE; xTimerPendFunctionCallFromISR( vProcessInterface, NULL, ( uint32_t ) xInterfaceToService, &xHigherPriorityTaskWoken ); // If xHigherPriorityTaskWoken is now set to pdTRUE then a context // switch should be requested. The macro used is port specific and will // be either portYIELD_FROM_ISR() or portEND_SWITCHING_ISR() - refer to // the documentation page for the port being used. portYIELD_FROM_ISR( xHigherPriorityTaskWoken ); }

**Return**pdPASS is returned if the message was successfully sent to the timer daemon task, otherwise pdFALSE is returned.

**Parameters**`xFunctionToPend`

: The function to execute from the timer service/ daemon task. The function must conform to the PendedFunction_t prototype.`pvParameter1`

: The value of the callback functionâs first parameter. The parameter has a void * type to allow it to be used to pass any type. For example, unsigned longs can be cast to a void *, or the void * can be used to point to a structure.`ulParameter2`

: The value of the callback functionâs second parameter.`pxHigherPriorityTaskWoken`

: As mentioned above, calling this function will result in a message being sent to the timer daemon task. If the priority of the timer daemon task (which is set using configTIMER_TASK_PRIORITY in FreeRTOSConfig.h) is higher than the priority of the currently running task (the task the interrupt interrupted) then *pxHigherPriorityTaskWoken will be set to pdTRUE within xTimerPendFunctionCallFromISR(), indicating that a context switch should be requested before the interrupt exits. For that reason *pxHigherPriorityTaskWoken must be initialised to pdFALSE. See the example code below.

-
BaseType_t
`xTimerPendFunctionCall`

([PendedFunction_t](https://docs.espressif.com#_CPPv416PendedFunction_t)*xFunctionToPend*, void **pvParameter1*, uint32_t*ulParameter2*, TickType_t*xTicksToWait*)[Â¶](https://docs.espressif.com#_CPPv422xTimerPendFunctionCall16PendedFunction_tPv8uint32_t10TickType_t) Used to defer the execution of a function to the RTOS daemon task (the timer service task, hence this function is implemented in timers.c and is prefixed with âTimerâ).

**Return**pdPASS is returned if the message was successfully sent to the timer daemon task, otherwise pdFALSE is returned.

**Parameters**`xFunctionToPend`

: The function to execute from the timer service/ daemon task. The function must conform to the PendedFunction_t prototype.`pvParameter1`

: The value of the callback functionâs first parameter. The parameter has a void * type to allow it to be used to pass any type. For example, unsigned longs can be cast to a void *, or the void * can be used to point to a structure.`ulParameter2`

: The value of the callback functionâs second parameter.`xTicksToWait`

: Calling this function will result in a message being sent to the timer daemon task on a queue. xTicksToWait is the amount of time the calling task should remain in the Blocked state (so not using any processing time) for space to become available on the timer queue if the queue is found to be full.

-
*const*char *`pcTimerGetTimerName`

([TimerHandle_t](https://docs.espressif.com#_CPPv413TimerHandle_t)*xTimer*)[Â¶](https://docs.espressif.com#_CPPv419pcTimerGetTimerName13TimerHandle_t) Returns the name that was assigned to a timer when the timer was created.

**Return**The name assigned to the timer specified by the xTimer parameter.

**Parameters**`xTimer`

: The handle of the timer being queried.

### Macros[Â¶](https://docs.espressif.com#id10)

-
`tmrCOMMAND_EXECUTE_CALLBACK_FROM_ISR`

[Â¶](https://docs.espressif.com#c.tmrCOMMAND_EXECUTE_CALLBACK_FROM_ISR)

-
`tmrCOMMAND_EXECUTE_CALLBACK`

[Â¶](https://docs.espressif.com#c.tmrCOMMAND_EXECUTE_CALLBACK)

-
`tmrCOMMAND_START_DONT_TRACE`

[Â¶](https://docs.espressif.com#c.tmrCOMMAND_START_DONT_TRACE)

-
`tmrCOMMAND_START`

[Â¶](https://docs.espressif.com#c.tmrCOMMAND_START)

-
`tmrCOMMAND_RESET`

[Â¶](https://docs.espressif.com#c.tmrCOMMAND_RESET)

-
`tmrCOMMAND_STOP`

[Â¶](https://docs.espressif.com#c.tmrCOMMAND_STOP)

-
`tmrCOMMAND_CHANGE_PERIOD`

[Â¶](https://docs.espressif.com#c.tmrCOMMAND_CHANGE_PERIOD)

-
`tmrCOMMAND_DELETE`

[Â¶](https://docs.espressif.com#c.tmrCOMMAND_DELETE)

-
`tmrFIRST_FROM_ISR_COMMAND`

[Â¶](https://docs.espressif.com#c.tmrFIRST_FROM_ISR_COMMAND)

-
`tmrCOMMAND_START_FROM_ISR`

[Â¶](https://docs.espressif.com#c.tmrCOMMAND_START_FROM_ISR)

-
`tmrCOMMAND_RESET_FROM_ISR`

[Â¶](https://docs.espressif.com#c.tmrCOMMAND_RESET_FROM_ISR)

-
`tmrCOMMAND_STOP_FROM_ISR`

[Â¶](https://docs.espressif.com#c.tmrCOMMAND_STOP_FROM_ISR)

-
`tmrCOMMAND_CHANGE_PERIOD_FROM_ISR`

[Â¶](https://docs.espressif.com#c.tmrCOMMAND_CHANGE_PERIOD_FROM_ISR)

-
`xTimerStart`

(xTimer, xTicksToWait)[Â¶](https://docs.espressif.com#c.xTimerStart) Timer functionality is provided by a timer service/daemon task. Many of the public FreeRTOS timer API functions send commands to the timer service task through a queue called the timer command queue. The timer command queue is private to the kernel itself and is not directly accessible to application code. The length of the timer command queue is set by the configTIMER_QUEUE_LENGTH configuration constant.

xTimerStart() starts a timer that was previously created using the xTimerCreate() API function. If the timer had already been started and was already in the active state, then xTimerStart() has equivalent functionality to the xTimerReset() API function.

Starting a timer ensures the timer is in the active state. If the timer is not stopped, deleted, or reset in the mean time, the callback function associated with the timer will get called ânâ ticks after xTimerStart() was called, where ânâ is the timers defined period.

It is valid to call xTimerStart() before the scheduler has been started, but when this is done the timer will not actually start until the scheduler is started, and the timers expiry time will be relative to when the scheduler is started, not relative to when xTimerStart() was called.

The configUSE_TIMERS configuration constant must be set to 1 for xTimerStart() to be available.

Example usage:

**Return**pdFAIL will be returned if the start command could not be sent to the timer command queue even after xTicksToWait ticks had passed. pdPASS will be returned if the command was successfully sent to the timer command queue. When the command is actually processed will depend on the priority of the timer service/daemon task relative to other tasks in the system, although the timers expiry time is relative to when xTimerStart() is actually called. The timer service/daemon task priority is set by the configTIMER_TASK_PRIORITY configuration constant.

**Parameters**`xTimer`

: The handle of the timer being started/restarted.`xTicksToWait`

: Specifies the time, in ticks, that the calling task should be held in the Blocked state to wait for the start command to be successfully sent to the timer command queue, should the queue already be full when xTimerStart() was called. xTicksToWait is ignored if xTimerStart() is called before the scheduler is started.

See the xTimerCreate() API function example usage scenario.

-
`xTimerStop`

(xTimer, xTicksToWait)[Â¶](https://docs.espressif.com#c.xTimerStop) Timer functionality is provided by a timer service/daemon task. Many of the public FreeRTOS timer API functions send commands to the timer service task through a queue called the timer command queue. The timer command queue is private to the kernel itself and is not directly accessible to application code. The length of the timer command queue is set by the configTIMER_QUEUE_LENGTH configuration constant.

xTimerStop() stops a timer that was previously started using either of the The xTimerStart(), xTimerReset(), xTimerStartFromISR(), xTimerResetFromISR(), xTimerChangePeriod() or xTimerChangePeriodFromISR() API functions.

Stopping a timer ensures the timer is not in the active state.

The configUSE_TIMERS configuration constant must be set to 1 for xTimerStop() to be available.

Example usage:

**Return**pdFAIL will be returned if the stop command could not be sent to the timer command queue even after xTicksToWait ticks had passed. pdPASS will be returned if the command was successfully sent to the timer command queue. When the command is actually processed will depend on the priority of the timer service/daemon task relative to other tasks in the system. The timer service/daemon task priority is set by the configTIMER_TASK_PRIORITY configuration constant.

**Parameters**`xTimer`

: The handle of the timer being stopped.`xTicksToWait`

: Specifies the time, in ticks, that the calling task should be held in the Blocked state to wait for the stop command to be successfully sent to the timer command queue, should the queue already be full when xTimerStop() was called. xTicksToWait is ignored if xTimerStop() is called before the scheduler is started.

See the xTimerCreate() API function example usage scenario.

-
`xTimerChangePeriod`

(xTimer, xNewPeriod, xTicksToWait)[Â¶](https://docs.espressif.com#c.xTimerChangePeriod) Timer functionality is provided by a timer service/daemon task. Many of the public FreeRTOS timer API functions send commands to the timer service task through a queue called the timer command queue. The timer command queue is private to the kernel itself and is not directly accessible to application code. The length of the timer command queue is set by the configTIMER_QUEUE_LENGTH configuration constant.

xTimerChangePeriod() changes the period of a timer that was previously created using the xTimerCreate() API function.

xTimerChangePeriod() can be called to change the period of an active or dormant state timer.

The configUSE_TIMERS configuration constant must be set to 1 for xTimerChangePeriod() to be available.

Example usage:

// This function assumes xTimer has already been created. If the timer // referenced by xTimer is already active when it is called, then the timer // is deleted. If the timer referenced by xTimer is not active when it is // called, then the period of the timer is set to 500ms and the timer is // started. void vAFunction( TimerHandle_t xTimer ) { if( xTimerIsTimerActive( xTimer ) != pdFALSE ) // or more simply and equivalently "if( xTimerIsTimerActive( xTimer ) )" { // xTimer is already active - delete it. xTimerDelete( xTimer ); } else { // xTimer is not active, change its period to 500ms. This will also // cause the timer to start. Block for a maximum of 100 ticks if the // change period command cannot immediately be sent to the timer // command queue. if( xTimerChangePeriod( xTimer, 500 / portTICK_PERIOD_MS, 100 ) == pdPASS ) { // The command was successfully sent. } else { // The command could not be sent, even after waiting for 100 ticks // to pass. Take appropriate action here. } } }

**Return**pdFAIL will be returned if the change period command could not be sent to the timer command queue even after xTicksToWait ticks had passed. pdPASS will be returned if the command was successfully sent to the timer command queue. When the command is actually processed will depend on the priority of the timer service/daemon task relative to other tasks in the system. The timer service/daemon task priority is set by the configTIMER_TASK_PRIORITY configuration constant.

**Parameters**`xTimer`

: The handle of the timer that is having its period changed.`xNewPeriod`

: The new period for xTimer. Timer periods are specified in tick periods, so the constant portTICK_PERIOD_MS can be used to convert a time that has been specified in milliseconds. For example, if the timer must expire after 100 ticks, then xNewPeriod should be set to 100. Alternatively, if the timer must expire after 500ms, then xNewPeriod can be set to ( 500 / portTICK_PERIOD_MS ) provided configTICK_RATE_HZ is less than or equal to 1000.`xTicksToWait`

: Specifies the time, in ticks, that the calling task should be held in the Blocked state to wait for the change period command to be successfully sent to the timer command queue, should the queue already be full when xTimerChangePeriod() was called. xTicksToWait is ignored if xTimerChangePeriod() is called before the scheduler is started.

-
`xTimerDelete`

(xTimer, xTicksToWait)[Â¶](https://docs.espressif.com#c.xTimerDelete) Timer functionality is provided by a timer service/daemon task. Many of the public FreeRTOS timer API functions send commands to the timer service task through a queue called the timer command queue. The timer command queue is private to the kernel itself and is not directly accessible to application code. The length of the timer command queue is set by the configTIMER_QUEUE_LENGTH configuration constant.

xTimerDelete() deletes a timer that was previously created using the xTimerCreate() API function.

The configUSE_TIMERS configuration constant must be set to 1 for xTimerDelete() to be available.

Example usage:

**Return**pdFAIL will be returned if the delete command could not be sent to the timer command queue even after xTicksToWait ticks had passed. pdPASS will be returned if the command was successfully sent to the timer command queue. When the command is actually processed will depend on the priority of the timer service/daemon task relative to other tasks in the system. The timer service/daemon task priority is set by the configTIMER_TASK_PRIORITY configuration constant.

**Parameters**`xTimer`

: The handle of the timer being deleted.`xTicksToWait`

: Specifies the time, in ticks, that the calling task should be held in the Blocked state to wait for the delete command to be successfully sent to the timer command queue, should the queue already be full when xTimerDelete() was called. xTicksToWait is ignored if xTimerDelete() is called before the scheduler is started.

See the xTimerChangePeriod() API function example usage scenario.

-
`xTimerReset`

(xTimer, xTicksToWait)[Â¶](https://docs.espressif.com#c.xTimerReset) Timer functionality is provided by a timer service/daemon task. Many of the public FreeRTOS timer API functions send commands to the timer service task through a queue called the timer command queue. The timer command queue is private to the kernel itself and is not directly accessible to application code. The length of the timer command queue is set by the configTIMER_QUEUE_LENGTH configuration constant.

xTimerReset() re-starts a timer that was previously created using the xTimerCreate() API function. If the timer had already been started and was already in the active state, then xTimerReset() will cause the timer to re-evaluate its expiry time so that it is relative to when xTimerReset() was called. If the timer was in the dormant state then xTimerReset() has equivalent functionality to the xTimerStart() API function.

Resetting a timer ensures the timer is in the active state. If the timer is not stopped, deleted, or reset in the mean time, the callback function associated with the timer will get called ânâ ticks after xTimerReset() was called, where ânâ is the timers defined period.

It is valid to call xTimerReset() before the scheduler has been started, but when this is done the timer will not actually start until the scheduler is started, and the timers expiry time will be relative to when the scheduler is started, not relative to when xTimerReset() was called.

The configUSE_TIMERS configuration constant must be set to 1 for xTimerReset() to be available.

Example usage:

// When a key is pressed, an LCD back-light is switched on. If 5 seconds pass // without a key being pressed, then the LCD back-light is switched off. In // this case, the timer is a one-shot timer. TimerHandle_t xBacklightTimer = NULL; // The callback function assigned to the one-shot timer. In this case the // parameter is not used. void vBacklightTimerCallback( TimerHandle_t pxTimer ) { // The timer expired, therefore 5 seconds must have passed since a key // was pressed. Switch off the LCD back-light. vSetBacklightState( BACKLIGHT_OFF ); } // The key press event handler. void vKeyPressEventHandler( char cKey ) { // Ensure the LCD back-light is on, then reset the timer that is // responsible for turning the back-light off after 5 seconds of // key inactivity. Wait 10 ticks for the command to be successfully sent // if it cannot be sent immediately. vSetBacklightState( BACKLIGHT_ON ); if( xTimerReset( xBacklightTimer, 100 ) != pdPASS ) { // The reset command was not executed successfully. Take appropriate // action here. } // Perform the rest of the key processing here. } void main( void ) { int32_t x; // Create then start the one-shot timer that is responsible for turning // the back-light off if no keys are pressed within a 5 second period. xBacklightTimer = xTimerCreate( "BacklightTimer", // Just a text name, not used by the kernel. ( 5000 / portTICK_PERIOD_MS), // The timer period in ticks. pdFALSE, // The timer is a one-shot timer. 0, // The id is not used by the callback so can take any value. vBacklightTimerCallback // The callback function that switches the LCD back-light off. ); if( xBacklightTimer == NULL ) { // The timer was not created. } else { // Start the timer. No block time is specified, and even if one was // it would be ignored because the scheduler has not yet been // started. if( xTimerStart( xBacklightTimer, 0 ) != pdPASS ) { // The timer could not be set into the Active state. } } // ... // Create tasks here. // ... // Starting the scheduler will start the timer running as it has already // been set into the active state. xTaskStartScheduler(); // Should not reach here. for( ;; ); }

**Return**pdFAIL will be returned if the reset command could not be sent to the timer command queue even after xTicksToWait ticks had passed. pdPASS will be returned if the command was successfully sent to the timer command queue. When the command is actually processed will depend on the priority of the timer service/daemon task relative to other tasks in the system, although the timers expiry time is relative to when xTimerStart() is actually called. The timer service/daemon task priority is set by the configTIMER_TASK_PRIORITY configuration constant.

**Parameters**`xTimer`

: The handle of the timer being reset/started/restarted.`xTicksToWait`

: Specifies the time, in ticks, that the calling task should be held in the Blocked state to wait for the reset command to be successfully sent to the timer command queue, should the queue already be full when xTimerReset() was called. xTicksToWait is ignored if xTimerReset() is called before the scheduler is started.

-
`xTimerStartFromISR`

(xTimer, pxHigherPriorityTaskWoken)[Â¶](https://docs.espressif.com#c.xTimerStartFromISR) A version of xTimerStart() that can be called from an interrupt service routine.

Example usage:

// This scenario assumes xBacklightTimer has already been created. When a // key is pressed, an LCD back-light is switched on. If 5 seconds pass // without a key being pressed, then the LCD back-light is switched off. In // this case, the timer is a one-shot timer, and unlike the example given for // the xTimerReset() function, the key press event handler is an interrupt // service routine. // The callback function assigned to the one-shot timer. In this case the // parameter is not used. void vBacklightTimerCallback( TimerHandle_t pxTimer ) { // The timer expired, therefore 5 seconds must have passed since a key // was pressed. Switch off the LCD back-light. vSetBacklightState( BACKLIGHT_OFF ); } // The key press interrupt service routine. void vKeyPressEventInterruptHandler( void ) { BaseType_t xHigherPriorityTaskWoken = pdFALSE; // Ensure the LCD back-light is on, then restart the timer that is // responsible for turning the back-light off after 5 seconds of // key inactivity. This is an interrupt service routine so can only // call FreeRTOS API functions that end in "FromISR". vSetBacklightState( BACKLIGHT_ON ); // xTimerStartFromISR() or xTimerResetFromISR() could be called here // as both cause the timer to re-calculate its expiry time. // xHigherPriorityTaskWoken was initialised to pdFALSE when it was // declared (in this function). if( xTimerStartFromISR( xBacklightTimer, &xHigherPriorityTaskWoken ) != pdPASS ) { // The start command was not executed successfully. Take appropriate // action here. } // Perform the rest of the key processing here. // If xHigherPriorityTaskWoken equals pdTRUE, then a context switch // should be performed. The syntax required to perform a context switch // from inside an ISR varies from port to port, and from compiler to // compiler. Inspect the demos for the port you are using to find the // actual syntax required. if( xHigherPriorityTaskWoken != pdFALSE ) { // Call the interrupt safe yield function here (actual function // depends on the FreeRTOS port being used). } }

**Return**pdFAIL will be returned if the start command could not be sent to the timer command queue. pdPASS will be returned if the command was successfully sent to the timer command queue. When the command is actually processed will depend on the priority of the timer service/daemon task relative to other tasks in the system, although the timers expiry time is relative to when xTimerStartFromISR() is actually called. The timer service/daemon task priority is set by the configTIMER_TASK_PRIORITY configuration constant.

**Parameters**`xTimer`

: The handle of the timer being started/restarted.`pxHigherPriorityTaskWoken`

: The timer service/daemon task spends most of its time in the Blocked state, waiting for messages to arrive on the timer command queue. Calling xTimerStartFromISR() writes a message to the timer command queue, so has the potential to transition the timer service/daemon task out of the Blocked state. If calling xTimerStartFromISR() causes the timer service/daemon task to leave the Blocked state, and the timer service/ daemon task has a priority equal to or greater than the currently executing task (the task that was interrupted), then *pxHigherPriorityTaskWoken will get set to pdTRUE internally within the xTimerStartFromISR() function. If xTimerStartFromISR() sets this value to pdTRUE then a context switch should be performed before the interrupt exits.

-
`xTimerStopFromISR`

(xTimer, pxHigherPriorityTaskWoken)[Â¶](https://docs.espressif.com#c.xTimerStopFromISR) A version of xTimerStop() that can be called from an interrupt service routine.

Example usage:

// This scenario assumes xTimer has already been created and started. When // an interrupt occurs, the timer should be simply stopped. // The interrupt service routine that stops the timer. void vAnExampleInterruptServiceRoutine( void ) { BaseType_t xHigherPriorityTaskWoken = pdFALSE; // The interrupt has occurred - simply stop the timer. // xHigherPriorityTaskWoken was set to pdFALSE where it was defined // (within this function). As this is an interrupt service routine, only // FreeRTOS API functions that end in "FromISR" can be used. if( xTimerStopFromISR( xTimer, &xHigherPriorityTaskWoken ) != pdPASS ) { // The stop command was not executed successfully. Take appropriate // action here. } // If xHigherPriorityTaskWoken equals pdTRUE, then a context switch // should be performed. The syntax required to perform a context switch // from inside an ISR varies from port to port, and from compiler to // compiler. Inspect the demos for the port you are using to find the // actual syntax required. if( xHigherPriorityTaskWoken != pdFALSE ) { // Call the interrupt safe yield function here (actual function // depends on the FreeRTOS port being used). } }

**Return**pdFAIL will be returned if the stop command could not be sent to the timer command queue. pdPASS will be returned if the command was successfully sent to the timer command queue. When the command is actually processed will depend on the priority of the timer service/daemon task relative to other tasks in the system. The timer service/daemon task priority is set by the configTIMER_TASK_PRIORITY configuration constant.

**Parameters**`xTimer`

: The handle of the timer being stopped.`pxHigherPriorityTaskWoken`

: The timer service/daemon task spends most of its time in the Blocked state, waiting for messages to arrive on the timer command queue. Calling xTimerStopFromISR() writes a message to the timer command queue, so has the potential to transition the timer service/daemon task out of the Blocked state. If calling xTimerStopFromISR() causes the timer service/daemon task to leave the Blocked state, and the timer service/ daemon task has a priority equal to or greater than the currently executing task (the task that was interrupted), then *pxHigherPriorityTaskWoken will get set to pdTRUE internally within the xTimerStopFromISR() function. If xTimerStopFromISR() sets this value to pdTRUE then a context switch should be performed before the interrupt exits.

-
`xTimerChangePeriodFromISR`

(xTimer, xNewPeriod, pxHigherPriorityTaskWoken)[Â¶](https://docs.espressif.com#c.xTimerChangePeriodFromISR) A version of xTimerChangePeriod() that can be called from an interrupt service routine.

Example usage:

// This scenario assumes xTimer has already been created and started. When // an interrupt occurs, the period of xTimer should be changed to 500ms. // The interrupt service routine that changes the period of xTimer. void vAnExampleInterruptServiceRoutine( void ) { BaseType_t xHigherPriorityTaskWoken = pdFALSE; // The interrupt has occurred - change the period of xTimer to 500ms. // xHigherPriorityTaskWoken was set to pdFALSE where it was defined // (within this function). As this is an interrupt service routine, only // FreeRTOS API functions that end in "FromISR" can be used. if( xTimerChangePeriodFromISR( xTimer, &xHigherPriorityTaskWoken ) != pdPASS ) { // The command to change the timers period was not executed // successfully. Take appropriate action here. } // If xHigherPriorityTaskWoken equals pdTRUE, then a context switch // should be performed. The syntax required to perform a context switch // from inside an ISR varies from port to port, and from compiler to // compiler. Inspect the demos for the port you are using to find the // actual syntax required. if( xHigherPriorityTaskWoken != pdFALSE ) { // Call the interrupt safe yield function here (actual function // depends on the FreeRTOS port being used). } }

**Return**pdFAIL will be returned if the command to change the timers period could not be sent to the timer command queue. pdPASS will be returned if the command was successfully sent to the timer command queue. When the command is actually processed will depend on the priority of the timer service/daemon task relative to other tasks in the system. The timer service/daemon task priority is set by the configTIMER_TASK_PRIORITY configuration constant.

**Parameters**`xTimer`

: The handle of the timer that is having its period changed.`xNewPeriod`

: The new period for xTimer. Timer periods are specified in tick periods, so the constant portTICK_PERIOD_MS can be used to convert a time that has been specified in milliseconds. For example, if the timer must expire after 100 ticks, then xNewPeriod should be set to 100. Alternatively, if the timer must expire after 500ms, then xNewPeriod can be set to ( 500 / portTICK_PERIOD_MS ) provided configTICK_RATE_HZ is less than or equal to 1000.`pxHigherPriorityTaskWoken`

: The timer service/daemon task spends most of its time in the Blocked state, waiting for messages to arrive on the timer command queue. Calling xTimerChangePeriodFromISR() writes a message to the timer command queue, so has the potential to transition the timer service/ daemon task out of the Blocked state. If calling xTimerChangePeriodFromISR() causes the timer service/daemon task to leave the Blocked state, and the timer service/daemon task has a priority equal to or greater than the currently executing task (the task that was interrupted), then *pxHigherPriorityTaskWoken will get set to pdTRUE internally within the xTimerChangePeriodFromISR() function. If xTimerChangePeriodFromISR() sets this value to pdTRUE then a context switch should be performed before the interrupt exits.

-
`xTimerResetFromISR`

(xTimer, pxHigherPriorityTaskWoken)[Â¶](https://docs.espressif.com#c.xTimerResetFromISR) A version of xTimerReset() that can be called from an interrupt service routine.

Example usage:

// This scenario assumes xBacklightTimer has already been created. When a // key is pressed, an LCD back-light is switched on. If 5 seconds pass // without a key being pressed, then the LCD back-light is switched off. In // this case, the timer is a one-shot timer, and unlike the example given for // the xTimerReset() function, the key press event handler is an interrupt // service routine. // The callback function assigned to the one-shot timer. In this case the // parameter is not used. void vBacklightTimerCallback( TimerHandle_t pxTimer ) { // The timer expired, therefore 5 seconds must have passed since a key // was pressed. Switch off the LCD back-light. vSetBacklightState( BACKLIGHT_OFF ); } // The key press interrupt service routine. void vKeyPressEventInterruptHandler( void ) { BaseType_t xHigherPriorityTaskWoken = pdFALSE; // Ensure the LCD back-light is on, then reset the timer that is // responsible for turning the back-light off after 5 seconds of // key inactivity. This is an interrupt service routine so can only // call FreeRTOS API functions that end in "FromISR". vSetBacklightState( BACKLIGHT_ON ); // xTimerStartFromISR() or xTimerResetFromISR() could be called here // as both cause the timer to re-calculate its expiry time. // xHigherPriorityTaskWoken was initialised to pdFALSE when it was // declared (in this function). if( xTimerResetFromISR( xBacklightTimer, &xHigherPriorityTaskWoken ) != pdPASS ) { // The reset command was not executed successfully. Take appropriate // action here. } // Perform the rest of the key processing here. // If xHigherPriorityTaskWoken equals pdTRUE, then a context switch // should be performed. The syntax required to perform a context switch // from inside an ISR varies from port to port, and from compiler to // compiler. Inspect the demos for the port you are using to find the // actual syntax required. if( xHigherPriorityTaskWoken != pdFALSE ) { // Call the interrupt safe yield function here (actual function // depends on the FreeRTOS port being used). } }

**Return**pdFAIL will be returned if the reset command could not be sent to the timer command queue. pdPASS will be returned if the command was successfully sent to the timer command queue. When the command is actually processed will depend on the priority of the timer service/daemon task relative to other tasks in the system, although the timers expiry time is relative to when xTimerResetFromISR() is actually called. The timer service/daemon task priority is set by the configTIMER_TASK_PRIORITY configuration constant.

**Parameters**`xTimer`

: The handle of the timer that is to be started, reset, or restarted.`pxHigherPriorityTaskWoken`

: The timer service/daemon task spends most of its time in the Blocked state, waiting for messages to arrive on the timer command queue. Calling xTimerResetFromISR() writes a message to the timer command queue, so has the potential to transition the timer service/daemon task out of the Blocked state. If calling xTimerResetFromISR() causes the timer service/daemon task to leave the Blocked state, and the timer service/ daemon task has a priority equal to or greater than the currently executing task (the task that was interrupted), then *pxHigherPriorityTaskWoken will get set to pdTRUE internally within the xTimerResetFromISR() function. If xTimerResetFromISR() sets this value to pdTRUE then a context switch should be performed before the interrupt exits.

### Type Definitions[Â¶](https://docs.espressif.com#id11)

-
*typedef*void *`TimerHandle_t`

[Â¶](https://docs.espressif.com#_CPPv413TimerHandle_t) Type by which software timers are referenced. For example, a call to xTimerCreate() returns an TimerHandle_t variable that can then be used to reference the subject timer in calls to other software timer API functions (for example, xTimerStart(), xTimerReset(), etc.).

-
*typedef*void (*`TimerCallbackFunction_t`

)([TimerHandle_t](https://docs.espressif.com#_CPPv413TimerHandle_t)xTimer)[Â¶](https://docs.espressif.com#_CPPv423TimerCallbackFunction_t) Defines the prototype to which timer callback functions must conform.

-
*typedef*void (*`PendedFunction_t`

)(void *, uint32_t)[Â¶](https://docs.espressif.com#_CPPv416PendedFunction_t) Defines the prototype to which functions used with the xTimerPendFunctionCallFromISR() function must conform.

## Event Group API[Â¶](https://docs.espressif.com#event-group-api)

### Header File[Â¶](https://docs.espressif.com#id12)

### Functions[Â¶](https://docs.espressif.com#id13)

-
[EventGroupHandle_t](https://docs.espressif.com#_CPPv418EventGroupHandle_t)`xEventGroupCreate`

(void)[Â¶](https://docs.espressif.com#_CPPv417xEventGroupCreatev) Create a new event group.

Internally, within the FreeRTOS implementation, event groups use a [small] block of memory, in which the event groupâs structure is stored. If an event groups is created using xEventGroupCreate() then the required memory is automatically dynamically allocated inside the xEventGroupCreate() function. (see

[http://www.freertos.org/a00111.html](http://www.freertos.org/a00111.html)). If an event group is created using xEventGropuCreateStatic() then the application writer must instead provide the memory that will get used by the event group. xEventGroupCreateStatic() therefore allows an event group to be created without using any dynamic memory allocation.Although event groups are not related to ticks, for internal implementation reasons the number of bits available for use in an event group is dependent on the configUSE_16_BIT_TICKS setting in FreeRTOSConfig.h. If configUSE_16_BIT_TICKS is 1 then each event group contains 8 usable bits (bit 0 to bit 7). If configUSE_16_BIT_TICKS is set to 0 then each event group has 24 usable bits (bit 0 to bit 23). The EventBits_t type is used to store event bits within an event group.

Example usage:

// Declare a variable to hold the created event group. EventGroupHandle_t xCreatedEventGroup; // Attempt to create the event group. xCreatedEventGroup = xEventGroupCreate(); // Was the event group created successfully? if( xCreatedEventGroup == NULL ) { // The event group was not created because there was insufficient // FreeRTOS heap available. } else { // The event group was created. }

**Return**If the event group was created then a handle to the event group is returned. If there was insufficient FreeRTOS heap available to create the event group then NULL is returned. See

[http://www.freertos.org/a00111.html](http://www.freertos.org/a00111.html)

-
[EventGroupHandle_t](https://docs.espressif.com#_CPPv418EventGroupHandle_t)`xEventGroupCreateStatic`

(StaticEventGroup_t **pxEventGroupBuffer*)[Â¶](https://docs.espressif.com#_CPPv423xEventGroupCreateStaticP18StaticEventGroup_t) Create a new event group.

Internally, within the FreeRTOS implementation, event groups use a [small] block of memory, in which the event groupâs structure is stored. If an event groups is created using xEventGropuCreate() then the required memory is automatically dynamically allocated inside the xEventGroupCreate() function. (see

[http://www.freertos.org/a00111.html](http://www.freertos.org/a00111.html)). If an event group is created using xEventGropuCreateStatic() then the application writer must instead provide the memory that will get used by the event group. xEventGroupCreateStatic() therefore allows an event group to be created without using any dynamic memory allocation.Although event groups are not related to ticks, for internal implementation reasons the number of bits available for use in an event group is dependent on the configUSE_16_BIT_TICKS setting in FreeRTOSConfig.h. If configUSE_16_BIT_TICKS is 1 then each event group contains 8 usable bits (bit 0 to bit 7). If configUSE_16_BIT_TICKS is set to 0 then each event group has 24 usable bits (bit 0 to bit 23). The EventBits_t type is used to store event bits within an event group.

Example usage:

// StaticEventGroup_t is a publicly accessible structure that has the same // size and alignment requirements as the real event group structure. It is // provided as a mechanism for applications to know the size of the event // group (which is dependent on the architecture and configuration file // settings) without breaking the strict data hiding policy by exposing the // real event group internals. This StaticEventGroup_t variable is passed // into the xSemaphoreCreateEventGroupStatic() function and is used to store // the event group's data structures StaticEventGroup_t xEventGroupBuffer; // Create the event group without dynamically allocating any memory. xEventGroup = xEventGroupCreateStatic( &xEventGroupBuffer );

**Return**If the event group was created then a handle to the event group is returned. If pxEventGroupBuffer was NULL then NULL is returned.

**Parameters**`pxEventGroupBuffer`

: pxEventGroupBuffer must point to a variable of type StaticEventGroup_t, which will be then be used to hold the event groupâs data structures, removing the need for the memory to be allocated dynamically.

-
[EventBits_t](https://docs.espressif.com#_CPPv411EventBits_t)`xEventGroupWaitBits`

([EventGroupHandle_t](https://docs.espressif.com#_CPPv418EventGroupHandle_t)*xEventGroup*,*const*[EventBits_t](https://docs.espressif.com#_CPPv411EventBits_t)*uxBitsToWaitFor*,*const*BaseType_t*xClearOnExit*,*const*BaseType_t*xWaitForAllBits*, TickType_t*xTicksToWait*)[Â¶](https://docs.espressif.com#_CPPv419xEventGroupWaitBits18EventGroupHandle_tK11EventBits_tK10BaseType_tK10BaseType_t10TickType_t) [Potentially] block to wait for one or more bits to be set within a previously created event group.

This function cannot be called from an interrupt.

Example usage:

{c}#define BIT_0 ( 1 << 0 ) #define BIT_4 ( 1 << 4 ) void aFunction( EventGroupHandle_t xEventGroup ) { EventBits_t uxBits; const TickType_t xTicksToWait = 100 / portTICK_PERIOD_MS; // Wait a maximum of 100ms for either bit 0 or bit 4 to be set within // the event group. Clear the bits before exiting. uxBits = xEventGroupWaitBits( xEventGroup, // The event group being tested. BIT_0 | BIT_4, // The bits within the event group to wait for. pdTRUE, // BIT_0 and BIT_4 should be cleared before returning. pdFALSE, // Don't wait for both bits, either bit will do. xTicksToWait ); // Wait a maximum of 100ms for either bit to be set. if( ( uxBits & ( BIT_0 | BIT_4 ) ) == ( BIT_0 | BIT_4 ) ) { // xEventGroupWaitBits() returned because both bits were set. } else if( ( uxBits & BIT_0 ) != 0 ) { // xEventGroupWaitBits() returned because just BIT_0 was set. } else if( ( uxBits & BIT_4 ) != 0 ) { // xEventGroupWaitBits() returned because just BIT_4 was set. } else { // xEventGroupWaitBits() returned because xTicksToWait ticks passed // without either BIT_0 or BIT_4 becoming set. } }

**Return**The value of the event group at the time either the bits being waited for became set, or the block time expired. Test the return value to know which bits were set. If xEventGroupWaitBits() returned because its timeout expired then not all the bits being waited for will be set. If xEventGroupWaitBits() returned because the bits it was waiting for were set then the returned value is the event group value before any bits were automatically cleared in the case that xClearOnExit parameter was set to pdTRUE.

**Parameters**`xEventGroup`

: The event group in which the bits are being tested. The event group must have previously been created using a call to xEventGroupCreate().`uxBitsToWaitFor`

: A bitwise value that indicates the bit or bits to test inside the event group. For example, to wait for bit 0 and/or bit 2 set uxBitsToWaitFor to 0x05. To wait for bits 0 and/or bit 1 and/or bit 2 set uxBitsToWaitFor to 0x07. Etc.`xClearOnExit`

: If xClearOnExit is set to pdTRUE then any bits within uxBitsToWaitFor that are set within the event group will be cleared before xEventGroupWaitBits() returns if the wait condition was met (if the function returns for a reason other than a timeout). If xClearOnExit is set to pdFALSE then the bits set in the event group are not altered when the call to xEventGroupWaitBits() returns.`xWaitForAllBits`

: If xWaitForAllBits is set to pdTRUE then xEventGroupWaitBits() will return when either all the bits in uxBitsToWaitFor are set or the specified block time expires. If xWaitForAllBits is set to pdFALSE then xEventGroupWaitBits() will return when any one of the bits set in uxBitsToWaitFor is set or the specified block time expires. The block time is specified by the xTicksToWait parameter.`xTicksToWait`

: The maximum amount of time (specified in âticksâ) to wait for one/all (depending on the xWaitForAllBits value) of the bits specified by uxBitsToWaitFor to become set.

-
[EventBits_t](https://docs.espressif.com#_CPPv411EventBits_t)`xEventGroupClearBits`

([EventGroupHandle_t](https://docs.espressif.com#_CPPv418EventGroupHandle_t)*xEventGroup*,*const*[EventBits_t](https://docs.espressif.com#_CPPv411EventBits_t)*uxBitsToClear*)[Â¶](https://docs.espressif.com#_CPPv420xEventGroupClearBits18EventGroupHandle_tK11EventBits_t) Clear bits within an event group. This function cannot be called from an interrupt.

Example usage:

#define BIT_0 ( 1 << 0 ) #define BIT_4 ( 1 << 4 ) void aFunction( EventGroupHandle_t xEventGroup ) { EventBits_t uxBits; // Clear bit 0 and bit 4 in xEventGroup. uxBits = xEventGroupClearBits( xEventGroup, // The event group being updated. BIT_0 | BIT_4 );// The bits being cleared. if( ( uxBits & ( BIT_0 | BIT_4 ) ) == ( BIT_0 | BIT_4 ) ) { // Both bit 0 and bit 4 were set before xEventGroupClearBits() was // called. Both will now be clear (not set). } else if( ( uxBits & BIT_0 ) != 0 ) { // Bit 0 was set before xEventGroupClearBits() was called. It will // now be clear. } else if( ( uxBits & BIT_4 ) != 0 ) { // Bit 4 was set before xEventGroupClearBits() was called. It will // now be clear. } else { // Neither bit 0 nor bit 4 were set in the first place. } }

**Return**The value of the event group before the specified bits were cleared.

**Parameters**`xEventGroup`

: The event group in which the bits are to be cleared.`uxBitsToClear`

: A bitwise value that indicates the bit or bits to clear in the event group. For example, to clear bit 3 only, set uxBitsToClear to 0x08. To clear bit 3 and bit 0 set uxBitsToClear to 0x09.

-
[EventBits_t](https://docs.espressif.com#_CPPv411EventBits_t)`xEventGroupSetBits`

([EventGroupHandle_t](https://docs.espressif.com#_CPPv418EventGroupHandle_t)*xEventGroup*,*const*[EventBits_t](https://docs.espressif.com#_CPPv411EventBits_t)*uxBitsToSet*)[Â¶](https://docs.espressif.com#_CPPv418xEventGroupSetBits18EventGroupHandle_tK11EventBits_t) Set bits within an event group. This function cannot be called from an interrupt. xEventGroupSetBitsFromISR() is a version that can be called from an interrupt.

Setting bits in an event group will automatically unblock tasks that are blocked waiting for the bits.

Example usage:

{c}#define BIT_0 ( 1 << 0 ) #define BIT_4 ( 1 << 4 ) void aFunction( EventGroupHandle_t xEventGroup ) { EventBits_t uxBits; // Set bit 0 and bit 4 in xEventGroup. uxBits = xEventGroupSetBits( xEventGroup, // The event group being updated. BIT_0 | BIT_4 );// The bits being set. if( ( uxBits & ( BIT_0 | BIT_4 ) ) == ( BIT_0 | BIT_4 ) ) { // Both bit 0 and bit 4 remained set when the function returned. } else if( ( uxBits & BIT_0 ) != 0 ) { // Bit 0 remained set when the function returned, but bit 4 was // cleared. It might be that bit 4 was cleared automatically as a // task that was waiting for bit 4 was removed from the Blocked // state. } else if( ( uxBits & BIT_4 ) != 0 ) { // Bit 4 remained set when the function returned, but bit 0 was // cleared. It might be that bit 0 was cleared automatically as a // task that was waiting for bit 0 was removed from the Blocked // state. } else { // Neither bit 0 nor bit 4 remained set. It might be that a task // was waiting for both of the bits to be set, and the bits were // cleared as the task left the Blocked state. } }

**Return**The value of the event group at the time the call to xEventGroupSetBits() returns. There are two reasons why the returned value might have the bits specified by the uxBitsToSet parameter cleared. First, if setting a bit results in a task that was waiting for the bit leaving the blocked state then it is possible the bit will be cleared automatically (see the xClearBitOnExit parameter of xEventGroupWaitBits()). Second, any unblocked (or otherwise Ready state) task that has a priority above that of the task that called xEventGroupSetBits() will execute and may change the event group value before the call to xEventGroupSetBits() returns.

**Parameters**`xEventGroup`

: The event group in which the bits are to be set.`uxBitsToSet`

: A bitwise value that indicates the bit or bits to set. For example, to set bit 3 only, set uxBitsToSet to 0x08. To set bit 3 and bit 0 set uxBitsToSet to 0x09.

-
[EventBits_t](https://docs.espressif.com#_CPPv411EventBits_t)`xEventGroupSync`

([EventGroupHandle_t](https://docs.espressif.com#_CPPv418EventGroupHandle_t)*xEventGroup*,*const*[EventBits_t](https://docs.espressif.com#_CPPv411EventBits_t)*uxBitsToSet*,*const*[EventBits_t](https://docs.espressif.com#_CPPv411EventBits_t)*uxBitsToWaitFor*, TickType_t*xTicksToWait*)[Â¶](https://docs.espressif.com#_CPPv415xEventGroupSync18EventGroupHandle_tK11EventBits_tK11EventBits_t10TickType_t) Atomically set bits within an event group, then wait for a combination of bits to be set within the same event group. This functionality is typically used to synchronise multiple tasks, where each task has to wait for the other tasks to reach a synchronisation point before proceeding.

This function cannot be used from an interrupt.

The function will return before its block time expires if the bits specified by the uxBitsToWait parameter are set, or become set within that time. In this case all the bits specified by uxBitsToWait will be automatically cleared before the function returns.

Example usage:

// Bits used by the three tasks. #define TASK_0_BIT ( 1 << 0 ) #define TASK_1_BIT ( 1 << 1 ) #define TASK_2_BIT ( 1 << 2 ) #define ALL_SYNC_BITS ( TASK_0_BIT | TASK_1_BIT | TASK_2_BIT ) // Use an event group to synchronise three tasks. It is assumed this event // group has already been created elsewhere. EventGroupHandle_t xEventBits; void vTask0( void *pvParameters ) { EventBits_t uxReturn; TickType_t xTicksToWait = 100 / portTICK_PERIOD_MS; for( ;; ) { // Perform task functionality here. // Set bit 0 in the event flag to note this task has reached the // sync point. The other two tasks will set the other two bits defined // by ALL_SYNC_BITS. All three tasks have reached the synchronisation // point when all the ALL_SYNC_BITS are set. Wait a maximum of 100ms // for this to happen. uxReturn = xEventGroupSync( xEventBits, TASK_0_BIT, ALL_SYNC_BITS, xTicksToWait ); if( ( uxReturn & ALL_SYNC_BITS ) == ALL_SYNC_BITS ) { // All three tasks reached the synchronisation point before the call // to xEventGroupSync() timed out. } } } void vTask1( void *pvParameters ) { for( ;; ) { // Perform task functionality here. // Set bit 1 in the event flag to note this task has reached the // synchronisation point. The other two tasks will set the other two // bits defined by ALL_SYNC_BITS. All three tasks have reached the // synchronisation point when all the ALL_SYNC_BITS are set. Wait // indefinitely for this to happen. xEventGroupSync( xEventBits, TASK_1_BIT, ALL_SYNC_BITS, portMAX_DELAY ); // xEventGroupSync() was called with an indefinite block time, so // this task will only reach here if the syncrhonisation was made by all // three tasks, so there is no need to test the return value. } } void vTask2( void *pvParameters ) { for( ;; ) { // Perform task functionality here. // Set bit 2 in the event flag to note this task has reached the // synchronisation point. The other two tasks will set the other two // bits defined by ALL_SYNC_BITS. All three tasks have reached the // synchronisation point when all the ALL_SYNC_BITS are set. Wait // indefinitely for this to happen. xEventGroupSync( xEventBits, TASK_2_BIT, ALL_SYNC_BITS, portMAX_DELAY ); // xEventGroupSync() was called with an indefinite block time, so // this task will only reach here if the syncrhonisation was made by all // three tasks, so there is no need to test the return value. } }

**Return**The value of the event group at the time either the bits being waited for became set, or the block time expired. Test the return value to know which bits were set. If xEventGroupSync() returned because its timeout expired then not all the bits being waited for will be set. If xEventGroupSync() returned because all the bits it was waiting for were set then the returned value is the event group value before any bits were automatically cleared.

**Parameters**`xEventGroup`

: The event group in which the bits are being tested. The event group must have previously been created using a call to xEventGroupCreate().`uxBitsToSet`

: The bits to set in the event group before determining if, and possibly waiting for, all the bits specified by the uxBitsToWait parameter are set.`uxBitsToWaitFor`

: A bitwise value that indicates the bit or bits to test inside the event group. For example, to wait for bit 0 and bit 2 set uxBitsToWaitFor to 0x05. To wait for bits 0 and bit 1 and bit 2 set uxBitsToWaitFor to 0x07. Etc.`xTicksToWait`

: The maximum amount of time (specified in âticksâ) to wait for all of the bits specified by uxBitsToWaitFor to become set.

-
[EventBits_t](https://docs.espressif.com#_CPPv411EventBits_t)`xEventGroupGetBitsFromISR`

([EventGroupHandle_t](https://docs.espressif.com#_CPPv418EventGroupHandle_t)*xEventGroup*)[Â¶](https://docs.espressif.com#_CPPv425xEventGroupGetBitsFromISR18EventGroupHandle_t) A version of xEventGroupGetBits() that can be called from an ISR.

**Return**The event group bits at the time xEventGroupGetBitsFromISR() was called.

**Parameters**`xEventGroup`

: The event group being queried.

-
void
`vEventGroupDelete`

([EventGroupHandle_t](https://docs.espressif.com#_CPPv418EventGroupHandle_t)*xEventGroup*)[Â¶](https://docs.espressif.com#_CPPv417vEventGroupDelete18EventGroupHandle_t) Delete an event group that was previously created by a call to xEventGroupCreate(). Tasks that are blocked on the event group will be unblocked and obtain 0 as the event groupâs value.

**Parameters**`xEventGroup`

: The event group being deleted.

### Macros[Â¶](https://docs.espressif.com#id14)

-
`xEventGroupClearBitsFromISR`

(xEventGroup, uxBitsToClear)[Â¶](https://docs.espressif.com#c.xEventGroupClearBitsFromISR) A version of xEventGroupClearBits() that can be called from an interrupt.

Setting bits in an event group is not a deterministic operation because there are an unknown number of tasks that may be waiting for the bit or bits being set. FreeRTOS does not allow nondeterministic operations to be performed while interrupts are disabled, so protects event groups that are accessed from tasks by suspending the scheduler rather than disabling interrupts. As a result event groups cannot be accessed directly from an interrupt service routine. Therefore xEventGroupClearBitsFromISR() sends a message to the timer task to have the clear operation performed in the context of the timer task.

Example usage:

#define BIT_0 ( 1 << 0 ) #define BIT_4 ( 1 << 4 ) // An event group which it is assumed has already been created by a call to // xEventGroupCreate(). EventGroupHandle_t xEventGroup; void anInterruptHandler( void ) { // Clear bit 0 and bit 4 in xEventGroup. xResult = xEventGroupClearBitsFromISR( xEventGroup, // The event group being updated. BIT_0 | BIT_4 ); // The bits being set. if( xResult == pdPASS ) { // The message was posted successfully. } }

**Return**If the request to execute the function was posted successfully then pdPASS is returned, otherwise pdFALSE is returned. pdFALSE will be returned if the timer service queue was full.

**Parameters**`xEventGroup`

: The event group in which the bits are to be cleared.`uxBitsToClear`

: A bitwise value that indicates the bit or bits to clear. For example, to clear bit 3 only, set uxBitsToClear to 0x08. To clear bit 3 and bit 0 set uxBitsToClear to 0x09.

-
`xEventGroupSetBitsFromISR`

(xEventGroup, uxBitsToSet, pxHigherPriorityTaskWoken)[Â¶](https://docs.espressif.com#c.xEventGroupSetBitsFromISR) A version of xEventGroupSetBits() that can be called from an interrupt.

Setting bits in an event group is not a deterministic operation because there are an unknown number of tasks that may be waiting for the bit or bits being set. FreeRTOS does not allow nondeterministic operations to be performed in interrupts or from critical sections. Therefore xEventGroupSetBitFromISR() sends a message to the timer task to have the set operation performed in the context of the timer task - where a scheduler lock is used in place of a critical section.

Example usage:

#define BIT_0 ( 1 << 0 ) #define BIT_4 ( 1 << 4 ) // An event group which it is assumed has already been created by a call to // xEventGroupCreate(). EventGroupHandle_t xEventGroup; void anInterruptHandler( void ) { BaseType_t xHigherPriorityTaskWoken, xResult; // xHigherPriorityTaskWoken must be initialised to pdFALSE. xHigherPriorityTaskWoken = pdFALSE; // Set bit 0 and bit 4 in xEventGroup. xResult = xEventGroupSetBitsFromISR( xEventGroup, // The event group being updated. BIT_0 | BIT_4 // The bits being set. &xHigherPriorityTaskWoken ); // Was the message posted successfully? if( xResult == pdPASS ) { // If xHigherPriorityTaskWoken is now set to pdTRUE then a context // switch should be requested. The macro used is port specific and // will be either portYIELD_FROM_ISR() or portEND_SWITCHING_ISR() - // refer to the documentation page for the port being used. portYIELD_FROM_ISR( xHigherPriorityTaskWoken ); } }

**Return**If the request to execute the function was posted successfully then pdPASS is returned, otherwise pdFALSE is returned. pdFALSE will be returned if the timer service queue was full.

**Parameters**`xEventGroup`

: The event group in which the bits are to be set.`uxBitsToSet`

: A bitwise value that indicates the bit or bits to set. For example, to set bit 3 only, set uxBitsToSet to 0x08. To set bit 3 and bit 0 set uxBitsToSet to 0x09.`pxHigherPriorityTaskWoken`

: As mentioned above, calling this function will result in a message being sent to the timer daemon task. If the priority of the timer daemon task is higher than the priority of the currently running task (the task the interrupt interrupted) then *pxHigherPriorityTaskWoken will be set to pdTRUE by xEventGroupSetBitsFromISR(), indicating that a context switch should be requested before the interrupt exits. For that reason *pxHigherPriorityTaskWoken must be initialised to pdFALSE. See the example code below.

-
`xEventGroupGetBits`

(xEventGroup)[Â¶](https://docs.espressif.com#c.xEventGroupGetBits) Returns the current value of the bits in an event group. This function cannot be used from an interrupt.

**Return**The event group bits at the time xEventGroupGetBits() was called.

**Parameters**`xEventGroup`

: The event group being queried.

### Type Definitions[Â¶](https://docs.espressif.com#id15)

-
*typedef*void *`EventGroupHandle_t`

[Â¶](https://docs.espressif.com#_CPPv418EventGroupHandle_t) An event group is a collection of bits to which an application can assign a meaning. For example, an application may create an event group to convey the status of various CAN bus related events in which bit 0 might mean âA CAN

message has been received and is ready for processingâ, bit 1 might mean âThe application has queued a message that is ready for sending onto the CAN networkâ, and bit 2 might mean âIt is time to send a SYNC message onto the CAN networkâ etc. A task can then test the bit values to see which events are active, and optionally enter the Blocked state to wait for a specified bit or a group of specified bits to be active. To continue the CAN bus example, a CAN controlling task can enter the Blocked state (and therefore not consume any processing time) until either bit 0, bit 1 or bit 2 are active, at which time the bit that was actually active would inform the task which action it had to take (process a received message, send a message, or send a SYNC).

The event groups implementation contains intelligence to avoid race conditions that would otherwise occur were an application to use a simple variable for the same purpose. This is particularly important with respect to when a bit within an event group is to be cleared, and when bits have to be set and then tested atomically - as is the case where event groups are used to create a synchronisation point between multiple tasks (a ârendezvousâ). event_groups.h

Type by which event groups are referenced. For example, a call to xEventGroupCreate() returns an EventGroupHandle_t variable that can then be used as a parameter to other event group functions.

-
*typedef*TickType_t`EventBits_t`

[Â¶](https://docs.espressif.com#_CPPv411EventBits_t)
