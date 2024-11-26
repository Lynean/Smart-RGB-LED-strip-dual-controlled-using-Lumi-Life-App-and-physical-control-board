// This file is generated by Simplicity Studio.  Please do not edit manually.
//
//

// This is a set of generated functions that parse the
// the incomming message, and call appropriate command handler.



#include PLATFORM_HEADER
#ifdef EZSP_HOST
// Includes needed for ember related functions for the EZSP host
#include "stack/include/error.h"
#include "stack/include/ember-types.h"
#include "app/util/ezsp/ezsp-protocol.h"
#include "app/util/ezsp/ezsp.h"
#include "app/util/ezsp/ezsp-utils.h"
#include "app/util/ezsp/serial-interface.h"
#else
// Includes needed for ember related functions for the EM250
#include "stack/include/ember.h"
#endif // EZSP_HOST

#include "app/framework/util/util.h"
#include "af-structs.h"
#include "call-command-handler.h"
#include "command-id.h"
#include "callback.h"

static EmberAfStatus status(bool wasHandled, bool clusterExists, bool mfgSpecific)
{
  if (wasHandled) {
    return EMBER_ZCL_STATUS_SUCCESS;
  } else if (mfgSpecific) {
    return EMBER_ZCL_STATUS_UNSUP_MANUF_CLUSTER_COMMAND;
  } else if (clusterExists) {
    return EMBER_ZCL_STATUS_UNSUP_CLUSTER_COMMAND;
  } else {
    return EMBER_ZCL_STATUS_UNSUPPORTED_CLUSTER;
  }
}

// Main command parsing controller.
EmberAfStatus emberAfClusterSpecificCommandParse(EmberAfClusterCommand *cmd)
{
  EmberAfStatus result = status(false, false, cmd->mfgSpecific);
  if (cmd->direction == (uint8_t)ZCL_DIRECTION_SERVER_TO_CLIENT
      && emberAfContainsClientWithMfgCode(cmd->apsFrame->destinationEndpoint,
                               cmd->apsFrame->clusterId,
                               cmd->mfgCode)) {
    switch (cmd->apsFrame->clusterId) {
    case ZCL_IDENTIFY_CLUSTER_ID:
      result = status(false, true, cmd->mfgSpecific);
      break;
    default:
      // Unrecognized cluster ID, error status will apply.
      break;
    }
  } else if (cmd->direction == (uint8_t)ZCL_DIRECTION_CLIENT_TO_SERVER
             && emberAfContainsServerWithMfgCode(cmd->apsFrame->destinationEndpoint,
                                       cmd->apsFrame->clusterId,
                                       cmd->mfgCode)) {
    switch (cmd->apsFrame->clusterId) {
    case ZCL_BASIC_CLUSTER_ID:
      result = emberAfBasicClusterServerCommandParse(cmd);
      break;
    case ZCL_IDENTIFY_CLUSTER_ID:
      result = emberAfIdentifyClusterServerCommandParse(cmd);
      break;
    case ZCL_ON_OFF_CLUSTER_ID:
      result = emberAfOnOffClusterServerCommandParse(cmd);
      break;
    case ZCL_TIME_CLUSTER_ID:
      result = status(false, true, cmd->mfgSpecific);
      break;
    case ZCL_COLOR_CONTROL_CLUSTER_ID:
      result = emberAfColorControlClusterServerCommandParse(cmd);
      break;
    case ZCL_ILLUM_MEASUREMENT_CLUSTER_ID:
      result = status(false, true, cmd->mfgSpecific);
      break;
    case ZCL_TEMP_MEASUREMENT_CLUSTER_ID:
      result = status(false, true, cmd->mfgSpecific);
      break;
    case ZCL_RELATIVE_HUMIDITY_MEASUREMENT_CLUSTER_ID:
      result = status(false, true, cmd->mfgSpecific);
      break;
    default:
      // Unrecognized cluster ID, error status will apply.
      break;
    }
  }
  return result;
}

// Cluster: Basic, server
EmberAfStatus emberAfBasicClusterServerCommandParse(EmberAfClusterCommand *cmd)
{
  bool wasHandled = false;
  if (!cmd->mfgSpecific) {
    switch (cmd->commandId) {
    case ZCL_RESET_TO_FACTORY_DEFAULTS_COMMAND_ID:
      {
        // Command is fixed length: 0
        wasHandled = emberAfBasicClusterResetToFactoryDefaultsCallback();
        break;
      }
    default:
      {
        // Unrecognized command ID, error status will apply.
        break;
      }
    }
  }
  return status(wasHandled, true, cmd->mfgSpecific);
}

