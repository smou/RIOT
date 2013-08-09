/**
 * sixlowpan/lowpan.h   - 6LoWPAN constants, data structs, and
 *                        prototypes for 6LoWPAN layer
 *
 * Copyright (C) 2013  INRIA.
 *
 * This file subject to the terms and conditions of the GNU Lesser General
 * Public License. See the file LICENSE in the top level directory for more
 * details.
 *
 * @ingroup sixlowpan
 * @{
 * @file
 * @brief   6LoWPAN LoWPAN layer header
 * @author  Stephan Zeisberg <zeisberg@mi.fu-berlin.de>
 * @author  Martin Lenders <mlenders@inf.fu-berlin.de>
 * @author  Eric Engel <eric.engel@fu-berlin.de>
 * @author  Oliver Gesch <oliver.gesch@googlemail.com>
 */

#ifndef SIXLOWPAN_LOWPAN_H
#define SIXLOWPAN_LOWPAN_H

#include <stdint.h>

#include "transceiver.h"
#include "sixlowpan/types.h"

/**
 * @brief   6LoWPAN dispatch value for uncompressed IPv6 packets.
 * @see <a href="http://tools.ietf.org/html/rfc4944#section-5.1">
 *          RFC 4944, section 5.1
 *      </a>
 */
#define SIXLOWPAN_IPV6_DISPATCH   	(0x41)

/**
 * @brief   6LoWPAN dispatch value for IPv6 header compression (part of
 *          first byte of LOWPAN_IPHC).
 * @see <a href="http://tools.ietf.org/html/rfc6282#section-3.1.1">
 *          RFC 4944, section 3.1.1
 *      </a>
 */
#define SIXLOWPAN_IPHC1_DISPATCH   	(0x60)

/**
 * @brief   Flag for Flow Label elision (part of first byte of
 *          LOWPAN_IPHC).
 * @see <a href="http://tools.ietf.org/html/rfc6282#section-3.1.1">
 *          RFC 6282, section 3.1.1
 *      </a>
 */
#define SIXLOWPAN_IPHC1_FL_C       	(0x10)

/**
 * @brief   Flag for Traffic Class elision (part of first byte of
 *          LOWPAN_IPHC).
 * @see <a href="http://tools.ietf.org/html/rfc6282#section-3.1.1">
 *          RFC 6282, section 3.1.1
 *      </a>
 */
#define SIXLOWPAN_IPHC1_TC_C       	(0x08)

/**
 * @brief   Flag for Next Header Compression (part of first byte of
 *          LOWPAN_IPHC).
 * @see <a href="http://tools.ietf.org/html/rfc6282#section-3.1.1">
 *          RFC 6282, section 3.1.1
 *      </a>
 */
#define SIXLOWPAN_IPHC1_NH         	(0x04)

/**
 * @brief   Flag for Context Identifier Extention (part of second byte
 *          of LOWPAN_IPHC).
 * @see <a href="http://tools.ietf.org/html/rfc6282#section-3.1.1">
 *          RFC 6282, section 3.1.1
 *      </a>
 */
#define SIXLOWPAN_IPHC2_CID        	(0x80)

/**
 * @brief   Flag for Source Address Compression (part of second byte
 *          of LOWPAN_IPHC).
 * @see <a href="http://tools.ietf.org/html/rfc6282#section-3.1.1">
 *          RFC 6282, section 3.1.1
 *      </a>
 */
#define SIXLOWPAN_IPHC2_SAC        	(0x40)

/**
 * @brief   Bits for Source Address Mode (part of second byte of
 *          LOWPAN_IPHC).
 * @see <a href="http://tools.ietf.org/html/rfc6282#section-3.1.1">
 *          RFC 6282, section 3.1.1
 *      </a>
 */
#define SIXLOWPAN_IPHC2_SAM        	(0x30)

/**
 * @brief   Flag for Destination Address Compression (part of second
 *          byte of LOWPAN_IPHC).
 * @see <a href="http://tools.ietf.org/html/rfc6282#section-3.1.1">
 *          RFC 6282, section 3.1.1
 *      </a>
 */
#define SIXLOWPAN_IPHC2_DAC        	(0x04)

/**
 * @brief   Bits for Destination Address Mode (part of second byte of
 *          LOWPAN_IPHC).
 * @see <a href="http://tools.ietf.org/html/rfc6282#section-3.1.1">
 *          RFC 6282, section 3.1.1
 *      </a>
 */
