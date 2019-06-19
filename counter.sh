#! /bin/sh

count=0
tmp=`find . -name "*.cpp"|xargs cat|grep -v ^$|wc -l`
count=`expr $count + $tmp`
tmp=`find . -name "*.l" | xargs cat | grep -v ^$ | wc -l`
count=`expr $count + $tmp`
tmp=`find . -name "*.y" | xargs cat | grep -v ^$ | wc -l`
count=`expr $count + $tmp`
tmp=`find . -name "*.hpp" | xargs cat | grep -v ^$ | wc -l`
count=`expr $count + $tmp`
tmp=`find . -name "*.h" | xargs cat | grep -v ^$ | wc -l`
cout=`expr $count + $tmp`
tmp=`find . -name "*.c" | xargs cat | grep -v ^$ | wc -l`
count=`expr $count + $tmp`
tmp=`cat ./src/parser.y | wc -l`
count=`expr $count - $tmp`
echo $count
