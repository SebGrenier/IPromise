#pragma once
#include <functional>

class Promise
{
	template <typename ... ResolveTypes>
	using ResolveFunc = std::function<void(ResolveTypes...)>;

	template <typename ... RejectTypes>
	using RejectFunc = std::function<void(RejectTypes...)>;

public:
	Promise() = delete;

	template <typename ... ResolveTypes, typename ... RejectTypes>
	explicit Promise(std::function<void(ResolveFunc<ResolveTypes...>, RejectFunc<RejectTypes...>)> &func)
		: _state(State::INPROGRESS)
	{
		ResolveFunc<ResolveTypes...> resolve = [&](auto ...)
		{
			if (_state != State::INPROGRESS)
				return;

			_state = State::RESOLVED;


			// Go through all then functions
		};
	}

	template <typename ... ResolveTypes, typename ... RejectTypes>
	typedef void(*PromiseFunc)(void(*resolve)(ResolveTypes...), void(*reject)(RejectTypes...));

	template <typename ... ResolveTypes, typename ... RejectTypes>
	explicit Promise(PromiseFunc<ResolveTypes..., RejectTypes...> func)
		: _state(State::INPROGRESS)
	{

	}

	Promise(const Promise &rhs) = delete;

	template <typename ... ResolveTypes, typename ... RejectTypes>
	Promise<ResolveTypes..., RejectTypes...> then(std::function<void(ResolveFunc<ResolveTypes...>, RejectFunc<RejectTypes...>)> &func)
	{

	}

private:

	enum class State
	{
		INPROGRESS,
		RESOLVED,
		REJECTED,
	};

	State _state;
};
