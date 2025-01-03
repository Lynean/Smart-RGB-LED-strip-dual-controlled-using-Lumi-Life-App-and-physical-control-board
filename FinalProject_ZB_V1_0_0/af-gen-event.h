// This file is generated by Simplicity Studio.  Please do not edit manually.
//
//

// Enclosing macro to prevent multiple inclusion
#ifndef __AF_GEN_EVENT__
#define __AF_GEN_EVENT__


// Code used to configure the cluster event mechanism
#define EMBER_AF_GENERATED_EVENT_CODE \
  EmberEventControl emberAfIdentifyClusterServerTickCallbackControl1; \
  EmberEventControl emberAfIdentifyClusterServerTickCallbackControl2; \
  EmberEventControl emberAfIdentifyClusterServerTickCallbackControl3; \
  EmberEventControl emberAfIdentifyClusterServerTickCallbackControl4; \
  extern EmberEventControl WS2812SubmitEventControl; \
  extern EmberEventControl buttonTimeoutEventControl; \
  extern EmberEventControl changeColorEventControl; \
  extern EmberEventControl changePWMEventControl; \
  extern EmberEventControl commissioningLedEventControl; \
  extern EmberEventControl emberAfPluginColorControlServerHueSatTransitionEventControl; \
  extern EmberEventControl emberAfPluginColorControlServerTempTransitionEventControl; \
  extern EmberEventControl emberAfPluginColorControlServerXyTransitionEventControl; \
  extern EmberEventControl emberAfPluginInterpanFragmentReceiveEventControl; \
  extern EmberEventControl emberAfPluginInterpanFragmentTransmitEventControl; \
  extern EmberEventControl emberAfPluginNetworkSteeringFinishSteeringEventControl; \
  extern EmberEventControl emberAfPluginReportingTickEventControl; \
  extern EmberEventControl emberAfPluginScanDispatchScanEventControl; \
  extern EmberEventControl emberAfPluginUpdateTcLinkKeyBeginTcLinkKeyUpdateEventControl; \
  extern EmberEventControl findingAndBindingEventControl; \
  extern EmberEventControl getLightEventControl; \
  extern EmberEventControl getTempHumEventControl; \
  extern EmberEventControl joinNetworkEventControl; \
  extern EmberEventControl ledAnimEventControl; \
  extern EmberEventControl ledToggleEventControl; \
  extern EmberEventControl mainStateEventControl; \
  extern EmberEventControl minuteTimerEventControl; \
  extern void WS2812SubmitEventHandler(void); \
  extern void buttonTimeoutEventHandler(void); \
  extern void changeColorEventHandler(void); \
  extern void changePWMEventHandler(void); \
  extern void commissioningLedEventHandler(void); \
  extern void emberAfPluginColorControlServerHueSatTransitionEventHandler(void); \
  extern void emberAfPluginColorControlServerTempTransitionEventHandler(void); \
  extern void emberAfPluginColorControlServerXyTransitionEventHandler(void); \
  extern void emberAfPluginInterpanFragmentReceiveEventHandler(void); \
  extern void emberAfPluginInterpanFragmentTransmitEventHandler(void); \
  extern void emberAfPluginNetworkSteeringFinishSteeringEventHandler(void); \
  extern void emberAfPluginReportingTickEventHandler(void); \
  extern void emberAfPluginScanDispatchScanEventHandler(void); \
  extern void emberAfPluginUpdateTcLinkKeyBeginTcLinkKeyUpdateEventHandler(void); \
  extern void findingAndBindingEventHandler(void); \
  extern void getLightEventHandler(void); \
  extern void getTempHumEventHandler(void); \
  extern void joinNetworkEventHandler(void); \
  extern void ledAnimEventHandler(void); \
  extern void ledToggleEventHandler(void); \
  extern void mainStateEventHandler(void); \
  extern void minuteTimerEventHandler(void); \
  static void clusterTickWrapper(EmberEventControl *control, EmberAfTickFunction callback, uint8_t endpoint) \
  { \
    emberAfPushEndpointNetworkIndex(endpoint); \
    emberEventControlSetInactive(*control); \
    (*callback)(endpoint); \
    emberAfPopNetworkIndex(); \
  } \
  void emberAfIdentifyClusterServerTickCallbackWrapperFunction1(void) { clusterTickWrapper(&emberAfIdentifyClusterServerTickCallbackControl1, emberAfIdentifyClusterServerTickCallback, 1); } \
  void emberAfIdentifyClusterServerTickCallbackWrapperFunction2(void) { clusterTickWrapper(&emberAfIdentifyClusterServerTickCallbackControl2, emberAfIdentifyClusterServerTickCallback, 2); } \
  void emberAfIdentifyClusterServerTickCallbackWrapperFunction3(void) { clusterTickWrapper(&emberAfIdentifyClusterServerTickCallbackControl3, emberAfIdentifyClusterServerTickCallback, 3); } \
  void emberAfIdentifyClusterServerTickCallbackWrapperFunction4(void) { clusterTickWrapper(&emberAfIdentifyClusterServerTickCallbackControl4, emberAfIdentifyClusterServerTickCallback, 4); } \


