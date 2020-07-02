#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stddef.h>
#include <string.h>
#include <stdint.h>
#include "Coroutine.h"

#if __APPLE__ && __MACH__
#include <sys/ucontext.h>
#else 
#include <ucontext.h>
#endif 


namespace BaseCore
{
	namespace Common
	{
		

#define STACK_SIZE (1024*1024)
#define DEFAULT_COROUTINE 16

		struct coroutine;

		struct schedule // 协程调度器，用于管理协程
		{               
			char stack[STACK_SIZE];     // 用于保存当前的栈信息
			ucontext_t main;            // 用于保存主函数的上下文
			int nco;                    // 当前协程的数量
			int cap;                    // 当前schedule容器协程的容量（最大的协程数量，系统会动态扩展，每次*2）
			int running;                // 当前正在运行的协程的id
			struct coroutine **co;      // 二位数组，保存当前系统的协程对应的结构体
		};

		struct coroutine // 协程结构体
		{              
			coroutine_func func;        // 协程运行的函数，相当于多线程中指定的工作函数
			void *ud;                   // 工作函数的参数
			ucontext_t ctx;             // 协程的上下文
			struct schedule * sch;      // 对应的schedule
			ptrdiff_t cap;              // 当前栈的容量
			ptrdiff_t size;             // 栈的使用空间大小
			int status;                 // 协程的状态，宏定义COROUTINE_DEAD，COROUTINE_READY，COROUTINE_RUNNING，COROUTINE_SUSPEND
			char *stack;                // 栈指针，栈是通过malloc动态分配的，用于在协程休眠的时候保存协程的栈信息，就是说需要自己去管理每个协程的上下文
		};


		struct coroutine * _co_new(struct schedule *S , coroutine_func func, void *ud) 
		{
			struct coroutine * co = (coroutine * )malloc(sizeof(*co));
			co->func = func;
			co->ud = ud;
			co->sch = S;
			co->cap = 0;
			co->size = 0;
			co->status = COROUTINE_READY;
			co->stack = NULL;
			return co;
		}

		void _co_delete(struct coroutine *co) 
		{
			free(co->stack);
			free(co);
		}

		struct schedule * coroutine_open(void) 
		{
			struct schedule *S = (schedule *)malloc(sizeof(*S));
			S->nco = 0;
			S->cap = DEFAULT_COROUTINE;
			S->running = -1;
			S->co = (coroutine **)malloc(sizeof(struct coroutine *) * S->cap);
			memset(S->co, 0, sizeof(struct coroutine *) * S->cap);
			return S;
		}

		void coroutine_close(struct schedule *S) 
		{
			int i;
			for (i=0;i<S->cap;i++) 
			{
				struct coroutine * co = S->co[i];
				if (co) 
				{
					//printf(" delete success \n");
					_co_delete(co);
				}
				else{
					//printf(" delete empty \n");
				}
			}
			free(S->co);
			S->co = NULL;
			free(S);
		}


		int coroutine_new(struct schedule *S, coroutine_func func, void *ud) 
		{
			struct coroutine *co = _co_new(S, func , ud);
			if (S->nco >= S->cap) // 当协程调度器的空间不够的时候进行扩展
			{  
				int id = S->cap;
				S->co = (coroutine **)realloc(S->co, S->cap * 2 * sizeof(struct coroutine *));  // 扩展为原来的2倍
				memset(S->co + S->cap , 0 , sizeof(struct coroutine *) * S->cap);
				S->co[S->cap] = co;
				S->cap *= 2;     // 扩展为原来的两倍
				++S->nco;
				return id;
			} 
			else 
			{
				int i;
				for (i=0;i<S->cap;i++) 
				{   // 找到当前可用的id，这里通过for循环一个个查找，当协程数量比较多的时候效率相对比较低
					int id = (i+S->nco) % S->cap;
					if (S->co[id] == NULL) 
					{
						S->co[id] = co;
						++S->nco;
						return id;
					}
				}
			}
			assert(0);
			return -1;
		}


