SOURCES1:= cache.cc client.cc configuration.cc epoll.cc index.cc log.cc socket.cc spellcorrect.cc tcp.cc tcpserver.cc threadPool.cc main.cc
SOURCES2:= configuration.cc dictionary.cc log.cc splitTool.cc getDict.cc
SOURCES3:= client.cc socket.cc log.cc runClient.cc
OBJS1:=$(patsubst %.cc,%.o,$(SOURCES1))
OBJS2:=$(patsubst %.cc,%.o,$(SOURCES2))
OBJS3:=$(patsubst %.cc,%.o,$(SOURCES3))
ELF1:=runServer
ELF2:=getDict
ELF3:=runclient
CXX:=g++
CXXFLAGS:= -std=c++11 -lpthread 
all: $(ELF1) $(ELF2) $(ELF3)
$(ELF1):$(OBJS1)
	$(CXX) $(CXXFLAGS) $^ -o $(ELF1)
$(ELF2):$(OBJS2)
	$(CXX) $(CXXFLAGS) $^ -o $(ELF2)
$(ELF3):$(OBJS3)
	$(CXX) $(CXXFLAGS) $^ -o $(ELF3)
	rm -rf $(OBJS1) $(OBJS2) $(OBJS3)
.PHONY:clean
clean:
	rm -rf $(OBJS1) $(ELF1) $(OBJS2) $(ELF2) $(OBJS3) $(ELF3)


