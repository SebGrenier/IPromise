#pragma once

class BaseFunc
{
public:
	BaseFunc() {}
	virtual ~BaseFunc() = 0;

	template <typename R, typename ... Args>
	R operator () (Args... args)
	{

	}

protected:

};