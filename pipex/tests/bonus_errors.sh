# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    bonus_errors.sh                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/16 22:02:02 by sguilher          #+#    #+#              #
#    Updated: 2022/03/29 05:09:54 by sguilher         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

GREEN="\033[0;32m"
RED="\033[38;2;222;56;43m"
BLUE="\033[38;2;34;183;235m"
YELLOW="\033[1;33m"
RESET="\033[0m"

cd ..
make bonus

printf "$YELLOW"
echo "************************ PIPEX TESTER ************************"
printf "\n"

printf "$YELLOW"
echo "******************* Part 1 - Handling errors *******************"
printf "\n"

## ------------------ argumentos diferente de 5 ------------------------##

printf "$GREEN"
echo "------------------------- INPUTS TEST -------------------------"
printf "\n\n"
printf "$BLUE"
echo "Test 1:"
printf "$RESET"
./pipex_bonus infile0 "catzzz" "bonjour" "wc -w" tests/outfiles/outfile
printf "\n"

printf "$BLUE"
echo "Test 2:"
printf "$RESET"
./pipex_bonus infile0 "cat" tests/outfiles/outfile
printf "\n\n"

## ------------------ arquivo de entrada não existe ------------------------##
printf "$GREEN"
echo "--------------------- INFILE DOESN'T EXIST ---------------------"
printf "\n"

printf "$BLUE"
echo "Test 1:"
printf "$RESET"
touch tmp
< infile0 ls -l | wc -l > tests/outfiles/outfile00 # errno 2, não roda o primeiro comando, mas roda o segundo
#infile0: No such file or directory
# não executa o primeiro comando
rm tmp
./pipex_bonus infile0 "ls -l" "wc -l" tests/outfiles/outfile01
printf "$RED"
diff tests/outfiles/outfile00 tests/outfiles/outfile01
printf "$RESET"

printf "\n"
printf "$BLUE"
echo "Test 2:"
printf "$RESET"
< infile0 "" | "" > tests/outfiles/outfile10
./pipex_bonus infile0 "" "" tests/outfiles/outfile11
printf "$RED"
diff tests/outfiles/outfile10 tests/outfiles/outfile11
printf "$RESET"

printf "\n"
printf "$BLUE"
echo "Test 3:"
printf "$RESET"
< infile0 catzzz | wc -w > tests/outfiles/outfile20
./pipex_bonus infile0 "catzzz" "wc -w" tests/outfiles/outfile21
printf "$RED"
diff tests/outfiles/outfile20 tests/outfiles/outfile21
printf "$RESET"
#não roda o primeiro comando (dá erro), mas roda o segundo
#infile0: No such file or directory

printf "\n"
printf "$BLUE"
echo "Test 4:"
printf "$RESET"
< infile0 lss | wcc -l > tests/outfiles/outfile40
./pipex_bonus infile0 "lss" "wcc -l" tests/outfiles/outfile41
printf "$RED"
diff tests/outfiles/outfile40 tests/outfiles/outfile41
printf "$RESET"
## ambos comandos não existem e arquivo de entrada não existe:
# msg de erro "bash: infile: No such file or directory"
# msg de erro "bash: wcc: command not found" apenas para o último comando
# cria o arquivo de tests/outfiles/outfile ou deixa ele vazio se ele existe

printf "\n"
printf "$BLUE"
echo "Test 5:"
printf "$RESET"
< infile0 catzzz | bonjour | wc -l > tests/outfiles/outfile30
./pipex_bonus infile0 "catzzz" "bonjour" "wc -w" tests/outfiles/outfile31
diff tests/outfiles/outfile30 tests/outfiles/outfile31
#não roda o primeiro e o segundo comando (dá erro), mas roda o segundo

printf "\n\n"
## ------------------ arquivo de entrada existe ------------------------##
printf "$GREEN"
echo "-------------------------- INFILE EXISTS --------------------------"
printf "\n"

#permissões de arquivo de entrada - execução, não leitura
printf "$BLUE"
echo "Test 1:"
printf "$RESET"
chmod 000 tests/infiles/infile_no_permission
< tests/infiles/infile_no_permission ls -l | wc -l > tests/outfiles/outfile50
./pipex_bonus tests/infiles/infile_no_permission "ls -l" "wc -l" tests/outfiles/outfile51
chmod 644 tests/infiles/infile_no_permission
printf "$RED"
diff tests/outfiles/outfile50 tests/outfiles/outfile51
printf "$RESET"

