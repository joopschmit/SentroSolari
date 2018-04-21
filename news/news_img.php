<?php
	session_start();	
	$nid=$_GET['id'];
	$language=$_SESSION['language'];
	include('../inc/show.inc');
	include('../classes/class_news.php');
	include('../classes/class_labels.php');

	$labels = new seso_labels("news_item",$language);

	$news=new seso_news($language);
	$item=$news->getnewsimage($nid);

  if (file_exists("../news/img/".$item['nimage']))
	{ $img="news/img/".$item['nimage'];
    sh_showimage($labels->getlabel('image'),$img,$item['nimagewidth']);
    $imgsize=getimagesize("../".$img);
    echo "<div class='data'>".$labels->getlabel('imgsize').": ".$imgsize[0]." x ".$imgsize[1]."</div>";
	}
?>