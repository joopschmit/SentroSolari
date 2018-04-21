<?php
	session_start();
	$usergroup=$_GET['id'];
	$language=$_SESSION['language'];
	include('../inc/show.inc');
	include('../classes/class_users.php');
	include('../classes/class_labels.php');

	echo "<script>
	  group=".$usergroup.";
		function gotouser(uid)
		{ goto(1,'us/us_user_edit.php','us_user_edit',uid+'&usergroup='+group,0);
		}
	</script>";

  $users=new seso_users($language);
	$labels = new seso_labels("us_users",$language);
	$groupname=$users->groups[$usergroup];
	$ulist=$users->getuserlist($usergroup);
	
	echo "<div class='container'>";
	echo "<div class='datablock'>";
	
	sh_grouptitle($groupname);
	
	echo "<table>";
	echo "<tr><th>".$labels->getlabel('organisation')."/".$labels->getlabel('name')."</th>";
	echo "<th>".$labels->getlabel('usergroup')."</th></tr>";
	$org="";
	foreach($ulist as $uid=>$row)
	{ if ($org!=$row['organisation'])
	  { echo "<tr><td colspan=2>";
	    sh_subgrouptitle($row['organisation']);
	    echo "</td></tr>";
			$org=$row['organisation'];
		}	
		echo "<tr>";
		echo "<td><a href='#' onclick='gotouser(".$uid.");'>".$row['fullname']."</a></td>";
		echo "<td>".$users->members[$row['usergroup']]."</td>";
		echo "</tr>";
	}
  echo "</table>";	
	echo "</div><br></div>";
?>