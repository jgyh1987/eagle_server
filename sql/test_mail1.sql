drop procedure if exists insertAI;
delimiter //     
create procedure insertAI()
begin
	declare n int default 1;
	set @name = "";
	set @account = "";

	while n <= 200 
	do     
		insert into MAIL(PLAYERID, ACCOUNT, CREATETIME, ITEMTYPE, ITEMID, ITEMCOUNT, TITLE, CONTENT, SENDNAME, SENDACCOUNT) select PLAYERID, ACCOUNT, unix_timestamp(), 1,1,1, 'system', 'asdfasdf', '', '' from PLAYER_INFO;

		set n=n+1;
	end while;
end; //
delimiter ;

#执行存储过程插入数据
call insertAI();
drop procedure if exists insertAI;


