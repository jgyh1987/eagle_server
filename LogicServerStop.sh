dowork()
{
	echo "starting bin/LogicDataServer"
	./bin/LogicDataServer &
	sleep 2
	echo "starting bin/LogicServer"
	./bin/LogicServer &
	sleep 2
	echo "starting bin/GatewayServer"
	./bin/GatewayServer &
	ps x|grep "Server" |grep -v grep

}

stopwork()
{
	pkill  -2 GatewayServer
	sleep 1
	pkill  -2 LogicServer
	sleep 1
	pkill  -2 LogicDataServer
	sleep 1
}

echo "--------------------------------------------------"
echo "--------------------START-------------------------"
echo "--------------------------------------------------"
	stopwork
echo "--------------------------------------------------"
echo "----------------------DONE------------------------"
echo "--------------------------------------------------"