#define SIXLOWPAN_IPHC2_DAM        	(0x03)

/**
 * @brief   Flag for Multicast Compression (part of second byte of
 *          LOWPAN_IPHC).
 * @see <a href="http://tools.ietf.org/html/rfc6282#section-3.1.1">
 *          RFC 6282, section 3.1.1
 *      </a>
 */
#define SIXLOWPAN_IPHC2_M          	(0x08)


/**
 * 6LoWPAN dispatch value for fragmentation header (first fragment)
 * @see <a href="http://tools.ietf.org/html/rfc4944#section-5.1">
 *          RFC 4944, section 5.1
 *      </a>
 */
#define SIXLOWPAN_FRAG1_DISPATCH    (0xc0)

/**
 * 6LoWPAN dispatch value for fragmentation header (subsequent fragment)
 * @see <a href="http://tools.ietf.org/html/rfc4944#section-5.1">
 *          RFC 4944, section 5.1
 *      </a>
 */
#define SIXLOWPAN_FRAGN_DISPATCH    (0xe0)


/**
 * 6LoWPAN fragmentation header length (first fragment)
 */
#define SIXLOWPAN_FRAG1_HDR_LEN  	(4)

/**
 * 6LoWPAN fragmentation header length (subsequent fragment)
 */
#define SIXLOWPAN_FRAGN_HDR_LEN    	(5)


/**
 * @brief   Data type to configure 6LoWPAN IPv6 header compression.
 */
typedef enum __attribute__((packed))
{
    LOWPAN_IPHC_DISABLE = 0,    ///< header compression disabled
    LOWPAN_IPHC_ENABLE = 1      ///< header compression enabled
} sixlowpan_lowpan_iphc_status_t;

/**
 * @brief   Data type to represent an 6LoWPAN frame as byte stream.
 */
typedef struct __attribute__((packed)) {
    uint8_t length;             ///< length of the byte stream.
    uint8_t *data;              ///< the byte stream representing the 6LoWPAN frame.
} sixlowpan_lowpan_frame_t;


/**
 * @brief   Initializes 6LoWPAN.
 *
 * @param[in] trans     Transceiver to use with 6LoWPAN.
 * @param[in] r_addr    PHY layer address.
 * @param[in] as_border 1 if node should act as border router,
 *                      0 otherwise.
 */
void sixlowpan_lowpan_init(transceiver_type_t trans, uint8_t r_addr,
                           int as_border);

/**
 * @brief   Initializes a 6LoWPAN router with address prefix
 *
 * @param[in] trans     transceiver to use with 6LoWPAN.
 * @param[in] prefix    the address prefix to advertise.
 * @param[in] r_addr    PHY layer address.
 */
void sixlowpan_lowpan_adhoc_init(transceiver_type_t trans,
                                 const ipv6_addr_t *prefix, 
                                 uint8_t r_addr);

/**
 * @brief   Send data via 6LoWPAN to destination node dest.
 *
 * @param[in] dest      EUI-64 of destination node.
 * @param[in] data      Data to send to destination node (may be 
 *                      manipulated).
 * @param[in] data_len  Length of data.
 */
void sixlowpan_lowpan_sendto(const ieee_802154_long_t *dest, 
                             uint8_t *data, uint16_t data_len);

/**
 * @brief   Set header compression status for 6LoWPAN.
 *
 * @param[in] status    Header compression status to set to.
 */
void sixlowpan_lowpan_set_iphc_status(
    sixlowpan_lowpan_iphc_status_t status);

/**
 * @brief   Registers a thread to read received 6LoWPAN frames. The
 *          6LoWPAN frames are delivered as sixlowpan_lowpan_frame_t
 *          structs.
 *
 * @param[in] pid   The PID of the receiver thread.
 *
 * @return  1 on success, ENOMEM if maximum number of registrable
 *          threads is exceeded.
 */
uint8_t sixlowpan_lowpan_register(int pid);

#if ENABLE_DEBUG
/**
 * @brief   Print current buffer of assembled (i. e. not fragmented)
 *          6LoWPAN packages.
 */
void sixlowpan_lowpan_print_fifo_buffers(void);

/**
 * @brief   Print current buffer for 6LoWPAN fragmentation reassembly.
 */
void sixlowpan_lowpan_print_reassembly_buffers(void);
#endif

/**
 * @}
 */
#endif /* SIXLOWPAN_LOWPAN_H */
