#pragma once

#include "BaseFunc.hpp"
#include <functional>

template <typename R, typename ... Args>
class TemplateFunc : BaseFunc
{
	explicit TemplateFunc(std::function<R(Args...)> f)
		: BaseFunc()
		, _f(f)
	{ }

private:
	std::function<R(Args...)> _f;
};