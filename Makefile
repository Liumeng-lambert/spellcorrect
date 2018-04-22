SOURCES1:= cache.cc client.cc configuration.cc epoll.cc log.cc socket.cc spellcorrect.cc tcp.cc tcpserver.cc threadPool.cc main.cc
SOURCES2:= configuration.cc dictionary.cc log.cc splitTool.cc getDict.cc
OBJS1:=$(patsubst %.cc,%.o,$(SOURCES1))
OBJS2:=$(patsubst %.cc,%.o,$(SOURCES2))
ELF1:=runServer
ELF2:=getDict
CXX:=g++
CXXFLAGS:= -std=c++11
all: $(ELF1) $(ELF2)
$(ELF1):$(OBJS1)
	$(CXX) $(CXXFLAGS) $^ -o $(ELF1)
$(ELF2):$(OBJS2)
	$(CXX) $(CXXFLAGS) $^ -o $(ELF2)
	rm -rf $(OBJS1) $(OBJS2)
.PHONY:clean
clean:
	rm -rf $(OBJS1) $(ELF1) $(OBJS2) $(ELF2)


