#CXX=clang++
CXX=g++

CXXFLAGS= -g -std=c++14 

BINARIES=dataProj testStats1 testStatsData1 testStatsData2

all: ${BINARIES}

tests: ${BINARIES}
	./testStats1
	./testStatsData1
	./testStatsData2

dataProj: statTool.o stats.o statTool.o demogCombo.o demogData.o raceDemogData.o psData.o psCombo.o parse.o main.o
	${CXX} $^ -o $@

testStats1: testStats1.o stats.o statTool.o demogCombo.o demogData.o raceDemogData.o psData.o psCombo.o  parse.o  tddFuncs.o
	${CXX} $^ -o $@

testStatsData1: testStatsData1.o stats.o statTool.o demogCombo.o demogData.o raceDemogData.o psData.o psCombo.o  parse.o tddFuncs.o
	${CXX} $^ -o $@

testStatsData2: testStatsData2.o stats.o statTool.o demogCombo.o demogData.o raceDemogData.o psData.o psCombo.o  parse.o tddFuncs.o
	${CXX} $^ -o $@

clean:
	/bin/rm -f ${BINARIES} *.o 
