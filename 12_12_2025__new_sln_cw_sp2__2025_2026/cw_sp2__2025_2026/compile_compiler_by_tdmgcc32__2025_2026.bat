rem ###########################
rem  N.Kozak // Lviv'2025
rem ############################

setlocal
@echo off 
SET PATH=..\tools;..\tools\TDM-GCC-32\bin;%PATH%
@echo off
set CR=0x0D
<nul set /p="Compile compiler:                                              [ in progress, please wait ]"
g++                                                                                   ^
cw.cpp                                                                                ^
src\implementation\cli\cli.cpp                                                        ^
src\implementation\generator\add.cpp                                                  ^
src\implementation\generator\and.cpp                                                  ^
src\implementation\generator\bitwise_and.cpp                                          ^
src\implementation\generator\bitwise_not.cpp                                          ^
src\implementation\generator\bitwise_or.cpp                                           ^
src\implementation\generator\block.cpp                                                ^
src\implementation\generator\div.cpp                                                  ^
src\implementation\generator\else_block.cpp                                           ^
src\implementation\generator\else_if_then_block.cpp                                   ^
src\implementation\generator\equal.cpp                                                ^
src\implementation\generator\for_nonblockandblock.cpp                                 ^
src\implementation\generator\generator.cpp                                            ^
src\implementation\generator\goto_label.cpp                                           ^
src\implementation\generator\greater.cpp                                              ^
src\implementation\generator\greater_or_equal.cpp                                     ^
src\implementation\generator\if_then_block.cpp                                        ^
src\implementation\generator\index.cpp                                                ^
src\implementation\generator\index_to_value.cpp                                       ^
src\implementation\generator\input.cpp                                                ^
src\implementation\generator\less.cpp                                                 ^
src\implementation\generator\less_or_equal.cpp                                        ^
src\implementation\generator\lrassign.cpp                                             ^
src\implementation\generator\machinecodegen_addon.cpp                                 ^
src\implementation\generator\machinecodegen_pattern.cpp                               ^
src\implementation\generator\mod.cpp                                                  ^
src\implementation\generator\mul.cpp                                                  ^
src\implementation\generator\not.cpp                                                  ^
src\implementation\generator\not_equal.cpp                                            ^
src\implementation\generator\null_statement.cpp                                       ^
src\implementation\generator\objectcodegen_pattern.cpp                                ^
src\implementation\generator\operand.cpp                                              ^
src\implementation\generator\or.cpp                                                   ^
src\implementation\generator\output.cpp                                               ^
src\implementation\generator\repeat_until.cpp                                         ^
src\implementation\generator\rlassign.cpp                                             ^
src\implementation\generator\semicolon.cpp                                            ^
src\implementation\generator\sub.cpp                                                  ^
src\implementation\generator\while_block.cpp                                          ^
src\implementation\lexica\lexica.cpp                                                  ^
src\implementation\preparer\preparer.cpp                                              ^
src\implementation\semantics\semantics.cpp                                            ^
src\implementation\syntax\syntax.cpp                                                  ^
-w                                                                                    ^
-o                                                                                    ^
cw.exe                                                                                ^
-static-libgcc                                                                        ^
-static-libstdc++                                                                     ^
-std=c++11                                                                         
carriage_return.exe
<nul set /p="Compile compiler:                                              [  done, press any key ...  ]"
endlocal
pause 1 > nul
@echo on