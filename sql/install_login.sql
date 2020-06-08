-- ----------------------------
-- Table structure for `PACKAGE_CODE`
-- ----------------------------
DROP TABLE IF EXISTS `PACKAGE_CODE`;
CREATE TABLE IF NOT EXISTS `PACKAGE_CODE` (
		`ID` int(10) unsigned NOT NULL AUTO_INCREMENT,
		`CODE` varchar(64) BINARY NOT NULL,
		`PACKAGE_ITEMS` varchar(128) NOT NULL,
		`PACKAGE_TYPE` int(10) unsigned NOT NULL,
		`PACKAGE_TIME` int(10) unsigned DEFAULT 0,
		`MAIL_TITLE` varchar(128) NOT NULL DEFAULT '',
		`MAIL_CONTEXT` varchar(512) NOT NULL DEFAULT '',
		PRIMARY KEY (`ID`),
		UNIQUE KEY `CODE` (`CODE`)
		) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for `ACCOUNT_INFO`
-- ----------------------------
DROP TABLE IF EXISTS `ACCOUNT_INFO`;
CREATE TABLE IF NOT EXISTS `ACCOUNT_INFO` (	
		`ID` int(10) unsigned NOT NULL AUTO_INCREMENT,
		`ACCOUNT` varchar(128) BINARY NOT NULL DEFAULT '',	
		`SDKID` varchar(128) BINARY  NOT NULL DEFAULT '',	
		`PASSWD` varchar(64) BINARY NOT NULL DEFAULT '',	
		`PLATFORMSTR` varchar(128) BINARY NOT NULL DEFAULT '',
		`CREATETIME` int(10) unsigned DEFAULT '0',
		PRIMARY KEY (`ID`),		
		UNIQUE KEY `ACCOUNT` (`ACCOUNT`),
		UNIQUE KEY `SDKID` (`SDKID`)
	) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=713970;

-- ----------------------------
-- Table structure for `GM_ACCOUNT_INFO`
-- ----------------------------
DROP TABLE IF EXISTS `GM_ACCOUNT_INFO`;
CREATE TABLE IF NOT EXISTS `GM_ACCOUNT_INFO` (	
		`ID` int(10) unsigned NOT NULL AUTO_INCREMENT,
		`ACCOUNT` varchar(128) BINARY NOT NULL DEFAULT '',	
		`PASSWD` varchar(128) BINARY NOT NULL DEFAULT '',	
		`AUTH` int(10) unsigned DEFAULT 1,
		PRIMARY KEY (`ID`),		
		UNIQUE KEY `ACCOUNT` (`ACCOUNT`)
	) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=0;

