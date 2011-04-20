aiobjects = ai.o ability.o analyze_logs.o damage.o endofturn.o evaluate.o expectiminimax.o gender.o item.o move.o pokemon.o simple.o stat.o status.o switch.o team.o teampredictor.o weather.o

predictobjects = predictor.o ability.o damage.o gender.o item.o move.o pokemon.o simple.o stat.o status.o switch.o team.o teampredictor.o weather.o

rdcobjects = rdc.o ability.o damage.o item.o move.o pokemon.o reversedamage.o simple.o stat.o status.o team.o teampredictor.o unknown.o weather.o

analogobjects = analyze_logs_main.o ability.o analyze_logs.o damage.o move.o pokemon.o simple.o stat.o status.o team.o weather.o

analogguiobjects = analyze_logs_gui.o ability.o analyze_logs.o damage.o move.o pokemon.o simple.o stat.o status.o team.o weather.o

warnings = -Wall -Wextra -pedantic -Wno-unused  -Wformat=2
fulloptimizations = -O3 -march=native -ffast-math -DNDEBUG
fastdebug = -g -O1 -march=native -ffast-math -fno-var-tracking-assignments

ai : $(aiobjects)
	g++ -o ai $(aiobjects) $(CXXFLAGS)
ai : optimizations = -g

aio : $(aiobjects)
	g++ -o aio $(aiobjects) $(CXXFLAGS)
aio : optimizations = $(fulloptimizations)

predict : $(predictobjects)
	g++ -o predict $(predictobjects) -l fltk $(CXXFLAGS)
predict : optimizations = $(fulloptimizations)

rdc : $(rdcobjects)
	g++ -o rdc $(rdcobjects) $(CXXFLAGS)
rdc : optimizations = $(fastdebug)

rdco : $(rdcobjects)
	g++ -o rdco $(rdcobjects) $(CXXFLAGS)
rdco : optimizations = $(fulloptimizations)

analog : $(analogobjects)
	g++ -o analog $(analogobjects) $(CXXFLAGS)
analog : optimizations = -g

analoggui : $(analogguiobjects)
	g++ -o analoggui $(analogguiobjects) $(CXXFLAGS) -l fltk
analoggui : optimizations = -g

CXXFLAGS = $(warnings) $(optimizations)

ability.o: ability.cpp ability.h
ai.o: ai.cpp ai.h move.h type.h movefunction.h pokemon.h ability.h \
 gender.h item.h species.h stat.h status.h team.h weather.h \
 statfunction.h teampredictor.h analyze_logs.h expectiminimax.h \
 evaluate.h simple.h state.h
analyze_logs.o: analyze_logs.cpp analyze_logs.h pokemon.h ability.h \
 gender.h item.h move.h type.h species.h stat.h status.h team.h weather.h \
 movefunction.h switch.h
analyze_logs_main.o: analyze_logs_main.cpp analyze_logs.h pokemon.h \
 ability.h gender.h item.h move.h type.h stat.h status.h team.h \
 movefunction.h weather.h
analyze_logs_gui.o: analyze_logs_gui.cpp analyze_logs.h pokemon.h \
 ability.h gender.h item.h move.h type.h stat.h status.h team.h \
 movefunction.h weather.h
damage.o: damage.cpp damage.h pokemon.h ability.h gender.h item.h move.h \
 type.h species.h stat.h status.h team.h weather.h simple.h
endofturn.o: endofturn.cpp endofturn.h expectiminimax.h evaluate.h move.h \
 type.h pokemon.h ability.h gender.h item.h species.h stat.h status.h \
 simple.h weather.h team.h state.h damage.h statfunction.h \
 statusfunction.h
evaluate.o: evaluate.cpp evaluate.h move.h type.h pokemon.h ability.h \
 gender.h item.h species.h stat.h status.h simple.h weather.h team.h
expectiminimax.o: expectiminimax.cpp expectiminimax.h evaluate.h move.h \
 type.h pokemon.h ability.h gender.h item.h species.h stat.h status.h \
 simple.h weather.h team.h state.h endofturn.h movefunction.h \
 statfunction.h transposition.h switch.h
gender.o: gender.cpp gender.h
item.o: item.cpp item.h
move.o: move.cpp move.h type.h movefunction.h pokemon.h ability.h \
 gender.h item.h species.h stat.h status.h team.h weather.h damage.h \
 simple.h statfunction.h statusfunction.h switch.h
pokemon.o: pokemon.cpp movefunction.h move.h type.h pokemon.h ability.h \
 gender.h item.h species.h stat.h status.h team.h weather.h \
 statfunction.h
predictor.o: predictor.cpp movefunction.h move.h type.h pokemon.h \
 ability.h gender.h item.h stat.h status.h team.h weather.h \
 statfunction.h teampredictor.h
rdc.o: rdc.cpp ability.h item.h move.h type.h movefunction.h pokemon.h \
 gender.h stat.h status.h team.h weather.h reversedamage.h unknown.h \
 statfunction.h teampredictor.h
reversedamage.o: reversedamage.cpp reversedamage.h team.h pokemon.h \
 ability.h gender.h item.h move.h type.h stat.h status.h weather.h \
 unknown.h damage.h statfunction.h
simple.o: simple.cpp simple.h pokemon.h ability.h gender.h item.h move.h \
 type.h species.h stat.h status.h weather.h
stat.o: stat.cpp ability.h item.h move.h type.h pokemon.h gender.h \
 species.h stat.h status.h simple.h weather.h statfunction.h team.h
status.o: status.cpp pokemon.h ability.h gender.h item.h move.h type.h \
 species.h stat.h status.h simple.h weather.h statusfunction.h
switch.o: switch.cpp pokemon.h ability.h active.h gender.h item.h move.h \
 type.h species.h stat.h status.h simple.h weather.h statfunction.h \
 team.h statusfunction.h switch.h
team.o: team.cpp ability.h gender.h item.h move.h type.h movefunction.h \
 pokemon.h species.h stat.h status.h team.h weather.h statfunction.h \
 teampredictor.h switch.h
teampredictor.o: teampredictor.cpp pokemon.h ability.h gender.h item.h \
 move.h type.h species.h stat.h status.h team.h teampredictor.h
transposition.o: transposition.cpp expectiminimax.h evaluate.h move.h \
 type.h pokemon.h ability.h gender.h item.h stat.h status.h simple.h \
 weather.h team.h state.h transposition.h
unknown.o: unknown.cpp unknown.h item.h stat.h
weather.o: weather.cpp weather.h

.PHONY: clean
clean:
	rm *.o
