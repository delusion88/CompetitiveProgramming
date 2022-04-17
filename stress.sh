#!/bin/bash
i=1
g++ -std=c++17 gen.cpp -o ./stress/generator
g++ -std=c++17 source.cpp -o ./stress/orig
g++ -std=c++17 brute.cpp -o ./stress/brute
max_tests=$1
diff_found=0
RED='\033[1;31m'
GREEN='\033[1;32m'
NC='\033[0m'
On_IBlue='\033[0;104m' 
while [ $i -le $max_tests ]
do
    ./stress/generator > ./stress/input1
    ./stress/orig < ./stress/input1 > ./stress/original_output
    ./stress/brute < ./stress/input1 > ./stress/brute_output
    if diff --tabsize=1 -F --label --side-by-side --ignore-space-change ./stress/original_output ./stress/brute_output > ./stress/dont_show_on_terminal; then
        echo -e "Test $i: ${GREEN}Accepted${NC}"
    else
        echo -e "Test $i: ${RED}Wrong Answer${NC}"
        diff_found=1
        break
    fi
    i=$((i+1))
done
if [ $diff_found -eq 1 ]
then
    echo -e "${On_IBlue}Input:${NC}"
    cat ./stress/input1
    echo ""
    echo -e "${On_IBlue}Output:${NC}"
    cat ./stress/original_output
    echo ""
    echo ""
    echo -e "${On_IBlue}Expected:${NC}"
    cat ./stress/brute_output
    echo ""
    echo ""
else
    echo -e "${GREEN}Ok ${max_tests} of ${max_tests} test cases.${NC}"
fi
rm -rf ./stress/original_output
rm -rf ./stress/brute_output
rm -rf ./stress/input1
rm -rf ./stress/dont_show_on_terminal
