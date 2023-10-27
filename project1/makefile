playGame.exe: playGame.o boardLogic.o playerLogic.o
	g++ -o playGame.exe playGame.o boardLogic.o playerLogic.o

playGame.o: playGame.cpp
	g++ -c playGame.cpp

boardLogic.o: boardLogic.cpp boardLogic.h
	g++ -c boardLogic.cpp

playerLogic.o: playerLogic.cpp playerLogic.h boardLogic.h 
	g++ -c playerLogic.cpp

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
	cp Makefile backups
