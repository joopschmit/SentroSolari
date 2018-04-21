<?php
	session_start();	
	$nid=$_GET['id'];
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
	if ($nid==0) { $nid=$news->getlastitem();}

	$items=$news->getnewsitems(0,2);
	print_r($items);
	$item=$news->getnewsitem($nid);

	echo "<div class='container'>";
	echo "<div class='mainmenutile' style='height:100%; background-color:white;'>";

	echo "<table><tr>";
	echo "<td style='width:36px;'><a class='submenu' href='#' onclick='shift(-1);'><img src='img/nav_back.png' style='width:36px;'></td>";
	echo "<td><div class='newsheader' style='text-align:center;'>".$item[$language]['nitem']." - ".datetext($item[$language]['ndate'])."</div></td>"; 
	echo "<td style='width:36px;'><a class='submenu' href='#' onclick='shift(1);'><img src='img/nav_next.png' style='width:36px;'></td>";
  echo "</tr></table>";
 	echo "<div class='newspub' style='padding-top:15px;'>";
  if ($item[0]['nimage']!="" && file_exists("../news/img/".$item[0]['nimage']))
	{ $img="news/img/".$item[0]['nimage'];
    echo "<img class='newsimage' src='".$img."' align='right' hspace='10' title='".$item[$language]['nsubtext']."'>";
	}
	echo $item[$language]['ntext']."</div>";
	echo "<br></div></div>";  


/*
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
*/	
?>