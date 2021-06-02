
#include "ysos.h"
#include <cstdio>
//#include <string>
#include <csignal>
#include <unistd.h>
#include <boost/thread.hpp>


#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/simple_state.hpp>
#include <iostream>

/*
bool stop_flag = false; 
void signal_callback_handler(int signum) {
    printf("Caught signal = [%d]\n", signum);
    stop_flag = true;
    exit(signum);
}
*/



// We are declaring all types as structs only to avoid having to
// type public. If you don't mind doing so, you can just as well
// use class.

// We need to forward-declare the initial state because it can
// only be defined at a point where the state machine is
// defined.
struct Greeting;

// Boost.Statechart makes heavy use of the curiously recurring
// template pattern. The deriving class must always be passed as
// the first parameter to all base class templates.
//
// The state machine must be informed which state it has to
// enter when the machine is initiated. That's why Greeting is
// passed as the second template parameter.
struct Machine : boost::statechart::state_machine< Machine, Greeting > {};

// For each state we need to define which state machine it
// belongs to and where it is located in the statechart. Both is
// specified with Context argument that is passed to
// simple_state<>. For a flat state machine as we have it here,
// the context is always the state machine. Consequently,
// Machine must be passed as the second template parameter to
// Greeting's base (the Context parameter is explained in more
// detail in the next example).
struct Greeting : boost::statechart::simple_state< Greeting, Machine >
{
    // Whenever the state machine enters a state, it creates an
    // object of the corresponding state class. The object is then
    // kept alive as long as the machine remains in the state.
    // Finally, the object is destroyed when the state machine
    // exits the state. Therefore, a state entry action can be
    // defined by adding a constructor and a state exit action can
    // be defined by adding a destructor.
    Greeting()
    {
        std::cout << "Hello World!\n";
        //LOGD("Hello World!\n");
    } // entry
    ~Greeting()
    {
        std::cout << "Bye Bye World!\n";
        //LOGD("Bye Bye World!\n");
    } // exit
};

int main(int argc, char* argv[]) 
{
    /*
    // 设置信号回调函数，运行程序后键入ctrl + C回调signal_callback_handler函数
    signal(SIGINT, signal_callback_handler);
    printf("==========start service [check] ============\n");
    //TODO: first-  init ysoslog config and create all init log files
    int ret = theApp.InitInstance();
    printf("[********]mian[********][theApp.InitInstance()][ret][%d]\n", ret);
    //TODO: second- auto run all services
    if(!ret){
        printf("[********]mian[********][theApp.InitInstance()][fail][ret][%d]\n", ret);
    } else {
        printf("[********]mian[********][theApp.InitInstance()][success][ret][%d]\n", ret);
    }
    //boost::this_thread::sleep(boost::posix_time::seconds(2));
    ret = theApp.OnAutoRun();
    if(0 != ret) {
        printf("[********]mian[********][theApp.OnAutoRun()][fail][ret][%d]\n", ret);
    } else {
        printf("[********]mian[********][theApp.OnAutoRun()][success][ret][%d]\n", ret);   
        //signal(SIGTERM, signal_callback_handler);
        //  01.先运行该Link, 睡眠约50秒://NOLINT
        while (!stop_flag) {
            // boost::thread::sleep(boost::get_system_time() + boost::posix_time::seconds(65000));
            boost::this_thread::sleep_for(boost::chrono::seconds(1000));
        }
        //TODO: exit app
        theApp.ExitInstance();
    }
    
    printf("==========start service [enter] ============\n");
    */


    Machine myMachine;
    // The machine is not yet running after construction. We start
    // it by calling initiate(). This triggers the construction of
    // the initial state Greeting
    myMachine.initiate();
    // When we leave main(), myMachine is destructed what leads to
    // the destruction of all currently active states.


    return 0;
}