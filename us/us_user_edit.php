<?php
	session_start();
	$usergroup=$_GET['usergroup'];
	$uid=$_GET['id'];
	$language=$_SESSION['language'];
	include('../inc/show.inc');
	include('../inc/show_input.inc');
	include('../classes/class_users.php');
	include('../classes/class_labels.php');
  include('../inc/datefunctions.inc');

	echo "<script>
	function save_user(uid,field)
	{ f=field.name;
	  v=field.value;
		$.post('us/us_user_save.php',{uid:uid,f:f,v:v});
	}
	</script>";
	
	$users=new seso_users($language);
	$labels = new seso_labels("us_user_edit",$language);
	$groupname=$users->groups[$usergroup];
	$action="onchange='save_user(".$uid.",this);'";
  $now=actualdatecode();
	
  if ($uid==-1)
  { $uid=$users->adduser($usergroup,$now);}		

	echo "<div class='container'>";
	if ($uid>0)
	{	$user=$users->getuser($uid,"*"); 

  	sh_grouptitle($groupname.": ".$user['fullname']);

	  echo "<div class='datablock'>";
	  
		if ($usergroup>2)
		{	$options=$users->members;
		  $opt=array();
		  for ($t1=0; $t1<=$usergroup; $t1++) { $opt[$t1]=$options[$t1];}
		  shi_options_id($labels->getlabel('usergroup'),'usergroup',$user['usergroup'],$opt,$action);
		}
		shi_inputfield($labels->getlabel('organisation'),'organisation',$user['organisation'],120,$action);
		shi_inputfield($labels->getlabel('user'),'user',$user['user'],120,$action);
	  shi_inputfield($labels->getlabel('newpassword'),'newpassword',"",80,$action);
	  shi_inputfield($labels->getlabel('prename'),'prename',$user['prename'],40,$action);
	  shi_inputfield($labels->getlabel('fullname'),'fullname',$user['fullname'],120,$action);
	  shi_inputfield($labels->getlabel('phone'),'phone',$user['phone'],24,$action);
		
		echo "</div>";
	} 
  else
	{ echo "<div".$labels->getlabel('nouserselected')."</div>";}		

  echo "<br></div>";
?>