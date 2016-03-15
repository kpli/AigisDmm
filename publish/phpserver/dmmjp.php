<?php
require_once('webreq.php');
class Dmmjp
{
    protected $net,$mailuser,$mailaddr;
    function __construct() {
        $this->net = new Webreq('http://www.dmm.co.jp');
        $this->mailuser = '';
    }

    function retist($mail, $user){
        print 'retist'.'<br>';
        $this->mailuser = $user;
        $this->net->get('https://www.dmm.co.jp/my/-/register/');
        $data = array('back_url'=>'',
                        'client_id'=>'',
                        'display'=>'',
                        'email'=> $mail,
                        'opt_mail_cd'=>'adult',
                        'password'=> $user,
                        'ref'=>'',
                        'submit'=>'認証メールを送信',
                        'token'=>'');
        $this->net->post('https://www.dmm.co.jp/my/-/register/apply/', $data);
    }

    function valid($valurl){
        print 'valid mail'.'<br>';
        $ret = $this->net->get($valurl);
        $jump = $this->parseJump($ret);
        if ($jump == ''){
            return '';
        }
        $this->net->get($jump);
        #$this->net->get('http://www.dmm.co.jp/top/');
        #$this->net->get('http://www.dmm.co.jp/netgame_s/aigis/');
        $game = $this->net->get('http://www.dmm.co.jp/netgame/social/application/-/detail/=/app_id=156462/notification=1/myapp=1/act=install/');
        return $game;
    }

    function confirm($page){
        sleep(1);
        print 'comfirm age ...'.'<br>';
        $back = $this->parseBack($page);
        if ($back == ''){
            return '';
        }
        $data = array('nickname'=> $this->mailuser,
                        'gender'=>'male',
                        'year'=>'1997',
                        'month'=>'01',
                        'day'=>'01',
                        'confirm'=>'入力内容を確認する',
                        'paytype'=>'free',
                        'opt_mail_cd'=>'netgame',
                        'ch'=>'',
                        'back_url'=>$back,
                        'redirect_url'=>'',
                        'invite'=>'');
        $ret = $this->net->post('http://www.dmm.co.jp/netgame/profile/-/regist/confirm/',$data);
        return $ret;
    }

    function commit($page){
        sleep(1);
        print 'commit age ...'.'<br>';
        $back = $this->parseBack($page);
        if ($back == ''){
            return '';
        }
        $token = $this->parseToken($page);
        if ($token == ''){
            return '';
        }
        $data = array('act'=>'commit',
                        'nickname'=>$this->mailuser,
                        'gender'=>'male',
                        'year'=>'1997',
                        'month'=>'01',
                        'day'=>'01',
                        'back_url'=>$back,
                        'redirect_url'=>'http://www.dmm.co.jp/netgame/social/application/-/detail/=/app_id=156462/notification=1/myapp=1/act=install',
                        'opt_mail_cd'=>'netgame',
                        'invite'=>'',
                        'game_type'=>'',
                        'encode_hint'=>'◇',
                        'token'=>$token);
        $ret = $this->net->post('http://www.dmm.co.jp/netgame/profile/-/regist/commit/',$data);
        return $ret;
    }

    function play(){
        $page = $this->net->get('http://www.dmm.co.jp/netgame/social/application/-/detail/=/app_id=156462/notification=1/myapp=1/act=install');
        $game = $this->parseGame($page);
        return $game;
    }

    /////////////////////////////////////////////////////////////////
    function parseJump($content){
        preg_match('/a href=.*direct_login=1\/"/', $content, $matches);
        if( count($matches) == 0){
            return '';
        }
        $valid = $matches[0];

        return $this->parseTrim($valid);

    }
    function parseBack($content) {
        preg_match('/type="hidden" name="back_url" value=.*"/', $content, $matches);
        if( count($matches) == 0){
            return '';
        }
        $valid = $matches[0];

        preg_match('/value=.*"/', $valid, $matches);
        if( count($matches) == 0){
            return '';
        }
        $valid = $matches[0];

        return $this->parseTrim($valid);
    }
    function parseToken($content) {
        preg_match('/type="hidden" name="token" value=.* id/', $content, $matches);
        if( count($matches) == 0){
            return '';
        }
        $valid = $matches[0];

        preg_match('/value=.*"/', $valid, $matches);
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