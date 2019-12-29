include $(TOPDIR)/rules.mk

PKG_NAME:=alarm-xaiomi
PKG_VERSION:=0.1
PKG_RELEASE:=1

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz

PKG_MAINTAINER:=John Doe <john.doe@example.com>
PKG_LICENSE:=CC0-1.0

include $(INCLUDE_DIR)/package.mk

define Package/alarm-xaiomi
	SECTION:=net
	# Select package by default
	#DEFAULT:=y
	CATEGORY:=Network
	TITLE:=HUEHUEUEHUEH.
	# Feature FOO also needs libsodium:
	DEPENDS:=+librt +CONFIG_EXAMPLE2_ENABLE_FOO:libsodium
	URL:=https://www.example.com
	SUBMENU:=VPN
endef

define Package/alarm-xaiomi/description
	Some example Programm called alarm-xaiomi
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) -r ./src/* $(PKG_BUILD_DIR)/
endef

define Build/Configure
# Nothing to do here for us.
# By default example2/src/Makefile will be used.
endef

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) $(TARGET_CONFIGURE_OPTS)
endef

define Package/alarm-xaiomi/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/alarm-xaiomi $(1)/usr/sbin/
endef

$(eval $(call BuildPackage,alarm-xaiomi))