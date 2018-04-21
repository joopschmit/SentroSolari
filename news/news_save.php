<?php
  session_start();
  $nid=$_POST['id'];

  $field=$_POST['f'];
  $value=$_POST['v'];
	$language=$_SESSION['language'];
	include('../classes/class_news.php');

  $news=new seso_news($language);

  if ($nid==-1)
	{ include('../inc/datefunctions.inc');
    $date=actualdatecode();
    $newnid=$news->addnewsitem($value,$date,$_SESSION['user']['usergroup']);
  }
  else
	{ $geg=explode("_",$field);
    $lang=$geg[1];
		$f=$geg[0]; 
    if ($field=='nimagesize')
		{ $news->saveimage($nid,$f,$value);}
	  else
		{ $news->newssave($nid,$f,$value,$lang);}
	}
?>