// Saved in .. <OS>\Profiles\<username>\Application Data\Microsoft\Internet Explorer\UserData\

if(navigator.appName == "Microsoft Internet Explorer") { 
  window.onload = topicOnLoad;
  window.onunload = topicOnUnLoad;
}

//var fileid = "";
var persistlist = new MakeArray(5);
var persiststr  = "acHelp_PersistData";

var fixed = false;
if( fileid == "" ) { var fid = setFileId(); }
else { var fid = fileid; }

function topicOnLoad () {
  fixed = fixMoniker();
  if( fixed == true ) { fnLoadInput(fid); }
}

function topicOnUnLoad () {
  if( fixed == true ) { fnSaveInput(fid); }
}

function fixMoniker() {
  var curURL = document.location + ".";
  var pos = curURL.indexOf("mk:@MSITStore");
//  if( pos != -1 ) {
  if( pos == 0 ) {
    curURL = "ms-its:" + curURL.substring(14,curURL.length-1);
    document.location.replace(curURL);
    return false;
  }
  else { return true; }
}

// setFileId - returns the current path/filename as a unique id
//
function setFileId () {
  var fhref = document.location.href;
  var p1 = fhref.indexOf( "#" );
  if( p1 > 0 ) { var fhref = fhref.substring( 0, p1 ); }
  var p1 = fhref.indexOf( "/" );
  var p2 = fhref.lastIndexOf( "." );
  var fileid = fhref.substring( p1+1, p2 );
  fileid = unescape(fileid);
  return fileid.replace( /[ \/:\.]/g, "_" );
}

function fnSaveInput(fid){
  var oTimeNow = new Date(); // Start Time
  oTimeNow.setMinutes(oTimeNow.getMinutes() + (60*24*90));  // expires in three months
  var sExpirationDate = oTimeNow.toUTCString();
  for( i = 0; i < persistlist.length; i++) {
    eval("var persistid = "+persistlist[i]+";");
    if( persistid ) {
      persistid.expires = sExpirationDate;
      persistid.setAttribute(fid+"_"+i,persistid.value);
      persistid.save(persiststr+i);
    }
  }
}

function fnLoadInput(fid){
  for( i = 0; i < persistlist.length; i++) {
    eval("var persistid = "+persistlist[i]+";");
    if( persistid ) {
      persistid.load(persiststr+i);
      var val = persistid.getAttribute(fid+"_"+i);
      if( val == null ) { val = ""; }
      persistid.value = val;
    }
  }
}

function fnExpireData(persistname,fid,i){
  var oTimeNow = new Date(); // Start Time
  oTimeNow.setMinutes(oTimeNow.getMinutes() + 0);
  var sExpirationDate = oTimeNow.toUTCString();
  for( i = 0; i < persistlist.length; i++) {
    eval("var persistid = "+persistname+";");
    if( persistid ) {
      persistid.expires = sExpirationDate;
      persistid.setAttribute(fid+"_"+i,persistid.value);
      persistid.save(persiststr+i);
    }
  }
}

function MakeArray(n) {
  this.length = n;
  for (var i = 1; i <= n; i++) { 
    this[i] = 0;
  }
  return this;
}

