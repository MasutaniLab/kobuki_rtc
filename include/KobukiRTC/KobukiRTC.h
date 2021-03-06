﻿// -*- C++ -*-
/*!
 * @file  KobukiRTC.h
 * @brief Kobuki RTC
 * @date  $Date$
 *
 * $Id$
 */

#ifndef KOBUKIRTC_H
#define KOBUKIRTC_H

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

// Service implementation headers
// <rtc-template block="service_impl_h">

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="consumer_stub_h">
#include "ExtendedDataTypesStub.h"
#include "BasicDataTypeStub.h"

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="port_stub_h">


// </rtc-template>

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>

#include <chrono>
#ifdef JOYSTICK
#include <Windows.h>
#include <mmsystem.h>
#endif
#include "libkobuki.h"

using namespace RTC;

/*!
 * @class KobukiRTC
 * @brief Kobuki RTC
 *
 */
class KobukiRTC
  : public RTC::DataFlowComponentBase
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  KobukiRTC(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~KobukiRTC();

  // <rtc-template block="public_attribute">
  
  // </rtc-template>

  // <rtc-template block="public_operation">
  
  // </rtc-template>

  /***
   *
   * The initialize action (on CREATED->ALIVE transition)
   * formaer rtc_init_entry() 
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onInitialize();

  /***
   *
   * The finalize action (on ALIVE->END transition)
   * formaer rtc_exiting_entry()
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onFinalize();

  /***
   *
   * The startup action when ExecutionContext startup
   * former rtc_starting_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onStartup(RTC::UniqueId ec_id);

  /***
   *
   * The shutdown action when ExecutionContext stop
   * former rtc_stopping_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onShutdown(RTC::UniqueId ec_id);

  /***
   *
   * The activated action (Active state entry action)
   * former rtc_active_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id);

  /***
   *
   * The deactivated action (Active state exit action)
   * former rtc_active_exit()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id);

  /***
   *
   * The execution action that is invoked periodically
   * former rtc_active_do()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id);

  /***
   *
   * The aborting action when main logic error occurred.
   * former rtc_aborting_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onAborting(RTC::UniqueId ec_id);

  /***
   *
   * The error action in ERROR state
   * former rtc_error_do()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onError(RTC::UniqueId ec_id);

  /***
   *
   * The reset action that is invoked resetting
   * This is same but different the former rtc_init_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onReset(RTC::UniqueId ec_id);
  
  /***
   *
   * The state update action that is invoked after onExecute() action
   * no corresponding operation exists in OpenRTm-aist-0.2.0
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onStateUpdate(RTC::UniqueId ec_id);

  /***
   *
   * The action that is invoked when execution context's rate is changed
   * no corresponding operation exists in OpenRTm-aist-0.2.0
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onRateChanged(RTC::UniqueId ec_id);


 protected:
  // <rtc-template block="protected_attribute">
  
  // </rtc-template>

  // <rtc-template block="protected_operation">
  
  // </rtc-template>

  // Configuration variable declaration
  // <rtc-template block="config_declare">
  /*!
   * 
   * - Name:  debug
   * - DefaultValue: 0
   */
  int m_debug;
  /*!
   * 
   * - Name:  port
   * - DefaultValue: com1
   */
  std::string m_port;
  /*!
   * 
   * - Name:  gainP
   * - DefaultValue: 100
   */
  double m_gainP;
  /*!
   * 
   * - Name:  gainI
   * - DefaultValue: 0.1
   */
  double m_gainI;
  /*!
   * 
   * - Name:  gainD
   * - DefaultValue: 2
   */
  double m_gainD;
  /*!
   * 
   * - Name:  joy
   * - DefaultValue: 1
   */
  short int m_joy;
  /*!
   * 
   * - Name:  autoStop
   * - DefaultValue: 0
   */
  float m_autoStop;
  /*!
   * 
   * - Name:  displayHz
   * - DefaultValue: 0
   */
  short int m_displayHz;

  // </rtc-template>

  // DataInPort declaration
  // <rtc-template block="inport_declare">
  RTC::TimedVelocity2D m_targetVelocity;
  /*!
   */
  RTC::InPort<RTC::TimedVelocity2D> m_targetVelocityIn;
  RTC::TimedPose2D m_poseUpdate;
  /*!
   */
  RTC::InPort<RTC::TimedPose2D> m_poseUpdateIn;
  
  // </rtc-template>


  // DataOutPort declaration
  // <rtc-template block="outport_declare">
  RTC::TimedPose2D m_currentPose;
  /*!
   */
  RTC::OutPort<RTC::TimedPose2D> m_currentPoseOut;
  RTC::TimedDouble m_battery;
  /*!
   */
  RTC::OutPort<RTC::TimedDouble> m_batteryOut;
  RTC::TimedBooleanSeq m_bumper;
  /*!
   * bumper (seq: RIGHT, CENTER, LEFT)
   */
  RTC::OutPort<RTC::TimedBooleanSeq> m_bumperOut;
  
  // </rtc-template>

  // CORBA Port declaration
  // <rtc-template block="corbaport_declare">
  
  // </rtc-template>

  // Service declaration
  // <rtc-template block="service_declare">
  
  // </rtc-template>

  // Consumer declaration
  // <rtc-template block="consumer_declare">
  
  // </rtc-template>

 private:
  // <rtc-template block="private_attribute">
  
  // </rtc-template>

  // <rtc-template block="private_operation">
  
  // </rtc-template>


  rt_net::Kobuki *m_pKobuki;
  #ifdef JOYSTICK
  JOYINFOEX m_JoyInfoEx;
  #endif
  bool m_rtcError;  //OpenRTM-aist-1.2.0のバグ回避
  int m_count;
  std::chrono::high_resolution_clock::time_point m_lastDisplay;
  std::chrono::high_resolution_clock::time_point m_lastCommand;
};


extern "C"
{
  DLL_EXPORT void KobukiRTCInit(RTC::Manager* manager);
};

#endif // KOBUKIRTC_H
