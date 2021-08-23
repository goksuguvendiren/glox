//
// Auto-generated by Goksu Guvendiren Bakir. 
//

#pragma once

#include <utility>
#include "../token.hpp"
#include "expression.hpp"

namespace glox::repr
{
	template <class T>
	class binary : public repr::expression<T>
	{
	public:
		binary(
		std::unique_ptr<repr::expression<T>> expr0,
		std::unique_ptr<repr::opr<T>> expr1,
		std::unique_ptr<repr::expression<T>> expr2
		) : 
			expr0(std::move(expr0)),
			expr1(std::move(expr1)),
			expr2(std::move(expr2))
		{}

~binary() = default;

	private:
		std::unique_ptr<repr::expression<T>> expr0;
		std::unique_ptr<repr::opr<T>> expr1;
		std::unique_ptr<repr::expression<T>> expr2;

		T accept(const visitor<T>& visitor) const
		{
			return visitor.visit_binary_expr(*this);
		}
	};
}