#include "cxx/oop/thread.hpp"

namespace UCA_L2INFO_PW4
{
    int ThreadEntry::start()
    {
        return this->start(arguments());
    }

    int ThreadEntry::operator()(void *args)
    {
        return this->start(args);
    }

    int ThreadEntry::operator()()
    {
        return this->start(arguments());
    }

    void ThreadEntry::setArguments(void *args)
    {
        _F_args = args;
    }

    void* ThreadEntry::arguments() const
    {
        return _F_args;
    }

    ThreadFunction::ThreadFunction(thread_f f): _F_function(f)
    { /* ... */ }

    ThreadFunction::ThreadFunction(const ThreadFunction& func):
        _F_function(func._F_function)
    { /* ... */ }

    int ThreadFunction::start(void *args)
    {
        return _F_function(args);
    }

    hash_t ThreadFunction::hashCode() const
    {
        return reinterpret_cast<hash_t>(_F_function);
    }

    bool ThreadFunction::equals(const Object &tf) const
    {
        if (dynamic_cast<const ThreadFunction*>(&tf) == nullptr)
        {
            return false;
        }
        else
        {
            return dynamic_cast<const ThreadFunction*>(&tf)->_F_function == _F_function;
        }
    }

    Thread::Thread(ThreadEntry *entry): _F_entry(entry), _Mt_running(false)
    {
        /* ... */
    }

    int __thread_entrypoint(void* args)
    {
        Thread* local_thread((Thread*) args);
        ThreadEntry* entrypoint(local_thread->_F_entry);

        local_thread->_Mt_running = true;
        int exit_code(entrypoint->start(entrypoint->arguments()));
        local_thread->_Mt_running = false;
        return exit_code;
    }

    Thread::~Thread()
    {
        // if (_F_entry)
        //     delete _F_entry;
    }

    int Thread::run()
    {
        // Todo Thread::run()
        return -1;
    }

    void Thread::wait()
    {
        // Todo Thread::wait()
    }

    int Thread::kill(int _exit)
    {
        // Todo Thread::kill(int)
        return 0;
    }

    bool Thread::isRunning() const
    {
        return false;
    }
}