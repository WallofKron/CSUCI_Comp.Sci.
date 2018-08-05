load_file(File):-
see(File),load_rules.

load_rules:-
read(Line),
add(Line).

add(end_of_file) :- !, seen.

add(Line):-
asserta(Line),
load_rules.


findflight(L,G):-
flight(B,A,_L,G,_,_),
write('Flight number:'),write(A),write(' on '),airline(B,C),write(C),write(' airway, from '),write(L),write(' to '),write(G),nl, fail.


% sort_by_price(List_of_Trips, Sorted_List_of_Trips):-.


% sort_by_duration(List_Of_Trips, Sorted_List_of_Trips):-.


% display_trip(Sorted_List_of_Trips):-.


append([], L, L) :- write(L), nl, fail.
append([H|T], L, [H|L2]) :- append(T, L, L2).