		static void mainfunc(uint32_t low32, uint32_t hi32) 
		{
			uintptr_t ptr = (uintptr_t)low32 | ((uintptr_t)hi32 << 32);
			struct schedule *S = (struct schedule *)ptr;
			int id = S->running;
			struct coroutine *C = S->co[id];
			C->func(S,C->ud);
			_co_delete(C);
			S->co[id] = NULL;
			--S->nco;
			S->running = -1;
		}

		int coroutine_status(struct schedule * S, int id) 
		{
			assert(id>=0 && id < S->cap);
			if (S->co[id] == NULL) 
			{
				return COROUTINE_DEAD;
			}
			return S->co[id]->status;
		}

		int coroutine_running(struct schedule * S) 
		{
			return S->running;
		}

		void coroutine_resume(struct schedule * S, int id) 
		{
			assert(S->running == -1);
			assert(id >=0 && id < S->cap);
			struct coroutine *C = S->co[id];
			if (C == NULL)
				return;
			int status = C->status;
			uintptr_t ptr = (uintptr_t)S;
			switch(status) 
			{
			case COROUTINE_READY:        // 新建的协程处于READY状态，并没有开始运行
				getcontext(&C->ctx);     // 获取上下文，这里主要的作用是通过getcontext获得一个初始化话的ucontext_t结构体，下面会继续对其进行初始化
				C->ctx.uc_stack.ss_sp = S->stack;      // 指定协程运行时的栈（所有的栈信息都会保存在这里）
				C->ctx.uc_stack.ss_size = STACK_SIZE;  // 栈的大小
				C->ctx.uc_link = &S->main;             // 协程退出时返回的上下文，一般协程退出时需要返回到main函数上次执行的地方
				S->running = id;                       // 记录当前运行的协程id
				C->status = COROUTINE_RUNNING;         // 标识为运行状态
				// 初始化ucontext结构，并且指定对应的运行函数mainfunc，mainfunc会调用协程对应的工作函数
				makecontext(&C->ctx, (void (*)(void)) mainfunc, 2, (uint32_t)ptr, (uint32_t)(ptr>>32));
				swapcontext(&S->main, &C->ctx);// 切换到协程C的上下文，并且把旧的状态的上下文保存到S->main中（用于返回main函数）
				break;
			case COROUTINE_SUSPEND:
				memcpy(S->stack + STACK_SIZE - C->size, C->stack, C->size); // 将协程C的上下文（栈信息）拷贝到S->stack，因为C->ctx.uc_stack.ss_sp = S->stack，所以要进行恢复
				S->running = id;
				C->status = COROUTINE_RUNNING;
				swapcontext(&S->main, &C->ctx);        // 切换到协程C的上下文，并且把旧的状态的上下文保存到S->main中（用于返回main函数）
				printf("exit id:%d \n",id);
				break;
			default:
				assert(0);
			}
		}

		//保存协程栈的函数
		static void _save_stack(struct coroutine *C, char *top) 
		{
			char dummy = 0;                         // 定义一个临时变量，用于获取当前栈的顶端的地址，要知道的是栈是往下增长的
			assert(top - &dummy <= STACK_SIZE);     // 获取当前栈所用的空间大小
			if (C->cap < top - &dummy) 
			{
				free(C->stack);
				C->cap = top-&dummy;
				C->stack = (char *)malloc(C->cap);          // 申请空间用于保存协程C自己的栈信息，因为要切换到其他协程，所以每个协程在挂起的时候都要各自保存自己的栈信息
			}
			C->size = top - &dummy;
			memcpy(C->stack, &dummy, C->size);      // 保存协程C的栈信息，栈信息原本保存在S->statc中，并且从&dummy地址到S->stack + STACK_SIZE地址是当前栈的情况，从这里足以看出云风大哥深厚的编程功力
		}

		void coroutine_yield(struct schedule * S) 
		{
			int id = S->running;
			assert(id >= 0);
			struct coroutine * C = S->co[id];
			assert((char *)&C > S->stack);
			_save_stack(C,S->stack + STACK_SIZE);   // 保存协程C的上下文 
			C->status = COROUTINE_SUSPEND;          // 把协程的状态标志为挂起
			S->running = -1;
			swapcontext(&C->ctx , &S->main);        // 切换会main函数
		}

	}
}
