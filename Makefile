include $(TOPDIR)/rules.mk

PKG_NAME:=alarm-yeelight
PKG_VERSION:=0.1
PKG_RELEASE:=1

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz

PKG_MAINTAINER:=Henrique Eihara<rick.eihara@gmail.com>

include $(INCLUDE_DIR)/package.mk

define Package/alarm-yeelight
	SECTION:=utilities
	CATEGORY:=Utilities
	TITLE:=alarm-yeelight
	URL:=https://www.github.com/eiguike/alarm-yeelight
endef

define Package/alarm-yeelight/description
	Some example Programm called alarm-yeelight
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

define Package/alarm-yeelight/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/alarm-yeelight $(1)/usr/sbin/
endef

$(eval $(call BuildPackage,alarm-yeelight))
