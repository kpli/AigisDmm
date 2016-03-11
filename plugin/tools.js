

function t_close() {
    setTimeout("window.close();", 1000);
}

function t_submit( formname) {
    var theForm= document.getElementById(formname);
    if(theForm==null)
        return;
    theForm.submit();
}

function t_clickTag(eletype, eletext) {
    var allspan = document.getElementsByTagName(eletype);
    if(allspan == null)
        return;
    for (var i =0; i< allspan.length; i++) {
        if(allspan[i].innerText == eletext) {
            var ev = document.createEvent('HTMLEvents');
            ev.initEvent('click', true, true);
            allspan[i].dispatchEvent(ev);
            break;
        }
    }
}

function t_clickId(eleid) {
    var btnFind = window.document.getElementById(eleid);
    if(btnFind == null)
        return;
    var ev = document.createEvent('HTMLEvents');
    ev.initEvent('click', true, true);
    btnFind.dispatchEvent(ev);
}

function t_clickClass(classname,iseq) {
    var btnFind= document.getElementsByClassName(classname);
    if(btnFind == null)
        return;
    var ev = document.createEvent('HTMLEvents');
    ev.initEvent('click', true, true);
    btnFind[iseq].dispatchEvent(ev);
}

function t_clickName(elename,iseq) {
    var btnFind = document.getElementsByName(elename);
    if(btnFind == null)
        return;
    var ev = document.createEvent('HTMLEvents');
    ev.initEvent('click', true, true);
    btnFind[iseq].dispatchEvent(ev);
}

function t_valid(eleid)
{
    var btnFind = window.document.getElementById(eleid);
    if(btnFind == null)
        return false;
    return true;
}

function t_Signup() {
    window.open("https://www.dmm.co.jp/my/-/register/");
}

function t_OpenGame() {
    window.open("http://www.dmm.co.jp/netgame_s/aigis/");
}