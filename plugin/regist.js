/**
 * Created by John on 2015/8/7.
 */
 

function login(mailstri) {
	chrome.storage.local.set({"nutakuMailString": mailstri}, function() {
		window.location.href=("http://www.dmm.co.jp/netgame/social/application/-/detail/=/app_id=156462/notification=1/myapp=1/act=install/");
	}); 
}

function refresh() {
	window.location.href="http://127.0.0.1:8000/";
}

function getMaillAddr() {
	if(document.body.innerHTML == "empty"){
		refresh();
	}
	else{
		login(document.body.innerHTML);
	}
	return;
}

function main() {
    var sDomain = window.document.domain;
    if (sDomain ==  "127.0.0.1")
    {
		setTimeout("getMaillAddr()",500);
    }
}

main();
