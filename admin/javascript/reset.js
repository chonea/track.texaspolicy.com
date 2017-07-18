// JavaScript Document
function ResetForm(which){
var pass=true
var first=-1
if (document.images){
for (i=0;i<which.length;i++){
var tempobj=which.elements[i]
 if (tempobj.type=="text"){
  eval(tempobj.value="")
  if (first==-1) {first=i}
 }
 else if (tempobj.type=="checkbox") {
  eval(tempobj.checked=0)
  if (first==-1) {first=i}
 }
 else if (tempobj.col!="") {
  eval(tempobj.value="")
  if (first==-1) {first=i}
 }
}
}
which.elements[first].focus()
return false
}