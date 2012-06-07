// TimeSource.hh --- The Time
//
// Copyright (C) 2012 Rob Caelers <robc@krandor.nl>
// All rights reserved.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#ifndef TIMESOURCE_HH
#define TIMESOURCE_HH

#include "ITimeSource.hh"

namespace workrave
{
  namespace utils
  {
    //! A source of time.
    class TimeSource
    {
    public:
      //! Returns the time of this source.
      static time_t get_time();

    public:
      static ITimeSource *source;
    };
  }
}

#endif // TIMESOURCE_HH