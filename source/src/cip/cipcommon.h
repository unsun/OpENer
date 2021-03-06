/*******************************************************************************
 * Copyright (c) 2009, Rockwell Automation, Inc.
 * All rights reserved.
 *
 ******************************************************************************/
#ifndef OPENER_CIPCOMMON_H_
#define OPENER_CIPCOMMON_H_

/** @file cipcommon.h
 * Common CIP object interface
 */

#include "typedefs.h"
#include "ciptypes.h"

/** A buffer for holding the replay generated by explicit message requests
 *  or producing I/O connections. These will use this buffer in the following
 *  ways:
 *    1. Explicit messages will use this buffer to store the data generated by the request
 *    2. I/O Connections will use this buffer for the produced data
 */
extern EipUint8 g_message_data_reply_buffer[];

/** @brief Check if requested service present in class/instance and call appropriate service.
 *
 * @param class class receiving the message
 * @param message_router_request request message
 * @param message_router_response reply message
 * @return
 *     - kEipStatusOkSend ... success
 *     - kEipStatusOk ... no reply to send back
 *     - kEipStatusError ... error
 */
EipStatus NotifyClass(const CipClass *RESTRICT const cip_class,
                      CipMessageRouterRequest *const message_router_request,
                      CipMessageRouterResponse *const message_router_response,
                      struct sockaddr *originator_address);

/** @brief Generic implementation of the GetAttributeSingle CIP service
 *
 * Check from classID which Object requests an attribute, search if object has
 * the appropriate attribute implemented.
 * @param instance pointer to instance.
 * @param message_router_request pointer to request.
 * @param message_router_response pointer to response.
 * @return status  >0 .. success
 *          -1 .. requested attribute not available
 */
EipStatus GetAttributeSingle(CipInstance *RESTRICT const instance,
                             CipMessageRouterRequest *const message_router_request,
                             CipMessageRouterResponse *const message_router_response,
                             struct sockaddr *originator_address);

/** @brief Generic implementation of the GetAttributeAll CIP service
 *
 * Copy all attributes from Object into the global message buffer.
 * @param instance pointer to object instance with data.
 * @param message_router_request pointer to MR request.
 * @param message_router_response pointer for MR response.
 * @return length of data stream >0 .. success
 *              0 .. no reply to send
 */
EipStatus GetAttributeAll(CipInstance *instance,
                          CipMessageRouterRequest *message_router_request,
                          CipMessageRouterResponse *message_router_response,
                          struct sockaddr *originator_address);

/** @brief Decodes padded EPath
 *  @param epath EPath to the receiving element
 *  @param message CIP Message to decode
 *  @return Number of decoded bytes
 */
int DecodePaddedEPath(CipEpath *epath, const EipUint8 **data);

#endif /* OPENER_CIPCOMMON_H_ */
