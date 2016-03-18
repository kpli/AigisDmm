
<?php

//print $_POST['MAIL'].'<br>';
//print $_POST['PSWD'].'<br>';

require_once('logic.php');
$lg = new Logic();
$ret = $lg->login($_POST['MAIL'],$_POST['PSWD']);
print $ret[0].'<br>';

echo "<script language='javascript' type='text/javascript'>";
echo "window.location.href='".$ret[1]."'";
echo "</script>";

?>