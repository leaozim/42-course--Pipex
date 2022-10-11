# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    mandatory.sh                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/16 22:02:02 by sguilher          #+#    #+#              #
#    Updated: 2022/05/11 12:36:56 by sguilher         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

GREEN="\033[0;32m"
RED="\033[38;2;222;56;43m"
BLUE="\033[38;2;34;183;235m"
YELLOW="\033[1;33m"
RESET="\033[0m"

mkdir outfiles

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
touch tests/outfiles/outfile00
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
./pipex tests/infiles/infile "cd .." "ls -a" tests/outfiles/outfile201
#env | grep PWD --> cd não tem binário (assunto para o minishell)
#which cd - não dá resultado
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
< tests/infiles/swim_good find . -maxdepth 3 -name 'outfile*' | wc -l > tests/outfiles/outfile210
./pipex tests/infiles/swim_good "find . -maxdepth 3 -name 'outfile*'" "wc -l" tests/outfiles/outfile211
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

printf "\n"
printf "$BLUE"
echo "Test 13:"
printf "$RESET"
< tests/infiles/swim_good cat -e | ls > tests/outfiles/outfile300
./pipex tests/infiles/swim_good "cat -e" "ls" tests/outfiles/outfile301
printf "$RED"
diff tests/outfiles/outfile300 tests/outfiles/outfile301
printf "$RESET"

printf "\n"
printf "$BLUE"
echo "Test 14: Big file"
printf "$RESET"
< tests/infiles/infile_big grep she | wc -l > tests/outfiles/outfile310
./pipex tests/infiles/infile_big "grep she" "wc -l" tests/outfiles/outfile311
printf "$RED"
diff tests/outfiles/outfile310 tests/outfiles/outfile311
printf "$RESET"

printf "\n"
printf "$BLUE"
echo "Test 15: PipexTester test 6"
printf "$RESET"
< tests/infiles/infile_big tr a ' ' | tr ' ' x > tests/outfiles/outfile320
./pipex tests/infiles/infile_big "tr a ' '" "tr ' ' x" tests/outfiles/outfile321
printf "$RED"
diff tests/outfiles/outfile320 tests/outfiles/outfile321
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
< tests/infiles/swim_good grep swim | awk -F: '{print $1}' > tests/outfiles/outfile210
./pipex tests/infiles/swim_good "grep swim" "awk -F: '{print $1}'" tests/outfiles/outfile211
printf "$RED"
diff tests/outfiles/outfile210 tests/outfiles/outfile211
printf "$RESET"

printf "\n"
printf "$BLUE"
echo "Test 4:"
printf "$RESET"
< tests/infiles/swim_good ls -l | sed -n 'p;n' > tests/outfiles/outfile210
./pipex tests/infiles/swim_good "ls -l" "sed -n 'p;n'" tests/outfiles/outfile211
printf "$RED"
diff tests/outfiles/outfile210 tests/outfiles/outfile211
printf "$RESET"
printf "\n"

printf "$BLUE"
echo "Test 5:"
printf "$RESET"
< tests/infiles/swim_good grep -v swim | tr ' ' '  ' > tests/outfiles/outfile220
./pipex tests/infiles/swim_good "grep -v swim" "tr ' ' '  '" tests/outfiles/outfile221
printf "$RED"
diff tests/outfiles/outfile220 tests/outfiles/outfile221
printf "$RESET"

printf "\n"
#./pipex_bonus swim_good "grep swim" "tr 'o' 'O'" "tr 'mn' 'nm" "tr 'Ii' '1" tests/outfiles/outfile
#./clean.sh
