<?php

$sp = $_SERVER["QUERY_STRING"];
if ($sp == 'regist_aigis_dmm'){
    require_once('regist.php');
    $ret = regist_dmmjp();
    setcookie('aigis_title',$ret[0]);
    setcookie('aigis_frame',$ret[1]);
}
else{
    setcookie('aigis_title','empty');
    setcookie('aigis_frame','');
}

echo "<script language='javascript' type='text/javascript'>";
echo "window.location.href='/dmm/play.php'";
echo "</script>";

?>