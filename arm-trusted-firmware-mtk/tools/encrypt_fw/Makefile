#
# Copyright (c) 2024-2025, Arm Limited. All rights reserved.
# Copyright (c) 2019-2022, Linaro Limited. All rights reserved.
#
# SPDX-License-Identifier: BSD-3-Clause
#

BUILD_INFO	?= 1
DEBUG		:= 0
ENCTOOL		?= encrypt_fw$(.exe)
BINARY		:= $(notdir ${ENCTOOL})
OPENSSL_DIR	:= /usr
APSOC_COMMON	:= ../../plat/mediatek/apsoc_common

MAKE_HELPERS_DIRECTORY := ../../make_helpers/
include ${MAKE_HELPERS_DIRECTORY}build_macros.mk
include ${MAKE_HELPERS_DIRECTORY}common.mk
include ${MAKE_HELPERS_DIRECTORY}defaults.mk
include ${MAKE_HELPERS_DIRECTORY}toolchain.mk

OBJECTS := src/encrypt.o \
           src/cmd_opt.o \
           src/main.o

HOSTCCFLAGS := -Wall -std=c99

# Select OpenSSL version flag according to the OpenSSL build selected
# from setting the OPENSSL_DIR path.
$(eval $(call SELECT_OPENSSL_API_VERSION))

ifeq (${DEBUG},1)
  HOSTCCFLAGS += -g -O0 -DDEBUG -DLOG_LEVEL=40
else
ifeq (${BUILD_INFO},1)
  HOSTCCFLAGS += -O2 -DLOG_LEVEL=20
else
  HOSTCCFLAGS += -O2 -DLOG_LEVEL=10
endif
endif

HOSTCCFLAGS += ${DEFINES}
# USING_OPENSSL3 flag will be added to the HOSTCCFLAGS variable with the proper
# computed value.
HOSTCCFLAGS += -DUSING_OPENSSL3=$(USING_OPENSSL3)


# Make soft links and include from local directory otherwise wrong headers
# could get pulled in from firmware tree.
INC_DIR := -I ./include -I ../../include/tools_share -I ${OPENSSL_DIR}/include \
	   -I ${APSOC_COMMON}/fw_dec/mtk_roe

# Include library directories where OpenSSL library files are located.
# For a normal installation (i.e.: when ${OPENSSL_DIR} = /usr or
# /usr/local), binaries are located under the ${OPENSSL_DIR}/lib/
# directory. However, for a local build of OpenSSL, the built binaries are
# located under the main project directory (i.e.: ${OPENSSL_DIR}, not
# ${OPENSSL_DIR}/lib/).
LIB_DIR := -L ${OPENSSL_DIR}/lib -L ${OPENSSL_DIR}
LIB := -lssl -lcrypto

.PHONY: all clean realclean --openssl

all: --openssl ${BINARY}

${BINARY}: ${OBJECTS} Makefile
	$(s)echo "  HOSTLD  $@"
	$(q)$(host-cc) ${OBJECTS} ${LIB_DIR} ${LIB} -o $@

%.o: %.c
	$(s)echo "  HOSTCC  $<"
	$(q)$(host-cc) -c ${HOSTCCFLAGS} ${INC_DIR} $< -o $@

--openssl:
ifeq ($(DEBUG),1)
	$(s)echo "Selected OpenSSL version: ${OPENSSL_CURRENT_VER}"
endif

clean:
	$(q)rm -rf $(OBJECTS)

realclean: clean
	$(q)rm -f $(BINARY)
