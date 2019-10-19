#include <common.h>
#include <command.h>
#include <ufs.h>

int curr_device = 0;

#ifdef CONFIG_EXT4_SPARSE
extern int ufs_ext4_unsparse(const u8 *pbuf, u32 blk, u32 cnt);
#endif

unsigned long ticks2usec(unsigned long ticks)
{
	ulong tbclk = get_tbclk();

	ticks *= 1000L;
	ticks /= tbclk;
	ticks *= 1000L;

	return ((ulong)ticks);
}

#define UFS_BLKSIZE_SHIFT  (12)
#define B2M(a) ((a)/1000000)
#define B2K(a) (((a)/1000)%1000)
#define B2B(a) ((a)%1000)

static int do_ufs_read(cmd_tbl_t *cmdtp, int flag,
		       int argc, char * const argv[])
{
	unsigned long long start_ticks, end_ticks;
	unsigned long long size = 0;
	u32 blk = 0, cnt = 0, n = 0;
	void *addr;

	if (argc != 5) {
		printf("UFS read argc %d invalid\n", argc);
		return CMD_RET_USAGE;
	}
	addr = (void *)simple_strtoul(argv[2], NULL, 16);
	blk = simple_strtoul(argv[3], NULL, 16);
	cnt = simple_strtoul(argv[4], NULL, 16);

	printf("\nUFS read: dev # %d, block # %d, count %d ...\n",
		curr_device, blk, cnt);

	if (ufs_storage_init() != 0)
		return -1;

	start_ticks = get_ticks();

	if (ufs_read_storage((uint64_t)addr, (blk << UFS_BLKSIZE_SHIFT),
		(cnt << UFS_BLKSIZE_SHIFT)) == 0)
		n = cnt;

	end_ticks = get_ticks();
	size = (cnt << UFS_BLKSIZE_SHIFT);
/*
printf("size:%lld B  start:%llu  end:%llu  usec:%llu\n",
			  size, start_ticks, end_ticks,
			  (uint64_t)ticks2usec(end_ticks - start_ticks));
*/
uint64_t speed = (uint64_t)(size*1000000)/
		 ticks2usec(end_ticks - start_ticks);
	int mB = (int)B2M(speed);

	if (mB)
		printf("%d.%lld MB/s\n", mB, B2K(speed));
	else
		printf("%lld.%lld KB/s\n", B2K(speed), B2B(speed));
	printf("%d blocks read: %s\n", n, (n == cnt) ? "OK" : "ERROR");

	return (n == cnt) ? CMD_RET_SUCCESS : CMD_RET_FAILURE;
}
static int do_ufs_write(cmd_tbl_t *cmdtp, int flag,
			int argc, char * const argv[])
{
	unsigned long long start_ticks, end_ticks;
	unsigned long long size = 0;
	u32 blk = 0, cnt = 0, n = 0;
	void *addr;

	if (argc != 5) {
		printf("UFS write argc %d invalid\n", argc);
		return CMD_RET_USAGE;
	}

	addr = (void *)simple_strtoul(argv[2], NULL, 16);
	blk = simple_strtoul(argv[3], NULL, 16);
	cnt = simple_strtoul(argv[4], NULL, 16);

#ifdef CONFIG_EXT4_SPARSE
	if (!strcmp(argv[0], "write.ext4sp")) {
		printf("\nUFS write ext4 sparse: dev # %d, "
			"block # %d, count %d ... ",
			curr_device, blk, cnt);
		return ufs_ext4_unsparse(addr, blk, cnt);
	}
#endif

	printf("\nUFS write: dev # %d, block # %d, count %d ...\n",
	       curr_device, blk, cnt);

	if (ufs_storage_init() != 0)
		return -1;

	if ((blk == 0) && (cnt <= 0x400))	/*insert write boot when block == 0*/
		ufs_write_boot_storage((uint64_t)addr, (blk << UFS_BLKSIZE_SHIFT),
			(cnt << UFS_BLKSIZE_SHIFT));

	start_ticks = get_ticks();

	if (ufs_write_storage((uint64_t)addr, (blk << UFS_BLKSIZE_SHIFT),
		(cnt << UFS_BLKSIZE_SHIFT)) == 0)
		n = cnt;


	end_ticks = get_ticks();
	size = (cnt << UFS_BLKSIZE_SHIFT);
/*
	printf("size:%lld B  start:%llu  end:%llu  usec:%llu\n",
			size, start_ticks, end_ticks, i
			(uint64_t)ticks2usec(end_ticks - start_ticks));
*/
	uint64_t speed = (uint64_t)(size*1000000)/
		ticks2usec(end_ticks - start_ticks);
	int mB = (int)B2M(speed);

	if (mB)
		printf("%d.%lld MB/s\n", mB, B2K(speed));
	else
		printf("%lld.%lld KB/s\n", B2K(speed), B2B(speed));
	printf("%d blocks write: %s\n", n, (n == cnt) ? "OK" : "ERROR");

	return (n == cnt) ? CMD_RET_SUCCESS : CMD_RET_FAILURE;
}

