<?php
function thedate()
{
    $date=date("l h:i");
    return $date;
}

$thedate=thedate();
echo $thedate;
?>