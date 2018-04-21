<?php
	session_start();
	$visitorsgroup=$_GET['id'];
	$language=$_SESSION['language'];
	include('../inc/show.inc');
	include('../inc/datefunctions.inc');
	include('../classes/class_visitors.php');
	include('../classes/class_users.php');
	include('../classes/class_labels.php');

	echo "<script>
	  function gotovisitor(vid)
		{ goto(1,'vs/vs_visitor_edit.php','vs_visitor_edit',vid,0);
		}
	</script>";

  $vs=new seso_visitors();
  $users=new seso_users($language);
	$labels = new seso_labels("vs_visitors",$language);
	$vlist=$vs->getvisitorlist($visitorsgroup);
  $authorisaties=$users->members;
			
	echo "<div class='container'>";
	echo "<div class='datablock'>";
	if ($visitorsgroup==1) { $title=$labels->getlabel('knownvisitors');} else { $title=$labels->getlabel('publicvisitors');}
	sh_grouptitle($title);
	
	echo "<table><tr>";
	if ($visitorsgroup==0)
	{	echo "<th>IP</th><th>".$labels->getlabel('number')."</th><th>".$labels->getlabel('date')."</th>";}
	else
	{ echo "<th>e-mail</th><th>IP</th><th>".$labels->getlabel('date')."</th><th>".$labels->getlabel('authorized')."</th>";}
	echo "</tr>";
	foreach($vlist as $vid=>$row)
	{ echo "<tr>";
		if ($visitorsgroup==0)
		{ echo "<td><a href='#' onclick='gotovisitor(".$vid.");'>".$row['ip']."</a></td>";
		  echo "<td>".$row['number']."</td>";
		  echo "<td>".datetext($row['vdate'])."</td>";
		  echo "</tr>";
		}	
		else
		{ echo "<td><a href='#' onclick='gotovisitor(".$vid.");'>".$row['email']."</a></td>";
		  echo "<td>".$row['ip']."</td>";
		  echo "<td>".datetext($row['vdate'])."</td>";
		  echo "<td>".$authorisaties[$row['authorized']]."</td>";
		  echo "</tr>";
		}	
	}
  echo "</table>";	
	echo "</div><br></div>"; 
?>