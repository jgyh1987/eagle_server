dowork()
{
	echo "starting bin/ShareDBServer"
	./bin/ShareDBServer &
	echo "starting bin/WLeaderServer"
	./bin/WLeaderServer &
	echo "starting bin/WGameRoomServer"
	./bin/WGameRoomServer &
	sleep 2
	echo "starting bin/WFightServer"
	./bin/WFightServer &
	sleep 2
        echo "starting bin/WGatewayzServer"
        ./bin/WGatewayzServer &
	ps x|grep "Server" |grep -v grep

}

stopwork()
{
	pkill  -2 WFightServer
	sleep 1
	pkill  -2 WGatewayzServer
        sleep 1
	pkill  -2 WLeaderServer
	pkill  -2 WGameRoomServer
	pkill  -2 ShareDBServer
}

echo "--------------------------------------------------"
echo "--------------------START-------------------------"
echo "--------------------------------------------------"
	stopwork
echo "--------------------------------------------------"
echo "----------------------DONE------------------------"
echo "--------------------------------------------------"


