#ifndef TIMER_H_
#define TIMER_H_


#include "CrossPlatform.h"
#include <string>

namespace BaseCore
{
	namespace Clock
	{

		/*
			��ʱ����
			ʹ������Ҫ������TimerListener�࣬��ʵ��OnTimeOut����
		*/
		class DLL_CLASS  TimerListener
		{
		public:
		
			/** ��ʱ����ص�����
			* @param[in] hHandle����ָʾ���ĸ���ʱ�����õ�
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

			/** ������ʱ��  �����ε����򽫸���ԭ�еĶ�ʱ����Ͷ�ʱʱ�䣬������ԭ���Ļ����ϵ��Ӷ�ʱ����
			 * @param[in] intervalMilSec: ��ʱ���ļ��ʱ��һ����Ϊ��λ
			 * @param[in] times����ʱ����,�����0��ʶ��ʱ��������
			 * return void
			 */
			void Start(int intervalMilSec=3000,int times=0);

			/**  ֹͣ��ʱ��
			 * retun void
			 */
			void Stop();
			
			
			/** ���ö�ʱ���������Ҫ����������OnTimeOut�ص����������ֲ�ͬ��ʱ��
			 * @param[in] hHandle: ��ʱ�����
			 * return void
			 */
			void SetHandle(int hHandle);
			
			
			/** ��ȡ��ʱ�����
			 * return void
			 */
			int GetHandle();
			
			
			

			/** ��ȡ��ǰʱ��
			 * return std::string :��ǰʱ��
			 */
			static std::string LocalTime();

		private:
			TimerHelper *m_pDataHelper;

		};

	}
}


#endif //TIMER_H_