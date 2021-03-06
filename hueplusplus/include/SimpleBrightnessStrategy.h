/**
        \file SimpleBrightnessStrategy.h
        Copyright Notice\n
        Copyright (C) 2017  Jan Rogall		- developer\n
        Copyright (C) 2017  Moritz Wirger	- developer\n

        This program is free software; you can redistribute it and/or modify
        it under the terms of the GNU General Public License as published by
        the Free Software Foundation; either version 3 of the License, or
        (at your option) any later version.
        This program is distributed in the hope that it will be useful,
        but WITHOUT ANY WARRANTY; without even the implied warranty of
        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
        GNU General Public License for more details.
        You should have received a copy of the GNU General Public License
        along with this program; if not, write to the Free Software Foundation,
        Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
**/

#ifndef _SIMPLE_BRIGHTNESS_STRATEGY_H
#define _SIMPLE_BRIGHTNESS_STRATEGY_H

#include "BrightnessStrategy.h"
#include "HueLight.h"

//! Class implementing the functions of BrightnessStrategy
class SimpleBrightnessStrategy : public BrightnessStrategy {
public:
  //! \brief Function for changing a lights brightness with a specified
  //! transition.
  //!
  //! \param bri The brightness raning from 0 = off to 255 = fully lit
  //! \param transition The time it takes to fade to the new brightness in
  //! multiples of 100ms, 4 = 400ms and should be seen as the default \param
  //! light A reference of the light
  bool setBrightness(unsigned int bri, uint8_t transition,
                     HueLight &light) const override;
  //! \brief Function that returns the current brightness of the light
  //!
  //! Updates the lights state by calling refreshState()
  //! \param light A reference of the light
  //! \return Unsigned int representing the brightness
  unsigned int getBrightness(HueLight &light) const override;
  //! \brief Function that returns the current brightness of the light
  //!
  //! \note This does not update the lights state
  //! \param light A const reference of the light
  //! \return Unsigned int representing the brightness
  unsigned int getBrightness(const HueLight &light) const override;
};

#endif
