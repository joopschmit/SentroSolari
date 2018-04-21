<?php
	session_start();	
	$nid=$_GET['id'];
	$language=$_SESSION['language'];
	include('../inc/show.inc');
	include('../inc/datefunctions.inc');
	include('../classes/class_labels.php');
	include('../classes/class_news.php');

	$labels = new seso_labels("news_item",$language);
	$news=new seso_news($language);
  
	$item=$news->getnewsitem($nid);

	echo "<div class='container'>";
  echo "<div class='mainmenutile'>";
	sh_title($labels->getlabel('newsitem').": ".$item[$language]['nitem']); 
	
	sh_showfield(1,$labels->getlabel('header'),$item[$language]['nitem']);
	echo "<br>";
	sh_showfield(1,$labels->getlabel('date'),datetext($item[$language]['ndate']));
	echo "<br>";
	sh_showfield(1,$labels->getlabel('text'),$item[$language]['ntext']);
	echo "<br>";
  if ($item[0]['nimage']!="" && file_exists("../news/img/".$item[0]['nimage']))
	{ $img="news/img/".$item[0]['nimage'];
    sh_showimage($labels->getlabel('image'),$img,$item[$language]['nimagewidth']);
    $imgsize=getimagesize("../".$img);
    echo "<div class='labels'>".$labels->getlabel('imgsize')."</div>";
	  echo "<div class='data'>".$imgsize[0]." x ".$imgsize[1]." (".$labels->getlabel('showwidth')." ".$item[$language]['nimagewidth'].")</div>";
	}
	echo "<br>";
	sh_showfield(1,$labels->getlabel('imagetext'),$item[$language]['nsubtext']);
	
	echo "<br></div></div>";

?>