// Cluster: Identify, server
EmberAfStatus emberAfIdentifyClusterServerCommandParse(EmberAfClusterCommand *cmd)
{
  bool wasHandled = false;
  if (!cmd->mfgSpecific) {
    switch (cmd->commandId) {
    case ZCL_IDENTIFY_COMMAND_ID:
      {
        uint16_t payloadOffset = cmd->payloadStartIndex;
        uint16_t identifyTime;  // Ver.: always
        // Command is fixed length: 2
        if (cmd->bufLen < payloadOffset + 2u) { return EMBER_ZCL_STATUS_MALFORMED_COMMAND; }
        identifyTime = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfIdentifyClusterIdentifyCallback(identifyTime);
        break;
      }
    case ZCL_IDENTIFY_QUERY_COMMAND_ID:
      {
        // Command is fixed length: 0
        wasHandled = emberAfIdentifyClusterIdentifyQueryCallback();
        break;
      }
    default:
      {
        // Unrecognized command ID, error status will apply.
        break;
      }
    }
  }
  return status(wasHandled, true, cmd->mfgSpecific);
}

// Cluster: On/off, server
EmberAfStatus emberAfOnOffClusterServerCommandParse(EmberAfClusterCommand *cmd)
{
  bool wasHandled = false;
  if (!cmd->mfgSpecific) {
    switch (cmd->commandId) {
    case ZCL_OFF_COMMAND_ID:
      {
        // Command is fixed length: 0
        wasHandled = emberAfOnOffClusterOffCallback();
        break;
      }
    case ZCL_ON_COMMAND_ID:
      {
        // Command is fixed length: 0
        wasHandled = emberAfOnOffClusterOnCallback();
        break;
      }
    case ZCL_TOGGLE_COMMAND_ID:
      {
        // Command is fixed length: 0
        wasHandled = emberAfOnOffClusterToggleCallback();
        break;
      }
    default:
      {
        // Unrecognized command ID, error status will apply.
        break;
      }
    }
  }
  return status(wasHandled, true, cmd->mfgSpecific);
}

