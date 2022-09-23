#! /bin/bash

seed=42

yellow="\033[33m"
green="\033[32m"
red="\033[31m"
blue="\033[34m"
reset="\033[0m"

echo "making test directory for putting output of test";
mkdir -p -v test;
container=vector
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
else
    echo -e "${green} no diff found ${reset}";
fi

container=map
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
else
    echo -e "${green} no diff found ${reset}";
fi

container=stack
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
else
    echo -e "${green} no diff found ${reset}";
fi

container=set
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
else
    echo -e "${green} no diff found ${reset}";
fi