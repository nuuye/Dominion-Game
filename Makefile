
CXX=g++
CXXFLAGS=-Wall -Wextra -Werror

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -c -o $@

main: Plateau.o Carte.o CarteVictoire.o CarteRoyaume.o CarteTresor.o Joueur.o main.o
	$(CXX) $^ -o $@

.PHONY: run clean

run: main
	./$<

clean:
	rm -f *.o *~ *.core 

