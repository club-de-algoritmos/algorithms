c() { g++ -Wall -Wconversion -Wfatal-errors -g -std=c++17 -fsanitize=undefined,address $1.cpp -o $1 ; }
r() { ./$1 ; }
rc() { time "./$1" < "$2.in" ; }
ra() { for x in *.in ; do printf "Testcase %s\n" "$x" ; time "./$1" < "$x" ; echo "================" ; done ; }
cr() { c "$1" ; ra "$1" ; }
