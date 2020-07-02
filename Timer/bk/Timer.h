#ifndef TIMER_H_
#define TIMER_H_


#include "CrossPlatform.h"
#include <string>

namespace BaseCore
{
	namespace Clock
	{

		/*
			定时器类
			使用者需要派生自TimerListener类，并实现OnTimeOut函数
		*/
		class DLL_CLASS  TimerListener
		{
		public:
		
			/** 定时器类回调函数
			* @param[in] hHandle用来指示是哪个定时器调用的
			* return void
			*/
			virtual void OnTimeOut(int hHandle)=0;
		};

		

		class TimerHelper;
		class DLL_CLASS  Timer
		{
		public:
			Timer(TimerListener *pListener);
			virtual ~Timer();

			/** 启动定时器  如果多次调用则将覆盖原有的定时间隔和定时时间，不会在原来的基础上叠加定时次数
			 * @param[in] intervalMilSec: 定时器的间隔时间一毫秒为单位
			 * @param[in] times：定时次数,如果是0标识定时次数不限
			 * return void
			 */
			void Start(int intervalMilSec=3000,int times=0);

			/**  停止定时器
			 * retun void
			 */
			void Stop();
			
			
			/** 设置定时器句柄，主要用来区分在OnTimeOut回调函数中区分不同定时器
			 * @param[in] hHandle: 定时器句柄
			 * return void
			 */
			void SetHandle(int hHandle);
			
			
			/** 获取定时器句柄
			 * return void
			 */
			int GetHandle();
			
			
			

			/** 获取当前时间
			 * return std::string :当前时间
			 */
			static std::string LocalTime();

		private:
			TimerHelper *m_pDataHelper;

		};

	}
}


#endif //TIMER_H_