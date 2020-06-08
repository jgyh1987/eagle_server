drop procedure if exists insertAI;
delimiter //     
create procedure insertAI()
begin
	declare n int default 1;
    declare job int default 1;
	declare nlevel int default 1;
	set @name = "";
	set @account = "";

	while n <= 1000 
	do     
		set @name = concat('eagle_test_' , concat(n,''));
		set @account = @name;
		set job = 1;
		set nlevel = 1;
		insert into PLAYER_INFO (ACCOUNT, ISROBOT) values(@account, 1);

		set n=n+1;
	end while;
	
	insert into PLAYER_CREATE_INFO(PLAYERID, ACCOUNT, CREATETIME) select PLAYERID, ACCOUNT, unix_timestamp() from PLAYER_INFO;
	
	#insert into FRIEND(PLAYERID, NAME, JJCPOINT, ISROBOT) select PLAYERID, ACCOUNT, floor(rand()*100), 1  from PLAYER_INFO;
	
end; //
delimiter ;

#执行存储过程插入数据
call insertAI();
drop procedure if exists insertAI;


