CXX = g++

ROOTCFLAGS= $(shell root-config --cflags)
ROOTLIBS= $(shell root-config --libs)
ROOTGLIBS= $(shell root-config --glibs)

CXXFLAGS= -O -Wall -fPIC
CXXFLAGS += $(ROOTCFLAGS)

SOFLAGS= -O -shared
SOFLAGS += $(ROOTGLIBS)

Task: clean mydict main clean

mydict:
	@rootcint TTbarSelector_dict.cxx -c TTbarSelector.h
	@rootcint ZxSelector_dict.cxx -c ZxSelector.h

main: Analyze.C TTbarSelector_dict.o TTbarSelector.o ZxSelector.o ZxSelector_dict.o JetObj.o MuonObj.o ElecObj.o PhotonObj.o Plots.o
	$(CXX) $(CXXFLAGS) $(ROOTGLIBS) $^ -o $@
	@echo '-> main created!'
	@echo '-> run by command: ./main'

%.o: %.C
	$(CXX) $(CXXFLAGS) -c $^ -o $@

%.o: %.h
	$(CXX) $(CXXFLAGS) -c $^ -o $@

TTbarSelector_dict.o: TTbarSelector_dict.cxx
	$(CXX) $(CXXFLAGS) -c $^ -o $@

ZxSelector_dict.o : ZxSelector_dict.cxx
	$(CXX) $(CXXFLAGS) -c $^ -o $@

clean:
	rm -rf *.o *.so *_dict.cxx
