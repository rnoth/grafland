
EXE='./stringmath -- '

if [ $# != "0" ]
then	EXE="valgrind $EXE"
fi


$EXE 0666 0777

$EXE 01234 01234

$EXE 0987 0987

$EXE 08792783258 03257

$EXE 08348746239087 02308235

$EXE 027238  023823

$EXE 0576 0999

$EXE 023423 0982

$EXE 0524387 022

$EXE 023 08

$EXE 04598674987 0999999

$EXE  0239823234 09999911








$EXE -0524387 +022

$EXE -08792783258 +03257

$EXE -08348746239087 -02308235

$EXE +027238  -023823


$EXE 018908098123 0999999999