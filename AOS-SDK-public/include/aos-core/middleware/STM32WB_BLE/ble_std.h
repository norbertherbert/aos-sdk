/******************************************************************************
 * @file    ble_std.h
 * @author  MCD
 * @brief   BLE standard definitions
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2018-2021 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 *****************************************************************************
 */

#ifndef BLE_STD_H__
#define BLE_STD_H__


/* HCI packet type */
#define HCI_COMMAND_PKT_TYPE             0x01U
#define HCI_ACLDATA_PKT_TYPE             0x02U
#define HCI_EVENT_PKT_TYPE               0x04U

/* HCI packet header size */
#define HCI_COMMAND_HDR_SIZE             4
#define HCI_ACLDATA_HDR_SIZE             5
#define HCI_EVENT_HDR_SIZE               3

/* HCI parameters length */
#define HCI_COMMAND_MAX_PARAM_LEN        255
#define HCI_ACLDATA_SRV_BLE_DTM_MAX_DATA_LEN         251  /* HC_LE_Data_Packet_Length */
#define HCI_EVENT_MAX_PARAM_LEN          255

/* HCI packet maximum size */
#define HCI_COMMAND_PKT_MAX_SIZE \
            (HCI_COMMAND_HDR_SIZE + HCI_COMMAND_MAX_PARAM_LEN)
#define HCI_ACLDATA_PKT_MAX_SIZE \
            (HCI_ACLDATA_HDR_SIZE + HCI_ACLDATA_SRV_BLE_DTM_MAX_DATA_LEN)
#define HCI_EVENT_PKT_MAX_SIZE \
            (HCI_EVENT_HDR_SIZE   + HCI_EVENT_MAX_PARAM_LEN)

/* HCI event code */
#define HCI_DISCONNECTION_COMPLETE_EVT_CODE                    0x05U
#define HCI_ENCRYPTION_CHANGE_EVT_CODE                         0x08U
#define HCI_READ_REMOTE_VERSION_INFORMATION_COMPLETE_EVT_CODE  0x0CU
#define HCI_COMMAND_COMPLETE_EVT_CODE                          0x0EU
#define HCI_COMMAND_STATUS_EVT_CODE                            0x0FU
#define HCI_HARDWARE_ERROR_EVT_CODE                            0x10U
#define HCI_NUMBER_OF_COMPLETED_PACKETS_EVT_CODE               0x13U
#define HCI_DATA_BUFFER_OVERFLOW_EVT_CODE                      0x1AU
#define HCI_ENCRYPTION_KEY_REFRESH_COMPLETE_EVT_CODE           0x30U
#define HCI_LE_META_EVT_CODE                                   0x3EU
#define HCI_VENDOR_SPECIFIC_DEBUG_EVT_CODE                     0xFFU

/* HCI LE subevent code */
#define HCI_LE_CONNECTION_COMPLETE_SUBEVT_CODE                 0x01U
#define HCI_LE_ADVERTISING_REPORT_SUBEVT_CODE                  0x02U
#define HCI_LE_CONNECTION_UPDATE_COMPLETE_SUBEVT_CODE          0x03U
#define HCI_LE_READ_REMOTE_FEATURES_COMPLETE_SUBEVT_CODE       0x04U
#define HCI_LE_LONG_TERM_KEY_REQUEST_SUBEVT_CODE               0x05U
#define HCI_LE_DATA_LENGTH_CHANGE_SUBEVT_CODE                  0x07U
#define HCI_LE_READ_LOCAL_P256_PUBLIC_KEY_COMPLETE_SUBEVT_CODE 0x08U
#define HCI_LE_GENERATE_DHKEY_COMPLETE_SUBEVT_CODE             0x09U
#define HCI_LE_ENHANCED_CONNECTION_COMPLETE_SUBEVT_CODE        0x0AU
#define HCI_LE_DIRECT_ADVERTISING_REPORT_SUBEVT_CODE           0x0BU
#define HCI_LE_PHY_UPDATE_COMPLETE_SUBEVT_CODE                 0x0CU
#define HCI_LE_EXTENDED_ADVERTISING_REPORT_SUBEVT_CODE         0x0DU
#define HCI_LE_SCAN_TIMEOUT_SUBEVT_CODE                        0x11U
#define HCI_LE_ADVERTISING_SET_TERMINATED_SUBEVT_CODE          0x12U
#define HCI_LE_SCAN_REQUEST_RECEIVED_SUBEVT_CODE               0x13U

