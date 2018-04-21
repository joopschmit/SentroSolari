<?php
  session_start();
  $language=$_SESSION['language'];
	
  include("../inc/show.inc");
	include('../inc/show_input.inc');
	include('../inc/datefunctions.inc');
  include('../classes/class_labels.php');
	include('../classes/class_news.php');
	
  $news=new seso_news($language);
  $labels = new seso_labels("news_add",$language,1);
	
	echo "<script>
	function save_news(field)
	{ f=field.name;
	  v=field.value;
		$.post('news/news_save.php',{id:-1,f:f,v:v},
			function() 
			{ goto(1,'news/news_items.php','news_items',0,0);}
		);
	}
  </script>";
	
	$action="onchange='save_news(this);'";

	echo "<div class='container'>";
  echo "<div class='mainmenutile'>";
	
	sh_grouptitle($labels->getlabel('addnewsitem')." ".datetext(actualdatecode())); 
	
	shi_inputfield($labels->getlabel('newsitem'),'nitem','',254,$action); 

  echo "<br></div></div>";
?> 