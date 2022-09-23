#! /bin/bash

# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    test_container.sh                                  :+:    :+:             #
#                                                      +:+                     #
#    By: shoogenb <shoogenb@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/09/23 15:26:12 by shoogenb      #+#    #+#                  #
#    Updated: 2022/09/23 15:33:00 by shoogenb      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# Seed can be changed to test with other random values
seed=42

yellow="\033[33m"
green="\033[32m"
red="\033[31m"
blue="\033[34m"
reset="\033[0m"

container_test_function(){
    container=$1

    {
    make fclean; 
    make STD_MODE=0 -j4;
    } &> /dev/null
    echo -e "${yellow} Test - FT_${container} ${reset}";
    ./ft_containers $seed $container;
    echo -e "${blue} [Done] ${reset}";

    {
        make fclean;
        make STD_MODE=1 -j4;
    } &> /dev/null
    echo -e "${yellow} Test - STD_${container} ${reset}";
    ./ft_containers $seed $container;
    echo -e "${blue} [Done] ${reset}";
    diff -u test/out_ft.log test/out_std.log > test/diff.log;
    if [ -s test/diff.log ]; then
        echo -e "${red} Diff found check test/diff.log ${reset}";
        exit 1
    else
        echo -e "${green} no diff found ${reset}";
    fi
}

echo "making test directory for putting output of test";
mkdir -p -v test;

container_test_function "vector"
container_test_function "map"
container_test_function "stack"
container_test_function "set"

echo -e "${green} all test passed! ${reset}";