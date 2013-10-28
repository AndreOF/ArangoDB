////////////////////////////////////////////////////////////////////////////////
/// @brief threads
///
/// @file
///
/// DISCLAIMER
///
/// Copyright 2004-2013 triAGENS GmbH, Cologne, Germany
///
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
///
///     http://www.apache.org/licenses/LICENSE-2.0
///
/// Unless required by applicable law or agreed to in writing, software
/// distributed under the License is distributed on an "AS IS" BASIS,
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
/// See the License for the specific language governing permissions and
/// limitations under the License.
///
/// Copyright holder is triAGENS GmbH, Cologne, Germany
///
/// @author Dr. Frank Celler
/// @author Achim Brandt
/// @author Copyright 2008-2013, triAGENS GmbH, Cologne, Germany
////////////////////////////////////////////////////////////////////////////////

#ifndef TRIAGENS_BASICS_THREAD_H
#define TRIAGENS_BASICS_THREAD_H 1

#include "Basics/Common.h"

#include "BasicsC/threads.h"

namespace triagens {
  namespace basics {
    class ConditionVariable;

// -----------------------------------------------------------------------------
// --SECTION--                                                      class Thread
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup Threading
/// @{
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief thread
///
/// Each subclass must implement a method run. A thread can be started by
/// start and is stopped either when the method run ends or when stop is
/// called.
////////////////////////////////////////////////////////////////////////////////

    class Thread {
      private:
        Thread (Thread const&);
        Thread& operator= (Thread const&);

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                             static public methods
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup Threading
/// @{
////////////////////////////////////////////////////////////////////////////////

      public:

////////////////////////////////////////////////////////////////////////////////
/// @brief returns the process id
////////////////////////////////////////////////////////////////////////////////

        static TRI_pid_t currentProcessId ();

////////////////////////////////////////////////////////////////////////////////
/// @brief returns the thread process id
////////////////////////////////////////////////////////////////////////////////

        static TRI_tpid_t currentThreadProcessId ();

////////////////////////////////////////////////////////////////////////////////
/// @brief returns the thread id
////////////////////////////////////////////////////////////////////////////////

        static TRI_tid_t currentThreadId ();

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                      constructors and destructors
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup Threading
/// @{
////////////////////////////////////////////////////////////////////////////////

      public:

////////////////////////////////////////////////////////////////////////////////
/// @brief constructs a thread
////////////////////////////////////////////////////////////////////////////////

        explicit Thread (std::string const& name);

////////////////////////////////////////////////////////////////////////////////
/// @brief deletes the thread
////////////////////////////////////////////////////////////////////////////////

        virtual ~Thread ();

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                                    public methods
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup Threading
/// @{
////////////////////////////////////////////////////////////////////////////////

      public:

////////////////////////////////////////////////////////////////////////////////
/// @brief getter for running
////////////////////////////////////////////////////////////////////////////////

        bool isRunning ();

////////////////////////////////////////////////////////////////////////////////
/// @brief returns a thread identifier
////////////////////////////////////////////////////////////////////////////////

        TRI_tid_t threadId ();

////////////////////////////////////////////////////////////////////////////////
/// @brief starts the thread
////////////////////////////////////////////////////////////////////////////////

        bool start (ConditionVariable * _finishedCondition = 0);

////////////////////////////////////////////////////////////////////////////////
/// @brief stops the thread
////////////////////////////////////////////////////////////////////////////////

        int stop ();

////////////////////////////////////////////////////////////////////////////////
/// @brief joins the thread
////////////////////////////////////////////////////////////////////////////////

        int join ();

////////////////////////////////////////////////////////////////////////////////
/// @brief stops and joins the thread
////////////////////////////////////////////////////////////////////////////////

        int shutdown ();

////////////////////////////////////////////////////////////////////////////////
/// @brief send signal to thread
////////////////////////////////////////////////////////////////////////////////

        void sendSignal (int signal);

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                                 protected methods
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup Threading
/// @{
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief allows asynchrounous cancelation
////////////////////////////////////////////////////////////////////////////////

        void allowAsynchronousCancelation ();

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                         virtual protected methods
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup Threading
/// @{
////////////////////////////////////////////////////////////////////////////////

      protected:

////////////////////////////////////////////////////////////////////////////////
/// @brief allows the sub-class to perform cleanup
////////////////////////////////////////////////////////////////////////////////

        virtual void cleanup () {
        }

////////////////////////////////////////////////////////////////////////////////
/// @brief the thread program
////////////////////////////////////////////////////////////////////////////////

        virtual void run () = 0;

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                            static private methods
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup Threading
/// @{
////////////////////////////////////////////////////////////////////////////////

      private:

////////////////////////////////////////////////////////////////////////////////
/// @brief static started with access to the private variables
////////////////////////////////////////////////////////////////////////////////

        static void startThread (void* arg);

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                                   private methods
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup Threading
/// @{
////////////////////////////////////////////////////////////////////////////////

      private:

////////////////////////////////////////////////////////////////////////////////
/// @brief runner
////////////////////////////////////////////////////////////////////////////////

        void runMe ();

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                                 private variables
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup Threading
/// @{
////////////////////////////////////////////////////////////////////////////////

      private:

////////////////////////////////////////////////////////////////////////////////
/// @brief name of the thread
////////////////////////////////////////////////////////////////////////////////

        const string _name;

////////////////////////////////////////////////////////////////////////////////
/// @brief asynchronous cancelation is allowed
////////////////////////////////////////////////////////////////////////////////

        bool _asynchronousCancelation;

////////////////////////////////////////////////////////////////////////////////
/// @brief thread pointer
////////////////////////////////////////////////////////////////////////////////

        TRI_thread_t _thread;

////////////////////////////////////////////////////////////////////////////////
/// @brief condition variable for done
////////////////////////////////////////////////////////////////////////////////

        ConditionVariable* _finishedCondition;

////////////////////////////////////////////////////////////////////////////////
/// @brief status
////////////////////////////////////////////////////////////////////////////////

        volatile sig_atomic_t _started;

////////////////////////////////////////////////////////////////////////////////
/// @brief status
////////////////////////////////////////////////////////////////////////////////

        volatile sig_atomic_t _running;

    };
  }
}

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

#endif

// -----------------------------------------------------------------------------
// --SECTION--                                                       END-OF-FILE
// -----------------------------------------------------------------------------

// Local Variables:
// mode: outline-minor
// outline-regexp: "/// @brief\\|/// {@inheritDoc}\\|/// @addtogroup\\|/// @page\\|// --SECTION--\\|/// @\\}"
// End:
