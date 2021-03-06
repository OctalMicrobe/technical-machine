// Class to properly do integer multiplication / division
// Copyright David Stone 2020.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <tm/operators.hpp>

#include <bounded/integer.hpp>

#include <limits>
#include <string>

namespace technicalmachine {
using namespace bounded::literal;

template<typename Numerator, typename Denominator>
struct rational;

// Since we cannot use class template argument deduction inside the class body
template<typename Numerator, typename Denominator>
constexpr auto make_rational(Numerator const numerator, Denominator const denominator) {
	return rational<Numerator, Denominator>(numerator, denominator);
}

template<typename Numerator, typename Denominator>
struct rational {
private:
	Numerator m_numerator;
	Denominator m_denominator;
	using numerator_type = Numerator;
	using denominator_type = Denominator;
public:
	constexpr rational(Numerator const numerator, Denominator const denominator):
		m_numerator(numerator),
		m_denominator(denominator) {
	}
	
	template<typename N, typename D> requires(
		bounded::min_value<N> >= bounded::min_value<Numerator> and
		bounded::max_value<N> <= bounded::max_value<Numerator> and
		bounded::min_value<D> >= bounded::min_value<Denominator> and
		bounded::max_value<D> <= bounded::max_value<Denominator>
	)
	constexpr rational(rational<N, D> const other):
		m_numerator(other.numerator()),
		m_denominator(other.denominator())
	{
	}

	constexpr auto numerator() const {
		return m_numerator;
	}
	constexpr auto denominator() const {
		return m_denominator;
	}

	friend std::string to_string(rational const r) {
		using bounded::to_string;
		return to_string(r.numerator()) + " / " + to_string(r.denominator());
	}
	
	// Convert allows narrowing conversions, constructor does not
	template<typename T>
	constexpr T convert() const {
		return T(
			static_cast<typename T::numerator_type>(m_numerator),
			static_cast<typename T::denominator_type>(m_denominator)
		);
	}
	
	explicit constexpr operator double() const {
		return static_cast<double>(m_numerator) / static_cast<double>(m_denominator);
	}
	
	constexpr auto invert() const {
		return make_rational(m_denominator, m_numerator);
	}
};

template<typename Numerator, typename Denominator>
constexpr auto complement(rational<Numerator, Denominator> const r) {
	return rational(1_bi, 1_bi) - r;
}

template<typename N, typename D>
constexpr auto operator*(rational<N, D> const lhs, bounded::bounded_integer auto const rhs) {
	return rhs * lhs.numerator() / lhs.denominator();
}

template<typename N1, typename D1, typename N2, typename D2>
constexpr auto operator*(rational<N1, D1> const lhs, rational<N2, D2> const rhs) {
	return make_rational(lhs.numerator() * rhs.numerator(), lhs.denominator() * rhs.denominator());
}
template<typename N1, typename D1, typename N2, typename D2>
constexpr auto operator+(rational<N1, D1> const lhs, rational<N2, D2> const rhs) {
	return make_rational(
		lhs.numerator() * rhs.denominator() + rhs.numerator() * lhs.denominator(),
		lhs.denominator() * rhs.denominator()
	);
}
template<typename N1, typename D1, typename N2, typename D2>
constexpr auto operator-(rational<N1, D1> const lhs, rational<N2, D2> const rhs) {
	return make_rational(
		lhs.numerator() * rhs.denominator() - rhs.numerator() * lhs.denominator(),
		lhs.denominator() * rhs.denominator()
	);
}


template<typename N1, typename D1, typename N2, typename D2>
constexpr auto operator<=>(rational<N1, D1> const lhs, rational<N2, D2> const rhs) {
	return lhs.numerator() * rhs.denominator() <=> rhs.numerator() * lhs.denominator();
}

template<typename N, typename D>
constexpr auto operator<=>(rational<N, D> const lhs, bounded::bounded_integer auto const rhs) {
	return lhs.numerator() <=> rhs * lhs.denominator();
}

template<typename N1, typename D1, typename N2, typename D2>
constexpr auto operator==(rational<N1, D1> const lhs, rational<N2, D2> const rhs) -> bool {
	return lhs.numerator() * rhs.denominator() == rhs.numerator() * lhs.denominator();
}

template<typename N, typename D>
constexpr auto operator==(rational<N, D> const lhs, bounded::bounded_integer auto const rhs) -> bool {
	return lhs.numerator() == rhs * lhs.denominator();
}

template<typename N, typename D>
constexpr auto operator*(bounded::bounded_integer auto const lhs, rational<N, D> const rhs) {
	return rhs * lhs;
}


template<typename N, typename D>
constexpr auto operator/(bounded::bounded_integer auto const lhs, rational<N, D> const rhs) {
	return lhs * rhs.invert();
}


template<typename N, typename D>
constexpr auto operator%(bounded::bounded_integer auto const lhs, rational<N, D> const rhs) {
	auto const quotient = lhs / rhs;
	return lhs - quotient * rhs;
}


}	// namespace technicalmachine

namespace std {

template<typename N1, typename D1, typename N2, typename D2>
struct common_type<technicalmachine::rational<N1, D1>, technicalmachine::rational<N2, D2>> {
private:
	using numerator = typename common_type<N1, N2>::type;
	using denominator = typename common_type<D1, D2>::type;
public:
	using type = technicalmachine::rational<numerator, denominator>;
};

template<typename N1, typename D1, typename N2, typename D2>
struct common_type<technicalmachine::rational<N1, D1> const, technicalmachine::rational<N2, D2>> {
private:
	using numerator = typename common_type<N1, N2>::type;
	using denominator = typename common_type<D1, D2>::type;
public:
	using type = technicalmachine::rational<numerator, denominator> const;
};

template<typename N1, typename D1, typename N2, typename D2>
struct common_type<technicalmachine::rational<N1, D1>, technicalmachine::rational<N2, D2> const> {
private:
	using numerator = typename common_type<N1, N2>::type;
	using denominator = typename common_type<D1, D2>::type;
public:
	using type = technicalmachine::rational<numerator, denominator> const;
};

template<typename N1, typename D1, typename N2, typename D2>
struct common_type<technicalmachine::rational<N1, D1> const, technicalmachine::rational<N2, D2> const> {
private:
	using numerator = typename common_type<N1, N2>::type;
	using denominator = typename common_type<D1, D2>::type;
public:
	using type = technicalmachine::rational<numerator, denominator> const;
};

}	// namespace std

