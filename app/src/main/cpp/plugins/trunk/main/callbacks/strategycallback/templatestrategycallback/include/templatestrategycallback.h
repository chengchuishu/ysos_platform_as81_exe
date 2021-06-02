/**
 *@file templatestrategycallback.h
 *@brief the manager self strategy call back
 *@version 1.0
 *@author z.gg
 *@date Created on: 2020-3-31 15:16:00
 *@copyright Copyright (c) 2020 YS Technology. All rights reserved.
 * 
 */

#ifndef TEMPLATE_STRATEGY_CALLBACK_H_
#define TEMPLATE_STRATEGY_CALLBACK_H_


/// Private Headers //  NOLINT
#include "../../../../../../core/trunk/main/protect/include/sys_framework_package/basemoduleimpl.h"  //NOLINT
#include "../../../../../../core/trunk/main/protect/include/sys_framework_package/basemodulecallbackimpl.h"  //NOLINT
#include "../../../../../../core/trunk/main/protect/include/sys_framework_package/basestrategycallbackimpl.h"  //NOLINT
#include "../../../../../../core/trunk/main/protect/include/sys_framework_package/packageconfigimpl.h"
#include "../../../../../../core/trunk/main/protect/include/os_hal_package/datainterfacemanager.h"
#include "../../../../../../core/trunk/main/public/include/core_help_package/utility.h"

namespace ysos {


/**
 *@brief  自我管理策略层 //NOLINT
*/
class YSOS_EXPORT TemplateStrategyCallback : public BaseStrategyCallbackImpl {
  DECLARE_CREATEINSTANCE(TemplateStrategyCallback);
  DISALLOW_COPY_AND_ASSIGN(TemplateStrategyCallback);
  DECLARE_PROTECT_CONSTRUCTOR(TemplateStrategyCallback);

 public:
  ~TemplateStrategyCallback(void);

 protected:
  /**
  *@brief 处理事件的消息  // NOLINT
  *@param event_name[Input]： 事件的类型  // NOLINT
  *@param input_buffer[input]：待处理的数据  // NOLINT
  *@param context[Input]： 回调处理的上下文数据  // NOLINT
  *@return： 成功返回YSOS_ERROR_SUCCESS，失败返回相应错误值  // NOLINT
  */
  virtual int HandleMessage(const std::string &event_name, BufferInterfacePtr input_buffer, CallbackInterface *context);

  /**
  *@brief  配置文件中设置的Key、Value对，会在Initialized函数中调用 //  NOLINT
  *@param key 配置参数中的Key  // NOLINT
  *@param value 与Key对应的Value  // NOLINT
  *@return 成功返回YSOS_ERROR_SUCCESS，否则失败  //  NOLINT
  */
  virtual int Initialized(const std::string &key, const std::string &value);

 private:
  /**
  *@brief 请求平台服务  // NOLINT
  *@param service_name[Input]： 服务名  // NOLINT
  *@param id[Input]： 命令号  // NOLINT
  *@param type[Input]： 参数类型  // NOLINT
  *@param json_value[Input]： 参数数据  // NOLINT
  *@param context[Input]： 回调处理的上下文数据  // NOLINT
  *@return： 成功返回YSOS_ERROR_SUCCESS，失败返回YSOS_ERROR_FAILED  // NOLINT
  */
  int RequestService(std::string service_name, std::string id, std::string type, std::string json_value, CallbackInterface *context);

 private:

  DataInterfacePtr data_ptr_;       //< 内存指针
};

}///< namespace ysos    //NOLINT

#endif///< TEMPLATE_STRATEGY_CALLBACK_H_    //NOLINT