## ambos comandos não existem
printf "\n"
printf "$BLUE"
echo "Test 2: wrong commands"
printf "$RESET"
< tests/infiles/infile lss | wcc -l > tests/outfiles/outfile60
./pipex_bonus tests/infiles/infile "lss" "wcc -l" tests/outfiles/outfile61
printf "$RED"
diff tests/outfiles/outfile60 tests/outfiles/outfile61
printf "$RESET"
# cria o arquivo de tests/outfiles/outfile ou deixa ele vazio se ele existe
# msg de erro "bash: lss: command not found"
# msg de erro "bash: wcc: command not found"

printf "\n"
printf "$BLUE"
echo "Test 3: wrong first command"
printf "$RESET"
< tests/infiles/infile lss | wc -l > tests/outfiles/outfile70
./pipex_bonus tests/infiles/infile "lss" "wc -l" tests/outfiles/outfile71
printf "$RED"
diff tests/outfiles/outfile70 tests/outfiles/outfile71
printf "$RESET"

printf "\n"
printf "$BLUE"
echo "Test 3: wrong second command"
printf "$RESET"
< tests/infiles/infile ls -l | wcc -l > tests/outfiles/outfile80
./pipex_bonus tests/infiles/infile "ls -l" "wcc -l" tests/outfiles/outfile81
printf "$RED"
diff tests/outfiles/outfile80 tests/outfiles/outfile81
printf "$RESET"

printf "\n"
printf "$BLUE"
echo "Test 4: first empty command"
printf "$RESET"
< tests/infiles/swim_good "" | tr 'o' '0' > tests/outfiles/outfile90
./pipex_bonus tests/infiles/swim_good "" "tr 'o' '0'" tests/outfiles/outfile91
printf "$RED"
diff tests/outfiles/outfile90 tests/outfiles/outfile91
printf "$RESET"
# bash: : command not found
# cria o tests/outfiles/outfile

printf "\n"
printf "$BLUE"
echo "Test 5: second empty command"
printf "$RESET"
< tests/infiles/swim_good tr 'o' '0' | "" > tests/outfiles/outfile100
./pipex_bonus tests/infiles/swim_good "tr 'o' '0'" "" tests/outfiles/outfile101
printf "$RED"
diff tests/outfiles/outfile100 tests/outfiles/outfile101
printf "$RESET"

printf "\n"
printf "$BLUE"
echo "Test 6: empty commands"
printf "$RESET"
< tests/infiles/swim_good "" | "" > tests/outfiles/outfile110
./pipex_bonus tests/infiles/infile "" "" tests/outfiles/outfile111
printf "$RED"
diff tests/outfiles/outfile110 tests/outfiles/outfile111
printf "$RESET"
#bash: : command not found
#bash: : command not found

#< swim_good grep swim |  > tests/outfiles/outfile ou
#< swim_good grep swim | > tests/outfiles/outfile
#não joga nada no terminal
# não tem como colocar esse tipo de input no pipex (erro de número de argumentos)

printf "\n"
printf "$BLUE"
echo "Test 7: command argument invalid"
printf "$RESET"
< tests/infiles/swim_good find . -maxdeth 3 -name outfile* | wc -l > tests/outfiles/outfile210
./pipex_bonus tests/infiles/swim_good "find . -maxdeth 3 -name outfile*" "wc -l" tests/outfiles/outfile211
printf "$RED"
diff tests/outfiles/outfile210 tests/outfiles/outfile211
printf "$RESET"

printf "\n\n"
printf "$GREEN"
echo "------------------------ SINGLE QUOTE ERRORS ------------------------"
printf "\n"

printf "$BLUE"
echo "Test 1: missing single quote 1"
printf "$RESET"
./pipex_bonus tests/infiles/swim_good "tr 'o' 'O" "tr 'mn' 'nm'" tests/outfiles/outfile121
printf "\n"

printf "$BLUE"
echo "Test 2: missing single quote 2"
printf "$RESET"
./pipex_bonus tests/infiles/swim_good "tr 'o' 'O'" "tr 'mn' 'nm" tests/outfiles/outfile131
printf "\n"

printf "$BLUE"
echo "Test 3: missing single quote 3"
printf "$RESET"
./pipex_bonus tests/infiles/swim_good "tr 'o' 'O" "tr 'mn' 'nm" tests/outfiles/outfile141
printf "\n"

printf "$BLUE"
echo "Test 4: missing single quote 4"
printf "$RESET"
./pipex_bonus tests/infiles/swim_good "grep swim" "tr 'o' 'O'" "tr 'mn' 'nm" "tr 'Ii' '1" tests/outfiles/outfile
printf "\n"
#./clean.sh