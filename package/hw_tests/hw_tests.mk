################################################################################
#
#  hw_tests
#
################################################################################

HW_TESTS_SITE =  $(BASE_DIR)/../package/hw_tests/src
HW_TESTS_SITE_METHOD = local
HW_TESTS_INSTALL_TARGET = YES
HW_TESTS_DEPENDENCIES = linux

define HW_TESTS_BUILD_CMDS
        $(MAKE) CC=$(TARGET_CC) SYSROOT=$(STAGING_DIR) LINUX_DIR=$(LINUX_DIR) \
                -C $(@D) all
endef

define HW_TESTS_INSTALL_TARGET_CMDS
        $(MAKE) CC=$(TARGET_CC) DESTDIR=$(TARGET_DIR) \
                -C $(@D) install
endef

$(eval $(generic-package))