// EmberEventData structs used to populate the EmberEventData table
#define EMBER_AF_GENERATED_EVENTS   \
  { &emberAfIdentifyClusterServerTickCallbackControl1, emberAfIdentifyClusterServerTickCallbackWrapperFunction1 }, \
  { &emberAfIdentifyClusterServerTickCallbackControl2, emberAfIdentifyClusterServerTickCallbackWrapperFunction2 }, \
  { &emberAfIdentifyClusterServerTickCallbackControl3, emberAfIdentifyClusterServerTickCallbackWrapperFunction3 }, \
  { &emberAfIdentifyClusterServerTickCallbackControl4, emberAfIdentifyClusterServerTickCallbackWrapperFunction4 }, \
  { &WS2812SubmitEventControl, WS2812SubmitEventHandler }, \
  { &buttonTimeoutEventControl, buttonTimeoutEventHandler }, \
  { &changeColorEventControl, changeColorEventHandler }, \
  { &changePWMEventControl, changePWMEventHandler }, \
  { &commissioningLedEventControl, commissioningLedEventHandler }, \
  { &emberAfPluginColorControlServerHueSatTransitionEventControl, emberAfPluginColorControlServerHueSatTransitionEventHandler }, \
  { &emberAfPluginColorControlServerTempTransitionEventControl, emberAfPluginColorControlServerTempTransitionEventHandler }, \
  { &emberAfPluginColorControlServerXyTransitionEventControl, emberAfPluginColorControlServerXyTransitionEventHandler }, \
  { &emberAfPluginInterpanFragmentReceiveEventControl, emberAfPluginInterpanFragmentReceiveEventHandler }, \
  { &emberAfPluginInterpanFragmentTransmitEventControl, emberAfPluginInterpanFragmentTransmitEventHandler }, \
  { &emberAfPluginNetworkSteeringFinishSteeringEventControl, emberAfPluginNetworkSteeringFinishSteeringEventHandler }, \
  { &emberAfPluginReportingTickEventControl, emberAfPluginReportingTickEventHandler }, \
  { &emberAfPluginScanDispatchScanEventControl, emberAfPluginScanDispatchScanEventHandler }, \
  { &emberAfPluginUpdateTcLinkKeyBeginTcLinkKeyUpdateEventControl, emberAfPluginUpdateTcLinkKeyBeginTcLinkKeyUpdateEventHandler }, \
  { &findingAndBindingEventControl, findingAndBindingEventHandler }, \
  { &getLightEventControl, getLightEventHandler }, \
  { &getTempHumEventControl, getTempHumEventHandler }, \
  { &joinNetworkEventControl, joinNetworkEventHandler }, \
  { &ledAnimEventControl, ledAnimEventHandler }, \
  { &ledToggleEventControl, ledToggleEventHandler }, \
  { &mainStateEventControl, mainStateEventHandler }, \
  { &minuteTimerEventControl, minuteTimerEventHandler }, \


#define EMBER_AF_GENERATED_EVENT_STRINGS   \
  "Identify Cluster Server EP 1",  \
  "Identify Cluster Server EP 2",  \
  "Identify Cluster Server EP 3",  \
  "Identify Cluster Server EP 4",  \
  "W s2812 submit event control",  \
  "Button timeout event control",  \
  "Change color event control",  \
  "Change p w m event control",  \
  "Commissioning led event control",  \
  "Color Control Cluster Server Plugin HueSatTransition",  \
  "Color Control Cluster Server Plugin TempTransition",  \
  "Color Control Cluster Server Plugin XyTransition",  \
  "Interpan Plugin FragmentReceive",  \
  "Interpan Plugin FragmentTransmit",  \
  "Network Steering Plugin FinishSteering",  \
  "Reporting Plugin Tick",  \
  "Scan Dispatch Plugin Scan",  \
  "Update TC Link Key Plugin BeginTcLinkKeyUpdate",  \
  "Finding and binding event control",  \
  "Get light event control",  \
  "Get temp hum event control",  \
  "Join network event control",  \
  "Led anim event control",  \
  "Led toggle event control",  \
  "Main state event control",  \
  "Minute timer event control",  \


// The length of the event context table used to track and retrieve cluster events
#define EMBER_AF_EVENT_CONTEXT_LENGTH 4

// EmberAfEventContext structs used to populate the EmberAfEventContext table
#define EMBER_AF_GENERATED_EVENT_CONTEXT { 0x1, 0x3, false, EMBER_AF_LONG_POLL, EMBER_AF_OK_TO_SLEEP, &emberAfIdentifyClusterServerTickCallbackControl1}, \
{ 0x2, 0x3, false, EMBER_AF_LONG_POLL, EMBER_AF_OK_TO_SLEEP, &emberAfIdentifyClusterServerTickCallbackControl2}, \
{ 0x3, 0x3, false, EMBER_AF_LONG_POLL, EMBER_AF_OK_TO_SLEEP, &emberAfIdentifyClusterServerTickCallbackControl3}, \
{ 0x4, 0x3, false, EMBER_AF_LONG_POLL, EMBER_AF_OK_TO_SLEEP, &emberAfIdentifyClusterServerTickCallbackControl4}


#endif // __AF_GEN_EVENT__
