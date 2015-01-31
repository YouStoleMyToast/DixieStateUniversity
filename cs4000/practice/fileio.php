<?php

//$f1=fopen('text.txt','w+');
//fwrite($f1, 'all your base are belong to us');
//fclose($f1);

//$f1=fopen('text.txt', 'r');
//$f2=fread($f1,1024);
//echo "Did you know...$f2";
//fclose($f2)

readfile('text.txt');

fclose('text.txt');


$f1=fopen('text.txt', 'a+');
for($i=0;$i<10;$i++)
{
	fwrite($f1, 'You loose');
}
fclose($f1)

//$f1=fopen('text.txt', 'r');
//$f2=fread($f1,1024);
//echo "Did you know...$f2";
//fclose($f2)

?>