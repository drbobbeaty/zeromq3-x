/*
    Copyright (c) 2007-2009 FastMQ Inc.

    This file is part of 0MQ.

    0MQ is free software; you can redistribute it and/or modify it under
    the terms of the Lesser GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    0MQ is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    Lesser GNU General Public License for more details.

    You should have received a copy of the Lesser GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __ZS_CONFIG_HPP_INCLUDED__
#define __ZS_CONFIG_HPP_INCLUDED__

namespace zs
{

    //  Compile-time settings.

    enum 
    {

        //  Number of new messages in message pipe needed to trigger new memory
        //  allocation. Setting this parameter to 256 decreases the impact of
        //  memory allocation by approximately 99.6%
        message_pipe_granularity = 256,

        //  Number of new commands in command pipe needed to trigger new memory
        //  allocation. The number should  be kept low to decrease the memory
        //  footprint of dispatcher.
        command_pipe_granularity = 4,

        //  Maximal batching size for engines with receiving functionality.
        //  So, if there are 10 messages that fit into the batch size, all of
        //  them may be read by a single 'recv' system call, thus avoiding
        //  unnecessary network stack traversals.
        in_batch_size = 8192,

        //  Maximal batching size for engines with sending functionality.
        //  So, if there are 10 messages that fit into the batch size, all of
        //  them may be written by a single 'send' system call, thus avoiding
        //  unnecessary network stack traversals.
        out_batch_size = 8192,        

        //  Maximum number of events the I/O thread can process in one go.
        max_io_events = 256,

        //  Maximal wait time for a timer (milliseconds).
        max_timer_period = 100,

        //  Maximal delay to process command in API thread (in CPU ticks).
        //  3,000,000 ticks equals to 1 - 2 milliseconds on current CPUs.
        max_command_delay = 3000000,

        //  Maximal number of non-accepted connections that can be held by
        //  TCP listener object.
        tcp_connection_backlog = 10

    };

}

#endif
