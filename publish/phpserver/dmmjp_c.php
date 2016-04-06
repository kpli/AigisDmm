<?php
require_once('webreq.php');
class Dmmjp_Cancel
{
    protected $net,$mailuser,$mailaddr;
    function __construct() {
        $this->net = new Webreq('http://www.dmm.co.jp');
    }

    function cancel($mail,$pswd){
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


        require_once('resetpwd.php');
        $pwdset = new Reset_Pwd();
        if($pwdset->needReset($loginPostRet,$mail)){
            $ret = $this->net->get('https://www.dmm.co.jp/my/-/passwordreminder/');
            $postData = array('email'=>$mail,);
            $ret = $this->net->post('https://www.dmm.co.jp/my/-/passwordreminder/sendmail/',$postData);
            $newPwd = $pwdset->reset();
            if($newPwd == ''){
                return $newPwd;
            }
            $this->net = new Webreq('http://www.dmm.co.jp');
            return $this->cancel($mail,$newPwd);
        }

        # 进入设置页面
        $gameRet = $this->net->get('http://www.dmm.co.jp/my/-/top/');
        if ($gameRet == ''){
            return '';
        }

        $postData = array('mytop'=>'true',);
        $gameRet = $this->net->post_xhr('https://www.dmm.co.jp/digital/-/mypage/ajax-index/',$postData,'');
        if ($gameRet == ''){
            return '';
        }

        $gameRet = $this->net->get('https://www.dmm.co.jp/my/-/inactivate/payment/');
        if ($gameRet == ''){
            return '';
        }

        $gameRet = $this->net->get('https://www.dmm.co.jp/digital/-/inactivate/ajax-index/');
        if ($gameRet == ''){
            return '';
        }

        $gameRet = $this->net->get('https://www.dmm.co.jp/my/-/inactivate/r18com/');
        if ($gameRet == ''){
            return '';
        }

        $gameRet = $this->net->get('https://www.dmm.co.jp/my/-/inactivate/reason/');
        if ($gameRet == ''){
            return '';
        }

        $tokenvalue = $this->parseTokenValue($gameRet);
        //print $tokenvalue;
        if ($tokenvalue == ''){
            //print '$tokenvalue is empty'.'<br>';
            return '';
        }
        $postData = array('token'=>$tokenvalue,'reason'=>'');
        $gameRet = $this->net->post('https://www.dmm.co.jp/my/-/inactivate/complete/', $postData);
        if ($gameRet == ''){
            return '';
        }

        return $gameRet;
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

    function parseTokenValue($content){
        preg_match( '/input type="hidden" name="token" value=".*" id=/', $content, $matches);
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
