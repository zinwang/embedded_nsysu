#!/usr/bin/zsh
a=100
for ((i=0;i<$a;i+=1))
do
	./hw1|grep 'Pair\|Full\|Four\|Straight'
done

