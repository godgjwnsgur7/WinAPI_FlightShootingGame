#include "pch.h"

template <typename T>
class Singleton
{
private:
	static T* instance;

public:
	static T* GetInstance()
	{
		if (!instance)
			instance = new T;

		return instance;
	};
public:
	virtual ~Singleton() {};
	void DeleteSingleton()
	{
		delete instance;
		instance = nullptr;
	};
};