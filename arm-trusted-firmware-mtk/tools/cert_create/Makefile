#
# Copyright (c) 2015-2025, Arm Limited and Contributors. All rights reserved.
#
# SPDX-License-Identifier: BSD-3-Clause
#

PLAT		:= none
DEBUG		:= 0
CRTTOOL		?= cert_create$(.exe)
BINARY		:= $(notdir ${CRTTOOL})
COT		:= tbbr

MAKE_HELPERS_DIRECTORY := ../../make_helpers/
include ${MAKE_HELPERS_DIRECTORY}build_macros.mk
include ${MAKE_HELPERS_DIRECTORY}common.mk
include ${MAKE_HELPERS_DIRECTORY}defaults.mk
include ${MAKE_HELPERS_DIRECTORY}toolchain.mk
include ${MAKE_HELPERS_DIRECTORY}utilities.mk

ifneq (${PLAT},none)
TF_PLATFORM_ROOT	:=	../../plat/
include ${MAKE_HELPERS_DIRECTORY}plat_helpers.mk
PLAT_CERT_CREATE_HELPER_MK := ${PLAT_DIR}/cert_create_tbbr.mk
endif

# Common source files.
OBJECTS := src/cert.o \
           src/cmd_opt.o \
           src/ext.o \
           src/key.o \
           src/main.o \
           src/sha.o

# offline sign source files
OBJECTS += src/signoffline.o

# Chain of trust.
ifeq (${COT},tbbr)
  include src/tbbr/tbbr.mk
else ifeq (${COT},dualroot)
  include src/dualroot/cot.mk
else ifeq (${COT},cca)
  include src/cca/cot.mk
else
  $(error Unknown chain of trust ${COT})
endif

ifneq (,$(wildcard ${PLAT_CERT_CREATE_HELPER_MK}))
include ${PLAT_CERT_CREATE_HELPER_MK}
endif

# Select OpenSSL version flag according to the OpenSSL build selected
# from setting the OPENSSL_DIR path.
$(eval $(call SELECT_OPENSSL_API_VERSION))

HOSTCCFLAGS := -Wall -std=c99

ifeq (${DEBUG},1)
  HOSTCCFLAGS += -g -O0 -DDEBUG -DLOG_LEVEL=40
else
  HOSTCCFLAGS += -O2 -DLOG_LEVEL=20
endif

HOSTCCFLAGS += ${DEFINES} -DPLAT_MSG=$(call escape-shell,"$(PLAT_MSG)")
# USING_OPENSSL3 flag will be added to the HOSTCCFLAGS variable with the proper
# computed value.
HOSTCCFLAGS += -DUSING_OPENSSL3=$(USING_OPENSSL3)

# Make soft links and include from local directory otherwise wrong headers
# could get pulled in from firmware tree.
INC_DIR += -I ./include -I ${PLAT_INCLUDE} -I ${OPENSSL_DIR}/include

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
