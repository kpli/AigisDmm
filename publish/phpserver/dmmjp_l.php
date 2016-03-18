<?php
require_once('webreq.php');
class Dmmjp_Login
{
    protected $net,$mailuser,$mailaddr;
    function __construct() {
        $this->net = new Webreq('http://www.dmm.co.jp');
    }

    function login($mail,$pswd){
        //print '_login'.'<br>';

        $gameRet = $this->net->get('https://www.dmm.co.jp/my/-/login/');
        $path = $this->parsePath($gameRet);
        if($path==''){
            //print '$path is empty'.'<br>';
        }

        $xtHead = $this->parseDMMToken($gameRet);
        if($xtHead==''){
            //print '$xtHead is empty'.'<br>';
            return '';
        }
        $xtContent = $this->parseToken($gameRet);
        if($xtContent==''){
            //print '$xtContent is empty'.'<br>';
            return '';
        }
        $data = array('token'=> $xtContent,);
        $xhrReturn =$this->net->post_xhr('https://www.dmm.co.jp/my/-/login/ajax-get-token/', $data, $xtHead);
        if($xhrReturn==''){
            //print '$xhrReturn is empty'.'<br>';
            return '';
        }
        $xhr=json_decode($xhrReturn);

        $data = array(  ''.$xhr->login_id => $mail,
                        'client_id '=> '',
                        'display' => '',
                        ''.$xhr->password => $pswd,
                        'login_id' => $mail,
                        'password'=> $pswd,
                        'path' => $path,
                        'prompt' => '',
                        'save_login_id' => '0',
                        'save_password' => '0',
                        'token' => ''.$xhr->token,
                        'use_auto_login' => '0' );

        $loginPostRet = $this->net->post('https://www.dmm.co.jp/my/-/login/auth/', $data);
        if($loginPostRet==''){
            //print '$loginRet is empty'.'<br>';
            return '';
        }

        $gameUrl = $this->play();
        if($gameUrl==''){
            //print '$gameUrl is empty'.'<br>';
            return '';
        }
        return $gameUrl;
    }

    function play(){
        //print 'play'.'<br>';
        $page = $this->net->get('http://www.dmm.co.jp/netgame/social/application/-/detail/=/app_id=156462/notification=1/myapp=1/act=install');
        if($page==''){
            //print '$page is empty'.'<br>';
            return '';
        }
        $game = $this->parseGame($page);
        if($game==''){
            //print '$game is empty'.'<br>';
            return '';
        }
        return $game;
    }

    /////////////////////////////////////////////////////////////////

    function parsePath($content){
        preg_match('/name="path" value=".*"/', $content, $matches);
        if( count($matches) == 0){
            return '';
        }
        $valid = $matches[0];

        preg_match('/value=".*"/', $valid, $matches);
        if( count($matches) == 0){
            return '';
        }
        $valid = $matches[0];

        return $this->parseTrim($valid);
    }

    function parseDMMToken($content) {

        preg_match( '/"DMM_TOKEN", ".*"/', $content, $matches);
        if( count($matches) == 0){
            return '';
        }
        $valid = $matches[0];

        preg_match('/ ".*"/', $valid, $matches);
        if( count($matches) == 0){
            return '';
        }
        $valid = $matches[0];

        return $this->parseTrim($valid);
    }

    function parseToken($content) {

        preg_match( '/"token": ".*"/', $content, $matches);
        if( count($matches) == 0){
            return '';
        }
        $valid = $matches[0];

        preg_match('/ ".*"/', $valid, $matches);
        if( count($matches) == 0){
            return '';
        }
        $valid = $matches[0];

        return $this->parseTrim($valid);
    }

    function parseGame($content) {
        preg_match('/"http:\/\/osapi.dmm.com\/gadgets\/ifr.*"/', $content, $matches);
        if( count($matches) == 0){
            return '';
        }
        $valid = $matches[0];

        return $this->parseTrim($valid);
    }

    function parseTrim($content){
        preg_match('/".*"/', $content, $matches);
        if( count($matches) == 0){
            return '';
        }
        $valid = $matches[0];
        $valid = trim($valid,"\"");
        return $valid;
    }
}

?>