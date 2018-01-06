
#!bin/sh
for file in ./*
do
	if test -f $file
	then
		echo $file 是文件
	fi
	if test -d $file
	then
		echo $file 是目录
		FILE=${file:2}
		sed "s/alsa/${FILE}/g" alsa/txt > ${FILE}/CMakeLists.txt
	fi
done
