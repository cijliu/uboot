/*
* Copyright (c) 2018 HiSilicon Technologies Co., Ltd.
*
* This program is free software; you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the
* Free Software Foundation; either version 2 of the License, or (at your
* option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*
*/
#ifndef __JPEGD_ERROR_H__
#define __JPEGD_ERROR_H__

#include <common.h>

// for SOF error
#define HI_ERR_NOT_BASELINE        0x00000001
#define HI_UNSUPPORT_GRAY_PIC      0x00000002
#define HI_UNSUPPORT_PIC_SIZE      0x00000004
#define HI_UNSUPPORT_PIC_STRUCT    0x00000008
#define HI_UNSUPPORT_YUV411        0x00000010

#define HI_ERR_QUANT_TABLE         0x00000020
#define HI_ERR_HUFFMAN_TABLE       0x00000040
#define HI_ERR_FRAME_HEADER        0x00000080
#define HI_ERR_SCAN_HEADER         0x00000100
#define HI_ERR_RESTART_ERROR       0x00000200
#define HI_ERR_UNSUPPORT_DNL       0x00000400

#define HI_DBG_EMERG               0 /* system is unusable                   */
#define HI_DBG_ALERT               1 /* action must be taken immediately     */
#define HI_DBG_CRIT                2 /* critical conditions                  */
#define HI_DBG_ERR                 3 /* error conditions                     */
#define HI_DBG_WARN                4 /* warning conditions                   */
#define HI_DBG_NOTICE              5 /* normal but significant condition     */
#define HI_DBG_INFO                6 /* informational                        */
#define HI_DBG_DEBUG               7 /* debug-level messages                 */

#define HI_ID_JPEGD                14


#define HI_TRACE(fmt...)                             \
    do {                                             \
        printf("[%s]-%d: ", __FUNCTION__, __LINE__); \
        printf(fmt);                                 \
    } while (0)

/**************************************************************************************/
/* invlalid channel ID */
#define HI_ERR_JPEGD_INVALID_CHNID HI_DEF_ERR(HI_ID_JPEGD, EN_ERR_LEVEL_ERROR, EN_ERR_INVALID_CHNID)
/* at lease one parameter is illagal ,eg, an illegal enumeration value  */
#define HI_ERR_JPEGD_ILLEGAL_PARAM HI_DEF_ERR(HI_ID_JPEGD, EN_ERR_LEVEL_ERROR, EN_ERR_ILLEGAL_PARAM)
/* channel exists */
#define HI_ERR_JPEGD_EXIST         HI_DEF_ERR(HI_ID_JPEGD, EN_ERR_LEVEL_ERROR, EN_ERR_EXIST)
/* using a NULL point */
#define HI_ERR_JPEGD_NULL_PTR      HI_DEF_ERR(HI_ID_JPEGD, EN_ERR_LEVEL_ERROR, EN_ERR_NULL_PTR)
/* try to enable or initialize system,device or channel, before configing attribute */
#define HI_ERR_JPEGD_NOT_CONFIG    HI_DEF_ERR(HI_ID_JPEGD, EN_ERR_LEVEL_ERROR, EN_ERR_NOT_CONFIG)
/* operation is not supported by NOW */
#define HI_ERR_JPEGD_NOT_SURPPORT  HI_DEF_ERR(HI_ID_JPEGD, EN_ERR_LEVEL_ERROR, EN_ERR_NOT_SUPPORT)
/* operation is not permitted ,eg, try to change stati attribute */
#define HI_ERR_JPEGD_NOT_PERM      HI_DEF_ERR(HI_ID_JPEGD, EN_ERR_LEVEL_ERROR, EN_ERR_NOT_PERM)
/* the channle is not existed  */
#define HI_ERR_JPEGD_UNEXIST       HI_DEF_ERR(HI_ID_JPEGD, EN_ERR_LEVEL_ERROR, EN_ERR_UNEXIST)
/* failure caused by malloc memory */
#define HI_ERR_JPEGD_NOMEM         HI_DEF_ERR(HI_ID_JPEGD, EN_ERR_LEVEL_ERROR, EN_ERR_NOMEM)
/* failure caused by malloc buffer */
#define HI_ERR_JPEGD_NOBUF         HI_DEF_ERR(HI_ID_JPEGD, EN_ERR_LEVEL_ERROR, EN_ERR_NOBUF)
/* no data in buffer */
#define HI_ERR_JPEGD_BUF_EMPTY     HI_DEF_ERR(HI_ID_JPEGD, EN_ERR_LEVEL_ERROR, EN_ERR_BUF_EMPTY)
/* no buffer for new data */
#define HI_ERR_JPEGD_BUF_FULL      HI_DEF_ERR(HI_ID_JPEGD, EN_ERR_LEVEL_ERROR, EN_ERR_BUF_FULL)
/* system is not ready,had not initialed or loaded */
#define HI_ERR_JPEGD_SYS_NOTREADY  HI_DEF_ERR(HI_ID_JPEGD, EN_ERR_LEVEL_ERROR, EN_ERR_SYS_NOTREADY)
/* system busy */
#define HI_ERR_JPEGD_BUSY          HI_DEF_ERR(HI_ID_JPEGD, EN_ERR_LEVEL_ERROR, EN_ERR_BUSY)

/* bad address,  eg. used for copy_from_user & copy_to_user   */
#define HI_ERR_JPEGD_BADADDR       HI_DEF_ERR(HI_ID_JPEGD, EN_ERR_LEVEL_ERROR, EN_ERR_BADADDR)


#endif /* End of __JPEGD_ERROR_H__ */