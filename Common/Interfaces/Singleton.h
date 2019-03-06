#pragma once


template<class NativeType>
class Singletone abstract
{
protected:
	Singletone() = default;
	virtual ~Singletone() = default;

	Singletone(Singletone&) = delete;
	Singletone(Singletone&&) = delete;

public:
	static NativeType& Instance()
	{
		static NativeType instance;
		return instance;
	}
};
