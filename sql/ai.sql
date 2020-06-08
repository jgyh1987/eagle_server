
# 创建AI

DELETE FROM PLAYER_INFO where NAME LIKE 'Warrior%';
DELETE FROM JINGJICHANG;
drop procedure if exists insertAI;
delimiter //     
create procedure insertAI()
begin
	declare n int default 1;
    declare sex int default 1;
    declare job int default 1;
    declare country int default 1;
	declare rank int default 1;
	declare nlevel int default 1;
	set @name = "";
	set @account = "";
	set @playerId = 1;

	DELETE FROM PLAYER_INFO where NAME LIKE 'Warrior%';
	DELETE FROM JINGJICHANG where NAME LIKE 'Warrior%';

	while n <= 1 
	do     
		set @name = concat('Warrior' , concat(n,''));
		set @account = concat(@name , '.boyo');
		set job = n % 3 + 1;
		set sex = n % 2 + 1;
        set country = n % 2 + 1;
		set nlevel = 20;
		select @name, @account, job, sex;
		insert into PLAYER_INFO (NAME, ACCOUNT, SEX, JOB, COUNTRYID, `LEVEL`, BITMASK, ISROBOT)values(@name,@account, sex, job, country, nlevel, 0, 1);

		select PLAYERID, JOB,SEX into @playerId, job, sex from PLAYER_INFO where ACCOUNT = @account limit 1;

		insert into JINGJICHANG (PLAYERID, NAME, SEX, JOB, RANK, COUNTRY, RANKLEVEL, REALLEVEL,  ISROBOT, ROBOTRANK, POINT)values(@playerId,@name, sex, job, n, country, nlevel, nlevel, 1, n, 1);

		set n=n+1;
	end while;
end; //
delimiter ;

#执行存储过程插入数据
call insertAI();
insert into PLAYER_INFO (NAME, ACCOUNT, SEX, JOB, COUNTRYID, `LEVEL`, BITMASK, ISROBOT)values('Warrior1','Warrior1.boyo', 1, 1, 1, 20, 0, 1);
insert into JINGJICHANG (PLAYERID, NAME, SEX, JOB, RANK, COUNTRY, RANKLEVEL, REALLEVEL,  ISROBOT, ROBOTRANK, POINT) select PLAYERID, NAME, 1, 1, 1, 1, 20, 20, 1, 1, 1  from PLAYER_INFO where ACCOUNT like "%Warrior1%";
drop procedure if exists insertAI;
