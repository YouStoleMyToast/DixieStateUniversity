<?php
//slides 9
//note: for encryption use a crypt function and be sure to use the salt value to give it a random starting point
//examples of mysql and php together at last (a few different examples)


$username='joe';
$plaintext='secret';
echo '<br />';
$hash=crypt($plaintext, $username);//in this case the username is the salt
echo $hash;
?>