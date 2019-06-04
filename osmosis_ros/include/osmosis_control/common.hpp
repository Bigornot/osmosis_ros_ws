/*
 * Copyright 2017 ONERA
 *
 * This file is part of the MAUVE Unicycle Control project.
 *
 * MAUVE Unicycle Control is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * MAUVE Unicycle Control is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with MAUVE.  If not, see <https://www.gnu.org/licenses/gpl-3.0>.
 */
#ifndef MAUVE_UNICYCLE_CONTROL_COMMON_HPP
#define MAUVE_UNICYCLE_CONTROL_COMMON_HPP

    /**
     * Get sign of a value
     * \tparam T value type
     * \param val value
     * \return sign of \a value
     */
    template <typename T> int sign(T val) {
      return (T(0) < val) - (val < T(0));
    };

#endif // MAUVE_UNICYCLE_CONTROL_COMMON_HPP
