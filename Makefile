
CXX = g++-8

libs = -lcurl 
libs += -Lprotobuf/.libs/lib 
libs += -lprotobuf
libs += -lprotoc
libs += #-lprofiler

includes = -I . 
includes += -I secp256k1/includes
includes += -I protobuf/.libs/include
#######objects for main prog:
app_objects = app.cpp
app_objects += sawtooth_client.o
app_objects += protos_pb_h/transaction.pb.cc protos_pb_h/batch.pb.cc

app_static_lib = cryptopp/libcryptopp.a
app_static_lib += secp256k1/.libs/libsecp256k1.a

client_static_lib = -l:protobuf/src/.libs/libprotobuf.a
client_static_lib += -l:protobuf/src/.libs/libprotoc.a

#some flags
flag_global = -O2 -std=c++11  -g #eosio is on standart c++17  -pg 
flag_main = -Wall -pthread

all: app

app: $(app_objects)
	$(CXX) $(flag_global) $(flag_main) -DNDEBUG $(app_objects) $(libs) $(includes) -o app $(app_static_lib) 

sawtooth_client.o: sawtooth_client.cpp sawtooth_client.h protos_pb_h/transaction.pb.h
	$(CXX) $(flag_global) $(libs) $(includes) -c sawtooth_client.cpp $(client_static_lib)  -o sawtooth_client.o 

protos_pb_h/transaction.pb.h: protos/transaction.proto
	mkdir -p protos_pb_h &&  ./protobuf/src/protoc --proto_path=protos --cpp_out=protos_pb_h/ protos/*.proto


clean: 
	rm -fr app
	rm -fr *.o *.out.* *.out *.stats *.a protos_pb_h