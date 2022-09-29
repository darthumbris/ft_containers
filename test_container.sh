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

#This function will make a test for the ft version and then std version and then compare the outputs
#If a test fails (so there is a difference between files) it will exit
container_test_function(){
    container=$1
    seed=$2
    {
    make fclean; 
    make STD_MODE=0 -j4;
    } &> /dev/null
    mkdir -p -v "test/${container}"
    mkdir -p -v "result/${container}"
    echo -e "${yellow} Test - FT_${container} ${reset}";
    ./ft_containers $seed $container 
	#>> "result/${container}/time_ft.out";
    echo -e "${blue} [Done] ${reset}";
    cp "test/${container}/out_ft.log" "result/${container}"
    {
        make fclean;
        make STD_MODE=1 -j4;
    } &> /dev/null
    mkdir -p -v "test/${container}";
    echo -e "${yellow} Test - STD_${container} ${reset}";
    ./ft_containers $seed $container
   #	>> "result/${container}/time_std.out";
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

#if you want to test a single container comment out the other ones

container_test_all(){

    #you can also change this so it is always a fixed seed value
    current_seed=$[RANDOM%10000+1]
    container_test_function "vector" "$current_seed"
    container_test_function "map" "$current_seed"
    container_test_function "stack" "$current_seed"
    container_test_function "set" "$current_seed"
}

#if you want to only test once set the end value to 1
start=1
end=10
for (( c=$start; c<=$end; c++ ))
do
    echo ""
    container_test_all
    echo ""
    echo "========Next test=========="
done

echo -e "${green} all test passed! ${reset}";

make fclean &> /dev/null
#comment out following line to check out the outputs (time outputs, diff etc)
rm -rf "result";
