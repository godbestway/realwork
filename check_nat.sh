#ps aux|pgrep nat
#num=$(ps aux|pgrep nat)
#echo $num
#if [ ! -n "$num"];
#then
#echo "IS NULL"
#else
#echo "NOT NULL"
#fi

#for var in 1 2 3
while :
do 
num=$(ps aux|pgrep nat)
if [ ! -n "$num" ];
then
     echo "continue"
     continue
else
     echo "nat start"
     break
fi
done
