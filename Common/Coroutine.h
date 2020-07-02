#ifndef C_COROUTINE_H
#define C_COROUTINE_H

namespace BaseCore
{
	namespace Common
	{		
		#define COROUTINE_DEAD 0
		#define COROUTINE_READY 1
		#define COROUTINE_RUNNING 2
		#define COROUTINE_SUSPEND 3
		struct schedule;
		typedef void (*coroutine_func)(struct schedule *, void *ud);
		struct schedule * coroutine_open(void);
		void coroutine_close(struct schedule *);
		int coroutine_new(struct schedule *, coroutine_func, void *ud);//�����µ�Э�� 
		void coroutine_resume(struct schedule *, int id);//�ָ�Э�̵�����״̬
		int coroutine_status(struct schedule *, int id);
		int coroutine_running(struct schedule *);
		void coroutine_yield(struct schedule *);//����Э��
	}
}

#endif
