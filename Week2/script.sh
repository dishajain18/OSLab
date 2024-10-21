echo the name of this script is $0
echo the first argument is $1
echo a list of all arguments is $*
echo this script places the date into a temporary file called $1.$$ 
# $1 is first argument $$ is process id if script so we are name the file Rahul.processid
date>$1.$$
#redirect the output of date
ls $1.$$
#list the file 
#here if you do cat $1.$$ it will display the date
rm $1.$$
