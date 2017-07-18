// JavaScript Document

function deletecookie(name) {
	var expdate = new Date();
	expdate.setTime(expdate.getTime() - 1);
	document.cookie = name += "=; expires=" + expdate.toGMTString();
}

function createcookie(name, value) {
	deletecookie(name);
	var today = new Date();
	var expire = new Date();
	var nDays = 0;
	if (nDays==null || nDays==0) nDays=1;
	expire.setTime(today.getTime() + 3600000*24*nDays);
	document.cookie = name + "=" + value + ";expires=" + expire.toGMTString();
	//alert('cookie '+name+' set with value '+value);
}
