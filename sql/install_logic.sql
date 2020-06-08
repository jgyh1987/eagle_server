-- ----------------------------
-- Table structure for `PLAYER_INFO`
-- ----------------------------
DROP TABLE IF EXISTS `PLAYER_INFO`;
CREATE TABLE IF NOT EXISTS `PLAYER_INFO` (		
		`PLAYERID` bigint(20) unsigned NOT NULL AUTO_INCREMENT,		
		`VIPLEVEL` int(10) unsigned NOT NULL DEFAULT '0',
		`ACCOUNT` char(128) BINARY NOT NULL,		
		`MODEL` varchar(128) NOT NULL DEFAULT '',				
		`LASTOFFLINETIME` bigint(20) unsigned NOT NULL DEFAULT '0',					
		`SEX` int(10) unsigned NOT NULL DEFAULT '0',				
		`ALLCHARGE`  int(10) unsigned NOT NULL DEFAULT '0',	
		`AUTHORITY` int(10) unsigned NOT NULL DEFAULT '0',
        `ISROBOT` tinyint(3) unsigned NOT NULL DEFAULT '0',
        `PLATFORMID` varchar(256) NOT NULL DEFAULT '0',
        `INVITEID` char(128) NOT NULL DEFAULT '0',
		`ROLESOLT` int(10) unsigned NOT NULL DEFAULT '0',
		`ALLBINARY` BLOB,
		PRIMARY KEY (`PLAYERID`),		
		UNIQUE KEY `ACCOUNT` (`ACCOUNT`),
		KEY `INVITEID` (`INVITEID`)
	) ENGINE = InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=10000000;
		

-- ----------------------------
-- Table structure for `PLAYER_CREATE_INFO`
-- ----------------------------
DROP TABLE IF EXISTS `PLAYER_CREATE_INFO`;
CREATE TABLE IF NOT EXISTS `PLAYER_CREATE_INFO` (		
		`PLAYERID` bigint(20) unsigned NOT NULL,
		`ACCOUNT` varchar(128) BINARY NOT NULL,
		`CREATETIME` int(10) unsigned NOT NULL DEFAULT '0',	
		`CREATEIP` varchar(64)  NOT NULL DEFAULT '0',	
		`LASTLOGINIP` varchar(64) DEFAULT '0',		
		`LASTMAC` varchar(128) DEFAULT '0',
		PRIMARY KEY (`PLAYERID`)
	) ENGINE = InnoDB DEFAULT CHARSET=utf8;


-- ----------------------------
-- Table structure for `ROLE_INFO`
-- ----------------------------
DROP TABLE IF EXISTS `ROLE_INFO`;
CREATE TABLE IF NOT EXISTS `ROLE_INFO` (		
		`ROLEID` bigint(20) unsigned NOT NULL AUTO_INCREMENT,		
		`PLAYERID` bigint(20) unsigned NOT NULL,
		`CREATETIME` int(10) unsigned NOT NULL DEFAULT '0',	
		`NAME` char(64) BINARY NOT NULL,
		`LASTOFFLINETIME` int(10) unsigned NOT NULL DEFAULT '0',	
		`LEVEL` int(10) unsigned NOT NULL DEFAULT '1',				
		`EXP` bigint(20) unsigned NOT NULL DEFAULT '0',		
		`FIGHT`  int(10) unsigned  DEFAULT '0',	
		`JOBID`  int(10) unsigned NOT NULL,
		`MAPID`  bigint(20) unsigned NOT NULL DEFAULT '0',
		`ROLESTATUS`  int(10) unsigned NOT NULL DEFAULT '0',
		`FUNCTIONOPENBITMAP` int(10) unsigned NOT NULL DEFAULT '0',
		`OTHERFUNOPENBITMAP` int(10) unsigned NOT NULL DEFAULT '0',
		`x` bigint(20) unsigned NOT NULL DEFAULT '0',	
		`y` bigint(20) unsigned NOT NULL DEFAULT '0',	
		`z` bigint(20) unsigned NOT NULL DEFAULT '0',	
		`dirx` bigint(20) unsigned NOT NULL DEFAULT '0',	
		`diry` bigint(20) unsigned NOT NULL DEFAULT '0',	
		`dirz` bigint(20) unsigned NOT NULL DEFAULT '0',	
		`ALLBINARY` BLOB,
		PRIMARY KEY (`ROLEID`),		
		UNIQUE KEY `NAME` (`NAME`)
	) ENGINE = InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for `MAIL`
-- ----------------------------
DROP TABLE IF EXISTS `MAIL`;
CREATE TABLE IF NOT EXISTS `MAIL` (		
		`MAILID` int(10) unsigned NOT NULL AUTO_INCREMENT,
		`PLAYERID` bigint(20) unsigned NOT NULL,
		`ACCOUNT` char(128) BINARY NOT NULL,
		`CREATETIME` int(10) unsigned NOT NULL DEFAULT '0',
		`ITEMTYPE` int(10) unsigned DEFAULT '0',
		`ITEMID` bigint(20) unsigned DEFAULT '0',
		`ITEMCOUNT` int(10) unsigned DEFAULT '0',
		`TITLE` varchar(128),
		`CONTENT` varchar(1024),
		`SENDNAME` varchar(128),
		`SENDACCOUNT` varchar(128),
		PRIMARY KEY (`MAILID`),		
		KEY `PLAYERID` (`PLAYERID`),
		KEY `ACCOUNT` (`ACCOUNT`)
	) ENGINE = InnoDB DEFAULT CHARSET=utf8;
	
-- ----------------------------
-- Table structure for `CLIMBTOWER`
-- ----------------------------
DROP TABLE IF EXISTS `CLIMBTOWER`;
CREATE TABLE IF NOT EXISTS `CLIMBTOWER` (	
		`PLAYERID` bigint(20) unsigned NOT NULL,
		`TOWERNUMBER` int(10) unsigned NOT NULL,
		`PASSTIME` int(10) unsigned NOT NULL,
		PRIMARY KEY (`PLAYERID`)
	) ENGINE = InnoDB DEFAULT CHARSET=utf8;

	-- ----------------------------
-- Table structure for `PLAYER_ITEM`
-- ----------------------------
DROP TABLE IF EXISTS `PLAYER_ITEM`;
CREATE TABLE IF NOT EXISTS `PLAYER_ITEM` (		
		`ITEMID` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
		`ROLEID` bigint(20) unsigned NOT NULL,
		`CONFIGID` bigint(20)  unsigned NOT NULL,
		`ITEMTYPE` int(10) unsigned NOT NULL,	
		`ITEMCOUNT` bigint(20) unsigned NOT NULL,
		`BAGTYPE` int(10) unsigned NOT NULL,
		`ALLBINARY` BLOB,
		PRIMARY KEY (`ITEMID`),
		KEY `ROLEID` (`ROLEID`)
	) ENGINE = InnoDB DEFAULT CHARSET=utf8;
