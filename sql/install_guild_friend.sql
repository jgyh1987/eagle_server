
-- ----------------------------
-- Table structure for `GUILD`
-- ----------------------------
DROP TABLE IF EXISTS `GUILD`;
CREATE TABLE IF NOT EXISTS `GUILD` (	
		`GUILDID` int(10) unsigned NOT NULL AUTO_INCREMENT,
		`GUILDNAME` char(64) BINARY NOT NULL,
		`GUILDPHOTOID` int(10) unsigned NOT NULL,
		`DECLARATION` varchar(128) NOT NULL,
		`GUILDLEVEL` int(10) unsigned DEFAULT '0',
		`GUILDGOLD` int(10) unsigned DEFAULT '0',
		`CLEARDATA` BLOB,
		`ALLBINARY` BLOB,
		PRIMARY KEY (`GUILDID`),
		UNIQUE KEY `GUILDNAME` (`GUILDNAME`)
	) ENGINE = InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1000000;
	
-- ----------------------------
-- Table structure for `GUILDMEMBER`
-- ----------------------------
DROP TABLE IF EXISTS `GUILDMEMBER`;
CREATE TABLE IF NOT EXISTS `GUILDMEMBER` (
		`ROLEID` bigint(10) unsigned NOT NULL,
		`PLAYERID` bigint(10) unsigned NOT NULL,
		`GUILDID` int(10) unsigned NOT NULL,
		`AUTH` int(10) unsigned DEFAULT '0',
		`AllSOURCE` int(10) unsigned DEFAULT '0',
		`CURSOURCE` int(10) unsigned DEFAULT '0',
		
		PRIMARY KEY (`ROLEID`),
		KEY (`GUILDID`)
	) ENGINE = InnoDB DEFAULT CHARSET=utf8;
	