cat $1>sorted.txt #write file 1 to sorted.txt
cat $2>>sorted.txt #append file2 from wherever we wrote in sorted.txt last (so that old content not erased)
sort -u -o sorted.txt sorted.txt  #u is for unique, o is to store output of sort in the second filename (here same file)
