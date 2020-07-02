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

		struct schedule // Э�̵����������ڹ���Э��
		{               
			char stack[STACK_SIZE];     // ���ڱ��浱ǰ��ջ��Ϣ
			ucontext_t main;            // ���ڱ�����������������
			int nco;                    // ��ǰЭ�̵�����
			int cap;                    // ��ǰschedule����Э�̵�����������Э��������ϵͳ�ᶯ̬��չ��ÿ��*2��
			int running;                // ��ǰ�������е�Э�̵�id
			struct coroutine **co;      // ��λ���飬���浱ǰϵͳ��Э�̶�Ӧ�Ľṹ��
		};

		struct coroutine // Э�̽ṹ��
		{              
			coroutine_func func;        // Э�����еĺ������൱�ڶ��߳���ָ���Ĺ�������
			void *ud;                   // ���������Ĳ���
			ucontext_t ctx;             // Э�̵�������
			struct schedule * sch;      // ��Ӧ��schedule
			ptrdiff_t cap;              // ��ǰջ������
			ptrdiff_t size;             // ջ��ʹ�ÿռ��С
			int status;                 // Э�̵�״̬���궨��COROUTINE_DEAD��COROUTINE_READY��COROUTINE_RUNNING��COROUTINE_SUSPEND
			char *stack;                // ջָ�룬ջ��ͨ��malloc��̬����ģ�������Э�����ߵ�ʱ�򱣴�Э�̵�ջ��Ϣ������˵��Ҫ�Լ�ȥ����ÿ��Э�̵�������
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
			if (S->nco >= S->cap) // ��Э�̵������Ŀռ䲻����ʱ�������չ
			{  
				int id = S->cap;
				S->co = (coroutine **)realloc(S->co, S->cap * 2 * sizeof(struct coroutine *));  // ��չΪԭ����2��
				memset(S->co + S->cap , 0 , sizeof(struct coroutine *) * S->cap);
				S->co[S->cap] = co;
				S->cap *= 2;     // ��չΪԭ��������
				++S->nco;
				return id;
			} 
			else 
			{
				int i;
				for (i=0;i<S->cap;i++) 
				{   // �ҵ���ǰ���õ�id������ͨ��forѭ��һ�������ң���Э�������Ƚ϶��ʱ��Ч����ԱȽϵ�
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
			case COROUTINE_READY:        // �½���Э�̴���READY״̬����û�п�ʼ����
				getcontext(&C->ctx);     // ��ȡ�����ģ�������Ҫ��������ͨ��getcontext���һ����ʼ������ucontext_t�ṹ�壬��������������г�ʼ��
				C->ctx.uc_stack.ss_sp = S->stack;      // ָ��Э������ʱ��ջ�����е�ջ��Ϣ���ᱣ�������
				C->ctx.uc_stack.ss_size = STACK_SIZE;  // ջ�Ĵ�С
				C->ctx.uc_link = &S->main;             // Э���˳�ʱ���ص������ģ�һ��Э���˳�ʱ��Ҫ���ص�main�����ϴ�ִ�еĵط�
				S->running = id;                       // ��¼��ǰ���е�Э��id
				C->status = COROUTINE_RUNNING;         // ��ʶΪ����״̬
				// ��ʼ��ucontext�ṹ������ָ����Ӧ�����к���mainfunc��mainfunc�����Э�̶�Ӧ�Ĺ�������
				makecontext(&C->ctx, (void (*)(void)) mainfunc, 2, (uint32_t)ptr, (uint32_t)(ptr>>32));
				swapcontext(&S->main, &C->ctx);// �л���Э��C�������ģ����ҰѾɵ�״̬�������ı��浽S->main�У����ڷ���main������
				break;
			case COROUTINE_SUSPEND:
				memcpy(S->stack + STACK_SIZE - C->size, C->stack, C->size); // ��Э��C�������ģ�ջ��Ϣ��������S->stack����ΪC->ctx.uc_stack.ss_sp = S->stack������Ҫ���лָ�
				S->running = id;
				C->status = COROUTINE_RUNNING;
				swapcontext(&S->main, &C->ctx);        // �л���Э��C�������ģ����ҰѾɵ�״̬�������ı��浽S->main�У����ڷ���main������
				printf("exit id:%d \n",id);
				break;
			default:
				assert(0);
			}
		}

		//����Э��ջ�ĺ���
		static void _save_stack(struct coroutine *C, char *top) 
		{
			char dummy = 0;                         // ����һ����ʱ���������ڻ�ȡ��ǰջ�Ķ��˵ĵ�ַ��Ҫ֪������ջ������������
			assert(top - &dummy <= STACK_SIZE);     // ��ȡ��ǰջ���õĿռ��С
			if (C->cap < top - &dummy) 
			{
				free(C->stack);
				C->cap = top-&dummy;
				C->stack = (char *)malloc(C->cap);          // ����ռ����ڱ���Э��C�Լ���ջ��Ϣ����ΪҪ�л�������Э�̣�����ÿ��Э���ڹ����ʱ��Ҫ���Ա����Լ���ջ��Ϣ
			}
			C->size = top - &dummy;
			memcpy(C->stack, &dummy, C->size);      // ����Э��C��ջ��Ϣ��ջ��Ϣԭ��������S->statc�У����Ҵ�&dummy��ַ��S->stack + STACK_SIZE��ַ�ǵ�ǰջ����������������Կ����Ʒ������ı�̹���
		}

		void coroutine_yield(struct schedule * S) 
		{
			int id = S->running;
			assert(id >= 0);
			struct coroutine * C = S->co[id];
			assert((char *)&C > S->stack);
			_save_stack(C,S->stack + STACK_SIZE);   // ����Э��C�������� 
			C->status = COROUTINE_SUSPEND;          // ��Э�̵�״̬��־Ϊ����
			S->running = -1;
			swapcontext(&C->ctx , &S->main);        // �л���main����
		}

	}
}
