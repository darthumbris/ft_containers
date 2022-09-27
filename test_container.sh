#! /bin/bash

yellow="\033[33m"
green="\033[32m"
red="\033[31m"
blue="\033[34m"
reset="\033[0m"

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

# Seed can be changed for the std::srand(seed)
seed=42

#This function will make a test for the ft version and then std version and then compare the outputs
#If a test fails (so there is a difference between files) it will exit
container_test_function(){
    container=$1
    {
    make fclean; 
    make STD_MODE=0 -j4;
    } &> /dev/null
    mkdir -p -v "test/${container}"
    mkdir -p -v "result/${container}"
    echo -e "${yellow} Test - FT_${container} ${reset}";
    ./ft_containers $seed $container > "result/${container}/time_ft.out";
    echo -e "${blue} [Done] ${reset}";
    cp "test/${container}/out_ft.log" "result/${container}"
    {
        make fclean;
        make STD_MODE=1 -j4;
    } &> /dev/null
    mkdir -p -v "test/${container}";
    echo -e "${yellow} Test - STD_${container} ${reset}";
    ./ft_containers $seed $container > "result/${container}/time_std.out";
    cp "test/${container}/out_std.log" "result/${container}"
    echo -e "${blue} [Done] ${reset}";
    diff -u result/${container}/out_ft.log result/${container}/out_std.log > "result/${container}/diff.log";
    if [ -s result/${container}/diff.log ]; then
        echo -e "${red} Diff found check result/${container}/diff.log ${reset}";
        exit 1
    else
        echo -e "${green} no diff found ${reset}";
    fi
}

#if you want to test a single test comment out the other ones
container_test_function "vector"
container_test_function "map"
container_test_function "stack"
container_test_function "set"

echo -e "${green} all test passed! ${reset}";

make fclean &> /dev/null
# rm -rf "result";
