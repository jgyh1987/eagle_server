db_user="root"
db_password="leshu@3307"
db_host="192.168.1.216"
db_port=3307
db_name="logindata"

items="3-100-10000;3-101-1000"
package_type=1
package_time=0
title=""
context=""

#code="asdf"

#mysql -u$db_user -p$db_password -h$db_host -P$db_port  -e "insert into $db_name.PACKAGE_CODE(CODE, PACKAGE_ITEMS, PACKAGE_TYPE, PACKAGE_TIME, MAIL_TITLE, MAIL_CONTEXT)  VALUES('$code', '$items', $package_type, $package_time, '$code', '$code') ;"

#exit

while read value1 valus2
do
	if [ -n "$value1" ] ; then
		echo $value1
		mysql -u$db_user -p$db_password -h$db_host -P$db_port  -e "insert into $db_name.PACKAGE_CODE(CODE, PACKAGE_ITEMS, PACKAGE_TYPE, PACKAGE_TIME, MAIL_TITLE, MAIL_CONTEXT)  VALUES('$value1', '$items', $package_type, $package_time, '$value1', '$value1') ;"
	fi
done < package_code


