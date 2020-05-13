// Copyright (C) 2019 David Stone
//
// This file is part of Technical Machine.
//
// Technical Machine is free software: you can redistribute it and / or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

#pragma once

#include <tm/type/type.hpp>
#include <tm/ability.hpp>
#include <tm/generation.hpp>
#include <tm/item.hpp>
#include <tm/operators.hpp>
#include <tm/rational.hpp>

#include <bounded/integer.hpp>
#include <bounded/detail/variant/variant.hpp>

#include <cstdint>

namespace technicalmachine {

struct MutableActivePokemon;
struct Pokemon;
struct Weather;

enum class Statuses : uint8_t {
	clear,
	burn,
	freeze,
	paralysis,
	poison,
	toxic,
	sleep,
	rest
};

}	// namespace technicalmachine
namespace bounded {

template<>
inline constexpr auto min_value<technicalmachine::Statuses> = technicalmachine::Statuses();

template<>
inline constexpr auto max_value<technicalmachine::Statuses> = technicalmachine::Statuses::rest;

}	// namespace bounded
namespace technicalmachine {

struct Status {
private:
	struct Clear {
		friend auto operator==(Clear const &, Clear const &) -> bool = default;
	};
	struct Burn {
		friend auto operator==(Burn const &, Burn const &) -> bool = default;
	};
	struct Freeze {
		friend auto operator==(Freeze const &, Freeze const &) -> bool = default;
	};
	struct Paralysis {
		friend auto operator==(Paralysis const &, Paralysis const &) -> bool = default;
	};
	struct Poison {
		friend auto operator==(Poison const &, Poison const &) -> bool = default;
	};
	struct Toxic {
		friend auto operator==(Toxic const &, Toxic const &) -> bool = default;
	};
	struct Sleep {
		bounded::clamped_integer<0, 4> turns_slept = 0_bi;
		friend auto operator==(Sleep const &, Sleep const &) -> bool = default;
	};
	struct Rest {
		bounded::clamped_integer<0, 2> turns_slept = 0_bi;
		friend auto operator==(Rest const &, Rest const &) -> bool = default;
	};

public:
	constexpr Status() = default;
	explicit Status(Statuses const status);

	constexpr auto name() const {
		return static_cast<Statuses>(m_state.index());
	}
	
	constexpr Status & operator=(Statuses const status) & {
		*this = Status(status);
		return *this;
	}

	auto advance_from_move(Ability ability, bool clear) & -> void;

	// If the current status is sleep or rest, returns the probability the
	// status can change from sleeping to awake on this move. If the current
	// status is freeze, returns the probability of thawing. Returns 0.0 if the
	// Pokemon is not asleep or frozen or if, due to the sleep counter, they
	// will definitely not awaken.
	auto probability_of_clearing(Generation, Ability) const -> double;

	friend auto operator==(Status const &, Status const &) -> bool = default;

private:
	using State = bounded::variant<
		Clear,
		Burn,
		Freeze,
		Paralysis,
		Poison,
		Toxic,
		Sleep,
		Rest
	>;
	State m_state{Clear{}};
};


constexpr auto is_clear(Status const status) {
	return status.name() == Statuses::clear;
}
constexpr auto is_frozen(Status const status) {
	return status.name() == Statuses::freeze;
}
constexpr auto is_sleeping(Status const status) {
	switch (status.name()) {
		case Statuses::rest:
		case Statuses::sleep:
			return true;
		default:
			return false;
	}
}
constexpr auto is_sleeping_due_to_other(Status const status) {
	return status.name() == Statuses::sleep;
}
constexpr auto weakens_physical_attacks(Status const status) {
	return status.name() == Statuses::burn;
}
constexpr auto boosts_smellingsalt(Status const status) {
	return status.name() == Statuses::paralysis;
}

auto lowers_speed(Status status, Ability ability) -> bool;
auto boosts_facade(Status status) -> bool;


bool blocks_status(Ability ability, Ability other_ability, Statuses status, Weather weather);

constexpr auto blocks_status(Type const type, Statuses const status) {
	switch (status) {
		case Statuses::burn:
			return type == Type::Fire;
		case Statuses::freeze:
			return type == Type::Ice;
		case Statuses::poison:
		case Statuses::toxic:
			return type == Type::Poison or type == Type::Steel;
		default:
			return false;
	}
}

constexpr auto clears_status(Item const item, Statuses const status) -> bool {
	switch (item) {
		case Item::Ice_Berry:
		case Item::Rawst_Berry:
			return status == Statuses::burn;
		case Item::Aspear_Berry:
		case Item::Burnt_Berry:
			return status == Statuses::freeze;
		case Item::Cheri_Berry:
		case Item::PRZCureBerry:
			return status == Statuses::paralysis;
		case Item::Chesto_Berry:
		case Item::Mint_Berry:
			return status == Statuses::rest or status == Statuses::sleep;
		case Item::Pecha_Berry:
		case Item::PSNCureBerry:
			return status == Statuses::poison or status == Statuses::toxic;
		case Item::Lum_Berry:
		case Item::MiracleBerry:
			return true;
		default:
			return false;
	}
}

constexpr bool can_clear_status(Ability const ability, Status const status) {
	return ability == Ability::Shed_Skin and !is_clear(status);
}

constexpr bool boosts_defense(Ability const ability, Status const status) {
	return ability == Ability::Marvel_Scale and !is_clear(status);
}

}	// namespace technicalmachine
