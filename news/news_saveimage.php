<?php
  session_start();
  $nid=$_GET['id'];
  $field=$_GET['f'];
	$value=$_GET['v'];
	$language=$_SESSION['language'];
	include('../classes/class_news.php');

  $news=new seso_news($language);
  $news->saveimage($nid,$field,$value);
  
	$img=$news->getnewsimage($nid);
	
  $imgsize=getimagesize("../news/img/".$img['nimage']);
  echo "<img src='news/img/".$img['nimage']."' style='text-align:left; width:".$img['nimagewidth']."px;'>";
  echo "<div class='data'>size: ".$imgsize[0]." x ".$imgsize[1]."</div>";
	
?>	