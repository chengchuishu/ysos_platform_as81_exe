/**
 *@file ttsextcallback.cpp
 *@brief tts ext callback
 *@version 1.0
 *@author l.j..
 *@date Created on: 2016-10-20 15:16:00
 *@copyright Copyright (c) 2016 YunShen Technology. All rights reserved.
 * 
 */
/// self header
#include "../include/ttsextcallback.h"

/// boost headers
#include <boost/thread/thread.hpp>

/// ysos headers
#include "../../../../../../core/trunk/main/public/include/os_hal_package/lock.h"              //NOLINT
#include "../../../../../../core/trunk/main/public/include/core_help_package/utility.h"
#include "../../../../../../core/trunk/main/public/include/os_hal_package/bufferutility.h"

/// private headers
#include "../../../public/include/common/commonenumdefine.h"
#include "../../../public/include/common/commonstructdefine.h"

namespace ysos {
DECLARE_PLUGIN_REGISTER_INTERFACE(TtsExtCallback, CallbackInterface);
TtsExtCallback::TtsExtCallback(const std::string &strClassName):BaseModuleThreadCallbackImpl(strClassName) {
  logger_ = GetUtility()->GetLogger("ysos.asrext");
}

TtsExtCallback::~TtsExtCallback(void) {

}

int TtsExtCallback::RealCallback(BufferInterfacePtr input_buffer, BufferInterfacePtr output_buffer, BufferInterfacePtr external_buf, void *context) {

  int n_return = YSOS_ERROR_FAILED;

  YSOS_LOG_DEBUG("TtsExtCallback RealCallback in");

  do {
    BaseModuelCallbackContext* module_callback_context_ptr = reinterpret_cast<BaseModuelCallbackContext*>(context);
    BaseInterface* pModule = dynamic_cast<BaseInterface*>(module_callback_context_ptr->cur_module_ptr);

    //test
    if (input_buffer != NULL) {
      UINT8* buffer;
      UINT32 buffer_size;
      input_buffer->GetBufferAndLength(&buffer, &buffer_size);
      std::string input_data((char*)buffer);
      if (!input_data.empty()) {
        if (Utility::UTF8 == GetUtility()->GetEncoding((unsigned char*)buffer, input_buffer->GetBufferAndLength(&buffer, &buffer_size))) {
          YSOS_LOG_DEBUG("tts get data [UTF-8] = " << GetUtility()->Utf8ToGbk(input_data));//add for linux
        } else {
          YSOS_LOG_DEBUG("tts get data = " << /*GetUtility()->Utf8ToGbk(input_data)*/input_data);//add for linux
        }
      }
      if ("DetectAsrResult" == input_data) {
        YSOS_LOG_DEBUG("tts get DetectAsrResult");
        n_return = InvokeNextCallback(input_buffer, NULL, module_callback_context_ptr);
        break;
      }
    }

    AbilityParam input_param, out_param;
#ifdef _WIN32
    sprintf_s(input_param.ability_name, sizeof(input_param.ability_name), input_ability_name_.c_str());
    sprintf_s(input_param.data_type_name, sizeof(input_param.data_type_name), input_type_.c_str());
    input_param.buf_interface_ptr = input_buffer;
    sprintf_s(out_param.ability_name, sizeof(out_param.ability_name), output_ability_name_.c_str());
    sprintf_s(out_param.data_type_name, sizeof(out_param.data_type_name), output_type_.c_str());
#else
    sprintf(input_param.ability_name, "%s", input_ability_name_.c_str());
    sprintf(input_param.data_type_name, "%s", input_type_.c_str());
    input_param.buf_interface_ptr = input_buffer;
    sprintf(out_param.ability_name, "%s", output_ability_name_.c_str());
    sprintf(out_param.data_type_name, "%s", output_type_.c_str());
#endif
    out_param.buf_interface_ptr = output_buffer;

    FunObjectCommon2 funobject2;
    funobject2.pparam1 = &input_param;
    funobject2.pparam2 = &out_param;

    int iloop_max_times = /*10000*/max_loop_time_;  //< 最多一万次，防止死循环
    int i = 0;
    for (i = 0; 0 == iloop_max_times || i<iloop_max_times; ++i) { //< 由于数据不是一次性合成的，是由多次调用后合成的，所以这里会循环调用。
      n_return = pModule->GetProperty(PROP_FUN_CALLABILITY, &funobject2);
      if (YSOS_ERROR_SUCCESS != n_return) {
        YSOS_LOG_DEBUG("call PROP_FUN_CALLABILITY failed: " << n_return);
        break;
      }

      //< 输出buff可能为空的呢
      if (NULL != out_param.buf_interface_ptr) {
        UINT8* out_data = NULL;
        UINT32 data_size = 0;
        out_param.buf_interface_ptr->GetBufferAndLength(&out_data, &data_size);
        if (0 == data_size) { //< 表示解析成功，但当前没有数据，所以返因true
          YSOS_LOG_DEBUG("empty data and out_param.is_not_finish = " << out_param.is_not_finish);
          if (0 == out_param.is_not_finish) //< have finish all data
            break;
          else
            continue;
        }
      }
      YSOS_LOG_DEBUG("get tts TtsExtCallback InvokeNextCallback");
      n_return = InvokeNextCallback(out_param.buf_interface_ptr, NULL, module_callback_context_ptr);
      if (0 == out_param.is_not_finish) {  ///< have finish tts all voice data
        YSOS_LOG_DEBUG("tts finish");
        break;
      }
    }  // end for
    if (i > iloop_max_times)
      YSOS_LOG_DEBUG("execute too much, i = " << i);

    n_return = YSOS_ERROR_SKIP;
  } while (0);

  return n_return;
}

int TtsExtCallback::Initialized(const std::string &key, const std::string &value) {
  if (strcasecmp(key.c_str(), "input_type") ==0) {
    input_type_ = value;
  } else if (strcasecmp(key.c_str(), "output_type")==0) {
    output_type_ = value;
  } else if (strcasecmp(key.c_str(), "input_ability") ==0) {
    input_ability_name_ = value;
  } else if (strcasecmp(key.c_str(), "output_ability") ==0) {
    output_ability_name_ = value;
  } else if (strcasecmp(key.c_str(), "max_loop_time") ==0) {
    if (value.length() >0) {
      max_loop_time_ = atoi(value.c_str());
    } else {
      max_loop_time_ = 1;
    }
  }

  YSOS_LOG_DEBUG("input_type = " << input_type_ <<"; output_type = " << output_type_ << "; input_ability = " << input_ability_name_ << "; output_ability = " << output_ability_name_);
  return YSOS_ERROR_SUCCESS;
}

}
