// Pokemon Showdown incoming messages
// Copyright (C) 2018 David Stone
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

#include <iostream>
#include <string_view>

namespace technicalmachine {
namespace ps {
namespace detail {

constexpr auto separator_size(char) {
	return 1U;
}
constexpr auto separator_size(std::string_view const separator) {
	return separator.size();
}

template<typename Separator>
constexpr auto split(std::string_view str, Separator const separator) {
	auto const index = str.find(separator);
	if (index == std::string_view::npos) {
		return std::pair(str, std::string_view{});
	}
	return std::pair(str.substr(0, index), str.substr(index + separator_size(separator)));
}

}	// namespace detail

// TODO: Maybe something with iterators?
template<typename Separator>
struct BufferView {
	static_assert(std::is_same_v<Separator, char> or std::is_same_v<Separator, std::string_view>);

	constexpr BufferView(std::string_view buffer, Separator const separator):
		m_buffer(buffer),
		m_separator(separator)
	{
	}
	
	template<typename S>
	constexpr auto next(S const separator) -> std::string_view {
		auto const [first, second] = detail::split(m_buffer, separator);
		m_buffer = second;
		return first;
	}
	constexpr auto next() -> std::string_view {
		return next(m_separator);
	}
	constexpr auto remainder() const {
		return m_buffer;
	}
	
private:
	std::string_view m_buffer;
	Separator m_separator;
};

BufferView(std::string_view, char const *) -> BufferView<std::string_view>;

struct InMessage {
	explicit constexpr InMessage(std::string_view const room, BufferView<char> view):
		m_room(room),
		// Because messages start with a '|', discard first empty string
		m_type([&]{
			auto const discarded = view.next();
			if (!discarded.empty()) {
				std::cerr << "Expected empty string, got " << discarded << '\n';
			}
			return view.next();
		}()),
		m_view(view)
	{
	}

	constexpr auto room() const noexcept {
		return m_room;
	}
	constexpr auto type() const noexcept {
		return m_type;
	}
	template<typename Separator>
	constexpr auto next(Separator const separator) {
		return m_view.next(separator);
	}
	constexpr auto next() {
		return m_view.next();
	}
	constexpr auto remainder() const noexcept {
		return m_view.remainder();
	}

private:
	std::string_view m_room;
	std::string_view m_type;
	BufferView<char> m_view;
};

}	// namespace ps
}	// namespace technicalmachine
