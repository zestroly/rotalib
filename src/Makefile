
CXX=arm-linux-gnueabihf-g++
TARGETNAME=libDriver.so
TARGETPATH=../build/arm


LFLAGS= -shared -Wl,-soname,$(TARGETNAME)
CFLAGS= -pipe -fPIC -std=gnu++11
CXXFLAGS=-pipe -fPIC -std=gnu++11

LIBS = -pthread -ljsoncpp -lbluetooth

TARGET0=$(TARGETPATH)/$(TARGETNAME)

SRC_OBJ= \
		 BarCodeScanner.o \
		 ZSerialPort.o \
		 ZCalculatedWeight.o \
         ZSerialPortToSerialPort.o \
         ZNetWorkBase.o \
         ZNetWork.o \
         ZSystemIO.o \
         ZWifiMananger.o \
         ZBluetooth.o \

INC_OBJ= \
		 BarCodeScanner.h \
		 ZSerialPort.h \
		 ZCalculatedWeight.h \
         ZSerialPortToSerialPort.h \
         ZNetWorkBase.h \
         ZNetWork.h \
         ZSystemIO.h \
         ZWifiMananger.h \
         ZBluetooth.h \

all:$(TARGET0)

$(TARGET0):$(SRC_OBJ) $(INC_OBJ)
	mkdir -p $(TARGETPATH)
	$(CXX) $(LFLAGS) $(CXXFLAGS) $(SRC_OBJ) -o $(TARGET0) $(LIBS)
	mkdir -p $(TARGETPATH)/include
	cp *.h $(TARGETPATH)/include


.cpp.o:
	$(CXX) -c $(CXXFLAGS)  -o "$@" "$<"

.c.o:
	$(CC)  -c -o "$@" "$<" 

clean:
	rm $(SRC_OBJ) -f
	rm $(TARGET0) -f
	rm $(TARGETPATH)/include -rf





