<?php

require_once('idd.php');
require_once('logic.php');

$str_query = $_SERVER["QUERY_STRING"];
$arr_query = convertUrlQuery($str_query);
function convertUrlQuery($string){
    $queryParts = explode('&', $string);
    $params = array();
    foreach ($queryParts as $param)
    {
        $item = explode('=', $param);
        $params[$item[0]] = $item[1];
    }
    return $params;
}
$p_cmd = $arr_query['cmd'];
$p_sid = $arr_query['sid'];
$p_pwd = $arr_query['pwd'];
$p_key = $arr_query['key'];
$p_val = $arr_query['val'];

//if ($p_cmd != 'play'){
//    print 'cmd => '.$p_cmd.'<br>';
//    print 'sid => '.$p_sid.'<br>';
//    print 'key => '.$p_key.'<br>';
//    print 'val => '.$p_val.'<br>';
//}

$db = new IdoDB();
if ($p_cmd == 'play'){
    $ret = array('empty','err.html');
    $lg = new Logic();
    if ( $p_key == 'regist') {
        $ret = $lg->autoRun();
    }
    else if ($p_key == 'second') {
        $ret = $lg->playSecond();
    }
    else if ($p_key == 'signup') {
        $ret = $lg->playSignup();
    }
    else if ($p_key == 'login') {
        $ret= $lg->login($p_sid,$p_pwd);
    }
    else if ($p_key == 'login_only') {
        $ret= $lg->login_only($p_sid,$p_pwd);
    }
    else if ($p_key == 'cancel') {
        $ret = $lg->cancel($p_sid,$p_pwd,($p_val == 'auto'));
    }
    setcookie('aigis_title',$ret[0]);
    setcookie('aigis_frame',$ret[1]);
    //print $ret[0].'<br>';
    //print $ret[1].'<br>';
    echo "<script language='javascript' type='text/javascript'>";
    echo "window.location.href='play.php'";
    echo "</script>";
}
else if ($p_cmd == 'query') {
    $ret = $db->search($p_key,$p_val);
    output_acc_table($ret);
}
else if ($p_cmd == 'update') {
    if( $p_key == 'signdate' || $p_key == 'random2'){
        $db->unlock($p_sid);
    }
    if ( $p_key == 'signdate') {
        $db->refresh_signup_date($p_sid);
    }
    else if( $p_key == 'passwd' ||  $p_key == 'random1'|| $p_key == 'random2' ||  $p_key == 'locked' || $p_key == 'info' ){
        print 'update -> '.$p_key.' | '.$p_val.' <br>';
        $db->update($p_sid,$p_key,$p_val);
    }
    else{
        print 'p_key is error <br>';
    }
    showTitle('done');
}
else if ($p_cmd == 'quick') {
    $ret = array();
    if ( $p_key == '0black') {
        $ret = $db->search_0_black();
    }
    else if ($p_key == '1black') {
        $ret = $db->search_1_black();
    }
    else if ($p_key == '2black') {
        $ret = $db->search_2_black();
    }
    else if ($p_key == '1black_only') {
        $ret = $db->search_1_black_only();
    }
    else if ($p_key == 'timeout') {
        $ret = $db->search_timeout();
    }
    output_acc_table($ret);
}
else if ($p_cmd == 'addnew') {
    $db->add_history($p_sid,$p_pwd,$p_val);
}
else if ($p_cmd == 'delete') {
    $db->del($p_sid);
}
else if ($p_cmd == 'unlockall') {
        $db->unlockall();
}
else {
    showTitle('done');
}

function showTitle($ts){
    $dom = new DOMDocument('1.0');
    $title = $dom->createElement('title',$ts );
    $dom->appendChild($title);
    echo $dom->saveHTML();
}
function output_acc_table($arrret){
    echo '<script type="text/javascript">function login(x,y) {window.location.href = "ido.php?cmd=play&key=login&sid=" + x + "&pwd=" + y; }</script>';
	echo '<style>table{border-collapse:collapse;} table td{border:1px solid;}</style>';
    echo '<table>';
    echo '<tr> <th>seq</th>  <th>account</th>  <th>passwd</th>  <th>createtime</th>  <th>random1</th>  <th>random2</th>  <th>locked</th>  <th>info</th> <th>signdate</th> </tr>';
    foreach($arrret as $key=>$value){
	    echo '<tr align="center">';
        echo '<td><input type="button" value="'.($key+1).'" onclick="login(\''.$value[0].'\',\''.$value[1].'\')" /></td>';
        foreach($value as $param){
            echo '<td>'.$param."</td>";
        }
	    echo '</tr>';
    }
    echo '</table>';
    echo '<script type="text/javascript">sc();function sc() {var trs = document.getElementsByTagName("tr");for (var i = 0; i < trs.length; i+=2) {trs[i].style.background = "LightYellow";} }</script>';
}
?>