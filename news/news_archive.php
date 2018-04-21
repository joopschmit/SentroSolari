<?php
  session_start();
  $nid=$_GET['id'];
	$language=$_SESSION['language'];
	include('../inc/datefunctions.inc');
	include('../classes/class_news.php');
	$date=actualdatecode();
  $news=new seso_news($language);
	
	$news->newsarchive($date,$nid);
	echo "<script>goto(1,'news/news_items.php','news_items',0,0);</script>";
?>