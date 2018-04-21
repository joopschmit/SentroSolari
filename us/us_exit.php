<?php
  session_start();
	$language=$_SESSION['language'];
	$uid=$_SESSION['user']['uid'];
  $_SESSION=array();
  session_regenerate_id(); 
  include('../classes/class_visitors.php');
  $vs=new seso_visitors($language);
  $vs->visitorexit(session_id());
	echo -1;
?>