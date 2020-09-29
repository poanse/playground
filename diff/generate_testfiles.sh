#!/bin/sh

### Check for dir, if not found create it using the mkdir ##
DIR="./testfiles"
[ ! -d "$DIR" ] && mkdir "$DIR"
cd $DIR

N=0

let "N+=1"
printf "1\n2\n3\n" > test$(echo $N)_old.txt
printf "\n" > test$(echo $N)_new.txt
diff test$(echo $N)_old.txt test$(echo $N)_new.txt > test$(echo $N)_diff.txt

let "N+=1"
printf "1\n2\n3\n" > test$(echo $N)_old.txt
printf "1\n" > test$(echo $N)_new.txt
diff test$(echo $N)_old.txt test$(echo $N)_new.txt > test$(echo $N)_diff.txt

let "N+=1"
printf "1\n2\n3\n" > test$(echo $N)_old.txt
printf "2\n" > test$(echo $N)_new.txt
diff test$(echo $N)_old.txt test$(echo $N)_new.txt > test$(echo $N)_diff.txt

let "N+=1"
printf "1\n2\n3\n" > test$(echo $N)_old.txt
printf "3\n" > test$(echo $N)_new.txt
diff test$(echo $N)_old.txt test$(echo $N)_new.txt > test$(echo $N)_diff.txt

let "N+=1"
printf "1\n2\n3\n" > test$(echo $N)_old.txt
printf "1\n2\n" > test$(echo $N)_new.txt
diff test$(echo $N)_old.txt test$(echo $N)_new.txt > test$(echo $N)_diff.txt

let "N+=1"
printf "1\n2\n3\n" > test$(echo $N)_old.txt
printf "2\n3\n" > test$(echo $N)_new.txt
diff test$(echo $N)_old.txt test$(echo $N)_new.txt > test$(echo $N)_diff.txt

let "N+=1"
printf "1\n2\n3\n" > test$(echo $N)_old.txt
printf "1\n3\n" > test$(echo $N)_new.txt
diff test$(echo $N)_old.txt test$(echo $N)_new.txt > test$(echo $N)_diff.txt

let "N+=1"
printf "1\n2\n3\n" > test$(echo $N)_old.txt
printf "1\n2\n3\n" > test$(echo $N)_new.txt
diff test$(echo $N)_old.txt test$(echo $N)_new.txt > test$(echo $N)_diff.txt

#let "N+=1"
#printf "1\n2\n3\n" > test$(echo $N)_old.txt
#printf "1\n2\n3" > test$(echo $N)_new.txt
#diff test$(echo $N)_old.txt test$(echo $N)_new.txt > test$(echo $N)_diff.txt


let "N+=1"
printf "A\nB\nC\nD\nE\nF\n" > test$(echo $N)_old.txt
printf "A\nD\nE\nF\n" > test$(echo $N)_new.txt
diff test$(echo $N)_old.txt test$(echo $N)_new.txt > test$(echo $N)_diff.txt

let "N+=1"
printf "A\nB\nC\nD\nE\nF\n" > test$(echo $N)_old.txt
printf "A\nX\nX\nY\nD\nE\nF\n" > test$(echo $N)_new.txt
diff test$(echo $N)_old.txt test$(echo $N)_new.txt > test$(echo $N)_diff.txt

let "N+=1"
printf "A\nB\nC\nD\nE\nF\n" > test$(echo $N)_old.txt
printf "X\nX\nY\nD\nE\nF\n" > test$(echo $N)_new.txt
diff test$(echo $N)_old.txt test$(echo $N)_new.txt > test$(echo $N)_diff.txt

let "N+=1"
printf "A\nB\nC\nD\nE\nF\n" > test$(echo $N)_old.txt
printf "X\nY\nD\nE\nF\n" > test$(echo $N)_new.txt
diff test$(echo $N)_old.txt test$(echo $N)_new.txt > test$(echo $N)_diff.txt

let "N+=1"
printf "A\nB\nC\nD\nE\nF\n" > test$(echo $N)_old.txt
printf "X\nY\nD\nE\n" > test$(echo $N)_new.txt
diff test$(echo $N)_old.txt test$(echo $N)_new.txt > test$(echo $N)_diff.txt

let "N+=1"
printf "A\nB\nC\nD\nE\nF\n" > test$(echo $N)_old.txt
printf "X\nY\nD\nE\nX\n" > test$(echo $N)_new.txt
diff test$(echo $N)_old.txt test$(echo $N)_new.txt > test$(echo $N)_diff.txt


let "N+=1"
printf "Oh so hot\nno time\nto\ntake a rest\nyeah\n" > test$(echo $N)_old.txt
printf "\nOh so hot\nno time\n\nto\ntake\na rest\n\nyeah\n" > test$(echo $N)_new.txt
diff test$(echo $N)_old.txt test$(echo $N)_new.txt > test$(echo $N)_diff.txt

let "N+=1"
printf "Oh so hot\nno time\nto\ntake a rest\nyeah\n" > test$(echo $N)_old.txt
printf "\nOh so hot\nno time\n\nto\ntake\na rest\n\nyeah\n" > test$(echo $N)_new.txt
diff test$(echo $N)_old.txt test$(echo $N)_new.txt > test$(echo $N)_diff.txt

echo $N > Ntests.txt

exit 0
