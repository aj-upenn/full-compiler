#!bin/sh

FLAG=$1

goodtest(){
    for testfile in given/good*.bminor 
    do
        echo "$testfile Output:"
        ./bminor -codegen $testfile a.s && gcc -g a.s library.c -o myprogram && ./myprogram
        echo ""
    done

   
   for testfile in good/good*.bminor 
    do
        echo "$testfile Output:"
        ./bminor -codegen $testfile a.s && gcc -g a.s library.c -o myprogram && ./myprogram
        echo ""
    done
    
}

badtest(){
    for testfile in given/bad*.bminor 
    do
        echo "$testfile Output:"
        ./bminor -typecheck $testfile
        echo ""
    done

   
    for testfile in bad/bad*.bminor 
    do
        echo "$testfile Output:"
        ./bminor -typecheck $testfile
        echo ""
    done
    
}

if [ -z "$FLAG" ] 
then 
   goodtest
   echo "--------------------------------------------"
   echo ""
   #badtest
elif [ $FLAG == "-b" ] 
then 
    badtest
elif [ $FLAG == "-g" ]
then
   goodtest
fi

rm -rf test1.bminor test2.bminor

