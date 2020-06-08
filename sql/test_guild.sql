drop procedure if exists insertAI;
delimiter //     
create procedure insertAI()
begin
	declare n int default 1;
	set @name = "";
	set @account = "";

	while n <= 1000 
	do     
		set @name = 'guild_test_';
		insert into GUILD (GUILDNAME, GUILDLEVEL, GUILDPHOTOID, DECLARATION) values(concat(@name, n), 1, 1, "asdfasdfasdf");

		set n=n+1;
	end while;
end; //
delimiter ;

#执行存储过程插入数据
call insertAI();
drop procedure if exists insertAI;


