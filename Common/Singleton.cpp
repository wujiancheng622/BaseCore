#ifndef SINGLETON_H_
#define SINGLETON_H_ 

#include <cstdio>
#include "CrossPlatform.h"
#include "Mutex.h"




namespace BaseCore
{

	namespace Common
	{

		template <typename T>  
		class DLL_CLASS  Singleton{  
		private:  

			static T * m_pInstance;
			static BaseCore::Threads::Mutex m_mutex;
		protected:  
			Singleton()  
			{  

			}  
			virtual ~Singleton()
			{
				
			}  
		public:  
			static T* Instance();
			static void Release();
			static bool IsCreated();
		};  

		template <typename T>
		bool BaseCore::Common::Singleton<T>::IsCreated()
		{
			BaseCore::Threads::MutexGuard mutexGuard(m_mutex());
			return m_pInstance != NULL;
		}



		template<typename T>  
		T*  Singleton<T>::m_pInstance=NULL;



		template<typename T>  
		BaseCore::Threads::Mutex Singleton<T>::m_mutex;


		template <typename T>
		T* Singleton<T>::Instance()
		{
			
			BaseCore::Threads::MutexGuard mutexGuard(m_mutex());
			if(NULL==m_pInstance )
			{
				m_pInstance=new T;
			}

			return m_pInstance;  
		}

		template <typename T>
		void Singleton<T>::Release()
		{
			BaseCore::Threads::MutexGuard mutexGuard(m_mutex());
			if(m_pInstance)
			{
				delete m_pInstance;
				m_pInstance=NULL;
			}
		}

	}

}




#endif //SINGLETON_H_


