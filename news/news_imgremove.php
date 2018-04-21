<?php
  session_start();
  $nid=$_POST['id'];
	$language=$_SESSION['language'];
	include('../classes/class_news.php');
  $news=new seso_news($language);
	$news->saveimg($nid,'');
?>