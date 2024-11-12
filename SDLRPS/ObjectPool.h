#ifndef OBJECTPOOL_H
#define OBJECTPOOL_H

#include "StandardIncludes.h"

template<class T>
class ObjectPool
{
public:
	ObjectPool() {}
	virtual ~ObjectPool()
	{
		for (unsigned int count = 0; count < m_all.size(); count++)
		{
			cout << "Deleting pool object " << typeid(T).name() << endl;
			delete m_all[count];
		}
		m_all.clear();
		m_available.clear();
	}

	T* GetResource()
	{
		if (m_available.empty())
		{
			cout << "Creating New. " << typeid(T).name() << endl;
			T* resource = new T();
			m_all.push_back(resource);
			return resource;
		}
		else
		{
			cout << "Reusing existing. " << typeid(T).name() << endl;
			T* resourse = m_available[0];
			m_available.erase(m_available.begin());
			return resourse;
		}
	}

	void ReleaseResource(T* _object)
	{
		m_available.push_back(_object);
	}

private:
	vector<T*> m_available;
	vector<T*> m_all;
};

#endif OBJECTPOOL_H

