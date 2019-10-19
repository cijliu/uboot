/*
 * (C) Copyright 2008-2011 Freescale Semiconductor, Inc.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

/* #define DEBUG */

#include <common.h>

#include <command.h>
#include <environment.h>
#include <linux/stddef.h>
#include <malloc.h>
#include <memalign.h>
#include <search.h>
#include <errno.h>
#include <ufs.h>

#define UFS_BLKSIZE_SHIFT  (12)
#define UFS_ALIGN_SIZE  (4096)

#if defined(CONFIG_ENV_SIZE_REDUND) &&  \
	(CONFIG_ENV_SIZE_REDUND != CONFIG_ENV_SIZE)
#error CONFIG_ENV_SIZE_REDUND should be the same as CONFIG_ENV_SIZE
#endif

char *ufs_env_name_spec = "UFS";

DECLARE_GLOBAL_DATA_PTR;

#if !defined(CONFIG_ENV_OFFSET)
#define CONFIG_ENV_OFFSET 0
#endif

__weak int ufs_get_env_addr(int copy, u32 *env_addr)
{
	s64 offset;

	offset = CONFIG_ENV_OFFSET;
#ifdef CONFIG_ENV_OFFSET_REDUND
	if (copy)
		offset = CONFIG_ENV_OFFSET_REDUND;
#endif
	*env_addr = offset;
	return 0;
}

int ufs_env_init(void)
{
	/* use default */
	gd->env_addr	= (ulong)&default_environment[0];
	gd->env_valid	= 1;

	return 0;
}

static const char *init_ufs_for_env(void)
{
	if (ufs_storage_init())
		return "!UFS init failed";

	return NULL;
}

#ifdef CONFIG_CMD_SAVEENV
static inline int write_env(unsigned long size,
			    unsigned long offset, const void *buffer)
{
	uint blk_start, blk_cnt, n;

	blk_start	= ALIGN(offset, UFS_ALIGN_SIZE);
	blk_cnt		= ALIGN(size, UFS_ALIGN_SIZE);

	if (ufs_write_storage((uint64_t)buffer, blk_start, blk_cnt) == 0)
		n = blk_cnt;

	return (n == blk_cnt) ? 0 : -1;
}

#ifdef CONFIG_ENV_OFFSET_REDUND
static unsigned char env_flags;
#endif

int ufs_saveenv(void)
{
	ALLOC_CACHE_ALIGN_BUFFER(env_t, env_new, 1);
	u32	offset;
	int	ret, copy = 0;
	const char *errmsg;

	errmsg = init_ufs_for_env();
	if (errmsg) {
		printf("%s\n", errmsg);
		return 1;
	}

	ret = env_export(env_new);
	if (ret)
		goto err;

#ifdef CONFIG_ENV_OFFSET_REDUND
	env_new->flags	= ++env_flags; /* increase the serial */

	if (gd->env_valid == 1)
		copy = 1;
#endif

	if (ufs_get_env_addr(copy, &offset)) {
		ret = 1;
		goto err;
	}

	printf("Writing to %sUFS... ", copy ? "redundant " : "");
	if (write_env(CONFIG_ENV_SIZE, offset, (u_char *)env_new)) {
		puts("failed\n");
		ret = 1;
		goto err;
	}

	puts("done\n");
	ret = 0;

#ifdef CONFIG_ENV_OFFSET_REDUND
	gd->env_valid = gd->env_valid == 2 ? 1 : 2;
#endif

err:
	return ret;
}
#endif /* CONFIG_CMD_SAVEENV */

static inline int read_env(unsigned long size,
			   unsigned long offset, const void *buffer)
{
	uint blk_start, blk_cnt, n;

	blk_start	= ALIGN(offset, UFS_ALIGN_SIZE);
	blk_cnt		= ALIGN(size, UFS_ALIGN_SIZE);

	if (ufs_read_storage((uint64_t)buffer, blk_start, blk_cnt) == 0)
		n = blk_cnt;

	return (n == blk_cnt) ? 0 : -1;
}

