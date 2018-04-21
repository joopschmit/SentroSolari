<?php
  session_start();
  $uid=$_POST['uid'];
  $fieldname=$_POST['f'];
  $value=$_POST['v'];
	$language=$_SESSION['language'];
	include('../classes/class_users.php');
  $users=new seso_users($language);
	$test=0;
  $values=array();
	
	if ($fieldname=='newpassword')
	{ $values+=array('password'=>$value);
    $values+=array('password_md5'=>md5($value));
		$values+=array('authorized'=>0);
	}
  else	
	{ $values+=array($fieldname=>$value);
  }
  $users->saveuser($uid,$values);
?>