/* HCI error code */
#define HCI_SUCCESS_ERR_CODE                                   0x00U
#define HCI_UNKNOWN_HCI_COMMAND_ERR_CODE                       0x01U
#define HCI_UNKNOWN_CONNECTION_IDENTIFIER_ERR_CODE             0x02U
#define HCI_AUTHENTICATION_FAILURE_ERR_CODE                    0x05U
#define HCI_PIN_OR_KEY_MISSING_ERR_CODE                        0x06U
#define HCI_MEMORY_CAPACITY_EXCEEDED_ERR_CODE                  0x07U
#define HCI_CONNECTION_TIMEOUT_ERR_CODE                        0x08U
#define HCI_CONNECTION_ALREADY_EXISTS_ERR_CODE                 0x0BU
#define HCI_COMMAND_DISALLOWED_ERR_CODE                        0x0CU
#define HCI_UNSUPPORTED_FEATURE_OR_PARAMETER_VALUE_ERR_CODE    0x11U
#define HCI_INVALID_HCI_COMMAND_PARAMETERS_ERR_CODE            0x12U
#define HCI_REMOTE_USER_TERMINATED_CONNECTION_ERR_CODE         0x13U
#define HCI_CONNECTION_TERMINATED_BY_LOCAL_HOST_ERR_CODE       0x16U
#define HCI_LMP_FEATURE_ERR_CODE                               0x1AU
#define HCI_INVALID_LL_PARAMETERS_ERR_CODE                     0x1EU
#define HCI_UNSPECIFIED_ERROR_ERR_CODE                         0x1FU
#define HCI_UNSUPPORTED_LL_PARAMETER_VALUE_ERR_CODE            0x20U
#define HCI_LL_RESPONSE_TIMEOUT_ERR_CODE                       0x22U
#define HCI_LL_PROCEDURE_COLLISION_ERR_CODE                    0x23U
#define HCI_LMP_PDU_NOT_ALLOWED_ERR_CODE                       0x24U
#define HCI_INSTANT_PASSED_ERR_CODE                            0x28U
#define HCI_DIFFERENT_TRANSACTION_COLLISION_ERR_CODE           0x2AU
#define HCI_PARAMETER_OUT_OF_MANDATORY_RANGE_ERR_CODE          0x30U
#define HCI_HOST_BUSY_PAIRING_ERR_CODE                         0x38U
#define HCI_CONTROLLER_BUSY_ERR_CODE                           0x3AU
#define HCI_ADVERTISING_TIMEOUT_ERR_CODE                       0x3CU
#define HCI_CONNECTION_TERMINATED_DUE_TO_MIC_FAILURE_ERR_CODE  0x3DU
#define HCI_CONNECTION_FAILED_TO_BE_ESTABLISHED_ERR_CODE       0x3EU
#define HCI_UNKNOWN_ADVERTISING_IDENTIFIER_ERR_CODE            0x42U
#define HCI_ADVERTISING_LIMIT_REACHED_ERR_CODE                 0x43U
#define HCI_PACKET_TOO_LONG_ERR_CODE                           0x45U

/* HCI_LE_Set_Advertising_Parameters: Advertising_Type */
#define HCI_ADV_TYPE_ADV_IND                           0x00U
#define HCI_ADV_TYPE_ADV_DIRECT_IND_HDC                0x01U
#define HCI_ADV_TYPE_ADV_SCAN_IND                      0x02U
#define HCI_ADV_TYPE_ADV_NONCONN_IND                   0x03U
#define HCI_ADV_TYPE_ADV_DIRECT_IND_LDC                0x04U

