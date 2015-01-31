<?php
include_once "header.php";
?>

<div id="addmediaform">
<form method="POST" action="addmedia.php">
	<p>
    <lable>Media Type</lable>
    <select name="mediatype">
	<option value="music">Music</option>
	<option value="show">Show</option>
	<option value="movie">Movie</option>
	<option value="picture">Picture</option>
    </select>
	</p>
	
	<p>
	<lable>Title</lable>
	<input type="text" name="title" />
	</p>
	
	<p>
	<lable>Artist</lable>
	<input type="text" name="artist" />
	</p>
	
	<p>
    <lable>Genre</lable>
    <select name="genre">
    <option value="rock">Rock</option>
    <option value="classical">Classical</option>
    <option value="game">Game</option>
    </select>
	</p>
	
    <p><input type="submit"></p>
    
</form>
</div>

<div id="addmediaresponse">
<?php
	echo "<lable>Media Type: </lable>";
    echo "$_POST[mediatype]";
    echo "<br />";
	echo "<lable>Title: </lable>";
    echo "$_POST[title]"; 
	echo "<br />";
	echo "<lable>Artist: </lable>";
	echo "$_POST[artist]";
    echo "<br />";
	echo "<lable>Genre: </lable>";
    echo "$_POST[genre]"; 
	
	
	
	$currentContents = file_get_contents("mediadata.txt");
	$fin=fopen("mediadata.txt",'w');
	$object = json_encode($_POST);
	fwrite($fin, $currentContents.$object."\n");
	fclose($fin);
	
	/*$mediatype="$_POST[mediatype] ";
	$mediatitle="$_POST[title] ";	
	$mediaartist="$_POST[artist] ";
	$mediagenre="$_POST[genre] ";
	
	fwrite($fin,"<p>");
	fwrite($fin, $mediatype);
	fwrite($fin,"','");
	fwrite($fin, $mediatitle);
	fwrite($fin,"','");
	fwrite($fin, $mediaartist);
	fwrite($fin,"','");
	fwrite($fin, $mediagenre);
	fwrite($fin,"</p>");
	
	fclose($fin);*/
	
	/*
	//Email code
	$mediatype=$_POST['mediatype'];
	$title=$_POST['title'];
	$msg="You added a new $mediatype called $title to your collection";
	mail("mavortius@yahoo.com","Media collection update",$msg);
	*/
?>
</div>

<?php
include_once "footer.php";
?>