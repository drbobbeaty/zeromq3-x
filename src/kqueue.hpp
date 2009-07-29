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

#ifndef __ZS_KQUEUE_HPP_INCLUDED__
#define __ZS_KQUEUE_HPP_INCLUDED__

#include "platform.hpp"

#if defined ZS_HAVE_FREEBSD || defined ZS_HAVE_OPENBSD || defined ZS_HAVE_OSX

#include <vector>

#include "i_poller.hpp"
#include "fd.hpp"
#include "thread.hpp"
#include "atomic_counter.hpp"

namespace zs
{

    //  Implements socket polling mechanism using the BSD-specific
    //  kqueue interface.

    class kqueue_t : public i_poller
    {
    public:

        kqueue_t ();
        virtual ~kqueue_t ();

        //  i_poller implementation.
        handle_t add_fd (fd_t fd_, i_poll_events *events_);
        void rm_fd (handle_t handle_);
        void set_pollin (handle_t handle_);
        void reset_pollin (handle_t handle_);
        void set_pollout (handle_t handle_);
        void reset_pollout (handle_t handle_);
        void add_timer (i_poll_events *events_);
        void cancel_timer (i_poll_events *events_);
        int get_load ();
        void start ();
        void stop ();
        void join ();

    private:

        //  Main worker thread routine.
        static void worker_routine (void *arg_);

        //  Main event loop.
        void loop ();

        //  File descriptor referring to the kernel event queue.
        fd_t kqueue_fd;

        //  Adds the event to the kqueue.
        void kevent_add (fd_t fd_, short filter_, void *udata_);

        //  Deletes the event from the kqueue.
        void kevent_delete (fd_t fd_, short filter_);

        struct poll_entry_t
        {
            fd_t fd;
            bool flag_pollin;
            bool flag_pollout;
            i_poll_events *reactor;
        };

        //  List of retired event sources.
        typedef std::vector <poll_entry_t*> retired_t;
        retired_t retired;

        //  List of all the engines waiting for the timer event.
        typedef std::vector <struct i_poll_events*> timers_t;
        timers_t timers;

        //  If true, thread is in the process of shutting down.
        bool stopping;

        //  Handle of the physical thread doing the I/O work.
        thread_t worker;

        //  Load of the poller. Currently number of file descriptors
        //  registered with the poller.
        atomic_counter_t load;

        kqueue_t (const kqueue_t&);
        void operator = (const kqueue_t&);
    };

}

#endif

#endif
