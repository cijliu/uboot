//#include <linux/bcma/bcma.h>
//#include <linux/delay.h>
//#include <linux/platform_device.h>
//#include <linux/module.h>
//#include <linux/slab.h>
//#include <linux/dma-mapping.h>

#include <config.h>
#include <common.h>
#include <part.h>
#include <malloc.h>
//#include <asm/errno.h>
#include <asm/io.h>

/*lint -e514 -e734*/
#include "scsi.h"
#include "ufs.h"

#ifdef LOG_TAG
#undef LOG_TAG
#endif

#define LOG_TAG /*lint -save -e750 -specific(-e750)*/"ufs"/*lint -restore*/

unsigned int ufs_scsi_rw_fua;
#define FORCE_UNIT_ACCESS (1 << 3)
unsigned int ufs_scsi_rw_fua = FORCE_UNIT_ACCESS;
unsigned int ufs_scsi_rw_dpo;
unsigned int ufs_scsi_rw_group_number;

unsigned int ufs_scsi_report_code;

unsigned int ufs_scsi_mode_page_ctrl;
unsigned int ufs_scsi_mode_page_code;
unsigned int ufs_scsi_mode_subpage_code;

unsigned int ufs_scsi_mode_select_sp;

unsigned int ufs_scsi_cache_sync_NV;
unsigned int ufs_scsi_cache_sync_IMMED;

unsigned int ufs_scsi_start_stop_immed;
unsigned int ufs_scsi_start_stop_power_condition;
unsigned int ufs_scsi_start_stop_no_flush;
unsigned int ufs_scsi_start_stop_start;

unsigned int ufs_scsi_send_diagnostic_selftest_code;
unsigned int ufs_scsi_send_diagnostic_PF;
unsigned int ufs_scsi_send_diagnostic_selftest;
unsigned int ufs_scsi_send_diagnostic_DEVOFFL;
unsigned int ufs_scsi_send_diagnostic_UNITOFFL;

unsigned int ufs_scsi_pre_fetch_immed;