static int do_ufs_hibernate_enter(cmd_tbl_t *cmdtp, int flag,
			int argc, char * const argv[])
{
	u32 pwr;

	if (argc != 2) {
		printf("UFS Hibernate Enter argc %d invalid\n", argc);
		return CMD_RET_USAGE;
	}
	pwr = simple_strtoul(argv[2], NULL, 16);
	return ufs_hibernate_enter(pwr);
}

static int do_ufs_hibernate_exit(cmd_tbl_t *cmdtp, int flag,
			int argc, char * const argv[])
{
	u32 pwr;

	if (argc != 2) {
		printf("UFS Hibernate Exit argc %d invalid\n", argc);
		return CMD_RET_USAGE;
	}
	pwr = simple_strtoul(argv[2], NULL, 16);
	printf("pwr = %d\n", pwr);
	return ufs_hibernate_exit(pwr);
}
static int do_ufs_reg(cmd_tbl_t *cmdtp, int flag,
			int argc, char * const argv[])
{
	switch (argc) {
	case 0:
	case 1:
		if (strncmp(argv[0], "reg", sizeof("reg")) == 0)
		{
			ufs_readreg_all();
		}
		break;

	default: /* at least 5 args */
		ufs_reg_param(argc,argv);
		break;
	}
	return CMD_RET_SUCCESS;
}
static cmd_tbl_t cmd_ufs[] = {
	U_BOOT_CMD_MKENT(read, 6, 1, do_ufs_read, "", ""),
	U_BOOT_CMD_MKENT(write, 6, 1, do_ufs_write, "", ""),
	U_BOOT_CMD_MKENT(hi, 3, 1, do_ufs_hibernate_enter, "", ""),
	U_BOOT_CMD_MKENT(ho, 3, 1, do_ufs_hibernate_exit, "", ""),
	U_BOOT_CMD_MKENT(reg, 6, 1, do_ufs_reg, "", ""),
};

static int do_ufsops(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	cmd_tbl_t *cp;

	cp = find_cmd_tbl(argv[1], cmd_ufs, ARRAY_SIZE(cmd_ufs));

	/* Drop the ufs command */
	argc--;
	argv++;

	if (cp == NULL || argc > cp->maxargs)
		return CMD_RET_USAGE;
	if (flag == CMD_FLAG_REPEAT && !cp->repeatable)
		return CMD_RET_SUCCESS;
	return cp->cmd(cmdtp, flag, argc, argv);
}

U_BOOT_CMD(
	ufs, 6, 1, do_ufsops,
	"UFS sub system",
	"ufs read <device num> addr blk# cnt\n"
	"ufs write <device num> addr blk# cnt\n"
	"ufs hi <pwr>\n"
	"ufs ho <pwr>\n"
	"ufs reg <cmd> <attr_sel > [attr_set] [mib_val]\n"
	"    cmd:1---DME_GET; e.g: ufs reg 0x1 0x15000000\n"
	"    cmd:2---DME_SET; e.g: ufs reg 0x2 0x15a70000 0 0x23\n"
	"    cmd:17---DME_HIBERNATE_ENTER\n"
	"    cmd:17---DME_HIBERNATE_EXIT\n"
	);
static int do_ufsinfo(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	u32 type = 0;
	switch (argc) {
	case 0:
	case 1:
		cmd_usage(cmdtp);
	break;
	case 2:
			type = simple_strtoul(argv[1], NULL, 10);
			ufs_show_desc_info(type);
		break;
	default:
		UFS_PRINT("unknow cmd.\n");
		break;
		}
	return 1;
}
U_BOOT_CMD(ufsinfo, 3, 1, do_ufsinfo,
	"ufsinfo <idn> -- display UFS info",
	"\n"
	"    idn :0xFF -- show basic info\n"
	"    idn :0x0 -- show device descriptor info\n"
	"    idn :0x1 -- show configuration descriptor info\n"
	"    idn :0x2 -- show unit descriptor info\n"
	"    idn :0x5 -- show string descriptor info\n"
	"    idn :0x7 -- show geometry descriptor info\n"
	"    idn :0x9 -- show health descriptor info\n"
	"    idn :0x10 -- show all info\n"
);
