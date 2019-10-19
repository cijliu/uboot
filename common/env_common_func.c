#include <common.h>
#include <config.h>
#include <environment.h>

struct env_common_func_t {
	int (*saveenv)(void);
	void (*env_relocate_spec)(void);
	char *env_name_spec;
};

#ifdef CONFIG_ENV_IS_IN_NAND
extern int nand_saveenv(void);
extern void nand_env_relocate_spec(void);

static struct env_common_func_t nand_env_cmn_func = {
	.saveenv = nand_saveenv,
	.env_relocate_spec = nand_env_relocate_spec,
	.env_name_spec = "NAND",
};

#else
static struct env_common_func_t nand_env_cmn_func = {0};

#endif /* CONFIG_ENV_IS_IN_NAND */

#ifdef CONFIG_ENV_IS_IN_SPI_FLASH
extern int sf_saveenv(void);
extern void sf_env_relocate_spec(void);

static struct env_common_func_t sf_env_cmn_func = {
	.saveenv = sf_saveenv,
	.env_relocate_spec = sf_env_relocate_spec,
	.env_name_spec = "SPI Flash",
};
#else
static struct env_common_func_t sf_env_cmn_func = {0};

#endif /* CONFIG_ENV_IS_IN_SPI_FLASH */

#ifdef CONFIG_ENV_IS_IN_MMC
extern int emmc_saveenv(void);
extern void emmc_env_relocate_spec(void);

static struct env_common_func_t emmc_env_cmn_func = {
	.saveenv = emmc_saveenv,
	.env_relocate_spec = emmc_env_relocate_spec,
	.env_name_spec = "eMMC Flash",
};
#else
static struct env_common_func_t emmc_env_cmn_func = {0};

#endif /* CONFIG_ENV_IS_IN_EMMC_FLASH */

#ifdef CONFIG_ENV_IS_IN_UFS
extern int ufs_saveenv(void);
extern void ufs_env_relocate_spec(void);

static struct env_common_func_t ufs_env_cmn_func = {
	.saveenv = ufs_saveenv,
	.env_relocate_spec = ufs_env_relocate_spec,
	.env_name_spec = "UFS Flash",
};
#else
static struct env_common_func_t ufs_env_cmn_func = {0};

#endif /* CONFIG_ENV_IS_IN_UFS_FLASH */
char *env_name_spec;
env_t *env_ptr;
struct env_common_func_t *env_cmn_func = NULL;


int saveenv(void)
{
	return env_cmn_func ? env_cmn_func->saveenv() : -1;
}

void env_relocate_spec(void)
{
	switch (get_boot_media()) {
	default:
		env_cmn_func = NULL;
		break;
	case BOOT_MEDIA_NAND:
		env_cmn_func = &nand_env_cmn_func;
		break;
	case BOOT_MEDIA_SPIFLASH:
		env_cmn_func = &sf_env_cmn_func;
		break;
	case BOOT_MEDIA_EMMC:
		env_cmn_func = &emmc_env_cmn_func;
		break;
	case BOOT_MEDIA_UFS:
		env_cmn_func = &ufs_env_cmn_func;
		break;
	case BOOT_MEDIA_UNKNOWN:
		env_cmn_func = NULL;
		break;
	}

	if (env_cmn_func && !env_cmn_func->env_name_spec)
		env_cmn_func = NULL;

	/* unknow start media */
	if (!env_cmn_func)
		return;

	env_name_spec = env_cmn_func->env_name_spec;

	env_cmn_func->env_relocate_spec();
}

DECLARE_GLOBAL_DATA_PTR;

int env_init(void)
{
	/* Device isn't usable before relocation */
	gd->env_addr = (ulong)&default_environment[0];
	gd->env_valid = 1;

	return 0;
}

