window.name='work';
window.addEventListener('load', function(){setTimeout(scrollTo, 0, 0, 1);}, false);
var lastparent=-1;
var lastid=-1;

function ucfirst(text) 
{ var ts=text.toString();
  var ch0=ts.substring(0,1);
  var ch1=ch0.toUpperCase();
	var ch2=ts.substring(1);
	tx=ch1+ch2;
	return tx;
}
function set_language(lang)
{ top.location='home.php?lang='+lang;
}	
function signin(fase,key,no)
{ var nm;
	var pw5;
	if (key==13)
	{ if (fase==0)
		{ nm=$('#nm').val();
			$.post('us/checksignin.php',{fase:fase,nm:nm},function(ansr) { $('#mainbasis').load('submenu_login.php?fase='+ansr);}); 
		}
		if (fase==1)
		{ pw=$('#pw').val();
			$.post('us/checksignin.php',{fase:fase,pw:pw},
			  function(ansr) 
				{ if (ansr>0) { goto(1,'submenu.php','submenu',0,0);}
				  else 
					{ alert(no); 
					  top.location='home.php';
					}
	   		});
	  }
  }		
}
function logout()
{ $.get('us/us_exit.php',function(ansr) { if (ansr==-1) { top.location='index.php';}});
}
function goto(menulevel,destination,title,id,check)
{ if (check==0 || confirm(check))
  { if (destination=='home.php') 
		{ top.location=destination;}
		else 
		{ $('#mainbasis').load(destination+'?id='+id,
	      function() 
				{ $('#maincockpit').load('cockpit.php?title='+title+'&id='+id);
 				  $('#maincockpit').animate({height:"55px"},500);  
					$('#mainbasis').height('calc(100% - 125px)');
		    }
			)	
		}
	}
} 
function showmessage(msg)
{ $('#signal').html(msg);
 	$('#signal').fadeIn("slow");
	$('#signal').fadeOut(1500);
}

function gotopage(parent)
{ if (parent==lastparent) 
  { showmessage('refresh');}
  lastparent=parent;
	if (parent>0)
	{ goto(1,'apps/app_page.php','app_page',parent,0);}
  else
  { top.location='home.php';}		
 // $('#signal').html('klaar');
}
function gototile(id)
{ if (id==lastid) 
  { showmessage('refresh');}
  lastid=id;
  goto(1,'cms/cms_tile_sheet.php','cms_tile_sheet',id,0);
}
function gotonews(id)
{ goto(1,'news/news_sheet.php','news_sheet',id,0);
}
function toonhelp(helpid,language)
{ window.open('help/help.php?helpID='+helpid+'&language='+language,'SeSo-Help','height=400,width=400');
} 
function toonvideo(link,bestemming) 
{ window.open(link,'Sentro Solari Video','height=400,width=400');
}
function checkurl(v)
{ if (v.substring(0,7)!='http://' && v.substring(0,7)!='https://') { v='http://'+v;}
  return v;
}
function tileaction(page,nr,id)
{ if (page=='Page_0')
	{ if (nr==0) { goto(1,'apps/info/app_info.php','app_info',id,0);}
		if (nr==1) { goto(1,'apps/news/app_news.php','app_news',id,0);}
		if (nr==2) { goto(1,'apps/assist/app_assist.php','app_assist',id,0);}
		if (nr==3) { goto(1,'apps/match/app_match.php','app_match',id,0);}
		if (nr==4) { goto(1,'apps/work/app_work.php','app_work',id,0);}
		if (nr==5) { goto(1,'apps/persons/app_persons.php','app_persons',id,0);}
	}
}