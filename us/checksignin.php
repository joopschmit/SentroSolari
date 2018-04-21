<?php
  session_start();
  $fase=$_POST['fase'];
  $ansr=0;
	$language=$_SESSION['language'];
	$uid=0;
	include('../classes/class_visitors.php');
	include('../classes/class_users.php');
  
	$vs=new seso_visitors();
  $users=new seso_users($language);
		
  if ($fase==0)
  { $_SESSION['signin']['nm']="";
    if ($users->check_nm($_POST['nm'])==1) { $ansr=1; $_SESSION['signin']['nm']=$_POST['nm']; } 
  }
  if ($fase==1)
  { $uid=$users->check_pw($_SESSION['signin']['nm'],md5($_POST['pw']));
	  if ($uid>0)
		{ $user=$users->getuser($uid,'uid,organisation,usergroup,user,prename,fullname,authorized,usergroup');	
			$_SESSION['user']=$user;
			$ansr=$uid;
		}
  }
  echo $ansr;	
?>