#ifdef CONFIG_ENV_OFFSET_REDUND
void ufs_env_relocate_spec(void)
{
#if !defined(ENV_IS_EMBEDDED)
	u32 offset1, offset2;
	int read1_fail = 0, read2_fail = 0;
	int crc1_ok = 0, crc2_ok = 0;
	env_t *ep;
	int ret;
	const char *errmsg = NULL;

	ALLOC_CACHE_ALIGN_BUFFER(env_t, tmp_env1, 1);
	ALLOC_CACHE_ALIGN_BUFFER(env_t, tmp_env2, 1);

#ifdef CONFIG_SPL_BUILD
	dev = 0;
#endif

	errmsg = init_ufs_for_env();
	if (errmsg) {
		ret = 1;
		goto err;
	}

	if (ufs_get_env_addr(0, &offset1) ||
	    ufs_get_env_addr(1, &offset2)) {
		ret = 1;
		goto err;
	}

	read1_fail = read_env(CONFIG_ENV_SIZE, offset1, tmp_env1);
	read2_fail = read_env(CONFIG_ENV_SIZE, offset2, tmp_env2);

	if (read1_fail && read2_fail)
		puts("*** Error - No Valid Environment Area found\n");
	else if (read1_fail || read2_fail)
		puts("*** Warning - some problems detected\n");

	crc1_ok = !read1_fail &&
		(crc32(0, tmp_env1->data, ENV_SIZE) == tmp_env1->crc);
	crc2_ok = !read2_fail &&
		(crc32(0, tmp_env2->data, ENV_SIZE) == tmp_env2->crc);

	if (!crc1_ok && !crc2_ok) {
		errmsg = "!bad CRC";
		ret = 1;
		goto err;
	} else if (crc1_ok && !crc2_ok) {
		gd->env_valid = 1;
	} else if (!crc1_ok && crc2_ok) {
		gd->env_valid = 2;
	} else {
		/* both ok - check serial */
		if (tmp_env1->flags == 255 && tmp_env2->flags == 0)
			gd->env_valid = 2;
		else if (tmp_env2->flags == 255 && tmp_env1->flags == 0)
			gd->env_valid = 1;
		else if (tmp_env1->flags > tmp_env2->flags)
			gd->env_valid = 1;
		else if (tmp_env2->flags > tmp_env1->flags)
			gd->env_valid = 2;
		else /* flags are equal - almost impossible */
			gd->env_valid = 1;
	}

	if (gd->env_valid == 1)
		ep = tmp_env1;
	else
		ep = tmp_env2;

	env_flags = ep->flags;
	env_import((char *)ep, 0);
	ret = 0;

err:
	if (ret)
		set_default_env(errmsg);
#endif
}
#else /* ! CONFIG_ENV_OFFSET_REDUND */
void ufs_env_relocate_spec(void)
{
#if !defined(ENV_IS_EMBEDDED)
	ALLOC_CACHE_ALIGN_BUFFER(char, buf, CONFIG_ENV_SIZE);
	u32 offset;
	int ret;
	const char *errmsg;

#ifdef CONFIG_SPL_BUILD
	dev = 0;
#endif

	errmsg = init_ufs_for_env();
	if (errmsg) {
		ret = 1;
		goto err;
	}

	if (ufs_get_env_addr(0, &offset)) {
		ret = 1;
		goto err;
	}

	if (ufs_read_storage((uint64_t)buf, offset, CONFIG_ENV_SIZE) != 0) {
		errmsg = "!read failed";
		ret = 1;
		goto err;
	}

	env_import(buf, 1);
	ret = 0;

err:
	if (ret)
		set_default_env(errmsg);
#endif
}
#endif /* CONFIG_ENV_OFFSET_REDUND */

