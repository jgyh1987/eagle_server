echo off

protoc.exe --cpp_out=./Imp/  ./proto/playerDataSave.proto ./proto/msg_net.proto ./proto/package_net.proto

pause