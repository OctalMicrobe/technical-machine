# Warnings if building with gcc
# Copyright (C) 2012 David Stone
#
# This file is part of Technical Machine.
#
# Technical Machine is free software: you can redistribute it and / or modify
# it under the terms of the GNU Affero General Public License as
# published by the Free Software Foundation, either version 3 of the
# License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU Affero General Public License for more details.
#
# You should have received a copy of the GNU Affero General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.


# -Wabi is not needed because I'm not combining binaries from different
# compilers.
#
# -Waggregate-return is not something that I consider an error. For instance,
# it triggers when using a range-based for loop on a vector of classes. Return
# value optimization should take care of any negative effects of this.
#
# -Wconversion triggers on this code: `short n = 0; n += 2;` The implicit
# conversion to int causes a warning when it's then converted back to its
# target type.
#
# -Weffc++ includes a warning if all data members are not initialized in the
# initializer list. I intentionally do not do this in many cases, so the set of
# warnings is too cluttered to be useful. It's helpful to turn on every once in
# a while and scan for other warnings, though (such as non-virtual destructors
# of base classes). This would be more useful as a collection of warnings (like
# -Wall) instead of a single warning on its own.
#
# -Wfloat-equal warns for safe equality comparisons (in particular, comparison
# with a non-computed value of -1). An example in my code where I use this is
# that I have a vector of float. I go through this vector, and there are some
# elements I cannot evaluate yet what they should be, so I set them to -1.0f
# (since my problem only uses positive numbers, -1 is out of the domain). I
# later go through and update -1.0f values. It does not easily lend itself to a
# different method of operation.
#
# -Winline is absent because I don't use the inline keyword for optimization
# purposes, just to define functions inline in headers. I don't care if the
# optimizer actually inlines it. This warning also complains if it can't inline
# a function declared in a class body (such as an empty virtual destructor).
#
# -Winvalid-pch is missing because I don't use precompiled headers.
#
# -Wmissing-format-attribute is not used because I do not use gnu extensions.
# Same for -Wsuggest-attribute and several others.
#
# -Wnormalized=nfc is already the default option, and looks to be the best.
#
# -Wpadded is turned on occasionally to optimize the layout of classes, but it
# is not left on because not all classes have enough elements to remove padding
# at the end. In theory I could get some extra variables for 'free', but it's
# not worth the extra effort of maintaining that (if my class size changes,
# it's not easy to remove those previously free variables).
#
# -Wstack-protector is not used because I do not use -fstack-protector.
#
# -Wstrict-aliasing=3 is turned on by -Wall and is the most accurate, but it
# looks like level 1 and 2 give more warnings. In theory a lower level is a
# 'stronger' warning, but it's at the cost of more false positives.
#
# -Wswitch-default seems pointless (I don't always want a default case if I've
# enumerated all possibilities explicitly). I suppose some people may have need
# of it, but I do not. I could see turning on this warning and putting
# something like assert (false) into the default case, which I may try.
#
# -Wswitch-enum isn't behavior that I want. I don't want to handle every switch
# statement explicitly. It would be useful if the language had some mechanism
# to activate this on specified switch statements (to ensure that future
# changes to the enum are handled everywhere that they need to be), but it's
# overkill for an "all-or-nothing" setting.
#
# -Wunsafe-loop-optimizations causes too many spurious warnings. It may be
# useful to apply this one periodically and manually verify the results. As an
# example, it generated this warning in my code when I looped over all elements
# in a vector to apply a set of functions to them (using the range-based for
# loop).  It is also warning for the constructor of a const array of const
# std::string (where this is no loop in user code).
#
# -Wzero-as-null-pointer-constant and -Wuseless-cast are GCC-4.7-only warnings,
# which I will add when I transition to GCC 4.7.

# Add -Wold-style-cast when I transition to my byte swapping library and
# rewrite the Rijndael implementation to use modern C++ techniques, rather than
# just being a C program with .cpp as the extension.

warnings = ['-Wall', '-Wextra', '-Wcast-align', '-Wcast-qual', '-Wctor-dtor-privacy', '-Wformat=2', '-Winit-self', '-Wlogical-op', '-Wmissing-declarations', '-Wmissing-include-dirs', '-Wnoexcept', '-Woverloaded-virtual', '-Wredundant-decls', '-Wshadow', '-Wsign-conversion', '-Wsign-promo', '-Wstrict-null-sentinel', '-Wstrict-overflow=5', '-Wswitch-default', '-Wundef', '-Werror', '-Wno-unused-parameter', '-Wno-unused-variable', '-Wno-unused-but-set-variable']
# I have to set -pedantic to be a "debug" warning because it conflicts with
# -ffast-math on my system.
warnings_debug = ['-pedantic']
warnings_optimized = ['-Wdisabled-optimization']
