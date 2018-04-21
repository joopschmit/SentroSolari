<?php
  session_start();
  $nid=$_GET['id'];
	$language=$_SESSION['language'];
	include('../classes/class_news.php');
  $news=new seso_news($language);
  $news->newsunarchive($nid);
	echo "<script>goto(1,'news/news_archived.php','news_archived',0,0);</script>";
?>