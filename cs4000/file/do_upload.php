<?php
//notes:
//phpinfo(): shows php current settings
//ini_set('upload_max_filesize','20M') for working with larger files also may need to keep the tcp(?) open longer
/*
if($_FILES['file']['error']>0)
{
	echo 'Error: '.$_FILES['file']['error']. '<br />'
}
else
{
	echo 'Name:'.$_FILES['file']['name']. '<br />'
	echo 'Type:'.$_FILES['file']['type']. '<br />'
	echo 'Size:'.$_FILES['file']['size']. '<br />'
	echo 'Stored in:'.$_FILES['file']['temp_name']. '<br />'
}
*/
$max_filesize = ini_get('upload_max_filesize');
echo "The max filesize is $max_filesize <br />";
echo filesize($_FILES['file']['name']);
if(filesize($_FILES['file']['name']) > $max_filesize)
{
	echo "Your file is greater than $max_filesize <br />";
}

$filename = $_FILES['file']['name'];
$ext = substr($filename, strpos($filename, '.'), strlen($filename)-1);
$ext=strtolower($ext);
$allowed_filetypes = array('.jpg','.gif', '.pdf', '.jpeg');
if(!in_array($ext, $allowed_filetypes))
{
	die("Not allowed to upload that file");
}

$tmpname = $_FILES['file']['tmp_name'];
$destination = 'U:\public_html\CS 4000\file\images';
$new_filename = $destination.$filename;

if(!is_dir($destination))
{
	mkdir($destination, 0755);
	chmod($destination, 0755);
}
if(move_uploaded_file($tmpname , $new_filename))
{
    echo "Successful copy <br />";
    //set permissions
    chmod($new_filename, 744);
    echo "<a href=$destination>here</a>";
}
else
{
	echo "No success <br />";
}

?>
