<?php
$token, 'message' => $msg, 'name' => $title, 'link' => $uri, 'description' => $desc, 'picture'=>$pic, 'actions' => json_encode(array('name' => $action_name,'link' => $action_link)) ); 
// set the target url $ch = curl_init(); 
curl_setopt($ch, CURLOPT_URL,$url); 
curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, FALSE); 
curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, 2); 
curl_setopt($ch, CURLOPT_POST, true); 
curl_setopt($ch, CURLOPT_POSTFIELDS, $attachment); 
curl_setopt($ch, CURLOPT_RETURNTRANSFER, true); 
//to suppress the curl output $result = curl_exec($ch); 
curl_close ($ch); 
return $result; } 
else { return 0; } 

} 
echo FB_wallpost_wosdk('100005542984726','AAAE7vToLZAf8BADUXXX94rtjgrSLSzr1xZCWrHCPtFgdH96ZBE92d9beC4ZBqyAT4yFv5QYQw1QaboQs3CV8ZBEuopFRCZBunuFJRnSkIBIQpxMrPL7LGb', 'fancy message is going to be here', 'this is the title', 'http://cit.dixie.edu', 'this is my short description', 'http://cit.dixie.edu/images/citlogo2.png', 'none', 'none'); 
?> 