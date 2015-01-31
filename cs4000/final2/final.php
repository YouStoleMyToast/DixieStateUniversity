<!DOCTYPE html>

<html>
<head>
<script src="//ajax.googleapis.com/ajax/libs/jquery/1.8.2/jquery.min.js"></script>
<script >
	$(document).ready(function (){
		$('#btn').click(function(){
			$.post("ftest.php", $("#testform").serialize(),function(response) {
				$('#answer').html(response);
			});//end .post
		});
	});

</script>
</head>
<body>
<?php

if(isset($_POST['textinput']) && isset($_POST['dropdown']) && isset($_POST['btn']))
{
	$string=$_POST['textinput'];
	$dropdown=$_POST['dropdown'];
	$url="http://vt4000.cs.dixie.edu/filter_api/f.php?string=".$string."type=".$dropdown."&format=json";
}

echo "<form method='post'>";
	echo "<input type='text' name='textinput'>";


	$typeurl="http://vt4000.cs.dixie.edu/filter_api/f.php?typeList";
	$file=file_get_contents($typeurl);
	$dec=json_decode($file,true);
	
	//echo $dec['description'][0];
/*
	?>
	<select name='filter' id='filter'><option value=b1ff title='The B1FF filter'>b1ff</option><option value=cockney title='Cockney English'>cockney</option><option value=chef title='convert English on stdin to Mock Swedish on stdout'>chef</option><option value=eleet title='K3wl hacker slang'>eleet</option><option value=fanboy title='Speak like a fanboy. Filters out extraneous words and focuses on the words fans use.'>fanboy</option><option value=fudd title='Elmer Fudd'>fudd</option><option value=jethro title='Hillbilly text filter'>jethro</option><option value=jive title='Jive English'>jive</option><option value=jibberish title=' Runs text through a random selection of the rest of the filters,to make really weird output.'>jibberish</option><option value=ken title='English  into  Cockney,  featuring (dubious) rhyming slang for alot of computer terminology.'>ken</option><option value=kraut title='Generates text with a bad German accent.'>kraut</option><option value=kenny title=' Generates text as spoken by Kenny on South Park.'>kenny</option><option value=ky00te title='This program places a very cute (and familiar to FurryMuck fans) accent on any text file.'>ky00te</option><option value=nethackify title='Wiped out text like can be found in nethack.'>nethackify</option><option value=newspeak title='A-la-1984'>newspeak</option><option value=censor title='CDA-ize text'>censor</option><option value=nyc title='Brooklyn English'>nyc</option><option value=pirate title='Talk like a pirate.'>pirate</option><option value=rasterman title='Makes text look like it came from the keyboard of Carsten Haitzler.'>rasterman</option><option value=scottish title='Fake scottish (dwarven) accent filter, inspired by the character "Durkon" from Order of the Stick.'>scottish</option><option value=spammer title='Turns honest text into something that is liable to be flagged as spam.'>spammer</option><option value=studly title='Studly caps.'>studly</option><option value=uiencode title='Use glorious unicode to the fullest possibile  extent.  As  seen previously in many man pages.'>uiencode</option><option value=upside-down title='Flips  text  upside  down. Stand on your head and squint to read the output.'>upside-down</option></select> 
	<?php
*/	
	echo "<input type='select' name='dropdown'>";
	
		echo "<select>".."</select>";

			
	echo "<input type='submit' name='btn' value='submit'>";
echo "</form>";
echo "<div id='answer'></div>";
echo "<a href='http://vt4000.cs.dixie.edu/filter_api/view_all_queries.php'>View all</a>";

?>
</body>
</html>