<?php

$username="francom";
$plaintext="secret";
echo $plaintext;
echo"<br />";
$hash=crypt($plaintxt,$username);//username is the "salt"(aka "key")to make sure password after being hashed is unique. if salt is not set it will be randomly generated making it difficult to retrieve.
echo $hash;

?>