
-- ----------------------------
-- Table structure for `ACTION_LOG`
-- ----------------------------
DROP TABLE IF EXISTS `ACTION_LOG`;
CREATE TABLE `ACTION_LOG` (
  `ID` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `ACCOUNT` varchar(128) BINARY NOT NULL DEFAULT '',
  `PLAYERID` bigint(10) unsigned NOT NULL,
  `PLAYERNAME` varchar(33) NOT NULL DEFAULT '',
  `PLAYERLEVEL` int(10) unsigned NOT NULL,
  `TYPE` int(10) unsigned NOT NULL,
  `TIME` int(10) unsigned NOT NULL,
  `INFO` varchar(16384) NOT NULL,
  PRIMARY KEY (`ID`),
  INDEX `TIME` ( `TIME` ),
  INDEX `TYPE_TIME` (`TYPE`,`TIME`),
  INDEX `PLAYERID_TYP_TIME`(`PLAYERID`, `TYPE`, `TIME`),
  INDEX `PLAYERNAME_TYPE_TIME` (`PLAYERNAME`,`TYPE`,`TIME`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for `CLIENT_LOG`
-- ----------------------------
DROP TABLE IF EXISTS `CLIENT_LOG`;
CREATE TABLE IF NOT EXISTS `CLIENT_LOG` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `browser` varchar(100) NOT NULL,
  `os` varchar(30) NOT NULL,
  `flashversion` varchar(30) NOT NULL,
  `firstload` int(11) NOT NULL,
  `module` varchar(30) NOT NULL,
  `loadseq` varchar(30) NOT NULL,
  `timelen` int(11) NOT NULL,
  `userid` varchar(100) NOT NULL,
  `version` varchar(20) NOT NULL,
  `logtype` int(11) NOT NULL,
  `logtime` int(11) NOT NULL,
  `ip` varchar(20) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for `CHARGE_LOG`
-- ----------------------------
DROP TABLE IF EXISTS `CHARGE_LOGS`;
CREATE TABLE `CHARGE_LOGS` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `user` varchar(128) BINARY NOT NULL DEFAULT '',
  `count` int(10) unsigned NOT NULL DEFAULT '0',
  `orderid` varchar(512) NOT NULL,
  `remark` varchar(16348) NOT NULL,
  `state` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `update_time` int(10) unsigned NOT NULL,
  PRIMARY KEY (`id`),
  INDEX `USER` ( `user` ),
  INDEX `update_time` ( `update_time` )
) ENGINE=MyISAM DEFAULT CHARSET=utf8;


