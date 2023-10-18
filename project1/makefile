playGame.exe: playGame.o boardLogic.o
	g++ -o playGame.exe playGame.o boardLogic.o

playGame.o: playGame.cpp
	g++ -c playGame.cpp

board_logic.o: boardLogic.cpp boardLogic.h
	g++ -c boardLogic.cpp

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
	cp Makefile backups
