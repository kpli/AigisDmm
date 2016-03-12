/**
 * Created by John on 2015/8/7.
 */


function loginAuto() {
    chrome.storage.local.get("nutakuMailString", function(valueArray) {

        var mailAll = valueArray["nutakuMailString"];
        var mailUser = mailAll.substr(0,8);

        document.getElementById("login_id").value=mailAll;
        document.getElementById("password").value=mailUser;

		var spanFind= document.getElementsByClassName("btn-login btn");
		var theForm= spanFind[0];
		var submitBtn = theForm.childNodes[0];
		var ev = document.createEvent('HTMLEvents');
		ev.initEvent('click', true, true);
		submitBtn.dispatchEvent(ev);
    });
}

function main() {
    var sDomain = window.document.domain;
	
    if (sDomain ==  "www.dmm.co.jp")
    {
		setTimeout("loginAuto()",1000);
    }
}

main();
