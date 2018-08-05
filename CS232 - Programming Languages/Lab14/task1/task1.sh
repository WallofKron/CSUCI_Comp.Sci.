#!/bin/bash
randomdraw(){
 Suits="Clubs Diamonds Hearts Spades"
 suit=($Suits)

 Denominations="2 3 4 5 6 7 8 9 10 Jack Queen King Ace"
 denomination=($Denominations)

 num_suits=${#suit[*]}
 num_denominations=${#denomination[*]}

for ((x=0 ; $x<$loopnum ; x=$x+1));
	do
 (( numoccurences[$(( RANDOM%num_denominations ))]++ ))
 (( suitoccurences[$(( RANDOM%num_suits ))]++ ))
	done
}


declare -a numoccurences
declare -a suitoccurences

declare starnum


echo "How Many Random Draws?: "
read loopnum
randomdraw loopnum

for ((x=0 ; $x<$num_denominations ; x=$x+1));
	do
		(( rounder = numoccurences[x] % 10 ))

		if [ $rounder -ge 5 ];
			then
				(( starnum = numoccurences[x] / 10 + 1 ))
			else
				(( starnum = numoccurences[x] / 10 ))
		fi
		printf "${denomination[x]}: "
	for ((k=0 ; $k<$starnum ; k=$k+1));
		do
			printf "*"
		done
		printf "\n"
	done

for ((x=0 ; $x<$num_suits ; x=$x+1));
	do
		(( rounder = suitoccurences[x] % 10 ))

		if [ $rounder -ge 5 ];
			then
				(( starnum = numoccurences[x] / 10 + 1 ))
			else
				(( starnum = numoccurences[x] / 10 ))
		fi
		printf "${suit[x]}: "
	for ((j=0 ; $j<$starnum ; j=$j+1));
		do
		printf "*"
		done
		printf "\n"
	done