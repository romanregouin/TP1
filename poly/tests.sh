#!/bin/bash
T=TestsFiles
EXE=test_egalite_poly
PERF=""

if [ $# -ne 4 ] ; then
    echo "Syntaxe : $0 [valgrind (0/1)] [scalaire for multiplication poly] 
    [scalaire for eval poly] [integer for puissance poly]"
    exit
fi
if [ $1 -eq 1 ]; then
    PERF="valgrind"
fi

make clean

echo "Début des tests d'égalités"
make test_egalite_poly
$PERF ./$EXE $T/p1 $T/p2
$PERF ./$EXE $T/poly_egalite_1-1 $T/poly_egalite_1-2
$PERF ./$EXE $T/poly_egalite_2-1 $T/poly_egalite_2-2
echo "Fin des test d'égalités"

echo ""

echo "Début des tests de addition de polynômes"
EXE=test_addition_poly
make $EXE
$PERF ./$EXE $T/p1 $T/p2
$PERF ./$EXE $T/poly_addition_1-1 $T/poly_addition_1-2
$PERF ./$EXE $T/poly_addition_2-1 $T/poly_addition_2-2
echo "Fin des tests de addition de polynômes"

echo ""

echo "Début des tests de multiplication de polynôme par 1 scalaire"
EXE=test_multiplication_scalaire
make $EXE
$PERF ./$EXE $T/p1 $2
$PERF ./$EXE $T/p2 $2
$PERF ./$EXE $T/poly_multiplication_scalaire_1-1 $2
echo "Fin des tests de multiplication de polynôme par 1 scalaire"

echo ""

echo "Début des tests d'évaluation des polynôme"
EXE=test_eval_poly
make $EXE
$PERF ./$EXE $T/p1 $3
$PERF ./$EXE $T/p2 $3
$PERF ./$EXE $T/poly_multiplication_scalaire_1-1 $3
echo "Fin des tests d'évaluation des polynôme"

echo "Début des tests multiplication_polynôme"
EXE=test_multiplication_poly
make $EXE
$PERF ./$EXE $T/p1 $T/p2
$PERF ./$EXE $T/poly_multiplication_poly_1-1 $T/poly_multiplication_poly_1-2
$PERF ./$EXE $T/p1 $T/poly_multiplication_scalaire_1-1
echo "Fin des tests multiplication_polynôme"

echo "Début des test puissance des polynômes"
EXE=test_puissance_poly
make $EXE
$PERF ./$EXE $T/p1 $4
$PERF ./$EXE $T/p2 $4
$PERF ./$EXE $T/poly_multiplication_scalaire_1-1 $4
$PERF ./$EXE $T/p1 1
$PERF ./$EXE $T/p1 0
echo "Fin des test puissance des polynômes"

echo ""

echo "Début des test sur la composition des polynômes"
EXE=test_composition_poly
make $EXE
$PERF ./$EXE $T/p1 $T/p2
$PERF ./$EXE $T/p2 $T/p1
$PERF ./$EXE $T/p1 $T/poly_multiplication_scalaire_1-1
$PERF ./$EXE $T/poly_multiplication_scalaire_1-1 $T/p1
echo "Fin des test sur la composition des polynômes"