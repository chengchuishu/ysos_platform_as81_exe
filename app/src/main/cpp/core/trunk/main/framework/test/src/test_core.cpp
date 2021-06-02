// CoreFramework_test.cpp : Defines the entry point for the console application.
//

//  一个测试用例, 如果既要在本测试工程里测试, 又要在主工程里测试, 那么可以这样来做://NOLINT
//  1.将//NOLINT
//  struct xxx_fixture
//  的完整定义放在//NOLINT
//  #if defined(FOR_BOOST_TEST)
//  与//NOLINT
//  #endif  //  FOR_BOOST_TEST
//  之间.//NOLINT
//  2.将//NOLINT
//  BOOST_FIXTURE_TEST_SUITE(xxx_assign, xxx_fixture);
//  BOOST_AUTO_TEST_CASE(xxx_yyy) {
//  //
//  };
//  BOOST_AUTO_TEST_SUITE_END();
//  放在//NOLINT
//  #if defined(FOR_BOOST_TEST)
//  与//NOLINT
//  #endif  //  FOR_BOOST_TEST
//  之间.//NOLINT
//  3.在本测试工程里定义FOR_BOOST_TEST://NOLINT

//#define BOOST_TEST_MODULE test_main

#if !defined(FOR_BOOST_TEST)
#define FOR_BOOST_TEST
#endif  //  FOR_BOOST_TEST
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN


#include <vector>
#include <string>

#ifdef CreateDirectory
#undef CreateDirectory
#endif

#ifdef RemoveDirectory
#undef RemoveDirectory
#endif

#ifdef CopyFile
#undef CopyFile
#endif

#ifdef DeleteFile
#undef DeleteFile
#endif

//TODO:
#include "../../../protect/include/core_help_package/bufferpoolimpl.h"
#include <boost/test/unit_test.hpp>
#include <boost/assign.hpp>
#include <boost/throw_exception.hpp>
#include <boost/thread.hpp>

/*
#include "../../../public/include/sys_interface_package/common.h"
#include "../../../public/include/core_help_package/ysos_log.h"
#include "../../../public/include/os_hal_package/lock.h"
#include "../../../public/include/os_hal_package/filepath.h"
#include "../../../public/include/core_help_package/multimap.h"
//  #include "../../../protect/include/core_help_package/bufferpoolimpl.h"
#include "../../../protect/include/os_hal_package/teamparamsimpl.h"

#include "../../../public/include/core_help_package/ysos_log.h"
*/

//  Detect memory leak using VLD
//#include "vld.h"

// 全局的初始化与清理函数
struct global_fixture {
  global_fixture() {
    std::cout << ("\r\nglobal setup\r\n");
    std::cout<<"开始准备测试数据------->"<<std::endl;
  }
  ~global_fixture() {
    std::cout << ("\r\nglobal teardown\r\n");
    std::cout<<"清理测试环境<---------"<<std::endl;
  }
};

//定义全局夹具
BOOST_GLOBAL_FIXTURE(global_fixture);

//// TODO-1: local function test
//  filepath_test();
//  xmlparser_main();
//  thread_main();
//  test_multimap();
//  buffer_pool_test();
//  JsonProtocolInterface_test();

//// TODO-2: remote  include header test 
/** boost_thread_unit_test **/
// #include "../../../test/components/ThirdParty/thread_unit.h"   //checked
/** uuid */
// #include "../../../test/components/ThirdParty/uuid_unit.h"   //checked
//#include "../../../test/components/self/filepath_unit.h"    //checked 
//#include "../../../test/components/ThirdParty/date_time_timer_unit.h"  //checked
//#include "../../../test/components/ThirdParty/mutex_for_thread_unit.h"  //checke
//#include "../../../test/components/ThirdParty/condition_with_mutex_unit.h"  //checked
//#include "../../../test/components/ThirdParty/thread_pool_unit.h"    //checked
//#include "../../../test/components/ThirdParty/mutex_unit.h"   //checked
//#include "../../../test/components/ThirdParty/multimap_test.h"  //checked-nouse


//  test SyncAsyn
//#include "../../../test/components/ThirdParty/test_unit.h"   //checked
//#include "../../../test/components/self/teamparams_unit.h    //checked
//#include "../../../test/components/self/serialization_unit.h"  //checked

//#include "../../../test/components/self/messageinterface_unit.h"   //no successed
//#include "../../../test/components/self/streaminterface_unit.h"     //no successed
//#include "../../../test/components/self/jsonprotocol_unit.h"       //no successed
//#include "../../../test/components/self/protocolmanager_unit.h"    //no successed


//#include "../../../test/components/self/buffer_pool_uint.h"  //no successed

//  #include "../../../test/components/self/pre_callback_queue_uint.h"
//  #include "../../../test/components/self/next_callback_queue_uinit.h"
//  #include "../../../test/components/self/httpprotocolimpl_unit.h"
//  #include "../../../test/components/self/base64protocolimpl_unit.h"
//  #include "../../../test/components/self/basemoduleimpl_unit.h"
//  #include "../../../test/components/self/test_unit_module_audio_capture.h"
//  #include "../../../test/components/self/module_link_unit.h"
//  #include "../../../test/components/self/httpconnectionimpl_unit.h"
//  #include "../../../test/components/self/treestructmap_unit.h"
//  #include "../../../test/components/self/package_config_impl_unit.h"
//  #include "../../../test/components/self/jsontree_unit.h"
//  #include "../../../test/components/self/tcpsocketserver_unit.h"
//  #include "../../../test/components/self/tcpsocketclient_unit.h"
//  #include "../../../test/components/self/jsonconnectionimpl_agent_unit.h"
//  #include "../../../test/components/self/jsonconnectionimpl_server_unit.h"
//  #include "../../../test/components/self/baseagentimpl_server_unit.h"
//  #include "../../../test/components/self/sys_init_unit.h"

//  #include "test_unit_videocapture.h"
//  #include "unit_test_log_basic_0.h"
//  #include "unit_test_log_basic_1.h"
//  #include "unit_test_log_basic_2.h"
//  #include "unit_test_video_link_manual.h"
//  #include "unit_test_vc_ff_link_manual.h"
//  #include "unit_test_link_no_repeater_using_sys_init.h"
//  #include "unit_test_link_specified_repeater_using_sys_init.h"
//  #include "unit_test_link_ac_asr_nlp_tts_play.h"
// #include "test_unit_update.h"
//  #include "test_unit_up_down_load.h"
//  #include "test_unit_sqlite3.h"
//  #include "test_unit_mysql.h"