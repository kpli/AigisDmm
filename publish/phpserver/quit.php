
<?php


require_once('dmmjp_c.php');
$qt = new Dmmjp_Cancel();

$urnm = '';
$pswd = '';

$sp = $_SERVER["QUERY_STRING"];
if ($sp == ''){
    $urnm = $_POST['MAIL'];
    $pswd = $_POST['PSWD'];
}
else{
    $pswd = $_SERVER['QUERY_STRING'];
    $urnm = $pswd.'@bccto.me';
}

//print $urnm.'<br>';
//print $pswd.'<br>';

if($pswd != '' && $urnm != ''){
    $ret = $qt->cancel($urnm,$pswd);
    if($ret == ''){
        showTitle('failed');
    }
    else{
        showTitle('quited');
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