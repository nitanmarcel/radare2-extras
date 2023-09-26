/* radare2-keystone - GPL - Copyright 2016-2023 - pancake */

#include <r_arch.h>
#include <r_lib.h>
#include <keystone/keystone.h>
#include <keystone/systemz.h>
#include "keystone.c"

static bool assemble(RArchSession *a, RAnalOp *ao, RArchEncodeMask mask) {
	ks_mode mode = (ks_mode)0;
	if (a->config->big_endian) {
		mode = (ks_mode)((int)mode | KS_MODE_BIG_ENDIAN);
	}
	return keystone_assemble (a, ao, ao->mnemonic, KS_ARCH_SYSTEMZ, mode);
}

RArchPlugin r_arch_plugin_s390x_ks = {
	.meta = {
		.name = "s390x.ks",
		.desc = "SystemZ keystone assembler (S390X)",
		.license = "GPL",
	},
	.arch = "s390x",
	.bits = 32,
	.encode = &assemble,
};

#ifndef CORELIB
RLibStruct radare_plugin = {
	.type = R_LIB_TYPE_ARCH,
	.data = &r_arch_plugin_s390x_ks,
	.version = R2_VERSION
};
#endif
