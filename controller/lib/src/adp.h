/*
 * Licensed under the MIT License (MIT)
 *
 * Copyright (c) 2013 AudioScience Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * adp.h
 *
 * AVDECC Discovery Protocol class
 */

#pragma once
#ifndef _AVDECC_CONTROLLER_LIB_ADP_H_
#define _AVDECC_CONTROLLER_LIB_ADP_H_

#include "jdksavdecc_adp.h"

namespace avdecc_lib
{
    class adp
    {
    private:
        struct jdksavdecc_frame ether_frame; // Structure containing the Ethernet Frame fields
        struct jdksavdecc_adpdu adpdu; // Structure containing the ADPDU fields
        uint8_t *adp_frame; // Point to a raw memory buffer to read from
        int frame_read_returned; // Status of extracting Ethernet Frame information from a network buffer
        int adpdu_read_returned; // Status of extracting ADPDU information from a network buffer

    public:
        enum ether_hdr_info
        {
            SRC_MAC_SIZE = 6,
            DEST_MAC_SIZE = 6,
            ETHER_PROTOCOL_SIZE = 2,
            ETHER_HDR_SIZE = SRC_MAC_SIZE + DEST_MAC_SIZE + ETHER_PROTOCOL_SIZE, // The header size of the Ethernet frame = dest mac + src mac + ether protocol sizes

        };

        enum protocol_hdr_info
        {
            PROTOCOL_HDR_SIZE = 4 // The Protocol Header size
        };

        /**
         * Constructor for ADP used for constructing an object with a base pointer and memory buffer length.
         */
        adp(const uint8_t *frame, size_t frame_len);

        ~adp();

        /**
         * Get the Ethernet type of the ADP packet.
         */
        inline uint16_t get_ethernet_type()
        {
            return ether_frame.ethertype;
        }

        /**
         * Get the source address of the ADP packet.
         */
        inline struct jdksavdecc_eui48 get_src_addr()
        {
            return ether_frame.src_address;
        }

        /**
         * Get the destination of the ADP packet.
         */
        inline struct jdksavdecc_eui48 get_dest_addr()
        {
            return ether_frame.dest_address;
        }

        /**
         * Get the Controller GUID of the AVDECC Entity sending the command.
         */
        static struct jdksavdecc_eui64 get_controller_guid();

        /**
         * Initialize and fill Ethernet frame payload with Ethernet frame information for ADP messages.
         */
        static int ether_frame_init(struct jdksavdecc_frame *ether_frame);

        /**
         * Initialize and fill Ethernet frame payload with 1722 ADP Header information.
         */
        static void adpdu_common_hdr_init(struct jdksavdecc_frame *ether_frame, uint64_t target_guid);

        /**
         * Get the header field of the ADP object.
         */
        inline struct jdksavdecc_adpdu_common_control_header get_hdr()
        {
            return adpdu.header;
        }

        /**
         * Get the Entity GUID field of the ADP object.
         */
        inline uint64_t get_entity_entity_id()
        {
            return jdksavdecc_uint64_get(&adpdu.header.entity_id, 0);
        }

        /**
         * Get the Entity model id field of the ADP object.
         */
        inline uint64_t get_entity_model_id()
        {
            return jdksavdecc_uint64_get(&adpdu.entity_model_id, 0);
        }

        /**
         * Get the Entity capabilities field of the ADP object.
         */
        inline uint32_t get_entity_capabilities()
        {
            return adpdu.entity_capabilities;
        }

        /**
         * Get the Talker stream sources field of the ADP object.
         */
        inline uint16_t get_talker_stream_sources()
        {
            return adpdu.talker_stream_sources;
        }

        /**
         * Get the Talker capabilities field of the ADP object.
         */
        inline uint16_t get_talker_capabilities()
        {
            return adpdu.talker_capabilities;
        }

        /**
         * Get the Listener stream sinks field of the ADP object.
         */
        inline uint16_t get_listener_stream_sinks()
        {
            return adpdu.listener_stream_sinks;
        }

        /**
         * Get the Listener capabilities field of the ADP object.
         */
        inline uint16_t get_listener_capabilities()
        {
            return adpdu.listener_capabilities;
        }

        /**
         * Get the Controller capabilities field of the ADP object.
         */
        inline uint32_t get_controller_capabilities()
        {
            return adpdu.controller_capabilities;
        }

        /**
         * Get the available index field of the ADP object.
         */
        inline uint32_t get_available_index()
        {
            return adpdu.available_index;
        }

        /**
         * Get the GPTP grandmaster id field of the ADP object.
         */
        inline uint64_t get_gptp_grandmaster_id()
        {
            return jdksavdecc_uint64_get(&adpdu.gptp_grandmaster_id, 0);
        }

        /**
         * Get the GPTP domain number field of the ADP object.
         */
        inline uint8_t get_gptp_domain_number()
        {
            return adpdu.gptp_domain_number;
        }

        /**
         * Get the reserved0 field of the ADP object.
         */
        inline uint32_t get_reserved0()
        {
            return adpdu.reserved0;
        }

        /**
         * Get the identify control index field of the ADP object.
         */
        inline uint16_t get_identify_control_index()
        {
            return adpdu.identify_control_index;
        }

        /**
         * Get the interface index field of the ADP object.
         */
        inline uint16_t get_interface_index()
        {
            return adpdu.interface_index;
        }

        /**
         * Get the association id field of the ADP object.
         */
        inline uint64_t get_association_id()
        {
            return jdksavdecc_uint64_get(&adpdu.association_id, 0);
        }

        /**
         * Get the reserved1 field of the ADPDU object.
         */
        inline uint32_t get_reserved1()
        {
            return adpdu.reserved1;
        }
    };
}

#endif
