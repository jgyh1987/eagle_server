dowork()
{
	echo "starting bin/LoginDataServer"
	./bin/LoginDataServer &
	sleep 2
	echo "starting bin/LoginServer"
	./bin/LoginServer &
	ps x|grep "Server" |grep -v grep

}

stopwork()
{
	pkill  -2 LoginServer
	sleep 1
	pkill  -2 LoginDataServer
	sleep 1
}

echo "--------------------------------------------------"
echo "--------------------START-------------------------"
echo "--------------------------------------------------"
	stopwork
	dowork
echo "--------------------------------------------------"
echo "----------------------DONE------------------------"
echo "--------------------------------------------------"


