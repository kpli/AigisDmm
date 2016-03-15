<?php

require_once('logic.php');

function regist_dmmjp() {

    print 'regist_dmmjp.......................................'.'<br>';
    $lg = new Logic();
    $lg->autoRun();

    $final_mail = 'empty';
    $gameURL = $lg->getGame();
    if ($gameURL != '')
        $final_mail = $lg->getMail();

    return array($final_mail,$gameURL);
}

?>