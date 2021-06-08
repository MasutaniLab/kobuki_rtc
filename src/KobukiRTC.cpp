// -*- C++ -*-
/*!
 * @file  KobukiRTC.cpp
 * @brief Kobuki RTC
 * @date $Date$
 *
 * $Id$
 */

#include <coil/TimeValue.h>
#include "KobukiRTC.h"
using namespace std;

// Module specification
// <rtc-template block="module_spec">
static const char* kobukirtc_spec[] =
  {
    "implementation_id", "KobukiRTC",
    "type_name",         "KobukiRTC",
    "description",       "Kobuki RTC",
    "version",           "1.1.0",
    "vendor",            "MasutaniLab",
    "category",          "MobileRobot",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.debug", "0",
    "conf.default.port", "com1",
    "conf.default.gainP", "100",
    "conf.default.gainI", "0.1",
    "conf.default.gainD", "2",
    "conf.default.joy", "1",
    "conf.default.autoStop", "0",
    "conf.default.displayHz", "0",

    // Widget
    "conf.__widget__.debug", "text",
    "conf.__widget__.port", "text",
    "conf.__widget__.gainP", "text",
    "conf.__widget__.gainI", "text",
    "conf.__widget__.gainD", "text",
    "conf.__widget__.joy", "text",
    "conf.__widget__.autoStop", "text",
    "conf.__widget__.displayHz", "text",
    // Constraints

    "conf.__type__.debug", "int",
    "conf.__type__.port", "std::string",
    "conf.__type__.gainP", "double",
    "conf.__type__.gainI", "double",
    "conf.__type__.gainD", "double",
    "conf.__type__.joy", "short",
    "conf.__type__.autoStop", "float",
    "conf.__type__.displayHz", "short",

    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
KobukiRTC::KobukiRTC(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_targetVelocityIn("targetVelocity", m_targetVelocity),
    m_poseUpdateIn("poseUpdate", m_poseUpdate),
    m_currentPoseOut("currentPose", m_currentPose),
    m_batteryOut("battery", m_battery),
    m_bumperOut("bumper", m_bumper)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
KobukiRTC::~KobukiRTC()
{
}



RTC::ReturnCode_t KobukiRTC::onInitialize()
{
  RTC_INFO(("onInitialize()"));
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("targetVelocity", m_targetVelocityIn);
  addInPort("poseUpdate", m_poseUpdateIn);

  // Set OutPort buffer
  addOutPort("currentPose", m_currentPoseOut);
  addOutPort("battery", m_batteryOut);
  addOutPort("bumper", m_bumperOut);

  // Set service provider to Ports

  // Set service consumers to Ports

  // Set CORBA Service Ports

  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("debug", m_debug, "0");
  bindParameter("port", m_port, "com1");
  bindParameter("gainP", m_gainP, "100");
  bindParameter("gainI", m_gainI, "0.1");
  bindParameter("gainD", m_gainD, "2");
  bindParameter("joy", m_joy, "1");
  bindParameter("autoStop", m_autoStop, "0");
  bindParameter("displayHz", m_displayHz, "0");
  // </rtc-template>
  
  std::cout << "end onInitialised()" << std::endl;
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t KobukiRTC::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t KobukiRTC::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t KobukiRTC::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t KobukiRTC::onActivated(RTC::UniqueId ec_id)
{
  std::cout << "begin onActivated()" << std::endl;
  RTC_INFO(("onActivated()"));
  RTC_INFO((("m_port: " + m_port).c_str()));
  m_rtcError = false;  //OpenRTM-aist-1.2.0のバグ回避

  try {
    m_pKobuki = nullptr;
    m_pKobuki = createKobuki(rt_net::KobukiStringArgument(m_port));
    m_pKobuki->setGain(m_gainP, m_gainI, m_gainD);
  } catch(std::exception &e) {
    RTC_ERROR((e.what()));
    m_rtcError = true;  //OpenRTM-aist-1.2.0のバグ回避
    return RTC::RTC_ERROR;
  }
  
  m_bumper.data.length(3);

  m_targetVelocity.data.vx = 0;
  m_targetVelocity.data.va = 0;

#ifdef JOYSTICK
  m_JoyInfoEx.dwSize = sizeof(JOYINFOEX);
  m_JoyInfoEx.dwFlags = JOY_RETURNALL;
  if (m_joy) {
    if (joyGetPosEx(0, &m_JoyInfoEx) == JOYERR_NOERROR) {
      RTC_INFO(("ゲームコントローラ有効"));
    } else {
      m_joy = 0;
      RTC_WARN(("ゲームコントローラ無効"));
    }
  }
  #else
    m_joy = 0;
  #endif

  return RTC::RTC_OK;
}


RTC::ReturnCode_t KobukiRTC::onDeactivated(RTC::UniqueId ec_id)
{
  RTC_INFO(("onDeactivate()"));
  if (m_pKobuki != nullptr) {
    delete m_pKobuki;
  }
  return RTC::RTC_OK;
}


RTC::ReturnCode_t KobukiRTC::onExecute(RTC::UniqueId ec_id)
{
  if (m_rtcError) return RTC::RTC_ERROR; //OpenRTM-aist-1.2.0のバグ回避

  if(m_targetVelocityIn.isNew()) {
    m_targetVelocityIn.read();
    if (abs(m_targetVelocity.data.vx) > 0.001
      || abs(m_targetVelocity.data.va) > 0.001
      || !m_joy) {
      m_pKobuki->setTargetVelocity(m_targetVelocity.data.vx, m_targetVelocity.data.va);
    }
  }

  if(m_poseUpdateIn.isNew()) {
    m_poseUpdateIn.read();
    m_pKobuki->setPose(m_poseUpdate.data.position.x, m_poseUpdate.data.position.y, m_poseUpdate.data.heading);
  }

  if(m_pKobuki->getDigitalIn(0)) {
    RTC_ERROR(("緊急停止ボタンが押されました！！"));
    m_pKobuki->setTargetVelocity(0,0);
    return RTC::RTC_ERROR;
  }

  static coil::TimeValue ptv(0.0);
  coil::TimeValue tv(coil::gettimeofday());
  //std::cout << double(tv-ptv) << std::endl;
  ptv = tv;

  m_currentPose.tm.sec = tv.sec();
  m_currentPose.tm.nsec = tv.usec() * 1000;
  m_currentPose.data.position.x = m_pKobuki->getPoseX();
  m_currentPose.data.position.y = m_pKobuki->getPoseY();
  m_currentPose.data.heading = m_pKobuki->getPoseTh();
  m_currentPoseOut.write();
  
  m_battery.tm.sec = tv.sec();
  m_battery.tm.nsec = tv.usec() * 1000;
  m_battery.data = m_pKobuki->getBatteryVoltage();
  m_batteryOut.write();
  
  m_bumper.tm.sec = tv.sec();
  m_bumper.tm.nsec = tv.usec() * 1000;
  m_bumper.data[0] = m_pKobuki->isRightBump();
  m_bumper.data[1] = m_pKobuki->isCenterBump();
  m_bumper.data[2] = m_pKobuki->isLeftBump();
  m_bumperOut.write();

#ifdef JOYSTICK
  if (m_joy && joyGetPosEx(0, &m_JoyInfoEx) == JOYERR_NOERROR) {
    if (abs(m_targetVelocity.data.vx) <= 0.001
      && abs(m_targetVelocity.data.va) <= 0.001) {
      int joyx = m_JoyInfoEx.dwXpos;
      int joyy = m_JoyInfoEx.dwYpos;
      const double vxmax = 0.3;
      const double vamax = 1.0;
      double vx = -vxmax*(joyy - 0x8000) / 0x8000;
      if (abs(vx) < 0.1*vxmax) vx = 0;
      double va = -vamax*(joyx - 0x8000) / 0x8000;
      if (abs(va) < 0.1*vamax) va = 0;
      m_pKobuki->setTargetVelocity(vx, va);
    }
  }
#endif

  coil::usleep(9000); //設定に関係なく10ms周期にするため．要件等！！
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t KobukiRTC::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t KobukiRTC::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t KobukiRTC::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t KobukiRTC::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t KobukiRTC::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void KobukiRTCInit(RTC::Manager* manager)
  {
    coil::Properties profile(kobukirtc_spec);
    manager->registerFactory(profile,
                             RTC::Create<KobukiRTC>,
                             RTC::Delete<KobukiRTC>);
  }
  
};