// Cluster: Color Control, server
EmberAfStatus emberAfColorControlClusterServerCommandParse(EmberAfClusterCommand *cmd)
{
  bool wasHandled = false;
  if (!cmd->mfgSpecific) {
    switch (cmd->commandId) {
    case ZCL_MOVE_TO_HUE_COMMAND_ID:
      {
        uint16_t payloadOffset = cmd->payloadStartIndex;
        uint8_t hue;  // Ver.: always
        uint8_t direction;  // Ver.: always
        uint16_t transitionTime;  // Ver.: always
        uint8_t optionsMask;  // Ver.: since zcl6-errata-14-0129-15
        uint8_t optionsOverride;  // Ver.: since zcl6-errata-14-0129-15
        // Command is not a fixed length
        if (cmd->bufLen < payloadOffset + 1u) { return EMBER_ZCL_STATUS_MALFORMED_COMMAND; }
        hue = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1u;
        if (cmd->bufLen < payloadOffset + 1u) { return EMBER_ZCL_STATUS_MALFORMED_COMMAND; }
        direction = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1u;
        if (cmd->bufLen < payloadOffset + 2u) { return EMBER_ZCL_STATUS_MALFORMED_COMMAND; }
        transitionTime = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2u;
        if ( ( cmd->bufLen < payloadOffset + 1u)) {
          // Argument is not always present:
          // - it is present only in versions higher than: zcl6-errata-14-0129-15
          optionsMask = 0xFF;
        } else {
          optionsMask = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
          payloadOffset += 1u;
        }
        if ( ( cmd->bufLen < payloadOffset + 1u)) {
          // Argument is not always present:
          // - it is present only in versions higher than: zcl6-errata-14-0129-15
          optionsOverride = 0xFF;
        } else {
          optionsOverride = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        }
        wasHandled = emberAfColorControlClusterMoveToHueCallback(hue,
                                                                 direction,
                                                                 transitionTime,
                                                                 optionsMask,
                                                                 optionsOverride);
        break;
      }
    case ZCL_MOVE_HUE_COMMAND_ID:
      {
        uint16_t payloadOffset = cmd->payloadStartIndex;
        uint8_t moveMode;  // Ver.: always
        uint8_t rate;  // Ver.: always
        uint8_t optionsMask;  // Ver.: since zcl6-errata-14-0129-15
        uint8_t optionsOverride;  // Ver.: since zcl6-errata-14-0129-15
        // Command is not a fixed length
        if (cmd->bufLen < payloadOffset + 1u) { return EMBER_ZCL_STATUS_MALFORMED_COMMAND; }
        moveMode = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1u;
        if (cmd->bufLen < payloadOffset + 1u) { return EMBER_ZCL_STATUS_MALFORMED_COMMAND; }
        rate = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1u;
        if ( ( cmd->bufLen < payloadOffset + 1u)) {
          // Argument is not always present:
          // - it is present only in versions higher than: zcl6-errata-14-0129-15
          optionsMask = 0xFF;
        } else {
          optionsMask = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
          payloadOffset += 1u;
        }
        if ( ( cmd->bufLen < payloadOffset + 1u)) {
          // Argument is not always present:
          // - it is present only in versions higher than: zcl6-errata-14-0129-15
          optionsOverride = 0xFF;
        } else {
          optionsOverride = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        }
        wasHandled = emberAfColorControlClusterMoveHueCallback(moveMode,
                                                               rate,
                                                               optionsMask,
                                                               optionsOverride);
        break;
      }
    case ZCL_STEP_HUE_COMMAND_ID:
      {
        uint16_t payloadOffset = cmd->payloadStartIndex;
        uint8_t stepMode;  // Ver.: always
        uint8_t stepSize;  // Ver.: always
        uint8_t transitionTime;  // Ver.: always
        uint8_t optionsMask;  // Ver.: since zcl6-errata-14-0129-15
        uint8_t optionsOverride;  // Ver.: since zcl6-errata-14-0129-15
        // Command is not a fixed length
        if (cmd->bufLen < payloadOffset + 1u) { return EMBER_ZCL_STATUS_MALFORMED_COMMAND; }
        stepMode = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1u;
        if (cmd->bufLen < payloadOffset + 1u) { return EMBER_ZCL_STATUS_MALFORMED_COMMAND; }
        stepSize = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1u;
        if (cmd->bufLen < payloadOffset + 1u) { return EMBER_ZCL_STATUS_MALFORMED_COMMAND; }
        transitionTime = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1u;
        if ( ( cmd->bufLen < payloadOffset + 1u)) {
          // Argument is not always present:
          // - it is present only in versions higher than: zcl6-errata-14-0129-15
          optionsMask = 0xFF;
        } else {
          optionsMask = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
          payloadOffset += 1u;
        }
        if ( ( cmd->bufLen < payloadOffset + 1u)) {
          // Argument is not always present:
          // - it is present only in versions higher than: zcl6-errata-14-0129-15
          optionsOverride = 0xFF;
        } else {
          optionsOverride = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        }
        wasHandled = emberAfColorControlClusterStepHueCallback(stepMode,
                                                               stepSize,
                                                               transitionTime,
                                                               optionsMask,
                                                               optionsOverride);
        break;
      }
    case ZCL_MOVE_TO_SATURATION_COMMAND_ID:
      {
        uint16_t payloadOffset = cmd->payloadStartIndex;
        uint8_t saturation;  // Ver.: always
        uint16_t transitionTime;  // Ver.: always
        uint8_t optionsMask;  // Ver.: since zcl6-errata-14-0129-15
        uint8_t optionsOverride;  // Ver.: since zcl6-errata-14-0129-15
        // Command is not a fixed length
        if (cmd->bufLen < payloadOffset + 1u) { return EMBER_ZCL_STATUS_MALFORMED_COMMAND; }
        saturation = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1u;
        if (cmd->bufLen < payloadOffset + 2u) { return EMBER_ZCL_STATUS_MALFORMED_COMMAND; }
        transitionTime = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2u;
        if ( ( cmd->bufLen < payloadOffset + 1u)) {
          // Argument is not always present:
          // - it is present only in versions higher than: zcl6-errata-14-0129-15
          optionsMask = 0xFF;
        } else {
          optionsMask = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
          payloadOffset += 1u;
        }
        if ( ( cmd->bufLen < payloadOffset + 1u)) {
          // Argument is not always present:
          // - it is present only in versions higher than: zcl6-errata-14-0129-15
          optionsOverride = 0xFF;
        } else {
          optionsOverride = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        }
        wasHandled = emberAfColorControlClusterMoveToSaturationCallback(saturation,
                                                                        transitionTime,
                                                                        optionsMask,
                                                                        optionsOverride);
        break;
      }
    case ZCL_MOVE_SATURATION_COMMAND_ID:
      {
        uint16_t payloadOffset = cmd->payloadStartIndex;
        uint8_t moveMode;  // Ver.: always
        uint8_t rate;  // Ver.: always
        uint8_t optionsMask;  // Ver.: since zcl6-errata-14-0129-15
        uint8_t optionsOverride;  // Ver.: since zcl6-errata-14-0129-15
        // Command is not a fixed length
        if (cmd->bufLen < payloadOffset + 1u) { return EMBER_ZCL_STATUS_MALFORMED_COMMAND; }
        moveMode = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1u;
        if (cmd->bufLen < payloadOffset + 1u) { return EMBER_ZCL_STATUS_MALFORMED_COMMAND; }
        rate = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1u;
        if ( ( cmd->bufLen < payloadOffset + 1u)) {
          // Argument is not always present:
          // - it is present only in versions higher than: zcl6-errata-14-0129-15
          optionsMask = 0xFF;
        } else {
          optionsMask = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
          payloadOffset += 1u;
        }
        if ( ( cmd->bufLen < payloadOffset + 1u)) {
          // Argument is not always present:
          // - it is present only in versions higher than: zcl6-errata-14-0129-15
          optionsOverride = 0xFF;
        } else {
          optionsOverride = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        }
        wasHandled = emberAfColorControlClusterMoveSaturationCallback(moveMode,
                                                                      rate,
                                                                      optionsMask,
                                                                      optionsOverride);
        break;
      }
    case ZCL_STEP_SATURATION_COMMAND_ID:
      {
        uint16_t payloadOffset = cmd->payloadStartIndex;
        uint8_t stepMode;  // Ver.: always
        uint8_t stepSize;  // Ver.: always
        uint8_t transitionTime;  // Ver.: always
        uint8_t optionsMask;  // Ver.: since zcl6-errata-14-0129-15
        uint8_t optionsOverride;  // Ver.: since zcl6-errata-14-0129-15
        // Command is not a fixed length
        if (cmd->bufLen < payloadOffset + 1u) { return EMBER_ZCL_STATUS_MALFORMED_COMMAND; }
        stepMode = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1u;
        if (cmd->bufLen < payloadOffset + 1u) { return EMBER_ZCL_STATUS_MALFORMED_COMMAND; }
        stepSize = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1u;
        if (cmd->bufLen < payloadOffset + 1u) { return EMBER_ZCL_STATUS_MALFORMED_COMMAND; }
        transitionTime = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1u;
        if ( ( cmd->bufLen < payloadOffset + 1u)) {
          // Argument is not always present:
          // - it is present only in versions higher than: zcl6-errata-14-0129-15
          optionsMask = 0xFF;
        } else {
          optionsMask = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
          payloadOffset += 1u;
        }
        if ( ( cmd->bufLen < payloadOffset + 1u)) {
          // Argument is not always present:
          // - it is present only in versions higher than: zcl6-errata-14-0129-15
          optionsOverride = 0xFF;
        } else {
          optionsOverride = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        }
        wasHandled = emberAfColorControlClusterStepSaturationCallback(stepMode,
                                                                      stepSize,
                                                                      transitionTime,
                                                                      optionsMask,
                                                                      optionsOverride);
        break;
      }
    case ZCL_MOVE_TO_HUE_AND_SATURATION_COMMAND_ID:
      {
        uint16_t payloadOffset = cmd->payloadStartIndex;
        uint8_t hue;  // Ver.: always
        uint8_t saturation;  // Ver.: always
        uint16_t transitionTime;  // Ver.: always
        uint8_t optionsMask;  // Ver.: since zcl6-errata-14-0129-15
        uint8_t optionsOverride;  // Ver.: since zcl6-errata-14-0129-15
        // Command is not a fixed length
        if (cmd->bufLen < payloadOffset + 1u) { return EMBER_ZCL_STATUS_MALFORMED_COMMAND; }
        hue = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1u;
        if (cmd->bufLen < payloadOffset + 1u) { return EMBER_ZCL_STATUS_MALFORMED_COMMAND; }
        saturation = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1u;
        if (cmd->bufLen < payloadOffset + 2u) { return EMBER_ZCL_STATUS_MALFORMED_COMMAND; }
        transitionTime = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2u;
        if ( ( cmd->bufLen < payloadOffset + 1u)) {
          // Argument is not always present:
          // - it is present only in versions higher than: zcl6-errata-14-0129-15
          optionsMask = 0xFF;
        } else {
          optionsMask = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
          payloadOffset += 1u;
        }
        if ( ( cmd->bufLen < payloadOffset + 1u)) {
          // Argument is not always present:
          // - it is present only in versions higher than: zcl6-errata-14-0129-15
          optionsOverride = 0xFF;
        } else {
          optionsOverride = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        }
        wasHandled = emberAfColorControlClusterMoveToHueAndSaturationCallback(hue,
                                                                              saturation,
                                                                              transitionTime,
                                                                              optionsMask,
                                                                              optionsOverride);
        break;
      }
    case ZCL_MOVE_TO_COLOR_COMMAND_ID:
      {
        uint16_t payloadOffset = cmd->payloadStartIndex;
        uint16_t colorX;  // Ver.: always
        uint16_t colorY;  // Ver.: always
        uint16_t transitionTime;  // Ver.: always
        uint8_t optionsMask;  // Ver.: since zcl6-errata-14-0129-15
        uint8_t optionsOverride;  // Ver.: since zcl6-errata-14-0129-15
        // Command is not a fixed length
        if (cmd->bufLen < payloadOffset + 2u) { return EMBER_ZCL_STATUS_MALFORMED_COMMAND; }
        colorX = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2u;
        if (cmd->bufLen < payloadOffset + 2u) { return EMBER_ZCL_STATUS_MALFORMED_COMMAND; }
        colorY = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2u;
        if (cmd->bufLen < payloadOffset + 2u) { return EMBER_ZCL_STATUS_MALFORMED_COMMAND; }
        transitionTime = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2u;
        if ( ( cmd->bufLen < payloadOffset + 1u)) {
          // Argument is not always present:
          // - it is present only in versions higher than: zcl6-errata-14-0129-15
          optionsMask = 0xFF;
        } else {
          optionsMask = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
          payloadOffset += 1u;
        }
        if ( ( cmd->bufLen < payloadOffset + 1u)) {
          // Argument is not always present:
          // - it is present only in versions higher than: zcl6-errata-14-0129-15
          optionsOverride = 0xFF;
        } else {
          optionsOverride = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        }
        wasHandled = emberAfColorControlClusterMoveToColorCallback(colorX,
                                                                   colorY,
                                                                   transitionTime,
                                                                   optionsMask,
                                                                   optionsOverride);
        break;
      }
    case ZCL_MOVE_COLOR_COMMAND_ID:
      {
        uint16_t payloadOffset = cmd->payloadStartIndex;
        int16_t rateX;  // Ver.: always
        int16_t rateY;  // Ver.: always
        uint8_t optionsMask;  // Ver.: since zcl6-errata-14-0129-15
        uint8_t optionsOverride;  // Ver.: since zcl6-errata-14-0129-15
        // Command is not a fixed length
        if (cmd->bufLen < payloadOffset + 2u) { return EMBER_ZCL_STATUS_MALFORMED_COMMAND; }
        rateX = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2u;
        if (cmd->bufLen < payloadOffset + 2u) { return EMBER_ZCL_STATUS_MALFORMED_COMMAND; }
        rateY = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2u;
        if ( ( cmd->bufLen < payloadOffset + 1u)) {
          // Argument is not always present:
          // - it is present only in versions higher than: zcl6-errata-14-0129-15
          optionsMask = 0xFF;
        } else {
          optionsMask = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
          payloadOffset += 1u;
        }
        if ( ( cmd->bufLen < payloadOffset + 1u)) {
          // Argument is not always present:
          // - it is present only in versions higher than: zcl6-errata-14-0129-15
          optionsOverride = 0xFF;
        } else {
          optionsOverride = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        }
        wasHandled = emberAfColorControlClusterMoveColorCallback(rateX,
                                                                 rateY,
                                                                 optionsMask,
                                                                 optionsOverride);
        break;
      }
    case ZCL_STEP_COLOR_COMMAND_ID:
      {
        uint16_t payloadOffset = cmd->payloadStartIndex;
        int16_t stepX;  // Ver.: always
        int16_t stepY;  // Ver.: always
        uint16_t transitionTime;  // Ver.: always
        uint8_t optionsMask;  // Ver.: since zcl6-errata-14-0129-15
        uint8_t optionsOverride;  // Ver.: since zcl6-errata-14-0129-15
        // Command is not a fixed length
        if (cmd->bufLen < payloadOffset + 2u) { return EMBER_ZCL_STATUS_MALFORMED_COMMAND; }
        stepX = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2u;
        if (cmd->bufLen < payloadOffset + 2u) { return EMBER_ZCL_STATUS_MALFORMED_COMMAND; }
        stepY = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2u;
        if (cmd->bufLen < payloadOffset + 2u) { return EMBER_ZCL_STATUS_MALFORMED_COMMAND; }
        transitionTime = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2u;
        if ( ( cmd->bufLen < payloadOffset + 1u)) {
          // Argument is not always present:
          // - it is present only in versions higher than: zcl6-errata-14-0129-15
          optionsMask = 0xFF;
        } else {
          optionsMask = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
          payloadOffset += 1u;
        }
        if ( ( cmd->bufLen < payloadOffset + 1u)) {
          // Argument is not always present:
          // - it is present only in versions higher than: zcl6-errata-14-0129-15
          optionsOverride = 0xFF;
        } else {
          optionsOverride = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        }
        wasHandled = emberAfColorControlClusterStepColorCallback(stepX,
                                                                 stepY,
                                                                 transitionTime,
                                                                 optionsMask,
                                                                 optionsOverride);
        break;
      }
    case ZCL_MOVE_TO_COLOR_TEMPERATURE_COMMAND_ID:
      {
        uint16_t payloadOffset = cmd->payloadStartIndex;
        uint16_t colorTemperature;  // Ver.: always
        uint16_t transitionTime;  // Ver.: always
        uint8_t optionsMask;  // Ver.: since zcl6-errata-14-0129-15
        uint8_t optionsOverride;  // Ver.: since zcl6-errata-14-0129-15
        // Command is not a fixed length
        if (cmd->bufLen < payloadOffset + 2u) { return EMBER_ZCL_STATUS_MALFORMED_COMMAND; }
        colorTemperature = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2u;
        if (cmd->bufLen < payloadOffset + 2u) { return EMBER_ZCL_STATUS_MALFORMED_COMMAND; }
        transitionTime = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2u;
        if ( ( cmd->bufLen < payloadOffset + 1u)) {
          // Argument is not always present:
          // - it is present only in versions higher than: zcl6-errata-14-0129-15
          optionsMask = 0xFF;
        } else {
          optionsMask = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
          payloadOffset += 1u;
        }
        if ( ( cmd->bufLen < payloadOffset + 1u)) {
          // Argument is not always present:
          // - it is present only in versions higher than: zcl6-errata-14-0129-15
          optionsOverride = 0xFF;
        } else {
          optionsOverride = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        }
        wasHandled = emberAfColorControlClusterMoveToColorTemperatureCallback(colorTemperature,
                                                                              transitionTime,
                                                                              optionsMask,
                                                                              optionsOverride);
        break;
      }
    case ZCL_STOP_MOVE_STEP_COMMAND_ID:
      {
        uint16_t payloadOffset = cmd->payloadStartIndex;
        uint8_t optionsMask;  // Ver.: since zcl6-errata-14-0129-15
        uint8_t optionsOverride;  // Ver.: since zcl6-errata-14-0129-15
        // Command is not a fixed length
        if ( ( cmd->bufLen < payloadOffset + 1u)) {
          // Argument is not always present:
          // - it is present only in versions higher than: zcl6-errata-14-0129-15
          optionsMask = 0xFF;
        } else {
          optionsMask = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
          payloadOffset += 1u;
        }
        if ( ( cmd->bufLen < payloadOffset + 1u)) {
          // Argument is not always present:
          // - it is present only in versions higher than: zcl6-errata-14-0129-15
          optionsOverride = 0xFF;
        } else {
          optionsOverride = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        }
        wasHandled = emberAfColorControlClusterStopMoveStepCallback(optionsMask,
                                                                    optionsOverride);
        break;
      }
    case ZCL_MOVE_COLOR_TEMPERATURE_COMMAND_ID:
      {
        uint16_t payloadOffset = cmd->payloadStartIndex;
        uint8_t moveMode;  // Ver.: always
        uint16_t rate;  // Ver.: always
        uint16_t colorTemperatureMinimum;  // Ver.: always
        uint16_t colorTemperatureMaximum;  // Ver.: always
        uint8_t optionsMask;  // Ver.: since zcl6-errata-14-0129-15
        uint8_t optionsOverride;  // Ver.: since zcl6-errata-14-0129-15
        // Command is not a fixed length
        if (cmd->bufLen < payloadOffset + 1u) { return EMBER_ZCL_STATUS_MALFORMED_COMMAND; }
        moveMode = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1u;
        if (cmd->bufLen < payloadOffset + 2u) { return EMBER_ZCL_STATUS_MALFORMED_COMMAND; }
        rate = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2u;
        if (cmd->bufLen < payloadOffset + 2u) { return EMBER_ZCL_STATUS_MALFORMED_COMMAND; }
        colorTemperatureMinimum = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2u;
        if (cmd->bufLen < payloadOffset + 2u) { return EMBER_ZCL_STATUS_MALFORMED_COMMAND; }
        colorTemperatureMaximum = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2u;
        if ( ( cmd->bufLen < payloadOffset + 1u)) {
          // Argument is not always present:
          // - it is present only in versions higher than: zcl6-errata-14-0129-15
          optionsMask = 0xFF;
        } else {
          optionsMask = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
          payloadOffset += 1u;
        }
        if ( ( cmd->bufLen < payloadOffset + 1u)) {
          // Argument is not always present:
          // - it is present only in versions higher than: zcl6-errata-14-0129-15
          optionsOverride = 0xFF;
        } else {
          optionsOverride = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        }
        wasHandled = emberAfColorControlClusterMoveColorTemperatureCallback(moveMode,
                                                                            rate,
                                                                            colorTemperatureMinimum,
                                                                            colorTemperatureMaximum,
                                                                            optionsMask,
                                                                            optionsOverride);
        break;
      }
    case ZCL_STEP_COLOR_TEMPERATURE_COMMAND_ID:
      {
        uint16_t payloadOffset = cmd->payloadStartIndex;
        uint8_t stepMode;  // Ver.: always
        uint16_t stepSize;  // Ver.: always
        uint16_t transitionTime;  // Ver.: always
        uint16_t colorTemperatureMinimum;  // Ver.: always
        uint16_t colorTemperatureMaximum;  // Ver.: always
        uint8_t optionsMask;  // Ver.: since zcl6-errata-14-0129-15
        uint8_t optionsOverride;  // Ver.: since zcl6-errata-14-0129-15
        // Command is not a fixed length
        if (cmd->bufLen < payloadOffset + 1u) { return EMBER_ZCL_STATUS_MALFORMED_COMMAND; }
        stepMode = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1u;
        if (cmd->bufLen < payloadOffset + 2u) { return EMBER_ZCL_STATUS_MALFORMED_COMMAND; }
        stepSize = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2u;
        if (cmd->bufLen < payloadOffset + 2u) { return EMBER_ZCL_STATUS_MALFORMED_COMMAND; }
        transitionTime = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2u;
        if (cmd->bufLen < payloadOffset + 2u) { return EMBER_ZCL_STATUS_MALFORMED_COMMAND; }
        colorTemperatureMinimum = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2u;
        if (cmd->bufLen < payloadOffset + 2u) { return EMBER_ZCL_STATUS_MALFORMED_COMMAND; }
        colorTemperatureMaximum = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 2u;
        if ( ( cmd->bufLen < payloadOffset + 1u)) {
          // Argument is not always present:
          // - it is present only in versions higher than: zcl6-errata-14-0129-15
          optionsMask = 0xFF;
        } else {
          optionsMask = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
          payloadOffset += 1u;
        }
        if ( ( cmd->bufLen < payloadOffset + 1u)) {
          // Argument is not always present:
          // - it is present only in versions higher than: zcl6-errata-14-0129-15
          optionsOverride = 0xFF;
        } else {
          optionsOverride = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        }
        wasHandled = emberAfColorControlClusterStepColorTemperatureCallback(stepMode,
                                                                            stepSize,
                                                                            transitionTime,
                                                                            colorTemperatureMinimum,
                                                                            colorTemperatureMaximum,
                                                                            optionsMask,
                                                                            optionsOverride);
        break;
      }
    default:
      {
        // Unrecognized command ID, error status will apply.
        break;
      }
    }
  }
  return status(wasHandled, true, cmd->mfgSpecific);
}
