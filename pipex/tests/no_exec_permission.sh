# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    mandatory.sh                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/16 22:02:02 by sguilher          #+#    #+#              #
#    Updated: 2022/03/29 04:43:14 by sguilher         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

GREEN="\033[0;32m"
RED="\033[38;2;222;56;43m"
BLUE="\033[38;2;34;183;235m"
YELLOW="\033[1;33m"
RESET="\033[0m"

cd ..
make

printf "$YELLOW"
echo "************************ PIPEX TESTER ************************"
printf "\n"

echo "******************* Part 2 - Testing commands results *******************"
printf "\n"

printf "\n"
printf "$BLUE"
echo "Test 1: pdf 1"
printf "$RESET"
< tests/infiles/infile ls -l | wc -l > tests/outfiles/outfile150
./pipex tests/infiles/infile "ls -l" "wc -l" tests/outfiles/outfile151
printf "$RED"
diff tests/outfiles/outfile150 tests/outfiles/outfile151
printf "$RESET"

printf "\n"
printf "$BLUE"
echo "Test 2: pdf 2"
printf "$RESET"
< tests/infiles/infile grep a1 | wc -w > tests/outfiles/outfile160
./pipex tests/infiles/infile "grep a1" "wc -w" tests/outfiles/outfile161
printf "$RED"
diff tests/outfiles/outfile160 tests/outfiles/outfile161
printf "$RESET"

printf "\n"
printf "$BLUE"
echo "Test 3:"
printf "$RESET"
< tests/infiles/infile grep ls | wc -w > tests/outfiles/outfile170
./pipex tests/infiles/infile "grep ls" "wc -w" tests/outfiles/outfile171
printf "$RED"
diff tests/outfiles/outfile170 tests/outfiles/outfile171
printf "$RESET"

printf "\n"
printf "$BLUE"
echo "Test 4:"
printf "$RESET"
< tests/infiles/infile echo 'hello world' | tr o 0 > tests/outfiles/outfile180
./pipex tests/infiles/infile "echo 'hello world'" "tr o 0" tests/outfiles/outfile181
printf "$RED"
diff tests/outfiles/outfile180 tests/outfiles/outfile181
printf "$RESET"

printf "\n"
printf "$BLUE"
echo "Test 5:"
printf "$RESET"
< tests/infiles/infile chmod 777 tests/outfiles/outfile00 | ls -l > tests/outfiles/outfile190
chmod 644 tests/outfiles/outfile00
./pipex tests/infiles/infile "chmod 777 tests/outfiles/outfile00" "ls -l" tests/outfiles/outfile191
printf "$RED"
diff tests/outfiles/outfile190 tests/outfiles/outfile191
printf "$RESET"

printf "\n"
printf "$BLUE"
echo "Test 6:"
printf "$RESET"
< tests/infiles/infile cd .. | ls -a > tests/outfiles/outfile200
cd pipex
./pipex tests/infiles/infile "cd .." "ls -a" tests/outfiles/outfile201
cd pipex
printf "$RED"
diff tests/outfiles/outfile200 tests/outfiles/outfile201
printf "$RESET"

printf "\n"
printf "$BLUE"
echo "Test 7:"
printf "$RESET"
< tests/infiles/swim_good cat | grep swim > tests/outfiles/outfile210
./pipex tests/infiles/swim_good "cat" "grep swim" tests/outfiles/outfile211
printf "$RED"
diff tests/outfiles/outfile210 tests/outfiles/outfile211
printf "$RESET"

printf "\n"
printf "$BLUE"
echo "Test 8:"
printf "$RESET"
< tests/infiles/swim_good grep swim | tr nm mn > tests/outfiles/outfile210
./pipex tests/infiles/swim_good "grep swim" "tr nm mn" tests/outfiles/outfile211
printf "$RED"
diff tests/outfiles/outfile210 tests/outfiles/outfile211
printf "$RESET"

printf "\n"
printf "$BLUE"
echo "Test 9:"
printf "$RESET"
< tests/infiles/swim_good find . -maxdepth 3 -name outfile* | wc -l > tests/outfiles/outfile210
./pipex tests/infiles/swim_good "find . -maxdepth 3 -name outfile*" "wc -l" tests/outfiles/outfile211
printf "$RED"
diff tests/outfiles/outfile210 tests/outfiles/outfile211
printf "$RESET"

printf "\n"
printf "$BLUE"
echo "Test 10:"
printf "$RESET"
< tests/infiles/swim_good git log -5 | grep Date > tests/outfiles/outfile210
./pipex tests/infiles/swim_good "git log -5" "grep Date" tests/outfiles/outfile211
printf "$RED"
diff tests/outfiles/outfile210 tests/outfiles/outfile211
printf "$RESET"

printf "\n"
printf "$BLUE"
echo "Test 11:"
printf "$RESET"
< tests/infiles/swim_good ls -l | cut -b 15- > tests/outfiles/outfile210
./pipex tests/infiles/swim_good "ls -l" "cut -b 15-" tests/outfiles/outfile211
printf "$RED"
diff tests/outfiles/outfile210 tests/outfiles/outfile211
printf "$RESET"

printf "\n"
printf "$BLUE"
echo "Test 12:"
printf "$RESET"
< tests/infiles/swim_good ls | cat -e > tests/outfiles/outfile210
./pipex tests/infiles/swim_good "ls" "cat -e" tests/outfiles/outfile211
printf "$RED"
diff tests/outfiles/outfile210 tests/outfiles/outfile211
printf "$RESET"

printf "$GREEN"
echo "------------------------ SINGLE QUOTE ------------------------"
printf "\n"

printf "\n"
printf "$BLUE"
echo "Test 1:"
printf "$RESET"
< tests/infiles/swim_good grep swim | tr 'nm' 'mn' > tests/outfiles/outfile210
./pipex tests/infiles/swim_good "grep swim" "tr 'nm' 'mn'" tests/outfiles/outfile211
printf "$RED"
diff tests/outfiles/outfile210 tests/outfiles/outfile211
printf "$RESET"

printf "\n"
printf "$BLUE"
echo "Test 2:"
printf "$RESET"
< tests/infiles/swim_good grep -v swim | tr 'nm' 'mn' > tests/outfiles/outfile210
./pipex tests/infiles/swim_good "grep -v swim" "tr 'nm' 'mn'" tests/outfiles/outfile211
printf "$RED"
diff tests/outfiles/outfile210 tests/outfiles/outfile211
printf "$RESET"

printf "\n"
printf "$BLUE"
echo "Test 3:"
printf "$RESET"
< tests/infiles/swim_good grep $PATH | awk -F : 'print $1' > tests/outfiles/outfile210
./pipex tests/infiles/swim_good "grep $PATH" "awk -F : 'print $1'" tests/outfiles/outfile211
printf "$RED"
diff tests/outfiles/outfile210 tests/outfiles/outfile211
printf "$RESET"

printf "\n"
printf "$BLUE"
echo "Test 13:"
printf "$RESET"
< tests/infiles/swim_good ls -l | -n 'p;n' > tests/outfiles/outfile210
./pipex tests/infiles/swim_good "ls -l" "-n 'p;n'" tests/outfiles/outfile211
printf "$RED"
diff tests/outfiles/outfile210 tests/outfiles/outfile211
printf "$RESET"

#./pipex_bonus swim_good "grep swim" "tr 'o' 'O'" "tr 'mn' 'nm" "tr 'Ii' '1" tests/outfiles/outfile
#./clean.sh