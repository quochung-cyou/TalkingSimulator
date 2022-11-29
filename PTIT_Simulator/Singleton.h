#pragma once

template <class T> class Singleton {
public:
	static T* GetInstance() {
		if (s_instance == nullptr) s_instance = new T();
		return s_instance;
	}

	static bool HasInstance() {
		return s_instance != 0;
	}
	static void FreeInstance() {
		if (s_instance) delete s_instance;
	}
protected:
	Singleton() {}
	virtual ~Singleton() {
		delete s_instance;
	}
private:
	static T* s_instance;
};

template <class T> T* Singleton<T>::s_instance = nullptr;