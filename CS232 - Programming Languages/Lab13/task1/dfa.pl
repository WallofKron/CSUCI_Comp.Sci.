%:- dynamic(move/3).
%:- dynamic(start/1).
%:- dynamic(final/1).

% test if the word given as a list is accepted by the automaton
parse(L) :-
  start(S), 
  trans(S,L).

% check if in the final state after the whole word has been processed
trans(X,[]) :- 
  final(X),
  write(X),
  write('  '),
  write([]), nl,
  write('Word accepted by the automaton.'), nl.

% lookup the transition table and go the the next state
trans(X,[A|B]) :- 
  move(X,A,Y),
  write(X),
  write('  '),
  write([A|B]),
  nl,
  trans(Y,B).  

% if the final state cannot be matched,
% then the word is not accepted by the automaton
trans(_,_) :-
  nl, write('Word rejected by the automaton.'), nl.