static void get_cmnd(uint32_t opcode, uint32_t lba, uint32_t size, uint8_t *cmd)
{
    //UFS_PRINT("opcode: 0x%x; LBA: %d; size: %d\n", opcode, lba, size);
    memset(cmd, 0x0, 16);

    switch (opcode) {
        case UFS_OP_READ_10:
            cmd[0] = UFS_OP_READ_10;
            cmd[1] = 0;
            if (ufs_scsi_rw_fua) {
                cmd[1] |= 1 << 3;
            }
            if (ufs_scsi_rw_dpo) {
                cmd[1] |= 1 << 4;
            }
            cmd[2] = (uint8_t)((lba & 0xff000000) >> 24); /* MSB Byte */
            cmd[3] = (uint8_t)((lba & 0x00ff0000) >> 16);
            cmd[4] = (uint8_t)((lba & 0x0000ff00) >> 8);
            cmd[5] = (uint8_t)(lba & 0x000000ff); /* LSB byte */
            cmd[6] = ufs_scsi_rw_group_number & 0x1f;
            cmd[7] = (uint8_t)((size >> 8) & 0xff);
            cmd[8] = (uint8_t)((size) & 0xff);
            cmd[9] = 0;
            break;

        case UFS_OP_WRITE_10:
            cmd[0] = UFS_OP_WRITE_10;
            cmd[1] = 0;
            if (ufs_scsi_rw_fua) {
                cmd[1] |= 1 << 3;
            }
            if (ufs_scsi_rw_dpo) {
                cmd[1] |= 1 << 4;
            }
            cmd[2] = (uint8_t)((lba & 0xff000000) >> 24); /* MSB Byte */
            cmd[3] = (uint8_t)((lba & 0x00ff0000) >> 16);
            cmd[4] = (uint8_t)((lba & 0x0000ff00) >> 8);
            cmd[5] = (uint8_t)(lba & 0x000000ff); /* LSB byte */
            cmd[6] = ufs_scsi_rw_group_number & 0x1f;
            cmd[7] = (uint8_t)((size >> 8) & 0xff);
            cmd[8] = (uint8_t)((size) & 0xff);
            cmd[9] = 0;
            break;

        case UFS_OP_READ_6:
            cmd[0] = UFS_OP_READ_6;
            cmd[1] = 0;
            cmd[2] = (uint8_t)((lba & 0x0000ff00) >> 8);
            cmd[3] = (uint8_t)(lba & 0x000000ff);
            cmd[4] = (uint8_t)((size) & 0xff);
            if ((size > 0x100) || (size == 0) || (lba > 0xffff))
                PRINT_ERROR("WARRING!!!! UFS READ 6 lba or size is not "
                            "support\n");
            break;

        case UFS_OP_WRITE_6:
            cmd[0] = UFS_OP_WRITE_6;
            cmd[1] = 0;
            cmd[2] = (uint8_t)((lba & 0x0000ff00) >> 8);
            cmd[3] = (uint8_t)(lba & 0x000000ff);
            cmd[4] = (uint8_t)((size) & 0xff);
            if ((size > 0x100) || (size == 0) || (lba > 0xffff))
                PRINT_ERROR("WARRING!!!! UFS WRITE 6 lba or size is "
                            "not support\n");
            break;

        case UFS_OP_VERIFY_10:
            cmd[0] = UFS_OP_VERIFY_10;
            cmd[1] = 0;
            cmd[2] = (uint8_t)((lba & 0xff000000) >> 24); /* MSB Byte */
            cmd[3] = (uint8_t)((lba & 0x00ff0000) >> 16);
            cmd[4] = (uint8_t)((lba & 0x0000ff00) >> 8);
            cmd[5] = (uint8_t)(lba & 0x000000ff); /* LSB byte */
            cmd[6] = 0;
            cmd[7] = (uint8_t)((size >> 8) & 0xff);
            cmd[8] = (uint8_t)((size) & 0xff);
            cmd[9] = 0;
            break;

        case UFS_OP_SEND_DIAGNOSTIC:
            cmd[0] = UFS_OP_SEND_DIAGNOSTIC;
            cmd[1] = ((ufs_scsi_send_diagnostic_selftest_code & 0x7) << 5) |
                     ((ufs_scsi_send_diagnostic_PF & 0x1) << 4) |
                     ((ufs_scsi_send_diagnostic_selftest & 0x1) << 2) |
                     ((ufs_scsi_send_diagnostic_DEVOFFL & 0x1) << 1) |
                     (ufs_scsi_send_diagnostic_UNITOFFL & 0x1);
            cmd[2] = 0;
            cmd[3] = (uint8_t)((size >> 8) & 0xff);
            cmd[4] = (uint8_t)((size) & 0xff);
            cmd[5] = 0;
            break;

        case UFS_OP_PRE_FETCH_10:
            cmd[0] = UFS_OP_PRE_FETCH_10;
            cmd[1] = (ufs_scsi_pre_fetch_immed & 0x1) << 1;
            cmd[2] = (uint8_t)((lba & 0xff000000) >> 24); /* MSB Byte */
            cmd[3] = (uint8_t)((lba & 0x00ff0000) >> 16);
            cmd[4] = (uint8_t)((lba & 0x0000ff00) >> 8);
            cmd[5] = (uint8_t)(lba & 0x000000ff); /* LSB byte */
            cmd[6] = 0;
            cmd[7] = (uint8_t)((size >> 8) & 0xff);
            cmd[8] = (uint8_t)((size) & 0xff);
            cmd[9] = 0;
            break;

        case UFS_OP_SYNCHRONIZE_CACHE_10:
            cmd[0] = UFS_OP_SYNCHRONIZE_CACHE_10;
            cmd[1] = ((uint8_t)ufs_scsi_cache_sync_NV << 2) | ((uint8_t)ufs_scsi_cache_sync_IMMED << 1);
            cmd[2] = (uint8_t)((lba & 0xff000000) >> 24); /* MSB Byte */
            cmd[3] = (uint8_t)((lba & 0x00ff0000) >> 16);
            cmd[4] = (uint8_t)((lba & 0x0000ff00) >> 8);
            cmd[5] = (uint8_t)(lba & 0x000000ff); /* LSB byte */
            cmd[6] = 0;
            cmd[7] = (uint8_t)((size >> 8) & 0xff);
            cmd[8] = (uint8_t)((size) & 0xff);
            cmd[9] = 0;
            break;
        case UFS_OP_UNMAP:
            cmd[0] = UFS_OP_UNMAP;
            cmd[1] = 0;
            cmd[2] = 0;
            cmd[3] = 0;
            cmd[4] = 0;
            cmd[5] = 0;
            cmd[6] = 0;
            cmd[7] = (uint8_t)((size >> 8) & 0xff);
            cmd[8] = (uint8_t)((size) & 0xff);
            cmd[9] = 0;
            break;
        case UFS_OP_TEST_UNIT_READY:
            cmd[0] = UFS_OP_TEST_UNIT_READY;
            cmd[1] = 0;
            cmd[2] = 0;
            cmd[3] = 0;
            cmd[4] = 0;
            cmd[5] = 0;
            break;

        case UFS_OP_READ_CAPACITY_10:
            cmd[0] = UFS_OP_READ_CAPACITY_10;
            cmd[1] = 0;
            cmd[2] = 0;
            cmd[3] = 0;
            cmd[4] = 0;
            cmd[5] = 0;
            cmd[6] = 0;
            cmd[7] = 0;
            cmd[8] = 0;
            cmd[9] = 0;
            if (size < 8)
                PRINT_ERROR("WARRING!!!! %s READ CAPACITY with not "
                            "enough buffer\n", LOG_TAG);
            break;
        case UFS_OP_START_STOP_UNIT:
            cmd[0] = UFS_OP_START_STOP_UNIT;
            cmd[1] = ufs_scsi_start_stop_immed & 0x1;
            cmd[2] = 0;
            cmd[3] = 0;
            cmd[4] = ((ufs_scsi_start_stop_power_condition & 0xf) << 4) |
                     ((ufs_scsi_start_stop_no_flush & 0x1) << 2) |
                     (ufs_scsi_start_stop_start & 0x1);
            cmd[5] = 0;
            break;
        case UFS_OP_MODE_SELECT_10:
            cmd[0] = UFS_OP_MODE_SELECT_10;
            cmd[1] = (1 << 4) | (!!ufs_scsi_mode_select_sp);
            cmd[2] = 0;
            cmd[3] = 0;
            cmd[4] = 0;
            cmd[5] = 0;
            cmd[6] = 0;
            cmd[7] = (uint8_t)((size >> 8) & 0xff);
            cmd[8] = (uint8_t)((size) & 0xff);
            cmd[9] = 0;
            break;

        case UFS_OP_MODE_SENSE_10:
            cmd[0] = UFS_OP_MODE_SENSE_10;
            cmd[1] = 1 << 3;
            cmd[2] = ((uint8_t)ufs_scsi_mode_page_ctrl << 6) | (uint8_t)ufs_scsi_mode_page_code;
            cmd[3] = (uint8_t)ufs_scsi_mode_subpage_code;
            cmd[4] = 0;
            cmd[5] = 0;
            cmd[6] = 0;
            cmd[7] = (uint8_t)((size >> 8) & 0xff);
            cmd[8] = (uint8_t)((size) & 0xff);
            cmd[9] = 0;
            break;

        case UFS_OP_REQUEST_SENSE:
            cmd[0] = UFS_OP_REQUEST_SENSE;
            cmd[1] = 0;
            cmd[2] = 0;
            cmd[3] = 0;
            cmd[4] = (uint8_t)((size) & 0xff);
            cmd[5] = 0;
            break;

        case UFS_OP_REPORT_LUNS:
            cmd[0] = UFS_OP_REPORT_LUNS;
            cmd[1] = 0;
            cmd[2] = (uint8_t)ufs_scsi_report_code;
            cmd[3] = 0;
            cmd[4] = 0;
            cmd[5] = 0;
            cmd[6] = (uint8_t)(size >> 24);
            cmd[7] = (uint8_t)((size >> 16) & 0xff);
            cmd[8] = (uint8_t)((size >> 8) & 0xff);
            cmd[9] = (uint8_t)(size & 0xff);
            cmd[10] = 0;
            cmd[11] = 0;
            break;

        case UFS_OP_INQUIRY:
            cmd[0] = UFS_OP_INQUIRY;
            cmd[1] = 0;
            cmd[2] = 0;
            cmd[3] = (uint8_t)((size >> 8) & 0xff);
            cmd[4] = (uint8_t)((size) & 0xff);
            cmd[5] = 0;
            break;

        case UFS_OP_FORMAT_UNIT:
            cmd[0] = UFS_OP_FORMAT_UNIT;
            cmd[1] = 0;
            cmd[2] = 0;
            cmd[3] = 0;
            cmd[4] = 0;
            cmd[5] = 0;
            break;

        case UFS_OP_SECURITY_PROTOCOL_IN:
            cmd[0] = UFS_OP_SECURITY_PROTOCOL_IN;
            cmd[1] = SECURITY_PROTOCOL; /* Manju updated from 0x00 */
            cmd[2] = 0x00;
            cmd[3] = 0x01;
            cmd[4] = 0x00;
            cmd[5] = 0x00;
            cmd[6] = (uint8_t)(size >> 24);
            cmd[7] = (uint8_t)((size >> 16) & 0xff);
            cmd[8] = (uint8_t)((size >> 8) & 0xff);
            cmd[9] = (uint8_t)(size & 0xff);
            cmd[10] = 0x00;
            cmd[11] = 0x00;
            break;

        case UFS_OP_SECURITY_PROTOCOL_OUT:
            cmd[0] = UFS_OP_SECURITY_PROTOCOL_OUT;
            cmd[1] = SECURITY_PROTOCOL;
            cmd[2] = 0x00;
            cmd[3] = 0x01;
            cmd[4] = 0x00;
            cmd[6] = (uint8_t)((size >> 24));
            cmd[7] = (uint8_t)((size >> 16) & 0xff);
            cmd[8] = (uint8_t)((size >> 8) & 0xff);
            cmd[9] = (uint8_t)(size & 0xff);
            cmd[10] = 0x00;
            cmd[11] = 0x00;
            break;

        case UFS_OP_WRITE_BUFFER: //just for hynix FFU cmd
            if (size != 0x40000) {
                UFS_PRINT("size is 0x%x, not 0x40000!!!!!!!!\n", size);
            }
            cmd[0] = UFS_OP_WRITE_BUFFER;
            cmd[1] = 0xE;
            cmd[2] = 0;
            cmd[3] = 0;
            cmd[4] = 0;
            cmd[5] = 0;
            cmd[6] = (uint8_t)((size >> 16) & 0xff);
            cmd[7] = (uint8_t)((size >> 8) & 0xff);
            cmd[8] = (uint8_t)(size & 0xff);
            cmd[9] = 0;
            break;

        default:
            break;
    }
}
/*lint +e514 +e734*/
