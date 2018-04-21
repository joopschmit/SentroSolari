<?php
	session_start();	
	$language=$_SESSION['language'];
	include('../inc/show.inc');
	include('../inc/show_input.inc');
	include('../inc/datefunctions.inc');
	include('../classes/class_labels.php');
	include('../classes/class_news.php');

	echo "<script>
	function newsitem(nid)
	{ goto(1,'news/news_item.php','news_item',nid,0);
	}
	</script>";
	
	$labels = new seso_labels("news_items",$language);
	$news=new seso_news($language);
  
	$items=$news->getnewsitems(0,$_SESSION['user']['usergroup']);

  echo "<div class='container' style='padding:5px;'>";
  echo "<div class='mainmenutile'>";
  sh_title($labels->getlabel('newsitems')); 
  echo "<div class='datablock'>";	
	if (count($items)>0)
	{ echo "<table>";
		echo "<tr><th>".$labels->getlabel('date')."</th>";
		echo "<th>".$labels->getlabel('item')."</th>";
		echo "<th>".$labels->getlabel('watched')."</th></tr>";

		foreach($items as $nid=>$item)
		{ echo "<tr><td><a href='#' onclick='newsitem(".$nid.");'>".datetext($item['ndate'])."</a></td>";
			echo "<td>".$item['nitem']."</td>";
			echo "<td>".$item['nwatched']."</td></tr>";
		}
		echo "</table>";
	}
	else
	{ echo "<div>".$labels->getlabel('nonewsitems')."</div>";
  }
  echo "</div><br></div></div>";
?>