<?php

$sp = $_SERVER["QUERY_STRING"];
if ($sp == 'regist_aigis_dmm'){
    require_once('regist.php');
    $ret = regist_dmmjp();
    setcookie('aigis_title',$ret[0]);
    setcookie('aigis_frame',$ret[1]);
	if($ret[0] != 'empty' && $ret[0] != ''){
		require_once('dbop.php');
		$dbop = new DBOP();
		$pswd = strstr($ret[0],"@",true);
		$rest = $dbop->addnew($ret[0],$pswd);
	}
}
else if($sp == 'second_aigis_dmm'){
	require_once('dbop.php');
	$dbop = new DBOP();
	$ret = $dbop->getForSecond();
	if($ret[0] == '' || $ret[1] == ''){
		setcookie('aigis_title','empty');
		setcookie('aigis_frame','');
	}
	else{
		require_once('logic.php');
		$lg = new Logic();
		$retlogin = $lg->login($ret[0],$ret[1]);
		setcookie('aigis_title',$retlogin[0]);
		setcookie('aigis_frame',$retlogin[1]);
	}
}
else{
    setcookie('aigis_title','empty');
    setcookie('aigis_frame','');
}

echo "<script language='javascript' type='text/javascript'>";
echo "window.location.href='/dmm/play.php'";
echo "</script>";

?>