/* HCI_LE_Set_Scan_Parameters: Scanning_Filter_Policy */
#define HCI_SCAN_FILTER_NO                             0x00U
#define HCI_SCAN_FILTER_WHITELIST                      0x01U
#define HCI_SCAN_FILTER_NO_EVEN_RPA                    0x02U
#define HCI_SCAN_FILTER_WHITELIST_BUT_RPA              0x03U

/* HCI_LE_Read_PHY: TX_PHY */
#define HCI_TX_PHY_LE_1M                               0x01U
#define HCI_TX_PHY_LE_2M                               0x02U
#define HCI_TX_PHY_LE_CODED                            0x03U

/* HCI_LE_Read_PHY: RX_PHY */
#define HCI_RX_PHY_LE_1M                               0x01U
#define HCI_RX_PHY_LE_2M                               0x02U
#define HCI_RX_PHY_LE_CODED                            0x03U

/* HCI_LE_Set_PHY: ALL_PHYS */
#define HCI_ALL_PHYS_TX_NO_PREF                        0x01U
#define HCI_ALL_PHYS_RX_NO_PREF                        0x02U

/* HCI_LE_Set_PHY: TX_PHYS */
#define HCI_TX_PHYS_LE_1M_PREF                         0x01U
#define HCI_TX_PHYS_LE_2M_PREF                         0x02U
#define HCI_TX_PHYS_LE_CODED_PREF                      0x04U

/* HCI_LE_Set_PHY: RX_PHYS */
#define HCI_RX_PHYS_LE_1M_PREF                         0x01U
#define HCI_RX_PHYS_LE_2M_PREF                         0x02U
#define HCI_RX_PHYS_LE_CODED_PREF                      0x04U

/* HCI_LE_Set_Extended_Advertising_Parameters: Advertising_Event_Properties */
#define HCI_ADV_EVENT_PROP_CONNECTABLE                 0x0001U
#define HCI_ADV_EVENT_PROP_SCANNABLE                   0x0002U
#define HCI_ADV_EVENT_PROP_DIRECTED                    0x0004U
#define HCI_ADV_EVENT_PROP_HDC_DIRECTED                0x0008U
#define HCI_ADV_EVENT_PROP_LEGACY                      0x0010U
#define HCI_ADV_EVENT_PROP_ANONYMOUS                   0x0020U
#define HCI_ADV_EVENT_PROP_TXPOWER_INC                 0x0040U

/* HCI_LE_Set_Extended_Advertising_Parameters: Primary_Advertising_PHY */
#define HCI_PRIMARY_ADV_PHY_LE_1M                      0x01U
#define HCI_PRIMARY_ADV_PHY_LE_CODED                   0x03U

/* HCI_LE_Set_Extended_Advertising_Data: Operation */
#define HCI_SET_ADV_DATA_OPERATION_INTERMEDIATE        0x00U
#define HCI_SET_ADV_DATA_OPERATION_FIRST               0x01U
#define HCI_SET_ADV_DATA_OPERATION_LAST                0x02U
#define HCI_SET_ADV_DATA_OPERATION_COMPLETE            0x03U
#define HCI_SET_ADV_DATA_OPERATION_UNCHANGED           0x04U

/* HCI_LE_Advertising_Report: Event_Type */
#define HCI_ADV_EVT_TYPE_ADV_IND                       0x00U
#define HCI_ADV_EVT_TYPE_ADV_DIRECT_IND                0x01U
#define HCI_ADV_EVT_TYPE_ADV_SCAN_IND                  0x02U
#define HCI_ADV_EVT_TYPE_ADV_NONCONN_IND               0x03U
#define HCI_ADV_EVT_TYPE_SCAN_RSP                      0x04U

/* HCI_LE_Set_Extended_Scan_Parameters: Scanning_PHYs */
#define HCI_SCANNING_PHYS_LE_1M                        0x01U
#define HCI_SCANNING_PHYS_LE_CODED                     0x04U


#endif /* BLE_STD_H__ */
