<?php
	session_start();	
	$language=$_SESSION['language'];
	include('../inc/show.inc');
	include('../inc/show_input.inc');
	include('../inc/datefunctions.inc');
	include('../classes/class_labels.php');
	include('../classes/class_news.php');

	echo "<script>
	function archivednewsitem(nid)
	{ goto(1,'news/news_archiveditem.php','news_archiveditem',nid,0);
	}
	function recovernewsitem(nid)
	{ goto(1,'news/news_unarchive.php','news_unarchive',nid,0);
	}
	</script>";
	
	$labels = new seso_labels("news_archived",$language);
	$news=new seso_news($language);
  
	$items=$news->getnewsitems(9,$_SESSION['user']['usergroup']);

  echo "<div class='container' style='padding:5px;'>";
  echo "<div class='mainmenutile'>";
  sh_title($labels->getlabel('archivednewsitems')); 
  echo "<div class='datablock'>";	
	if (count($items)>0)
	{ echo "<table>";
		echo "<tr><th>".$labels->getlabel('date')."</th>";
		echo "<th>".$labels->getlabel('item')."</th>";
		echo "<th>".$labels->getlabel('archived')."</th>";
		echo "<th>".$labels->getlabel('action')."</th></tr>";

		foreach($items as $nid=>$item)
		{ echo "<tr><td><a class='removed' href='#' onclick='archivednewsitem(".$nid.");'>".datetext($item['ndate'])."</a></td>";
			echo "<td class='removed'>".$item['nitem']."</td>";
			echo "<td class='removed'>".datetext($item['narchivedon'])."</td>";
			echo "<td><a class='removed' href='#' onclick='recovernewsitem(".$nid.");'>".$labels->getlabel('recover')."</a></td>";
			echo "</tr>";
		}
		echo "</table>";
	}
	else
	{ echo "<div>".$labels->getlabel('noarchiveditems')."</div>";
  }
  echo "</div><br></div></div>";
?>