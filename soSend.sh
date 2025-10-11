#! /bin/bash -x
cd "$(dirname "$0")"

testEnvDir=/home/jadeb/workspace/jHigh/testEnv/lib/


#echo $testEnvDir

modNames=(cardEngine)

#echo $modNames

for i in ${modNames[@]}; do
#	echo $i
#	echo cp ./lib/$i.so $testEnvDir
	cp ./lib/$i.so $testEnvDir
done



