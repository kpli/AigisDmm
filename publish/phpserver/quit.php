
<?php


require_once('dbop.php');
require_once('dmmjp_c.php');

$qt = new Dmmjp_Cancel();
$dbop = new DBOP();

$urnm = '';
$pswd = '';

$sp = $_SERVER["QUERY_STRING"];
if ($sp == ''){
	print '_POST<br>';
    $urnm = $_POST['MAIL'];
    $pswd = $_POST['PSWD'];
}
else if($sp == 'autoquit'){
	print 'autoquit<br>';
	$rest = $dbop->getNotBlack();
	$urnm = $rest[0];
	$pswd = $rest[1];
}
else
{
	print 'QUERY_STRING<br>';
    $pswd = $sp;
    $urnm = $pswd.'@bccto.me';
}

print $urnm.'<br>';
print $pswd.'<br>';

if($pswd != '' && $urnm != ''){
    $ret = $qt->cancel($urnm,$pswd);
    if($ret == ''){
        showTitle('failed');
    }
    else{
        showTitle('quited');
		$dbop->delNotBlack($urnm);
    }
}
else{
    showTitle('noid');
}

function showTitle($ts){
    $dom = new DOMDocument('1.0');
    $title = $dom->createElement('title',$ts );
    $dom->appendChild($title);
    echo $dom->saveHTML();
}


?>