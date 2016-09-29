#pragma once
#include <functional>


class Promise
{
public:
	template <typename ...ResolveTypes>
	using ResolveFunc = std::function<void(ResolveTypes...)>;
	template <typename ...RejectTypes>
	using RejectFunc = std::function<void(RejectTypes...)>;
	template <typename ... ResolveTypes, typename ... RejectTypes>
	typedef void(*PromiseFunc)(void(*resolve)(ResolveTypes...), void(*reject)(RejectTypes...));

	template <typename ThenResultType, typename ...ResolveTypes>
	using ThenResolveFunc = std::function<ThenResultType(ResolveTypes...)>;
	template <typename ThenResultType, typename ...RejectTypes>
	using ThenRejectFunc = std::function<ThenResultType(RejectTypes...)>;

	Promise() = delete;

	template <typename ... ResolveTypes, typename ... RejectTypes>
	explicit Promise(std::function<void(ResolveFunc<ResolveTypes>, RejectFunc<RejectTypes>)> &func)
		: _state(State::INPROGRESS)
	{
		ResolveFunc<ResolveTypes> resolve = [&](auto ...)
		{
			if (_state != State::INPROGRESS)
				return;

			_state = State::RESOLVED;


			// Go through all then.resolve functions
		};

		RejectFunc<RejectTypes> reject = [&](auto ...)
		{
			if (_state != State::INPROGRESS)
				return;

			_state = State::REJECTED;

			// Go through all the then.reject functions
		};

		func(resolve, reject);
	}

	template <typename ... ResolveTypes, typename ... RejectTypes>
	explicit Promise(PromiseFunc<ResolveTypes, RejectTypes> func)
		: _state(State::INPROGRESS)
	{

	}

	Promise(const Promise &rhs) = delete;

	template <typename ThenResultType, typename ThenRejectType, typename ... ResolveTypes, typename ... RejectTypes>
	Promise then(ThenResolveFunc<ThenResultType, ResolveTypes...> &resolve, ThenRejectFunc<ThenRejectType, RejectTypes...> &reject)
	{
		if (_state == State::RESOLVED)
			return Promise(resolve);

		if (_state == State::REJECTED)
			return Promise(reject);


		std::function<void(ResolveFunc<ThenResultType>, RejectFunc<ThenRejectType>)> func = [&](ResolveFunc<ThenResultType> &inner_resolve, RejectFunc<ThenRejectType> &inner_reject) -> void
		{
			auto reject_wrap = [&](RejectTypes&&... reject_args)
			{
				ThenRejectType result = reject(std::forward<RejectTypes>(reject_args)...);
				inner_reject(result);
			};
			auto resolve_wrap = [&](ResolveTypes&& ... resolve_args)
			{
				ThenResultType result = resolve(std::forward<ResolveTypes>(resolve_args)...);
				inner_resolve(result);
			};

			// Store these functions inside then and reject callbacks
		};

		return Promise(func);
	}

private:

	enum class State
	{
		INPROGRESS,
		RESOLVED,
		REJECTED,
	};

	State _state;

	// std::vector<Func> _thens;
	// std::vector<Func> _rejects;
	// Any _value;
};
