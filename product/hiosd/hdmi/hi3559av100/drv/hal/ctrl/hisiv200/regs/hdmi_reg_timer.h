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

#include "hi_type.h"

#ifndef __HDMI_TX_TIMER_H__
#define __HDMI_TX_TIMER_H__

/* Define the union U_TIMER_11_LOAD */
/* Define the union U_TIMER_11_LOAD,ATTR:,ADDR:0x0000,INIT:00000000,MASK:ffffffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    load       : 32  ; /* [31:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_TIMER_11_LOAD;

/* Define the union U_TIMER_11_VALUE */
/* Define the union U_TIMER_11_VALUE,ATTR:,ADDR:0x0004,INIT:0xFFFFFFFF,MASK:ffffffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    value       : 32  ; /* [31:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_TIMER_11_VALUE;

/* Define the union U_TIMER_11_CONTROL */
/* Define the union U_TIMER_11_CONTROL,ATTR:,ADDR:0x0008,INIT:0x00000000,MASK:ffffffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    oneshot       : 1  ; /* [0] */
        unsigned int    timersize     : 1  ; /* [1] */
        unsigned int    timerpre      : 2  ; /* [3:2] */
    	unsigned int    reserved0     : 1  ; /* [4] */
    	unsigned int    intenable     : 1  ; /* [5] */
    	unsigned int    timermode     : 1  ; /* [6] */
    	unsigned int    timeren       : 1  ; /* [7] */
    	unsigned int    reserved1     : 24 ; /* [31:8] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_TIMER_11_CONTROL;

/* Define the union U_TIMER_11_INTCLR */
/* Define the union U_TIMER_11_INTCLR,ATTR:,ADDR:0x000C,INIT:0x00000000,MASK:ffffffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    intclr       : 32  ; /* [31:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_TIMER_11_INTCLR ;

/* Define the union U_TIMER_11_RIS */
/* Define the union U_TIMER_11_RIS,ATTR:,ADDR:0x0010,INIT:0x00000000,MASK:ffffffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ris     : 1  ; /* [0] */
        unsigned int    reserved0     : 31 ; /* [31:1] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_TIMER_11_RIS;

/* Define the union U_TIMER_11_MIS */
/* Define the union U_TIMER_11_MIS,ATTR:,ADDR:0x0014,INIT:0x00000000,MASK:ffffffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mis     : 1  ; /* [0] */
        unsigned int    reserved0     : 31 ; /* [31:1] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_TIMER_11_MIS;

/* Define the union U_TIMER_11_BGLOAD */
/* Define the union U_TIMER_11_BGLOAD,ATTR:,ADDR:0x0018,INIT:0x00000000,MASK:ffffffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    bgload     : 32  ; /* [31:0] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_TIMER_11_BGLOAD;
//==============================================================================
/* Define the global struct */
typedef struct
{
    volatile U_TIMER_11_LOAD 	TIMER_11_LOAD         ;     /* 0000 */
    volatile U_TIMER_11_VALUE 	TIMER_11_VALUE         ;     /* 0004 */
    volatile U_TIMER_11_CONTROL	TIMER_11_CONTROL     ;     /* 0008 */
    volatile U_TIMER_11_INTCLR	TIMER_11_INTCLR     ;     /* 000C */
    volatile U_TIMER_11_RIS		TIMER_11_RIS         ;     /* 0010 */
    volatile U_TIMER_11_MIS		TIMER_11_MIS         ;     /* 0014 */
    volatile U_TIMER_11_BGLOAD	TIMER_11_BGLOAD     ;     /* 0018 */

} HDMI_REG_TIMER_11_S;


/* Define the union U_SC_CTRL */
/* Define the union U_SC_CTRL,ATTR:,ADDR:0x0000,INIT:0x00000000,MASK:ffffffff*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved0    : 8  ; /* [7:0] */
        unsigned int    remapclear   : 1  ; /* [8] */
        unsigned int    remapstat    : 1  ; /* [9] */
        unsigned int    reserved1    : 5  ; /* [14:10] */
    	unsigned int    wdogenov     : 15 ; /* [15] */
    	unsigned int    timeren0ov   : 16 ; /* [16] */
    	unsigned int    timeren1ov   : 17 ; /* [17] */
    	unsigned int    timeren2ov   : 18 ; /* [18] */
    	unsigned int    timeren3ov   : 19 ; /* [19] */
    	unsigned int    timeren4ov   : 20 ; /* [20] */
    	unsigned int    timeren5ov   : 21 ; /* [21] */
    	unsigned int    timeren6ov   : 22 ; /* [22] */
    	unsigned int    timeren7ov   : 23 ; /* [23] */
    	unsigned int    timeren8ov   : 24 ; /* [24] */
    	unsigned int    timeren9ov   : 25 ; /* [25] */
    	unsigned int    timerenaov   : 26 ; /* [26] */
    	unsigned int    timerenbov   : 27 ; /* [27] */
    	unsigned int    reserved2    : 4  ; /* [31:28] */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SC_CTRL;


typedef struct
{
    volatile U_SC_CTRL 	SC_CTRL         ;     /* 0000 */

} HDMI_REG_SC_CTRL_S;



/* Declare the struct pointor of the module sys_timer_11 */
int HDMI_REG_TIMER_11_S_Init(HI_CHAR *pcAddr);
int HDMI_REG_TIMER_11_S_DeInit(void);

int HDMI_REG_SC_CTRL_S_Init(HI_CHAR *pcAddr);
int HDMI_REG_SC_CTRL_S_DeInit(void);

/* Declare the functions that set the member value */
int HDMI_REG_TIMER_11_loadSet(unsigned int uload);
int HDMI_REG_TIMER_11_control_oneshotSet(unsigned int uoneshot);
int HDMI_REG_TIMER_11_control_timersizeSet(unsigned int utimersize);
int HDMI_REG_TIMER_11_control_timerpreSet(unsigned int utimerpre);
int HDMI_REG_TIMER_11_control_intenableSet(unsigned int uintenable);
int HDMI_REG_TIMER_11_control_timerenSet(unsigned int utimeren);
int HDMI_REG_TIMER_11_intclr_uintclrSet(unsigned int uintclr);
int HDMI_REG_TIMER_11_bgload_bgloadSet(unsigned int ubgload);

int HDMI_REG_SC_CTRL_timerenbovSet(unsigned int utimerenbov);

#endif // __HDMI_TX_TIMER_H__
