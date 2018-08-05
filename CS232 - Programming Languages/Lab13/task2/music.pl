artist(L) :-
tune(A,_,L,_,_,_),
write(A),nl, fail.


album(L) :-
tune(C,L,_,_,_,_),
write(C),nl, fail.


songs(L) :-
tune(L,_,V,_,_,_),
write(V),nl, fail.


audiophile(L) :-
tune(R,_,_,_,_,X),
X>L,
write(R),write(' - '),write(X),nl, fail.


songgenre(L) :-
tune(Z,_,_,L,_,_),
write(Z),nl, fail.


artistgenre(L) :-
tune(_,_,G,L,_,_),
write(G),nl, fail.

encodings(L) :-
tune(L,_,_,_,N,_),
write(N),nl, fail.


bitforsong(L) :-
tune(L,_,_,_,_,M),
write(M),nl, fail.
